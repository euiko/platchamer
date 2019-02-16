/*
 * routines to analyse japanese code and draw X 16 bit text < x11/japanese.c >
 *
 * 日本語コードを解析し、Xで16ビット文字列を出力するためのルーチン
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "jutil.h"
#include "japanese.h"

#define  ASCENT_CANNOT_FIND 14
#define DESCENT_CANNOT_FIND  2
#define   WIDTH_CANNOT_FIND  8
#define  HEIGHT_CANNOT_FIND (ASCENT_CANNOT_FIND+DESCENT_CANNOT_FIND)

#define TextHeight(fs)      ((fs!=NULL)?\
                             (fs->max_bounds.ascent+fs->max_bounds.descent):\
                             (ASCENT_CANNOT_FIND+DESCENT_CANNOT_FIND))
#define TextAscent(fs)      ((fs!=NULL)?\
                             (fs->max_bounds.ascent):\
                             (ASCENT_CANNOT_FIND))
#define TextDescent(fs)      ((fs!=NULL)?\
                              (fs->max_bounds.descent):\
                              (DESCENT_CANNOT_FIND))
#define TextWidth(fs,p,l)   ((fs!=NULL)?\
                             (XTextWidth(fs,p,l)):\
                             (WIDTH_CANNOT_FIND*l))
#define TextWidth16(fs,p,l) ((fs!=NULL)?\
                             (XTextWidth16(fs,p,l)):\
                             (WIDTH_CANNOT_FIND*2*l))

/*
 * XDrawBiString for japanese
 */
void XDrawBiString( Display *d, Drawable w, GC gc,
                   XFontStruct *afs, XFontStruct *bfs,
                   int x, int y, char *string, int len )
{
  unsigned char buf[2048], *ptr;
  XChar2b xchr;
  int ocode, code, c;
  unsigned jisc;

  ocode = jcode( string );
  str2jis( string, buf );
  if ( afs != NULL )
    XSetFont( d, gc, afs->fid );
  c = 0;
  ptr = buf;
  code = JCT_ANK;
  while ( *ptr != '\0' && c <= len ){
    if ( isjise(ptr) ){
      code = JCT_ANK;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else if ( isjiss(ptr) ){
      code = JCT_JIS;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else{
      if ( code==JCT_ANK ){
        if ( afs != NULL )
          XSetFont( d, gc, afs->fid );
        XDrawString( d, w, gc, x, y, ptr, 1 );
        x += TextWidth( afs, ptr, 1 );
        ptr++;
        c++;
      }else{
        jisc = s2code(ptr);
        xchr.byte1 = codec1(jisc);
        xchr.byte2 = codec2(jisc);
        if ( bfs != NULL )
          XSetFont( d, gc, bfs->fid );
        XDrawString16( d, w, gc, x, y, &xchr, 1 );
        x += TextWidth16( bfs, &xchr, 1 );
        ptr += 2;
        c += 2;
      }
    }
  }
}
/*
 * XBiTextWidth for japanese
 */
int XBiTextWidth( XFontStruct *afs, XFontStruct *bfs,
                 char *string, int len )
{
  unsigned char buf[2048], *ptr;
  XChar2b xchr;
  int ocode, code, c;
  unsigned jisc;
  int x = 0;

  ocode = jcode( string );
  str2jis( string, buf );
  c = 0;
  ptr = buf;
  code = JCT_ANK;
  while ( *ptr != '\0' && c <= len ){
    if ( isjise(ptr) ){
      code = JCT_ANK;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else if ( isjiss(ptr) ){
      code = JCT_JIS;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else{
      if ( code==JCT_ANK ){
        x += TextWidth( afs, ptr, 1 );
        ptr++;
        c++;
      }else{
        jisc = s2code(ptr);
        xchr.byte1 = codec1(jisc);
        xchr.byte2 = codec2(jisc);
        x += TextWidth16( bfs, &xchr, 1 );
        ptr += 2;
        c += 2;
      }
    }
  }
  return x;
}











