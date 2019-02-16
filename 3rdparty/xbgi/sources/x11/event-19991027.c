/*
 * Source File < x11/event.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include <sys/types.h>
#include <sys/time.h>
#include "x11_p.h"

/*
 * event loop with tools
 */
/* menu defined */
enum MENU_ITEM {
  NO_SELECT = -1,
  SAVE_XBM,
#ifdef ENABLE_XPMLIB
  SAVE_XPM,
#endif
#ifndef BUILD_STANDALONE
  SAVE_PS,
  SET_PS_OPTION,
#endif
  QUIT,
};
static char *MENU_TITLE = "menu";
static int   MENU_ITEMC = QUIT+1;
static int   MENU_ITEMI = NO_SELECT;
static char *MENU_ITEMV[] = {
  "save bitmap",
#ifdef ENABLE_XPMLIB
  "save pixmap",
#endif
#ifndef BUILD_STANDALONE
  "save ps",
  "set ps option",
#endif
  "quit (q)"
};
/* about, info and help defined */
#define ABOUT "xbgi\n"\
              "version 3.02\n"\
              "Borland Graphics Interface\n"\
              "for X11, PostScript, (PIX, VIX).\n"\
              "produced by Taiji Yamada, 1992-1999"
#define INFO  "id          %d\n"\
              "driver      %s\n"\
              "mode        %s\n"\
              "visual page %d\n"\
              "active page %d\n"\
              "pages       %d\n"\
              "color       %d\n"\
              "bkcolor     %d\n"\
              "ncolor      %d\n",\
              XBGI->id,\
              getdriversname(XBGI->gdriver),\
              getmodename(XBGI->gmode),\
              XBGI->apage,\
              XBGI->vpage,\
              XBGI->npage,\
              XBGI->color,\
              XBGI->bkcolor,\
              XBGI->ncolor
#define HELP  "-gd driver            Driver name X11, PS, (PIX, VIX).\n"\
              "-ncolor number        The number of graphics color.\n"\
              "-color number         Graphic forground color number.\n"\
              "-bkcolor number       Graphic background color number.\n"\
              "-npage number         The number of graphics page.\n"\
              "X11:\n"\
              "-gm mode              Mode name X11MONO, X11COLOR etc.\n"\
              "-display display      X display name.\n"\
              "-geometry geometry    Window size and position.\n"\
              "-fn font              Font of popup text.\n"\
              "-fg color             Foreground color of popup text.\n"\
              "-bg color             Background color of popup text.\n"\
              "-title string         Title of graphics window.\n"\
              "-name name            Resouce name of graphics window.\n"\
              "-icon file            Icon bitmap filename.\n"\
              "-backing[-]           Backing store on[off].\n"\
              "-colornames colorlist X named color list for graphics.\n"\
              "-l10n[-]              Bi-or-Multilingual text off[on].\n"\
              "PS:\n"\
              "-gm mode              Mode name PSMONO, PSGRAY, PSCOLOR.\n"\
              "-geometry geometry    Graphics geometry size and position.\n"\
              "-interp               Pipe open to PostScript interpreter.\n"\
              "-psfile name          File to save PostScript code.\n"\
              "-eps                  Encapsuled PostScript mode.\n"\
              "-paper name           Paper names letter, legal, a4 etc.\n"\
              "-portrait             Portrait orientation mode.\n"\
              "-landscape            Landscape orientation mode.\n"\
              "-title string         Title of PostScript document.\n"\
              "-l10n[-]              Bilingual text off[on].\n"\

/*
 * default event procs
 */
