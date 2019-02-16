/*
 * Source File < x11/arc.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions to draw arc
 */
void arc( int x, int y, int stangle, int endangle, int radius )
{
  XBGI->arcset.x        = x;
  XBGI->arcset.y        = y;
  XBGI->arcset.stangle  = stangle;
  XBGI->arcset.endangle = endangle;
  XBGI->arcset.xradius  = radius;
  XBGI->arcset.yradius  = radius;
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           64 * stangle, 64 * ( endangle - stangle ) );
}
void circle( int x, int y, int radius )
{
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           0, 64 * ( 360 - 0 ) );
}
void ellipse( int x, int y, int stangle, int endangle,
             int xradius, int yradius )
{
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - xradius ), Xy( y - yradius ), 2 * xradius, 2 * yradius,
           64 * stangle, 64 * ( endangle - stangle ) );
}
/*
 * extented functions for high-quality graphics
 */
void _arc( double x, double y, double stangle, double endangle,
	  double radius )
{
  XBGI->arcset.x        = x;
  XBGI->arcset.y        = y;
  XBGI->arcset.stangle  = stangle;
  XBGI->arcset.endangle = endangle;
  XBGI->arcset.xradius  = radius;
  XBGI->arcset.yradius  = radius;
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           64 * stangle, 64 * ( endangle - stangle ) );
}
void _circle( double x, double y, double radius )
{
  circle( x, y, radius );
}
void _ellipse( double x, double y, double stangle, double endangle,
	      double xradius, double yradius )
{
  ellipse( x, y, stangle, endangle, xradius, yradius );
}
