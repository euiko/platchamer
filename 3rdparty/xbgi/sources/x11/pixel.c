/*
 * Source File < x11/pixel.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard function to get and put pixel color
 */
unsigned getpixel( int x, int y )
{
  XImage *image;
  unsigned char val;

  image = XGetImage( XBGIDisplay, XBGIWins[XBGI->apage],
                    Xx( x ), Xy( y ), 1, 1, AllPlanes, ZPixmap );
#if 0 /* USE_COLORTABLE */
  val = XBGIColortable[XGetPixel(image,0,0)];
#else /* Without Colortable since version 3.01 */
  {
    int p;
    val = 0;
    for ( p=0; p<XBGI->palette.size; p++ )
      if ( XGetPixel(image,0,0) == XBGIPixels[p] ) {
	val = p;
	break;
      }
  }
#endif
  XDestroyImage( image );
  return (unsigned)val;
}
void putpixel( int x, int y, int color )
{
  XSetForeground( XBGIDisplay, XBGIPixelGC,
                 XBGIPixels[minmax(0,color,XBGI->palette.size-1)] );
  XDrawPoint( XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC, Xx(x), Xy(y) );
}
void putpixels( int numpoints, int *points, int color )
{
  XPoint *xpoints;
  
  if (numpoints <= MAX_SAFE_XPOINTS) {
    xpoints = (XPoint *)malloc( numpoints * sizeof(XPoint) );
    XSetForeground( XBGIDisplay, XBGIPixelGC,
		   XBGIPixels[minmax(0,color,XBGI->palette.size-1)] );
    bgipoints2XPoints( numpoints, points, xpoints );
    XDrawPoints( XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		xpoints, numpoints, CoordModeOrigin );
    free( xpoints );
  }
  else {
    int j, d, m, im;

    xpoints = (XPoint *)malloc(MAX_SAFE_XPOINTS*sizeof(XPoint));
    XSetForeground( XBGIDisplay, XBGIPixelGC,
		   XBGIPixels[minmax(0,color,XBGI->palette.size-1)] );
    d = numpoints/MAX_SAFE_XPOINTS, m = numpoints%MAX_SAFE_XPOINTS;
    for (j=0; j<(m?(d+1):d); j++) {
      im = (j!=d)?MAX_SAFE_XPOINTS:m;
      bgipoints2XPoints( im, &points[2*MAX_SAFE_XPOINTS*j], xpoints );
      XDrawPoints( XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, im, CoordModeOrigin );
    }
    free( xpoints );
  }
}
/*
 * extented functions for high-quality graphics
 */
void _putpixels( int numpoints, double *points, int color )
{
  XPoint *xpoints;
  
  if (numpoints <= MAX_SAFE_XPOINTS) {
    xpoints = (XPoint *)malloc( numpoints * sizeof(XPoint) );
    XSetForeground( XBGIDisplay, XBGIPixelGC,
		   XBGIPixels[minmax(0,color,XBGI->palette.size-1)] );
    _bgipoints2XPoints( numpoints, points, xpoints );
    XDrawPoints( XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		xpoints, numpoints, CoordModeOrigin );
    free( xpoints );
  }
  else {
    int j, d, m, im;

    xpoints = (XPoint *)malloc(MAX_SAFE_XPOINTS*sizeof(XPoint));
    XSetForeground( XBGIDisplay, XBGIPixelGC,
		   XBGIPixels[minmax(0,color,XBGI->palette.size-1)] );
    d = numpoints/MAX_SAFE_XPOINTS, m = numpoints%MAX_SAFE_XPOINTS;
    for (j=0; j<(m?(d+1):d); j++) {
      im = (j!=d)?MAX_SAFE_XPOINTS:m;
      _bgipoints2XPoints( im, &points[2*MAX_SAFE_XPOINTS*j], xpoints );
      XDrawPoints( XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, im, CoordModeOrigin );
    }
    free( xpoints );
  }
}
unsigned _getpixel( double x, double y )
{
  return getpixel( x, y );
}
void _putpixel( double x, double y, int color )
{
  putpixel( x, y, color );
}
