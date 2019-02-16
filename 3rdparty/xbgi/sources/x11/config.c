/*
 * Source File < x11/config.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions for configuration of graphics environment
 */
int getmaxx( void )
{
  Window root;
  int x, y, width, height, border, depth;
  
  if ( XBGI->apage == 0 )
    XGetGeometry( XBGIDisplay, XBGIRoot, &root,
                 &x, &y, &width, &height, &border, &depth );
  else
    XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
                 &x, &y, &width, &height, &border, &depth );
  return width-1;
}
int getmaxy( void )
{
  Window root;
  int x, y, width, height, border, depth;
  
  if ( XBGI->apage == 0 )
    XGetGeometry( XBGIDisplay, XBGIRoot, &root,
                 &x, &y, &width, &height, &border, &depth );
  else
    XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
                 &x, &y, &width, &height, &border, &depth );
  return height-1;
}
/*
 * official enhanced functions for configuration of graphics environment
 */
void setmaxx( int maxx )
{
  Window root;
  int i, x, y, width, height, border, depth;
  
  if ( maxx <= 0 ) return;
  if ( XBGI->apage == 0 ){
    XGetGeometry( XBGIDisplay, XBGIWins[0], &root, /* win[0] or root */
                 &x, &y, &width, &height, &border, &depth );
    XResizeWindow( XBGIDisplay, XBGIRoot, maxx+1, height );
    for ( i=0; i<XBGI->npage; i++ )
      XResizeWindow( XBGIDisplay, XBGIWins[i], maxx+1, height );
  }else{
    XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
                 &x, &y, &width, &height, &border, &depth );
    XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], maxx+1, height );
  }
}
void setmaxy( int maxy )
{
  Window root;
  int i, x, y, width, height, border, depth;

  if ( maxy <= 0 ) return;
  if ( XBGI->apage == 0 ){
    XGetGeometry( XBGIDisplay, XBGIWins[0], &root, /* win[0] or root */
                 &x, &y, &width, &height, &border, &depth );
    XResizeWindow( XBGIDisplay, XBGIRoot, width, maxy+1 );
    for ( i=0; i<XBGI->npage; i++ )
      XResizeWindow( XBGIDisplay, XBGIWins[i], width, maxy+1 );
  }else{
    XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
                 &x, &y, &width, &height, &border, &depth );
    XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], width, maxy+1 );
  }
}
void getsizexy( int *xsize, int *ysize )
{
  Window root;
  int x, y, width, height, border, depth;
  
  if ( XBGI->apage == 0 ){
    XGetGeometry( XBGIDisplay, XBGIRoot, &root,
                 &x, &y, &width, &height, &border, &depth );
  }else{
    XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
                 &x, &y, &width, &height, &border, &depth );
  }
  *xsize = width;
  *ysize = height;
}
void setsizexy( int xsize, int ysize )
{
  int i;
  
  if ( xsize <= 0 || ysize <= 0 ) return;
  if ( XBGI->apage == 0 ){
    for ( i=0; i<XBGI->npage; i++ )
      XResizeWindow( XBGIDisplay, XBGIWins[i], xsize, ysize );
    XResizeWindow( XBGIDisplay, XBGIRoot, xsize, ysize );
  }else{
    XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], xsize, ysize );
  }
}
void getgeometry( int *x, int *y, int *width, int *height )
{
  Window root;
  int border, depth;
  
  if ( XBGI->apage == 0 ){
    XGetGeometry( XBGIDisplay, XBGIRoot, &root,
		 x, y, width, height, &border, &depth );
  }else{
    XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
		 x, y, width, height, &border, &depth );
  }
}
void setgeometry( int x, int y, int width, int height )
{
  if ( XBGI->apage == 0 ){
    XResizeWindow( XBGIDisplay, XBGIRoot, width, height );
    XResizeWindow( XBGIDisplay, XBGIWins[0], width, height );
  }else{
    XMoveWindow( XBGIDisplay, XBGIWins[XBGI->apage], x, y );
    XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], width, height );
  }
}
void settitle( char *title )
{
  XStoreName( XBGIDisplay, XBGIRoot, title );
  XSetIconName( XBGIDisplay, XBGIRoot, title );
}
void seticonname( char *filename )
{
  XSetIconName( XBGIDisplay, XBGIRoot, filename );
}
int seticon( char *filename )
{
  Pixmap bm;
  unsigned int w, h;
  int xh, yh, status;
  
  status = XReadBitmapFile( XBGIDisplay, RootWindow(XBGIDisplay,XBGIScreen),
                           filename,
                           &w, &h, &bm, &xh, &yh );
  if ( status != BitmapSuccess ) return 0;
  status = XSetIconFromPixmap( XBGIDisplay, XBGIRoot, bm, w, h );
  XFreePixmap( XBGIDisplay, bm );
  return status;
}
void setbackingstore( int flg )
{
  XSetWindowAttributes att;

  if ( flg )
    att.backing_store = Always;
  else
    att.backing_store = NotUseful;
  XChangeWindowAttributes( XBGIDisplay, XBGIWins[XBGI->apage],
                          CWBackingStore, &att );
}








