/*
 * Source File < x11/util.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"
#ifdef ENABLE_XPMLIB
#  include <X11/xpm.h>
#endif

/*
 * official enhanced function to save to x bitmap file
 */
int savemonographtofile( char *filename, char *option )
{
  Pixmap bitmap;
  GC gc;
  XImage *image;
  int i, k;
  int x, y, width, height;
  int status = !BitmapSuccess;

  if ( 0 <= XBGI->vpage && XBGI->vpage < XBGI->npage ){
    getgeometry( &x, &y, &width, &height );
    bitmap = XCreatePixmap( XBGIDisplay, XBGIWins[XBGI->vpage],
                           width, height, 1 );
    gc = XCreateGC( XBGIDisplay, bitmap, 0, 0 );
    XSetForeground( XBGIDisplay, gc, WhitePixel(XBGIDisplay,XBGIScreen) );
    XSetBackground( XBGIDisplay, gc, BlackPixel(XBGIDisplay,XBGIScreen) );
    XSetFillStyle( XBGIDisplay, gc, FillSolid );
    XFillRectangle( XBGIDisplay, bitmap, gc, 0, 0, width, height );
    XSetForeground( XBGIDisplay, gc, BlackPixel(XBGIDisplay,XBGIScreen) );
    XSetBackground( XBGIDisplay, gc, WhitePixel(XBGIDisplay,XBGIScreen) );
    image = XGetImage( XBGIDisplay, XBGIWins[XBGI->vpage],
                      0, 0, width, height, AllPlanes, ZPixmap );
    for ( i=0; i<height; i++ ){
      for ( k=0; k<width; k++ ){
#if 0 /* USE_COLORTABLE */
        if ( XBGIColortable[XGetPixel(image,k,i)] != XBGI->bkcolor )
          XDrawPoint( XBGIDisplay, bitmap, gc, k, i );
#else /* Without Colortable since version 3.01 */
        if ( XGetPixel(image,k,i) != XBGIPixels[XBGI->bkcolor] )
          XDrawPoint( XBGIDisplay, bitmap, gc, k, i );
#endif
      }
    }
    XDestroyImage( image );
    status = XWriteBitmapFile( XBGIDisplay, filename, bitmap,
                              width, height, 0, 0 );
    XFreeGC( XBGIDisplay, gc );
    XFreePixmap( XBGIDisplay, bitmap );
  }
  return status == BitmapSuccess;
}
/*
 * official enhanced function to save to x pixmap file
 */
int savegraphtofile( char *filename, char *option )
{
  XImage *image;
  int x, y, width, height;
  int status = !BitmapSuccess;

#ifdef ENABLE_XPMLIB
  if ( 0 <= XBGI->vpage && XBGI->vpage < XBGI->npage ){
    XpmAttributes att; /* XpmAttributes is used since version 3.02 */

    att.valuemask = XpmColormap;
    att.colormap = XBGIColormap;
    getgeometry( &x, &y, &width, &height );
    image = XGetImage( XBGIDisplay, XBGIWins[XBGI->vpage],
                      0, 0, width, height, AllPlanes, ZPixmap );
    status = XpmWriteFileFromImage( XBGIDisplay, filename, image, NULL, &att );
    XDestroyImage( image );
  }
#else
  status = !BitmapSuccess;
#endif
  return status == BitmapSuccess;
}
/*
 * official enhanced function to save drawing procedure by postscript
 */
int saveexposetofile( char *filename, char *option )
{
  int status = 0;
#ifndef BUILD_STANDALONE
  char bgisetstr[1024], *ptr;
  xbgi *xptr = XBGI;
  int (*expose)(void) = XBGI->inherit_procedures->expose_handler;
  int x, y, width, height;
  int gd = PS, gm = PSCOLOR, i;
  struct palettetype p;
	  
  /* start postscript graphics system */
  getpalette( &p );
  getgeometry( &x, &y, &width, &height );
  sprintf( bgisetstr, "%s -geometry %1dx%1d -psfile %s ",
	  (option!=NULL)?option:"", width, height, filename );
  switch ( XBGI->gmode ){
  case X11MONO: default:
    strcat( bgisetstr, "-gd PS -gm PSMONO " );
    break;
  case X11SGRAY:
  case X11GRAY: 
    strcat( bgisetstr, "-gd PS -gm PSGRAY " );
    break;
  case X11SCOLOR:
  case X11COLOR:
  case X11TCOLOR:
  case X11DCOLOR:
    strcat( bgisetstr, "-gd PS -gm PSCOLOR " );
    break;
  }
  if ( (ptr=strstr(filename,".eps")) == NULL )
    strcat( bgisetstr, "-eps- " );
  else
    strcat( bgisetstr, "-eps " );
  initgraph( &gd, &gm, bgisetstr );
  ps_setmaxcolor( xptr->ncolor );
  for ( i=0; i<xptr->ncolor; i++ )
    ps__setrgbpalette( i,
		      XBGIsRGB(xptr)[i].red,
		      XBGIsRGB(xptr)[i].green,
		      XBGIsRGB(xptr)[i].blue );
  ps_setallpalette( &p );
  ps_setcolor( getcolor() );
  ps_setbkcolor( getbkcolor() );
  status = expose();
  closegraph();
  XBGI = xptr;
#else
  NotSupported( "saveexposetofile() is supported only in concatenated lib" );
#endif
  return status;
}
