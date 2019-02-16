/*
 * Source File < x11/bgiutl.c >
 *
 * BGI Utilities Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

#define DecoNothing   0
#define DecoRectFront 1
#define DecoRectBack  2

static void xbgiGetSizeVPrintf( XFontStruct *fs, int *width, int *height,
			       char *fmt, va_list argptr )
{
  int i, maxwidth, c = 0; 
  char str[2048], *ptr;
  
  vsprintf( str, fmt, argptr );
  strcat( str, "\n" );
  ptr = strtok( str, "\n" );
  while ( ptr != NULL ){
    c++;
    ptr = strtok( NULL, "\n" );
  }
  ptr = str;
  *height = TextHeight(fs);
  maxwidth = TextWidth( fs, ptr, strlen(ptr) );
  for ( i=0; i<c; i++ ){
    maxwidth = max( maxwidth, TextWidth( fs,ptr,strlen(ptr) ) );
    ptr = ptr + strlen(ptr);
    while ( ptr++ == NULL );
  }
  *width  = Brim(maxwidth);
  *height = Brim(*height)*c;
}

static void xbgiGetSizePrintf( XFontStruct *fs, int *width, int *height,
			      char *fmt, ... )
{
  va_list argptr;
  
  va_start( argptr, fmt );
  xbgiGetSizeVPrintf( fs, width, height, fmt, argptr );
  va_end( argptr );
}

static void xbgiVPrintf( Display *display, Window win, GC gc, XFontStruct *fs,
			int textjust, char *fmt, va_list argptr )
{
  Window root;
  int x, y, width, height, border, depth;
  int i, c = 0, textx, texty;
  char str[2048], *ptr;
  
  vsprintf( str, fmt, argptr );
  strcat( str, "\n" );
  ptr = strtok( str, "\n" );
  while ( ptr != NULL ){
    c++;
    ptr = strtok( NULL, "\n" );
  }
  XGetGeometry( display, win, &root, &x, &y,
               &width, &height, &border, &depth );
  ptr = str;
  for ( i=0; i<c; i++ ){
    switch( textjust ){
    case LEFT_TEXT: default:
      textx = HemBrim;
      break;
    case CENTER_TEXT:
      textx = ( width - TextWidth(fs,ptr,strlen(ptr)) )/2;
      break;
    case RIGHT_TEXT:
      textx = width - HemBrim - TextWidth(fs,ptr,strlen(ptr));
      break;
    }
    texty = HemBrim + TextAscent(fs) + i*Brim(TextHeight(fs));
    XDrawString( display, win, gc, textx, texty, ptr, strlen(ptr) );
    ptr = ptr + strlen(ptr);
    while ( ptr++ == NULL );
  }
}

static void xbgiPrintf( Display *display, Window win, GC gc, XFontStruct *fs,
		       int textjust, char *fmt, ... )
{
  va_list argptr;

  va_start( argptr, fmt );
  xbgiVPrintf( display, win, gc, fs, textjust, fmt, argptr );
  va_end( argptr );
}

static void xbgiDecorateWindow( Display *display, Window win, GC gc,
			       unsigned long fg,
			       unsigned long lc, unsigned long dc,
			       int type )
{
  XPoint orec[4], irec[4], lrec[4], trec[4], rrec[4], brec[4];
  XWindowAttributes att;

  XGetWindowAttributes( display, win, &att );
  orec[0].x = 0;                     orec[0].y = 0; 
  orec[1].x = 0;                     orec[1].y = att.height; 
  orec[2].x = att.width;             orec[2].y = att.height; 
  orec[3].x = att.width;             orec[3].y = 0; 
  irec[0].x = DecoHemBits;           irec[0].y = DecoHemBits; 
  irec[1].x = DecoHemBits;           irec[1].y = att.height-DecoHemBits; 
  irec[2].x = att.width-DecoHemBits; irec[2].y = att.height-DecoHemBits; 
  irec[3].x = att.width-DecoHemBits; irec[3].y = DecoHemBits; 
  lrec[0] = orec[0]; lrec[1] = orec[1]; lrec[2] = irec[1]; lrec[3] = irec[0];
  trec[0] = orec[0]; trec[1] = orec[3]; trec[2] = irec[3]; trec[3] = irec[0];
  rrec[0] = orec[2]; rrec[1] = orec[3]; rrec[2] = irec[3]; rrec[3] = irec[2];
  brec[0] = orec[1]; brec[1] = orec[2]; brec[2] = irec[2]; brec[3] = irec[1];
  XClearWindow( display, win );
  switch( type ){
  case DecoNothing:
    break;
  case DecoRectFront: 
    XSetForeground( display, gc, lc );
    XFillPolygon( display, win, gc, lrec, 4, Complex, CoordModeOrigin );
    XFillPolygon( display, win, gc, trec, 4, Complex, CoordModeOrigin );
    XSetForeground( display, gc, dc );
    XFillPolygon( display, win, gc, rrec, 4, Complex, CoordModeOrigin );
    XFillPolygon( display, win, gc, brec, 4, Complex, CoordModeOrigin );
    break;
  case DecoRectBack: 
    XSetForeground( display, gc, dc );
    XFillPolygon( display, win, gc, lrec, 4, Complex, CoordModeOrigin );
    XFillPolygon( display, win, gc, trec, 4, Complex, CoordModeOrigin );
    XSetForeground( display, gc, lc );
    XFillPolygon( display, win, gc, rrec, 4, Complex, CoordModeOrigin );
    XFillPolygon( display, win, gc, brec, 4, Complex, CoordModeOrigin );
    break;
  }
  XSetForeground( display, gc, fg );
}

void bgivprintf( char *title, int textjust, char *fmt, va_list argptr )
{
  Window rwin, twin, pwin;
  XSetWindowAttributes att;
  XEvent ev;
  int mwidth, twidth, theight, pwidth, pheight;
  int x, y;
  
  xbgiGetSizePrintf( XBGIFontStruct, &pwidth, &pheight, title );
  xbgiGetSizeVPrintf( XBGIFontStruct, &twidth, &theight, fmt, argptr );
  mwidth = max( twidth, pwidth );
  x = XBGIEvent.xkey.x_root;
  y = XBGIEvent.xkey.y_root;
  x = x - Hem(mwidth)/2;
  y = y - Hem(theight)/2;
  rwin = XCreateSimpleWindow( XBGIDisplay, RootWindow(XBGIDisplay,XBGIScreen),
                             x, y,
                             Hem(Hem(mwidth)), Hem(Hem(pheight)+Hem(theight)),
                             0, XBGIForeground, XBGIBackground );
  XSelectInput( XBGIDisplay, rwin, ExposureMask|ButtonPressMask );
  att.save_under = True;
  XChangeWindowAttributes( XBGIDisplay, rwin, CWSaveUnder, &att );
  twin = XCreateSimpleWindow( XBGIDisplay, rwin, 
                             DecoHemBits, DecoHemBits,
                             Hem(mwidth), Hem(pheight), 0,
                             XBGIForeground, XBGIBackground );
  pwin = XCreateSimpleWindow( XBGIDisplay, rwin, 
                             DecoHemBits, DecoHemBits+Hem(pheight), 
                             Hem(mwidth), Hem(theight),
                             0, XBGIForeground, XBGIBackground );
  XMapWindow( XBGIDisplay, rwin );
  XMapSubwindows( XBGIDisplay, rwin );
  XSetTransientForHint( XBGIDisplay, rwin, XBGIRoot );

  XFlush( XBGIDisplay );
  while (1){
    XNextEvent( XBGIDisplay, &ev );
    switch ( ev.type ){
    case Expose:
      if ( ev.xexpose.count != 0 ) break;
      xbgiDecorateWindow( XBGIDisplay, rwin, XBGIDefaultGC,
                         XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			 DecoRectFront );
      xbgiDecorateWindow( XBGIDisplay, twin, XBGIDefaultGC,
                         XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			 DecoRectFront );
      xbgiPrintf( XBGIDisplay, twin, XBGIDefaultGC, XBGIFontStruct,
		 CENTER_TEXT, "%s", title );
      xbgiDecorateWindow( XBGIDisplay, pwin, XBGIDefaultGC,
                         XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			 DecoNothing );
      xbgiVPrintf( XBGIDisplay, pwin, XBGIDefaultGC, XBGIFontStruct, textjust,
                  fmt, argptr );
      while ( XCheckTypedEvent(XBGIDisplay,Expose,&ev) );
      XFlush( XBGIDisplay );
      break;
    case ButtonPress:
    case KeyPress:
      XUnmapSubwindows( XBGIDisplay, rwin );
      XUnmapWindow( XBGIDisplay, rwin );
      XDestroySubwindows( XBGIDisplay, rwin );
      XDestroyWindow( XBGIDisplay, rwin );
      return;
    }
  }
}
void bgiprintf( char *title, int textjust, char *fmt, ... )
{
  va_list argptr;
  
  va_start( argptr, fmt );
  bgivprintf( title, textjust, fmt, argptr );
  va_end( argptr );
}
void bgigets( char *title, int maxlen, char *str )
{
  char *OK = " ok ", *CANCEL = " cancel ";
  Window rwin, twin, swin, owin, cwin;
  XSetWindowAttributes att;
  Cursor curs;
  XEvent ev, exposeev;
  char *bytes = NULL, c;
  KeySym key;
  int nbytes, width, height, textwidth, textheight, textstartx, textstarty;
  int x, y, owidth, cwidth;
  int flg = !0;

  textwidth  = TextWidth( XBGIFontStruct, "_", 1 )*20;
  textheight = TextHeight( XBGIFontStruct );
  width  = Brim( textwidth  );
  height = Brim( textheight );
  textstartx = HemBrim;
  textstarty = HemBrim + TextAscent(XBGIFontStruct);
  x = XBGIEvent.xbutton.x_root;
  y = XBGIEvent.xbutton.y_root;
  x = x - Hem(width)/2;
  y = y - Hem(height)/2;
  owidth = Brim( TextWidth(XBGIFontStruct,OK,    strlen(OK)    ) );
  cwidth = Brim( TextWidth(XBGIFontStruct,CANCEL,strlen(CANCEL)) );
  rwin = XCreateSimpleWindow( XBGIDisplay, RootWindow( XBGIDisplay, 0 ),
                             x, y, Hem(Hem(width)), Hem(3*Hem(height)), 0,
                             XBGIForeground, XBGIBackground );
  XSelectInput( XBGIDisplay, rwin, KeyPressMask|ButtonPressMask );
  att.save_under = True;
  XChangeWindowAttributes( XBGIDisplay, rwin, CWSaveUnder, &att );
  twin = XCreateSimpleWindow( XBGIDisplay, rwin,
                             DecoHemBits, DecoHemBits,
                             Hem(width), Hem(height), 0,
                             XBGIForeground, XBGIBackground );
  swin = XCreateSimpleWindow( XBGIDisplay, rwin,
                             DecoHemBits, DecoHemBits+Hem(height),
                             Hem(width), Hem(height), 0,
                             XBGIForeground, XBGIBackground );
  owin = XCreateSimpleWindow( XBGIDisplay, rwin,
                             DecoHemBits, DecoHemBits+2*Hem(height),
                             Hem(owidth), Hem(height), 0,
			     XBGIForeground, XBGIBackground );
  cwin = XCreateSimpleWindow( XBGIDisplay, rwin,
                             DecoHemBits+Hem(owidth),
                             DecoHemBits+2*Hem(height),
                             Hem(cwidth), Hem(height), 0,
			     XBGIForeground, XBGIBackground );
  XSelectInput( XBGIDisplay, twin, ExposureMask|KeyPressMask|ButtonPressMask );
  XSelectInput( XBGIDisplay, swin, ExposureMask|KeyPressMask|ButtonPressMask );
  XSelectInput( XBGIDisplay, owin, ExposureMask|KeyPressMask|ButtonPressMask );
  XSelectInput( XBGIDisplay, cwin, ExposureMask|KeyPressMask|ButtonPressMask );
  curs = XCreateFontCursor( XBGIDisplay, XC_xterm );
  XDefineCursor( XBGIDisplay, swin, curs );
  XFlush( XBGIDisplay );
  XMapWindow( XBGIDisplay, rwin );
  XMapSubwindows( XBGIDisplay, rwin );
  XSetTransientForHint( XBGIDisplay, rwin, XBGIRoot );
  do
    XNextEvent( XBGIDisplay, &ev );
  while ( ev.type != Expose );
  XPutBackEvent( XBGIDisplay, &ev );

  XFlush( XBGIDisplay );
  while ( flg ){
    XNextEvent( XBGIDisplay, &ev );
    switch ( ev.type ){
    case Expose:
      if ( ev.xexpose.count != 0 ) break;
      textwidth = TextWidth( XBGIFontStruct, str, strlen(str) )
        + TextWidth( XBGIFontStruct, " ", 1 );
      if ( textwidth < width )
        textstartx = 0;
      else
        textstartx = width - textwidth;
      if ( ev.xexpose.window == rwin ){
        xbgiDecorateWindow( XBGIDisplay, rwin, XBGIDefaultGC,
                           XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			   DecoRectFront );
      }else if ( ev.xexpose.window == twin ){
        xbgiDecorateWindow( XBGIDisplay, twin, XBGIDefaultGC,
                           XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			   DecoRectFront );
        xbgiPrintf( XBGIDisplay, twin, XBGIDefaultGC, XBGIFontStruct,
		   CENTER_TEXT, "%s", title );
      }else if ( ev.xexpose.window == swin ){
        exposeev = ev;
        xbgiDecorateWindow( XBGIDisplay, swin, XBGIDefaultGC,
                           XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			   DecoRectBack );
        XSetForeground( XBGIDisplay, XBGIDefaultGC, XBGIForeground );
        XSetBackground( XBGIDisplay, XBGIDefaultGC, XBGIBackground );
        XDrawString( XBGIDisplay, swin, XBGIDefaultGC, textstartx, textstarty,
                    str, strlen(str) );
        XSetForeground( XBGIDisplay, XBGIDefaultGC, XBGIBackground );
        XSetBackground( XBGIDisplay, XBGIDefaultGC, XBGIForeground );
        XDrawImageString( XBGIDisplay, swin, XBGIDefaultGC, 
                         textstartx
                         + TextWidth( XBGIFontStruct, str, strlen(str) ),
                         textstarty, " ", 1 );
        if ( textstartx < 0 ){
          XSetForeground( XBGIDisplay, XBGIDefaultGC, XBGIBackground );
          XSetBackground( XBGIDisplay, XBGIDefaultGC, XBGIForeground );
          XDrawImageString( XBGIDisplay, swin, XBGIDefaultGC, 0, textstarty,
			   "<", 1 );
          XSetForeground( XBGIDisplay, XBGIDefaultGC, XBGIForeground );
          XSetBackground( XBGIDisplay, XBGIDefaultGC, XBGIBackground );
        }
      }else if ( ev.xexpose.window == owin ){
        xbgiDecorateWindow( XBGIDisplay, owin, XBGIDefaultGC,
                           XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			   DecoRectFront );
        xbgiPrintf( XBGIDisplay, owin, XBGIDefaultGC, XBGIFontStruct,
		   CENTER_TEXT, OK );
      }else{
        xbgiDecorateWindow( XBGIDisplay, cwin, XBGIDefaultGC,
                           XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			   DecoRectFront );
        xbgiPrintf( XBGIDisplay, cwin, XBGIDefaultGC, XBGIFontStruct,
		   CENTER_TEXT, CANCEL );
      }
      /*while ( XCheckTypedEvent(XBGIDisplay,Expose,&ev) );*/
      XFlush( XBGIDisplay );
      break;
    case KeyPress:
      if ( XLookupString( (XKeyEvent*)&ev, &c, 1, &key, NULL ) == 1 ){
        switch ( key ){
        case XK_Escape:
          strcpy( str, "" );
          flg = 0;
          break;
        case XK_Return:
          flg = 0;
          break;
        case XK_BackSpace:
        case XK_Delete:
          str[ max(0,(int)strlen(str)-1) ] = '\0';
          break;
        case XK_Tab:
          break;
        /*case XK_space:
          break;*/
        default:
          if ( !IsCursorKey(key) && !IsFunctionKey(key) && !iscntrl(c) ){
            str[ min(strlen(str)+1,maxlen-1) ] = '\0';
            str[ min(strlen(str),  maxlen-2) ] = c;
          }else if ( iscntrl(c) ){
            switch(c){
            case CTRL('w'):
              strcpy( str, "" );
              break;
            }
          }
          break;
        }
      }
      XPutBackEvent( XBGIDisplay, &exposeev );
      break;
    case ButtonPress:
      switch ( ev.xbutton.button ){
      case Button1:
        if ( ev.xbutton.window == owin )
          flg = 0;
        else if ( ev.xbutton.window == cwin ){
          strcpy( str, "" );
          flg = 0;
        }
        break;
      case Button2:
        bytes = XFetchBytes( XBGIDisplay, &nbytes );
        bytes[nbytes] = '\0';
        if ( strlen(str)+nbytes < maxlen ){
          strcat( str, bytes );
        }
        XPutBackEvent( XBGIDisplay, &exposeev );
        break;
      }
    }
  }
  XUnmapSubwindows( XBGIDisplay, rwin );
  XUnmapWindow( XBGIDisplay, rwin );
}
void bgimenu( char *title, int menuc, char *menuv[], int *menui )
{
  Window rwin, twin, *mwin;
  XSetWindowAttributes att;
  XEvent ev;
  int i, width, height, textwidth, textheight, x, y;
  
  xbgiGetSizePrintf( XBGIFontStruct, &textwidth, &textheight, "%s", title );
  for ( i=0; i<menuc; i++ ){
    xbgiGetSizePrintf( XBGIFontStruct, &width, &textheight, "%s", menuv[i] );
    if ( textwidth < width )
      textwidth = width;
  }
  width  = textwidth;
  height = textheight;
  x = XBGIEvent.xbutton.x_root;
  y = XBGIEvent.xbutton.y_root;
  x = x - Hem(width)/2;
  y = y - Hem(height)/2;
  rwin = XCreateSimpleWindow( XBGIDisplay, RootWindow(XBGIDisplay,XBGIScreen),
                             x, y,
                             Hem(Hem(width)), Hem(Hem(height)*(menuc+1)), 0,
                             XBGIForeground, XBGIBackground );
  XSelectInput( XBGIDisplay, rwin, ExposureMask );

  att.override_redirect = True;
  XChangeWindowAttributes( XBGIDisplay, rwin, CWOverrideRedirect, &att );
  att.save_under = True;
  XChangeWindowAttributes( XBGIDisplay, rwin, CWSaveUnder, &att );
  twin = XCreateSimpleWindow( XBGIDisplay, rwin,
                             DecoHemBits, DecoHemBits,
                             Hem(width), Hem(height), 0,
                             XBGIForeground, XBGIBackground );
  mwin = (Window*)malloc( (menuc)*sizeof(Window) );
  for ( i=0; i<menuc; i++ ){
    mwin[i] = XCreateSimpleWindow( XBGIDisplay, rwin, 
                                  DecoHemBits, DecoHemBits+Hem(height)*(i+1),
                                  Hem(width), Hem(height), 0,
                                  XBGIForeground, XBGIBackground );
    XSelectInput( XBGIDisplay, mwin[i], ButtonMotionMask|
                 EnterWindowMask|LeaveWindowMask );
  }
  XPutBackEvent( XBGIDisplay, &XBGIEvent );
  while (1){
    XNextEvent( XBGIDisplay, &ev );
    switch ( ev.type ){
    case Expose:
      if ( ev.xexpose.count != 0 ) break;
      xbgiDecorateWindow( XBGIDisplay, rwin, XBGIDefaultGC,
                         XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			 DecoRectFront );
      xbgiDecorateWindow( XBGIDisplay, twin, XBGIDefaultGC,
                         XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			 DecoRectFront );
      xbgiPrintf( XBGIDisplay, twin, XBGIDefaultGC, XBGIFontStruct,
		 CENTER_TEXT,
                 "%s", title );
      for ( i=0; i<menuc; i++ ){
        xbgiDecorateWindow( XBGIDisplay, mwin[i], XBGIDefaultGC,
                           XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			   DecoNothing );
        xbgiPrintf( XBGIDisplay, mwin[i], XBGIDefaultGC, XBGIFontStruct,
		   LEFT_TEXT, "%s", menuv[i] );
      }
      while ( XCheckTypedEvent(XBGIDisplay,Expose,&ev) );
      XFlush( XBGIDisplay );
      break;
    case EnterNotify:
      for ( i=0; i<menuc; i++ ){
        if ( ev.xcrossing.window == mwin[i] ){
          xbgiDecorateWindow( XBGIDisplay, mwin[i], XBGIDefaultGC, 
                             XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			     DecoRectFront );
          xbgiPrintf( XBGIDisplay, mwin[i], XBGIDefaultGC, XBGIFontStruct,
		     LEFT_TEXT, "%s", menuv[i] );
          *menui = i;
        }
      }
      XFlush( XBGIDisplay );
      break;
    case LeaveNotify:
      *menui = -1;
      for ( i=0; i<menuc; i++ ){
        if ( ev.xcrossing.window == mwin[i] ){
          xbgiDecorateWindow( XBGIDisplay, mwin[i], XBGIDefaultGC,
                             XBGIForeground, XBGITopShadow, XBGIBottomShadow,
			     DecoNothing );
          xbgiPrintf( XBGIDisplay, mwin[i], XBGIDefaultGC, XBGIFontStruct,
		     LEFT_TEXT, "%s", menuv[i] );
        }
      }
      XFlush( XBGIDisplay );
      break;
    case ButtonPress:
      XMapWindow( XBGIDisplay, rwin );
      XMapSubwindows( XBGIDisplay, rwin );
      /*if ( XBGIColormap != DefaultColormap(XBGIDisplay,XBGIScreen) )
	;*/ /* What can I do? */
      XFlush( XBGIDisplay );
      break;
    case ButtonRelease:
      XUnmapSubwindows( XBGIDisplay, rwin );
      XUnmapWindow( XBGIDisplay, rwin );
      XDestroySubwindows( XBGIDisplay, rwin );
      free( mwin );
      XDestroyWindow( XBGIDisplay, rwin );
      /*if ( XBGIColormap != DefaultColormap(XBGIDisplay,XBGIScreen) )
	;*/ /* What can I do? */
      XFlush( XBGIDisplay );
      return;
      break;
    }
  }
}