int xbgi_button_press( int button, int x, int y )
{
  static char xbmfilename[80], xbmfilenamebak[80] = "scratch.xbm";
  static char xpmfilename[80], xpmfilenamebak[80] = "scratch.xpm";
  static char epsfilename[80], epsfilenamebak[80] = "scratch.eps";
  static char psoption[64] = "-portrait -paper a4";
  int status;

  switch( button ){
  case 1:
    break;
  case 2:
    bgimenu( MENU_TITLE, MENU_ITEMC, MENU_ITEMV, &MENU_ITEMI );
    switch( MENU_ITEMI ){
    case NO_SELECT:
      break;
    case SAVE_XBM:
      strcpy( xbmfilename, xbmfilenamebak );
      bgigets( "XBM NAME", 80, xbmfilename );
      if ( strcmp(xbmfilename,"") != 0 ){
        status = savemonographtofile( xbmfilename, NULL );
        strcpy( xbmfilenamebak, xbmfilename );
        if ( !status )
          bgiprintf( "Error!", CENTER_TEXT, "saving bitmap is failed" );
      }else{
        strcpy( xbmfilename, xbmfilenamebak );
      }
      break;
#ifdef ENABLE_XPMLIB
    case SAVE_XPM:
      strcpy( xpmfilename, xpmfilenamebak );
      bgigets( "XPM NAME", 80, xpmfilename );
      if ( strcmp(xpmfilename,"") != 0 ){
        status = savegraphtofile( xpmfilename, NULL );
        strcpy( xpmfilenamebak, xpmfilename );
        if ( !status )
          bgiprintf( "Error!", CENTER_TEXT, "saving pixmap is failed" );
      }else{
        strcpy( xpmfilename, xpmfilenamebak );
      }
      break;
#endif
#ifndef BUILD_STANDALONE
    case SAVE_PS:
      if ( XBGI->inherit_procedures->expose_handler ){
	strcpy( epsfilename, epsfilenamebak );
	bgigets( "(E)PS NAME", 80, epsfilename );
	if ( strcmp(epsfilename,"") != 0 ){
	  status = saveexposetofile( epsfilename, psoption );
	  strcpy( epsfilenamebak, epsfilename );
	  if ( !status )
	    bgiprintf( "Error!", LEFT_TEXT, "saving ps is failed" );
	}else{
	  strcpy( xpmfilename, xpmfilenamebak );
	}
      }else{
	bgiprintf( "Error!", LEFT_TEXT,
		  "No expose procedure!\n"
		  "Please set expose procedure before xbgiloop,\n"
		  "if you want to save PostScript as follows:  \n"
		  "--------------------------------------------\n"
		  "  int my_expose( void )\n"
		  "  {\n"
		  "    /* your drawing code */\n"
		  "    return !0;\n"
		  "  }\n"
		  "  int main( void )\n"
		  "  {\n"
		  "      :\n"
		  "    set_expose_handler( my_expose );\n"
		  "    xbgiloop();\n"
		  "      :\n"
		  "  }\n" );
      }
      break;
    case SET_PS_OPTION:
      bgigets( "PS OPTION", 64, psoption );
      break;
#endif /* BUILD_STANDALONE */
    case QUIT:
      return 0;
      break;
    }
    break;
  case 3:
    return 0;
    break;
  }
  return !0;
}
int xbgi_button_release( int button, int x, int y )
{
  return !0;
}
int xbgi_mouse_motion( int button_state, int x, int y )
{
  return !0;
}
int xbgi_page_enter( int page )
{
  return !0;
}
int xbgi_page_leave( int page )
{
  return !0;
}
int xbgi_key_press( int c )
{
  int i;
  char buf[1024];

  switch( c ){
  case CTRL('a'):
    bgiprintf( "about", CENTER_TEXT, ABOUT );
    break;
  case CTRL('i'):
    bgiprintf( "info.", LEFT_TEXT, INFO );
    break;
  case CTRL('o'):
    strcpy( buf, "" );
    for ( i=0; i<XBGI->argc; i++ ){
      if ( XBGI->argv[i][0] == '-' )
        strcat( buf, "\n" );
      strcat( buf, XBGI->argv[i] );
      if ( XBGI->argv[i][0] == '-' )
        strcat( buf, " " );
    }
    bgiprintf( "options", LEFT_TEXT, "%s", buf );
    break;
  case CTRL('h'):
    bgiprintf( "help", LEFT_TEXT, HELP );
    break;
  case 'n': case 'N':
    setvisualpage( min( XBGI->vpage+1, XBGI->npage-1 ) );
    break;
  case 'b': case 'B':
    setvisualpage( XBGI->vpage-1 );
    break;
  case CTRL('f'):
    if ( XBGI->vpage != XBGI->npage )
      setvisualpage( XBGI->npage );
    else
      setvisualpage( 0 );
    break;
  case CTRL('c'):
    exit( 0 );
    break;
  case 'q': case 'Q': case 0x1b:
    return 0;
    break;
  }
  return !0;
}
int xbgi_configure( void )
{
  return !0;
}
int xbgi_expose( void )
{
  return !0;
}
int xbgi_noevent( void )
{
  return !0;
}

