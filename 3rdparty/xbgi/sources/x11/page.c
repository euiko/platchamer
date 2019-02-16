/*
 * Source File < x11/page.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions for page as drawing device
 */
void cleardevice( void )
{
  XClearWindow( XBGIDisplay, XBGIWins[XBGI->apage] );
}
void setactivepage( int page )
{
  XBGI->apage = minmax( 0, page, XBGI->npage-1 );
}
void setvisualpage( int page )
{
  int i;

  if ( page >= XBGI->npage ){
    /* all pages full mapped mode */
    for ( i=0; i<XBGI->npage; i++ ){
      XReparentWindow( XBGIDisplay,
                      XBGIWins[i], RootWindow(XBGIDisplay,XBGIScreen), 0, 0 );
      XMapWindow( XBGIDisplay, XBGIWins[i] );
    }
    XUnmapWindow( XBGIDisplay, XBGIRoot );
    XBGI->vpage = XBGI->npage;
  }else if ( XBGI->vpage >= XBGI->npage && page < XBGI->npage ){
    /* one page mapped mode */
    XUnmapSubwindows( XBGIDisplay, XBGIRoot );
    for ( i=0; i<XBGI->npage; i++ )
      XReparentWindow( XBGIDisplay, XBGIWins[i], XBGIRoot, 0, 0 );
    XBGI->vpage = minmax( 0, page, XBGI->npage-1 );
    XMapWindow( XBGIDisplay, XBGIRoot );
    XMapRaised( XBGIDisplay, XBGIWins[XBGI->vpage] );
  }else{
    XBGI->vpage = minmax( 0, page, XBGI->npage-1 );
    XMapRaised( XBGIDisplay, XBGIWins[XBGI->vpage] );
  }
}
void restorecrtmode( void )
{
  NotSupported( "restorecrtmode()" );
}








