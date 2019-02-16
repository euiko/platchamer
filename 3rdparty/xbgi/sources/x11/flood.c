/*
 * Source File < x11/flood.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard function to fill flood
 */
#define SCANBUF_SIZE 10000

#if 0 /* FLOODFILL_VERSION_SLOW */

void floodfill( int x, int y, int border )
{
  int s[SCANBUF_SIZE][2];
  int p, cx, cy, u, u2, d, d2, pu, pd;
  int minx, miny, maxx, maxy;
  int width, height;

  getgeometry( &cx, &cy, &width, &height );
  if ( XBGI->viewport.clip ){
    minx = XBGI->viewport.left;
    miny = XBGI->viewport.top;
    maxx = XBGI->viewport.right;
    maxy = XBGI->viewport.bottom;
  }else{
    minx = 0;
    miny = 0;
    maxx = width-1;
    maxy = height-1;
  }
  p = 1;
  s[p][0] = Xx(x);
  s[p][1] = Xy(y);
  while ( p > 0 ){
    cx = s[p][0];
    cy = s[p--][1];
    if ( getpixel( xX(cx), yX(cy) ) != border ){
      while ( getpixel( xX(cx), yX(cy) )!=border && cx>=minx ) cx--;
      cx++;
      u = 0;
      d = 0;
      while ( getpixel( xX(cx), yX(cy) )!=border && cx<=maxx ){
        putpixel( xX(cx), yX(cy), XBGI->fillset.color );
        u2 = u;
        if ( cy > miny ){
          pu = getpixel( xX(cx), yX(cy-1) );
          if ( pu == border || pu == XBGI->fillset.color )
            u = 0;
          else
            u = 1;
        }
        if ( u2==0 && u==1 ){
          p++; if ( p>=SCANBUF_SIZE ) goto exit;
          s[p][0] = cx;
          s[p][1] = cy - 1;
        }
        d2 = d;
        if ( cy < maxy ) {
          pd = getpixel( xX(cx), yX(cy+1) );
          if ( pd == border || pd == XBGI->fillset.color )
            d = 0;
          else
            d = 1;
        }
        if ( d2==0 && d==1 ){
          p++; if ( p>=SCANBUF_SIZE ) goto exit;
          s[p][0] = cx;
          s[p][1] = cy + 1;
        }
        cx++;
      }
    }
  }
 exit:
}

#else /* FLOODFILL_VERSION_FAST */

#define GETPIXEL(x,y) ((Xx(x)<0||width-1<Xx(x)||Xy(y)<0||height-1<Xy(y))?\
		       border:mem[Xx(x)][Xy(y)])
void floodfill( int x, int y, int border )
{
  int s[SCANBUF_SIZE][2];
  int p, cx, cy, u, u2, d, d2, pu, pd;
  int minx, miny, maxx, maxy;
  int width, height, i, k;
  XImage *image;
  unsigned char *data, **mem;

  getgeometry( &cx, &cy, &width, &height );
  mem = (unsigned char **)malloc(sizeof(char*)*width);
  if ( mem == NULL ){ XBGI->gerror = grNoFloodMem; return; }
  mem[0] = (unsigned char *)malloc(sizeof(char)*(width*height));
  if ( mem[0] == NULL ){ XBGI->gerror = grNoFloodMem; return; }
  for (i=1; i<width; i++)
    mem[i] = mem[i-1] + height;
  image = XGetImage( XBGIDisplay, XBGIWins[XBGI->apage],
                    0, 0, width, height, AllPlanes, ZPixmap );
  data = (unsigned char *)image->data;
  for ( i=0; i<height; i++ ){
    for ( k=0; k<width; k++ ){
#if 0 /* USE_COLORTABLE */
      mem[k][i] = XBGIColortable[XGetPixel(image,k,i)];
#else /* Without Colortable since version 3.01 */
      {
        int p, val = 0;
        for ( p=0; p<XBGI->palette.size; p++ )
          if ( XGetPixel(image,k,i) == XBGIPixels[p] ) {
            val = p;
            break;
          }
        mem[k][i] = val;
      }
#endif
    }
  }
  XDestroyImage( image );
  if ( XBGI->viewport.clip ){
    minx = XBGI->viewport.left;
    miny = XBGI->viewport.top;
    maxx = XBGI->viewport.right;
    maxy = XBGI->viewport.bottom;
  }else{
    minx = 0;
    miny = 0;
    maxx = width-1;
    maxy = height-1;
  }
  p = 1;
  s[p][0] = Xx(x);
  s[p][1] = Xy(y);
  while ( p > 0 ){
    cx = s[p][0];
    cy = s[p--][1];
    if ( GETPIXEL( xX(cx), yX(cy) ) != border ){
      while ( GETPIXEL( xX(cx), yX(cy) )!=border && cx>=minx ) cx--;
      cx++;
      u = 0;
      d = 0;
      while ( GETPIXEL( xX(cx), yX(cy) )!=border && cx<=maxx ){
        putpixel( xX(cx), yX(cy), XBGI->fillset.color );
#if 0 /* bug, before version 3.02 generic 19991022 */
	GETPIXEL( xX(cx), yX(cy) ) = XBGI->fillset.color;
#else /* since version 3.02 generic 19991022 */
	mem[cx][cy] = XBGI->fillset.color;
#endif
        u2 = u;
        if ( cy > miny ){
          pu = GETPIXEL( xX(cx), yX(cy-1) );
          if ( pu == border || pu == XBGI->fillset.color )
            u = 0;
          else
            u = 1;
        }
        if ( u2==0 && u==1 ){
          p++; if ( p>=SCANBUF_SIZE ) goto exit;
          s[p][0] = cx;
          s[p][1] = cy - 1;
        }
        d2 = d;
        if ( cy < maxy ) {
          pd = GETPIXEL( xX(cx), yX(cy+1) );
          if ( pd == border || pd == XBGI->fillset.color )
            d = 0;
          else
            d = 1;
        }
        if ( d2==0 && d==1 ){
          p++; if ( p>=SCANBUF_SIZE ) goto exit;
          s[p][0] = cx;
          s[p][1] = cy + 1;
        }
        cx++;
      }
    }
  }
 exit:
  free( mem[0] );
  free( mem );
}

#endif
/*
 * extented functions for high-quality graphics
 */
void _floodfill( double x, double y, int border )
{
  floodfill( x, y, border );
}
