/*
 * Source File < x11/text.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard function to out text on graphics
 */
void outtextxy( int x, int y, char *textstring );
void outtext( char *textstring )
{
  outtextxy( XBGI->cp.x, XBGI->cp.y, textstring );
  moverel( (XBGI->textset.direction==HORIZ_DIR)?textwidth(textstring):0,
          (XBGI->textset.direction==VERT_DIR)?textwidth(textstring):0 );
}
void outtextxy( int x, int y, char *textstring )
{
  int font = XBGI->textset.font;
  int dir  = XBGI->textset.direction;
  int size = XBGI->textset.charsize;
  int width = textwidth(textstring), height = textheight(textstring);
  int i, k;
  Pixmap pixmap;
  XImage *image;
  GC gc;
  
  switch ( dir ){
  case VERT_DIR:
    /*
     * difficult vertical direction
     */
    pixmap = XCreatePixmap( XBGIDisplay, XBGIWins[XBGI->apage],
                           width, height, XBGIDepth );
    gc = XCreateGC( XBGIDisplay, pixmap, 0, 0 );
    XSetForeground( XBGIDisplay, gc, XBGIPixels[XBGI->bkcolor] );
    XFillRectangle( XBGIDisplay, pixmap, gc, 0, 0, width, height );
    XSetForeground( XBGIDisplay, gc, XBGIPixels[XBGI->color] );
    if ( !XBGI->l10n || font != DEFAULT_FONT ){
      if ( XBGIStrokeFonts[font][size] != NULL )
        XSetFont( XBGIDisplay, gc, XBGIStrokeFonts[font][size]->fid );
      XDrawString( XBGIDisplay, pixmap, gc,
                  0, TextAscent(XBGIStrokeFonts[font][size]),
                  textstring, strlen(textstring) );
    }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
      if ( XBGIStrokeFonts[font][size] != NULL )
        XSetFont( XBGIDisplay, gc, XBGIStrokeFonts[font][size]->fid );
      XDrawString( XBGIDisplay, pixmap, gc,
                  0, TextAscent(XBGIStrokeFonts[font][size]),
                  textstring, strlen(textstring) );
#endif
#ifdef ENABLE_BILINGUAL
      XDrawBiString( XBGIDisplay, pixmap, gc,
                    XBGIStrokeFonts[font][size], XBGIBiFonts[size], 0,
                    max( TextAscent(XBGIStrokeFonts[font][size]),
                        TextAscent(XBGIBiFonts[size]) ),
                    textstring, strlen(textstring) );
#endif
#ifdef ENABLE_MULTILINGUAL
      if ( XBGIMultiFonts[size] ){
        XmbDrawString( XBGIDisplay, pixmap, XBGIMultiFonts[size], gc, 0, 0,
                      textstring, strlen(textstring) );
      }else{
        XDrawString( XBGIDisplay, pixmap, gc,
                    0, 0, textstring, strlen(textstring) );
      }
#endif
    }
    switch( XBGI->textset.horiz ){
    case LEFT_TEXT:
      break;
    case CENTER_TEXT:
      x -= height/2;
      break;
    case RIGHT_TEXT:
      x -= height;
      break;
    }
    switch( XBGI->textset.vert ){
    case TOP_TEXT:
      break;
    case CENTER_TEXT:
      y -= width/2;
      break;
    case BOTTOM_TEXT:
      y -= width;
      break;
    }
    image = XGetImage( XBGIDisplay, pixmap, 0, 0, width, height,
                      AllPlanes, ZPixmap );
    for ( i=0; i<height; i++ ){
      for ( k=0; k<width; k++ ){
#if 0 /* USE_COLORTABLE */
        if ( XBGIColortable[XGetPixel(image,k,i)] == XBGI->color )
          XDrawPoint( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                     x + i, y + ( width - k ) );
#else /* Without Colortable since version 3.01 */
        if ( XGetPixel(image,k,i) == XBGIPixels[XBGI->color] )
          XDrawPoint( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                     x + i, y + ( width - k ) );
#endif
      }
    }
    XDestroyImage( image );
    XFreeGC( XBGIDisplay, gc );
    XFreePixmap( XBGIDisplay, pixmap );
    break;
  case HORIZ_DIR:
    /*
     * horizontal direction
     */
    switch( XBGI->textset.horiz ){
    case LEFT_TEXT:
      break;
    case CENTER_TEXT:
      x -= width/2;
      break;
    case RIGHT_TEXT:
      x -= width;
      break;
    }
    if ( !XBGI->l10n || font != DEFAULT_FONT ){
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += TextAscent( XBGIStrokeFonts[font][size] );
        break;
      case CENTER_TEXT:
        y += height/2;
        break;
      case BOTTOM_TEXT:
        y -= TextDescent( XBGIStrokeFonts[font][size] );
        break;
      }
    }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += TextAscent( XBGIStrokeFonts[font][size] );
        break;
      case CENTER_TEXT:
        y += height/2;
        break;
      case BOTTOM_TEXT:
        y -= TextDescent( XBGIStrokeFonts[font][size] );
        break;
      }
#endif
#ifdef ENABLE_BILINGUAL
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += max( TextAscent( XBGIStrokeFonts[font][size] ),
                 TextAscent( XBGIBiFonts[size] ) );
        break;
      case CENTER_TEXT:
        y += height/2;
        break;
      case BOTTOM_TEXT:
        y -= max( TextDescent( XBGIStrokeFonts[font][size] ),
                 TextDescent( XBGIBiFonts[size] ) );
        break;
      }
#endif
#ifdef ENABLE_MULTILINGUAL
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += height;
        break;
      case CENTER_TEXT:
        y -= height/2;
        break;
      case BOTTOM_TEXT:
        y -= height;
        break;
      }
#endif
    }
    if ( !XBGI->l10n || font != DEFAULT_FONT ){
      XDrawString( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                  Xx( x ), Xy( y ), textstring, strlen(textstring) );
    }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
      XDrawString( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                  Xx( x ), Xy( y ), textstring, strlen(textstring) );
#endif
#ifdef ENABLE_BILINGUAL
      XDrawBiString( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                    XBGIStrokeFonts[font][size], XBGIBiFonts[size],
                    Xx( x ), Xy( y ),
                    textstring, strlen(textstring) );
#endif
#ifdef ENABLE_MULTILINGUAL
      if ( XBGIMultiFonts[size] ){
        XmbDrawString( XBGIDisplay, XBGIWins[XBGI->apage],
                      XBGIMultiFonts[size], XBGIDrawGC,
                      Xx( x ), Xy( y ), textstring, strlen(textstring) );
      }else{
        XDrawString( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
                    Xx( x ), Xy( y ),
                    textstring, strlen(textstring) );
      }
#endif
    }
    break;
  }
}
/*
 * extented functions for high-quality graphics
 */
void _outtextxy( double x, double y, char *textstring )
{
  outtextxy( x, y, textstring );
}
