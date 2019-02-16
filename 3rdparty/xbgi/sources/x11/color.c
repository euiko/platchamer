/*
 * Source File < x11/color.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"
char x11_xbgi_scolor_names[MAXCOLORS+1][64] = {
#include "colors/scolor.def"
};

/*
 * standard functions to get and set color
 */
int getcolor( void )
{
  return XBGI->color;
}
int getbkcolor( void )
{
  return XBGI->bkcolor;
}
int getmaxcolor( void )
{
  return XBGI->palette.size-1;
}
void setcolor( int color )
{
  XBGI->color = minmax( 0, color, XBGI->palette.size-1 );
  XSetForeground( XBGIDisplay, XBGIDrawGC, XBGIPixels[XBGI->color] );
}
void setbkcolor( int color )
{
  XBGI->bkcolor = minmax( 0, color, XBGI->palette.size-1 );
  XSetWindowBackground( XBGIDisplay, XBGIWins[XBGI->apage], 
                       XBGIPixels[XBGI->bkcolor] );
  XSetBackground( XBGIDisplay, XBGIDrawGC,  XBGIPixels[XBGI->bkcolor] );
  XSetBackground( XBGIDisplay, XBGIFillGC,  XBGIPixels[XBGI->bkcolor] );
  XSetBackground( XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->bkcolor] );
  XSetBackground( XBGIDisplay, XBGIImageGC, XBGIPixels[XBGI->bkcolor] );
  /*XClearWindow( XBGIDisplay, XBGIWins[XBGI->apage] );*/
}
void setmaxcolor( int c )
{
  int i, cc;
  unsigned long plane_mask;
  unsigned long red_plane_mask, green_plane_mask, blue_plane_mask;
  struct rgbtype {
    unsigned short red, green, blue;
  } rgb[8] = {
    { 0, 0, 0 },
    { 0, 0, 1 },
    { 0, 1, 0 },
    { 0, 1, 1 },
    { 1, 0, 0 },
    { 1, 0, 1 },
    { 1, 1, 0 },
    { 1, 1, 1 },
  };
  XColor color;
  Status ok;

  switch( XBGI->gmode ){
  case X11MONO:
    XBGI->palette.size = XBGI->ncolor = 2;
#if 0 /* USE_COLORTABLE */
    XBGIColortable[BlackPixel(XBGIDisplay,XBGIScreen)] = 0;
    XBGIColortable[WhitePixel(XBGIDisplay,XBGIScreen)] = XBGI->palette.size-1;
#endif
    XBGIPixels[0] = BlackPixel( XBGIDisplay, XBGIScreen );
    XBGIPixels[XBGI->palette.size-1] = WhitePixel( XBGIDisplay, XBGIScreen );
    for ( i=0; i<XBGI->palette.size; i++ )
      XBGI->palette.colors[i] = i;
    break;
  case X11SGRAY: /* It's supported since version 3.01. */
  case X11SCOLOR: /* It's supported since version 2.2. */
  case X11TCOLOR: /* It's supported since version 3.01. */
    if ( c<1 || MAXCOLORS<c ) return;
    XBGI->palette.size = c + 1;
    for ( i=0; i<XBGI->palette.size; i++ ){
#if 0 /* USE_COLORTABLE */
      XBGIColortable[XBGIPixels[i]] = i;
#endif
      XBGI->palette.colors[i] = i;
    }
    if ( XBGI->colornames && XBGI->gerror == grNoInitGraph ){
      /* color name setting at graph booting */
      for ( i=0; i<XBGI->palette.size; i++ ){
        ok = XParseColor( XBGIDisplay, XBGIColormap,
                         x11_xbgi_scolor_names[i], &color );
        if ( ok == False ) Warning( "named color storing fault" );
        else
          _setrgbpalette( i, color.red, color.green, color.blue );
      }
    }else{
      switch ( XBGI->gmode ){
      case X11SGRAY:
        for ( i=1; i<XBGI->palette.size; i++ )
          setrgbpalette( i, i, i, i );
        break;
      case X11SCOLOR:
      case X11TCOLOR:
        if ( XBGI->palette.size>=8 ){
          /* normal color setting algorithm */
          for ( i=0; i<XBGI->palette.size/8; i++ )
            for ( cc=0; cc<8; cc++ )
              setrgbpalette( 8*i+cc,
                            8*(i+1)*rgb[cc].red,
                            8*(i+1)*rgb[cc].green,
                            8*(i+1)*rgb[cc].blue );
          for ( i=1; i<XBGI->palette.size/8; i++ )
            setrgbpalette( 8*i+0, 4*(i+1), 4*(i+1), 4*(i+1) );
          cc = XBGI->palette.size/2;
          for ( i=0; i<XBGI->palette.size/8; i++ )
            setrgbpalette( 8*i+7, cc+4*(i+1), cc+4*(i+1), cc+4*(i+1) );
        }else{
          /* case less than 8 color */
          _setrgbpalette( 0, 0, 0, 0 );
          for ( i=1; i<XBGI->palette.size-1; i++ ){
            _setrgbpalette( i, 65536-1, 65536-1, 65536-1 );
          }
          _setrgbpalette( 1, 65536-1, 65536-1, 65536-1 );
        }
        break;
      }
    }
    break;
  case X11GRAY:
  case X11COLOR:
  case X11DCOLOR: /* ! */
    if ( c<1 || MAXCOLORS<c ) return;
    if ( XBGI->gerror != grNoInitGraph )
      XFreeColors( XBGIDisplay, XBGIColormap, XBGIPixels,
                  XBGI->palette.size, 0 );
    XBGI->palette.size = c + 1;
    if ( XBGI->gmode == X11DCOLOR && XBGIVisualClass == DirectColor )
      ok = XAllocColorPlanes( XBGIDisplay, XBGIColormap,
			     False, XBGIPixels, XBGI->palette.size, 3,3,2,
			     &red_plane_mask,
			     &green_plane_mask,
			     &blue_plane_mask );
    else
      ok = XAllocColorCells( XBGIDisplay, XBGIColormap,
			    False, &plane_mask, False,
			    XBGIPixels, XBGI->palette.size );
    if ( ok == False ){
      /* 1st failed */
      XBGIColormap = XCreateColormap( XBGIDisplay, XBGIRoot, XBGIVisual,
                                     AllocNone );
      /*XInstallColormap( XBGIDisplay, XBGIColormap );*/ 
      XSetWindowColormap( XBGIDisplay, XBGIRoot, XBGIColormap );
      if ( XBGI->gmode == X11DCOLOR && XBGIVisualClass == DirectColor )
	ok = XAllocColorPlanes( XBGIDisplay, XBGIColormap,
			       False, XBGIPixels, XBGI->palette.size, 3,3,2,
			       &red_plane_mask,
			       &green_plane_mask,
			       &blue_plane_mask );
      else
	ok = XAllocColorCells( XBGIDisplay, XBGIColormap,
			      False, &plane_mask, False,
			      XBGIPixels, XBGI->palette.size );
      /* need technique for settings near the standard color map */
      if ( ok == False ) FatalError( "color cell allocation fault" );
    }
    for ( i=0; i<XBGI->palette.size; i++ ){
#if 0 /* USE_COLORTABLE */
      XBGIColortable[XBGIPixels[i]] = i;
#endif
      XBGI->palette.colors[i] = i;
    }
    if ( XBGI->colornames && XBGI->gerror == grNoInitGraph ){
      /* color name setting at graph booting */
      for ( i=0; i<XBGI->palette.size; i++ ){
        ok = XParseColor( XBGIDisplay, XBGIColormap,
                         x11_xbgi_scolor_names[i], &color );
        if ( ok == False ) Warning( "named color storing fault" );
        else
          _setrgbpalette( i, color.red, color.green, color.blue );
      }
    }else{
      switch( XBGI->gmode ){
      case X11GRAY:
        for ( i=1; i<XBGI->palette.size; i++ )
          setrgbpalette( i, i, i, i );
        setallpalette( &XBGI->palette );
        break;
      case X11COLOR:
      case X11DCOLOR:
        if ( XBGI->palette.size>=8 ){
          /* normal color setting algorithm */
          for ( i=0; i<XBGI->palette.size/8; i++ )
            for ( cc=0; cc<8; cc++ )
              setrgbpalette( 8*i+cc,
                            8*(i+1)*rgb[cc].red,
                            8*(i+1)*rgb[cc].green,
                            8*(i+1)*rgb[cc].blue );
          for ( i=1; i<XBGI->palette.size/8; i++ )
            setrgbpalette( 8*i+0, 4*(i+1), 4*(i+1), 4*(i+1) );
          cc = XBGI->palette.size/2;
          for ( i=0; i<XBGI->palette.size/8; i++ )
            setrgbpalette( 8*i+7, cc+4*(i+1), cc+4*(i+1), cc+4*(i+1) );
        }else{
          /* case less than 8 color */
          _setrgbpalette( 0, 0, 0, 0 );
          for ( i=1; i<XBGI->palette.size-1; i++ ){
            _setrgbpalette( i, 65536-1, 65536-1, 65536-1 );
          }
          _setrgbpalette( 1, 65536-1, 65536-1, 65536-1 );
        }
        break;
      }
    }
    break;
  }
}









