/*
 * Source File < x11/request.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * official enhanced functions to flush or sync request
 */
void xflush( void )
{
  XFlush( XBGIDisplay );
}
void xsync( void )
{
  XSync( XBGIDisplay, False );
}








