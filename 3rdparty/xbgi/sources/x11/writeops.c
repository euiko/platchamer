/*
 * Source File < x11/writeops.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard function to set write operation
 */
void setwritemode( int op )
{
  static int OP2GX[] = {
    GXcopy, GXxor, GXor, GXand, GXcopyInverted,
  };

  XSetFunction( XBGIDisplay, XBGIDrawGC,  OP2GX[op] );
  XSetFunction( XBGIDisplay, XBGIPixelGC, OP2GX[op] );
}











