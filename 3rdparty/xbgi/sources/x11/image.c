/*
 * Source File < x11/image.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions to get and put image
 */
unsigned imagesize( int left, int top, int right, int bottom )
{
  return (unsigned)(2 + (abs(right-left)+1)*(abs(bottom-top)+1));
}
void getimage( int left, int top, int right, int bottom, void *bitmap )
{
  XImage *image;
  int width, height, i, k;
  unsigned char *buffer = (unsigned char *)bitmap;

  width  = abs(right-left)+1;
  height = abs(bottom-top)+1;
  image = XGetImage( XBGIDisplay, XBGIWins[XBGI->apage],
                    min(Xx(left),Xx(right)), min(Xy(top),Xy(bottom)),
                    width, height, AllPlanes, ZPixmap );
  *buffer++ = width;
  *buffer++ = height;
  for ( i=0; i<height; i++ ){
    for ( k=0; k<width; k++ ){
#if 0 /* USE_COLORTABLE */
      *buffer++ = XBGIColortable[XGetPixel(image,k,i)];
#else /* Without Colortable since version 3.01 */
      {
	int p, val = 0;
	for ( p=0; p<XBGI->palette.size; p++ )
	  if ( XGetPixel(image,k,i) == XBGIPixels[p] ) {
	    val = p;
	    break;
	  }
	*buffer++ = val;
      }
#endif
    }
  }
  XDestroyImage( image );
}
void putimage( int left, int top, void *bitmap, int op )
{
  static int OP2GX[] = {
    GXcopy, GXxor, GXor, GXand, GXcopyInverted,
  };
  int i;
  int width, height;
  XImage *image;
  unsigned char *src, *dst, *buffer = (unsigned char *)bitmap;
  
  width  = buffer[0];
  height = buffer[1];
  src = buffer + 2;
  dst = (unsigned char*)malloc( width*height*sizeof(unsigned char) );
  for ( i=0; i<width*height; i++ )
    dst[i] = XBGIPixels[src[i]];
  XSetFunction( XBGIDisplay, XBGIImageGC, OP2GX[minmax(COPY_PUT,op,NOT_PUT)] );
  image = XCreateImage( XBGIDisplay, XBGIVisual, XBGIDepth, ZPixmap,
		       0, (char *)dst, width, height, 8, 0 );
  XPutImage( XBGIDisplay, XBGIWins[XBGI->apage], XBGIImageGC, image,
            0, 0, Xx(left), Xy(top), width, height );
  XDestroyImage( image );
#if 0 /* for segmentation fault, bug? */
  free( dst );
#endif
}
/*
 * extented functions for high-quality graphics
 */
void _getimage( double left, double top, double right, double bottom,
	       void *bitmap )
{
  getimage( left, top, right, bottom, bitmap );
}
void _putimage( double left, double top, void *bitmap, int op )
{
  putimage( left, top, bitmap, op );
}