/*
 * event looper for simple event programing
 */
#define SWITCH_EV(ev) do {\
switch ( ev.type ){\
case ButtonPress: /*fprintf(stderr, "ev: ButtonPress\n");*/\
  XBGIEvent = ev;\
  if ( XBGI->inherit_procedures->button_press_handler != NULL ){\
    switch( ev.xbutton.button ){\
    case Button1: b = 1; break;\
    case Button2: b = 2; break;\
    case Button3: b = 3; break;\
    }\
    ret = XBGI->inherit_procedures\
      ->button_press_handler( b, ev.xbutton.x, ev.xbutton.y );\
  }\
  break;\
case ButtonRelease: /*fprintf(stderr, "ev: ButtonRelease\n");*/\
  XBGIEvent = ev;\
  if ( XBGI->inherit_procedures->button_release_handler != NULL ){\
    switch( ev.xbutton.button ){\
    case Button1: b = 1; break;\
    case Button2: b = 2; break;\
    case Button3: b = 3; break;\
    }\
    ret = XBGI->inherit_procedures\
      ->button_release_handler( b, ev.xbutton.x, ev.xbutton.y );\
  }\
  break;\
case MotionNotify: /*fprintf(stderr, "ev: MotionNotify\n");*/\
  XBGIEvent = ev;\
  if ( XBGI->inherit_procedures->mouse_motion_handler != NULL ){\
    bs = 0;\
    if ( ev.xmotion.state & Button1Mask ) bs |= 1;\
    if ( ev.xmotion.state & Button2Mask ) bs |= 2;\
    if ( ev.xmotion.state & Button3Mask ) bs |= 4;\
    ret = XBGI->inherit_procedures\
      ->mouse_motion_handler( bs, ev.xbutton.x, ev.xbutton.y );\
  }\
  break;\
case EnterNotify: /*fprintf(stderr, "ev: EnterNotify\n");*/\
  XBGIEvent = ev;\
  if ( XBGI->inherit_procedures->page_enter_handler != NULL ){\
    for ( p=0; p<XBGI->npage; p++ )\
      if ( XBGIWins[p] == ev.xcrossing.window )\
        ret = XBGI->inherit_procedures->page_enter_handler( p );\
  }\
  break;\
case LeaveNotify: /*fprintf(stderr, "ev: LeaveNotify\n");*/\
  XBGIEvent = ev;\
  if ( XBGI->inherit_procedures->page_leave_handler != NULL ){\
    for ( p=0; p<XBGI->npage; p++ )\
      if ( XBGIWins[p] == ev.xcrossing.window )\
        ret = XBGI->inherit_procedures->page_leave_handler( p );\
  }\
  break;\
case KeyPress: /*fprintf(stderr, "ev: KeyPress\n");*/\
  if ( XLookupString( (XKeyEvent*)&ev, &c, 1, NULL, NULL ) == 1 ){\
   XBGIEvent = ev;\
    if ( XBGI->inherit_procedures->key_press_handler != NULL )\
      ret = XBGI->inherit_procedures->key_press_handler( c );\
  }\
  break;\
case ConfigureNotify: /*fprintf(stderr, "ev: ConfigureNotify\n");*/\
  XBGIEvent = ev;\
  if ( XBGI->inherit_procedures->configure_handler != NULL )\
    ret = XBGI->inherit_procedures->configure_handler();\
  break;\
case Expose: /*fprintf(stderr, "ev: Expose\n");*/\
  XBGIEvent = ev;\
  if ( ev.xexpose.window == XBGIRoot ) /* since 3.02 generic 19991024 */\
    break;\
  while ( XEventsQueued(ev.xexpose.display,QueuedAfterReading) > 0 ){\
    XPeekEvent( ev.xexpose.display, &ahead );\
    if ( ahead.type != Expose )\
      break;\
    if ( ahead.xexpose.window != ev.xexpose.window )\
      break;\
    XNextEvent( ev.xexpose.display, &ev );\
  }\
  if ( XBGI->inherit_procedures->expose_handler != NULL )\
    ret = XBGI->inherit_procedures->expose_handler();\
  break;\
}\
} while (0);
void xbgiloop( void )
{
  xbgi *ptr;
  XEvent ev, ahead;
  int b = 0, bs, p;
  char c;
  int ret;
  /*
     [References]
     R. Kinoshita, H. Hideyuki,
     ``X-Window Ver.11 Programing,''
     \S 119,
     Nikkan Kougyou Shinbunsha, 1989.

     Oliver Jones,
     ``Introduction to the X Window System,''
     \S 11.3,
     M.I.T. Press., 1989.

     W. Richard Stevens,
     ``Advanced Programming in the UNIX Environment,''
     \S 12.5.1,
     Addison-Wesley Publishing Company, Inc. 1992.
     */
  int nfds = 0;
  fd_set fds, readfds, writefds, exceptfds;
  struct timeval timeout;

  FD_ZERO(&fds);
  /*
   * flush all xbgi
   */
  ptr = XBGIS;
  while ( ptr != NULL ){
    if (ptr->gdriver == X11) {
      int cn;

      XFlush( XBGIsDisplay(ptr) );
      cn = ConnectionNumber(XBGIsDisplay(ptr));
      FD_SET(cn, &fds);
      nfds = max(nfds,cn+1);
    }
    ptr = ptr->next;
  }
  ptr = XBGI;
  XBGI = XBGIS;
  /*
   * finite event roop
   */
  ret = !0;
#if 1 /* event-wait loop, since version 3.02 generic 19991019 */
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  while (ret) {
    int has_bg_proc = 0, no_event = !0;

    while (XBGI != NULL) {
      if (XBGI->gdriver == X11) {
	if (XEventsQueued(XBGIDisplay, QueuedAfterReading) > 0) {
	  XNextEvent(XBGIDisplay, &ev);
	  SWITCH_EV(ev);
	  no_event = 0;
	  break;
	}
	else {
	  XFlush(XBGIDisplay);
	  if (XBGI->inherit_procedures->noevent_handler != NULL) {
	    has_bg_proc = !0;
	    ret = XBGI->inherit_procedures->noevent_handler();
	  }
	}
      }
      XBGI = XBGI->next;
    }
    if (no_event) {
      FD_ZERO(&writefds), FD_ZERO(&exceptfds);
      readfds = fds;
      select(nfds, &readfds, &writefds, &exceptfds, has_bg_proc?&timeout:NULL);
    }
    if (XBGI == NULL)
      XBGI = XBGIS;
  }
#else /* event loop without select before 3.02, event-delay loop with select */
  timeout.tv_sec = 0;
  timeout.tv_usec = 1000;
  while (ret) {
    if (XBGI == NULL)
      XBGI = XBGIS;
    if (XBGI->gdriver == X11) {
      if (XEventsQueued(XBGIDisplay, QueuedAfterFlush) > 0) {
	XNextEvent(XBGIDisplay, &ev);
	SWITCH_EV(ev);
      }
      else {
	if (XBGI->inherit_procedures->noevent_handler != NULL)
	  ret = XBGI->inherit_procedures->noevent_handler();
	select(0, NULL, NULL, NULL, &timeout);
      }
    }
    XBGI = XBGI->next;
  }
#endif
  XBGI = ptr;
}
/*
 * is event
 */
int isevent(void)
{
  if ( XEventsQueued( XBGIDisplay, QueuedAfterFlush ) > 0 )
    return !0;
  else
    return 0;
}
