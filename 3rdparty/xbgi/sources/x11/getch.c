/*
 * Source File < x11/getch.c >
 *
 * Standard Functions of Console I/O: on Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"
#include <X11/keysym.h>

int getch( void )
{
  xbgi *ptr;
  XEvent ev;
  char c;
  
  if (!XBGI){ return getchar(); }
  /*
   * flush all xbgi
   */
  ptr = XBGIS;
  while ( ptr != NULL ){
    XFlush( XBGIsDisplay(ptr) );
    ptr = ptr->next;
  }
  /*
   * finite roop by key press
   */
  while ( !0 ){
    XNextEvent( XBGIDisplay, &ev );
    switch ( ev.type ){
    case KeyPress:
      XBGIEvent = ev;
      if ( XLookupString( (XKeyEvent*)&ev, &c, 1, NULL, NULL ) == 1 )
        return (int)c;
      break;
    }
  }
}











