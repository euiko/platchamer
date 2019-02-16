/*
 * Source File < x11/kbhit.c >
 *
 * Standard Functions of Console I/O: on Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"
#include <X11/keysym.h>

int kbhit( void )
{
  XEvent ev;
  char c;
  
  if (!XBGI){ return 0; }

  if ( XCheckTypedWindowEvent( XBGIDisplay, XBGIWins[XBGI->vpage],
                              KeyPress, &ev ) ){
    if ( XLookupString( (XKeyEvent*)&ev, &c, 1, NULL, NULL ) == 1 ){
      XBGIEvent = ev;
      XPutBackEvent( XBGIDisplay, &ev );
      return !0;
    }
  }else{
    return 0;
  }
  return 0;
}











