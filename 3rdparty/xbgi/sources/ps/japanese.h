/*
 * routines to analyse japanese code and draw PS 16 bit text < ps/japanese.h >
 *
 * 日本語コードを解析し、PSで16ビット文字列を出力するためのルーチン
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _JAPANESE_H_
#define _JAPANESE_H_
#include "ps_p.h"

/*
  // 文字列をコード判定しながら英数文字と16ビット文字コードを出力する関数 //
  void ps_xbgi_put_bi_string(
    char *string, int len // len は string のバッファ長 //
  );

  // 文字列をコード判定しながら英数文字と16ビット文字の幅を計算する関数 //
  int ps_xbgi_bi_text_width(
    char *string, int len // len は string のバッファ長 //
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
 * ps_xbgi_put_bi_string for japanese
 */
extern void ps_xbgi_put_bi_string(
#if NeedFunctionPrototypes
  char *__string, int __len
#endif
);

/*
 * ps_xbgi_bi_text_width for japanese
 */
extern int ps_xbgi_bi_text_width(
#if NeedFunctionPrototypes
  char *__string, int __len
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif









