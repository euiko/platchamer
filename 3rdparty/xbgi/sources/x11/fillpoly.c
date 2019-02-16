/*
 * Source File < x11/fillpoly.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard function to fill polygon
 */
void fillpoly( int numpoints, int *polypoints )
{
  XPoint *xpoints;
  
  if (numpoints <= MAX_SAFE_XPOINTS) {
    xpoints = (XPoint *)malloc( numpoints * sizeof(XPoint) );
    bgipoints2XPoints( numpoints, polypoints, xpoints );
    XFillPolygon( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
		 xpoints, numpoints, Complex, CoordModeOrigin );
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
      bgipoints2XPoints( im, &polypoints[2*MAX_SAFE_XPOINTS*j], xpoints );
      XFillPolygon( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
		   xpoints, im, Complex, CoordModeOrigin );
      XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, im, CoordModeOrigin );
    }
    free( xpoints );
  }
}
/*
 * extented functions for high-quality graphics
 */
void _fillpoly( int numpoints, double *polypoints )
{
  XPoint *xpoints;
  
  if (numpoints <= MAX_SAFE_XPOINTS) {
    xpoints = (XPoint *)malloc( numpoints * sizeof(XPoint) );
    _bgipoints2XPoints( numpoints, polypoints, xpoints );
    XFillPolygon( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
		 xpoints, numpoints, Complex, CoordModeOrigin );
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
      _bgipoints2XPoints( im, &polypoints[2*MAX_SAFE_XPOINTS*j], xpoints );
      XFillPolygon( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
		   xpoints, im, Complex, CoordModeOrigin );
      XDrawLines( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, im, CoordModeOrigin );
    }
    free( xpoints );
  }
}
