/*
 * Source File < x11/fillrect.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions to fill rectangle
 */
void bar( int left, int top, int right, int bottom )
{
  XFillRectangle( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
                 min( Xx(left), Xx(right) ), min( Xy(top), Xy(bottom) ),
                 abs( right - left ) + 1, abs( bottom - top ) + 1 );
}
void bar3d( int left, int top, int right, int bottom, int depth, int topflag )
{
  int topheight = 0;
  XPoint xpoints[4];

  if ( topflag ) topheight = depth/2;
  xpoints[0].x = Xx( right );         xpoints[0].y = Xy( top );
  xpoints[1].x = Xx( right + depth ); xpoints[1].y = Xy( top - topheight );
  xpoints[2].x = Xx( left + depth );  xpoints[2].y = Xy( top - topheight );
  xpoints[3].x = Xx( left );          xpoints[3].y = Xy( top );
  XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
             xpoints, 4, CoordModeOrigin );
  xpoints[0].x = Xx( right );         xpoints[0].y = Xy( top );
  xpoints[1].x = Xx( right );         xpoints[1].y = Xy( bottom );
  xpoints[2].x = Xx( right + depth ); xpoints[2].y = Xy( bottom - topheight );
  xpoints[3].x = Xx( right + depth ); xpoints[3].y = Xy( top - topheight );
  XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
             xpoints, 4, CoordModeOrigin );
  XFillRectangle( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
                 min( Xx(left), Xx(right) ), min( Xy(top), Xy(bottom) ),
                 abs( right - left ) + 1, abs( bottom - top ) + 1 );
  XDrawRectangle( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                 min( Xx(left), Xx(right) ), min( Xy(top), Xy(bottom) ),
                 abs( right - left ), abs( bottom - top ) );
}
/*
 * extented functions for high-quality graphics
 */
void _bar( double left, double top, double right, double bottom )
{
  bar( left, top, right, bottom );
}
void _bar3d( double left, double top, double right, double bottom,
	    double depth, int topflag )
{
  bar3d( left, top, right, bottom, depth, topflag );
}
