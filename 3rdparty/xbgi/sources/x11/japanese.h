/*
 * routines to analyse japanese code and draw X 16 bit text < x11/japanese.h >
 *
 * 日本語コードを解析し、Xで16ビット文字列を出力するためのルーチン
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _JAPANESE_H_
#define _JAPANESE_H_
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
  // 文字列をコード判定しながら英数文字と16ビット文字を出力していく関数 //
  void XDrawBiString(
    Display *d, Drawable w, GC gc,
    XFontStruct *afs,              // 英数文字のフォント構造体 //
    XFontStruct *bfs,              // 16ビット文字のフォント構造体 //
    int x, int y,
    char *string, int len          // len は string のバッファ長 //
  );

  // 文字列をコード判定しながら英数文字と16ビット文字の幅を計算する関数 //
  int XBiTextWidth(
    XFontStruct *afs,              // 英数文字のフォント構造体 //
    XFontStruct *bfs,              // 16ビット文字のフォント構造体 //
    char *string, int len          // len は string のバッファ長 //
  );
 */

#ifndef NeedFunctionPrototypes
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define NeedFunctionPrototypes 1
#  else
#    define NeedFunctionPrototypes 0
#  endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
 * XDrawBiString for japanese
 */
extern void XDrawBiString(
#if NeedFunctionPrototypes
  Display *__d, Drawable __w, GC __gc,
  XFontStruct *__afs, XFontStruct *__bfs,
  int __x, int __y, char *__string, int __len
#endif
);

/*
 * XBiTextWidth for japanese
 */
extern int XBiTextWidth(
#if NeedFunctionPrototypes
  XFontStruct *__afs, XFontStruct *__bfs,
  char *__string, int __len
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif








