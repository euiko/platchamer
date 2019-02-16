/*
 * Source File < x11/line.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * official enhanced functions to draw lines
 */
void lines( int numpoints, int *points )
{
  XPoint *xpoints;
  
  if (numpoints <= MAX_SAFE_XPOINTS) {
    xpoints = (XPoint *)malloc( numpoints * sizeof(XPoint) );
    bgipoints2XPoints( numpoints, points, xpoints );
    XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
	       xpoints, numpoints, CoordModeOrigin );
    free( xpoints );
  }
  else {
    int j, d, m, im;

    xpoints = (XPoint *)malloc((MAX_SAFE_XPOINTS+1)*sizeof(XPoint));
    d = numpoints/MAX_SAFE_XPOINTS, m = numpoints%MAX_SAFE_XPOINTS;
    for (j=0; j<(m?(d+1):d); j++) {
      im = (j!=d)?MAX_SAFE_XPOINTS:m;
      if (j!=0) im++;
      bgipoints2XPoints( im, &points[2*MAX_SAFE_XPOINTS*j], xpoints );
      XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, im, CoordModeOrigin );
    }
    free( xpoints );
  }
}
/*
 * standard functions to draw line
 */
void line( int x1, int y1, int x2, int y2 )
{
  XDrawLine( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
            Xx( x1 ), Xy( y1 ), Xx( x2 ), Xy( y2 ) );
}
void linerel( int dx, int dy )
{
  line( XBGI->cp.x, XBGI->cp.y, XBGI->cp.x + dx, XBGI->cp.y + dy );
  XBGI->cp.x += dx;
  XBGI->cp.y += dy;
}
void lineto( int x, int y )
{
  line( XBGI->cp.x, XBGI->cp.y, x, y );
  XBGI->cp.x = x;
  XBGI->cp.y = y;
}
/*
 * extented functions for high-quality graphics
 */
void _lines( int numpoints, double *points )
{
  XPoint *xpoints;
  
  if (numpoints <= MAX_SAFE_XPOINTS) {
    xpoints = (XPoint *)malloc( numpoints * sizeof(XPoint) );
    _bgipoints2XPoints( numpoints, points, xpoints );
    XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
	       xpoints, numpoints, CoordModeOrigin );
    free( xpoints );
  }
  else {
    int j, d, m, im;

    xpoints = (XPoint *)malloc((MAX_SAFE_XPOINTS+1)*sizeof(XPoint));
    d = numpoints/MAX_SAFE_XPOINTS, m = numpoints%MAX_SAFE_XPOINTS;
    for (j=0; j<(m?(d+1):d); j++) {
      im = (j!=d)?MAX_SAFE_XPOINTS:m;
      if (j!=0) im++;
      _bgipoints2XPoints( im, &points[2*MAX_SAFE_XPOINTS*j], xpoints );
      XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, im, CoordModeOrigin );
    }
    free( xpoints );
  }
}
void _line( double x1, double y1, double x2, double y2 )
{
  line( x1, y1, x2, y2 );
}
void _linerel( double dx, double dy )
{
  line( XBGI->cp.x, XBGI->cp.y, XBGI->cp.x + dx, XBGI->cp.y + dy );
  XBGI->cp.x += dx;
  XBGI->cp.y += dy;
}
void _lineto( double x, double y )
{
  line( XBGI->cp.x, XBGI->cp.y, x, y );
  XBGI->cp.x = x;
  XBGI->cp.y = y;
}
