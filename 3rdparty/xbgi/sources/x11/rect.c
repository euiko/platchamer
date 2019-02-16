/*
 * Source File < x11/rect.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions to draw rectangle
 */
void rectangle( int left, int top, int right, int bottom )
{
  XDrawRectangle( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                 min( Xx(left), Xx(right) ), min( Xy(top), Xy(bottom) ),
                 abs( right - left ), abs( bottom - top ) );
}
/*
 * extented functions for high-quality graphics
 */
void _rectangle( double left, double top, double right, double bottom )
{
  rectangle( left, top, right, bottom );
}
