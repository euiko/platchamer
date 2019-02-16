/*
 * 2-dimensional logarithmic graphic interface in graffit < graphl2_.h >
 *
 * Logarithmic Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHL2__H_
#define _GRAPHL2__H_
#include <graphr2_.h>
#include <outtext_.h>

/*
   [名前]
   lxtox --- LOG-X座標からX座標を求めるマクロ
   lytoy --- LOG-Y座標からY座標を求めるマクロ

   [形式]
   lxtox(x)
   lytoy(y)
   double x, y; LOG座標

   [説明]
   例えば、setwindow_(1E-10, 1E+5, 1E+10, 1E-5) としてから
   これらの変換マクロを使用するとワールド座標系をLOG座標とみなし、
   対応するワールド座標系の座標を返します。
 */
#define lxtox(x) (log((x)/__W.left)*\
		  (__W.right-__W.left)/log(__W.right/__W.left)+__W.left)
#define lytoy(y) (log((y)/__W.bottom)*\
		  (__W.top-__W.bottom)/log(__W.top/__W.bottom)+__W.bottom)

/*
   [名前]
   linel2_      --- LOG2座標変換用 line     直線描画マクロ
   linetol2_    --- LOG2座標変換用 lineto   相対位置への直線描画マクロ
   putpixell2_  --- LOG2座標変換用 putpixel 点描画マクロ
   movetol2_    --- LOG2座標変換用 moveto   カレントポイント移動マクロ
   outtextxyl2_ --- LOG2座標変換用 outtext  テキスト出力マクロ
  
   [形式]
   linel2_     (x1,y1, x2,y2)
   linetol2_   (x,y)
   putpixell2_ (x,y,c)
   movetol2_   (x,y)
   outtextxyl2_(x,y,str)
   double x1,y1; LOG2座標
   double x2,y2; LOG2座標
   double x,y;   LOG2座標
   int c;        パレット番号
   char *str;    文字列
  
   [説明]
   これらの描画手続きはLOG2座標変換用のマクロです。
   LOG2グラフなどを簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・2次元ウィンドウ変換パッケージ graphr2_.h 
 */
#define linel2_(x0,y0,x1,y1) \
        line_(lxtox(x0),lytoy(y0),lxtox(x1),lytoy(y1))
#define linetol2_(x,y) \
        lineto_(lxtox(x),lytoy(y))
#define rectanglel2_(x0,y0,x1,y1) \
        rectangle_(lxtox(x0),lytoy(y0),lxtox(x1),lytoy(y1))
#define barl2_(x0,y0,x1,y1) \
        bar_(lxtox(x0),lytoy(y0),lxtox(x1),lytoy(y1))
#define putpixell2_(x,y,c) \
        putpixel_(lxtox(x),lytoy(y),c)
#define putpointl2_(x,y) \
        putpoint_(lxtox(x),lytoy(y))
#define movetol2_(x,y) \
        moveto_(lxtox(x),lytoy(y))
#define outtextxyl2_(x,y,s) \
        outtextxy_(lxtox(x),lytoy(y),s)

/*
   [名前]
   linelx_      --- LOGX座標変換用 line     直線描画マクロ
   linetolx_    --- LOGX座標変換用 lineto   相対位置への直線描画マクロ
   putpixellx_  --- LOGX座標変換用 putpixel 点描画マクロ
   movetolx_    --- LOGX座標変換用 moveto   カレントポイント移動マクロ
   outtextxylx_ --- LOGX座標変換用 outtext  テキスト出力マクロ

   [形式]
   linelx_     (x1,y1, x2,y2)
   linetolx_   (x,y)
   putpixellx_ (x,y,c)
   movetolx_   (x,y)
   outtextxylx_(x,y,str)
   double x1,y1; LOGX座標
   double x2,y2; LOGX座標
   double x,y;   LOGX座標
   int c;        パレット番号
   char *str;    文字列
  
   [説明]
   これらの描画手続きはLOGX座標変換用のマクロです。
   LOGXグラフなどを簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・2次元ウィンドウ変換パッケージ graphr2_.h 
 */
#define linelx_(x0,y0,x1,y1) \
        line_(lxtox(x0),y0,lxtox(x1),y1)
#define linetolx_(x,y) \
        lineto_(lxtox(x),y)
#define rectanglelx_(x0,y0,x1,y1) \
        rectangle_(lxtox(x0),y0,lxtox(x1),y1)
#define barlx_(x0,y0,x1,y1) \
        bar_(lxtox(x0),y0,lxtox(x1),y1)
#define putpixellx_(x,y,c) \
        putpixel_(lxtox(x),y,c)
#define putpointlx_(x,y) \
        putpoint_(lxtox(x),y)
#define movetolx_(x,y) \
        moveto_(lxtox(x),y)
#define outtextxylx_(x,y,s) \
        outtextxy_(lxtox(x),y,s)

/*
   [名前]
   linely_      --- LOGY座標変換用 line     直線描画マクロ
   linetoly_    --- LOGY座標変換用 lineto   相対位置への直線描画マクロ
   putpixelly_  --- LOGY座標変換用 putpixel 点描画マクロ
   movetoly_    --- LOGY座標変換用 moveto   カレントポイント移動マクロ
   outtextxyly_ --- LOGY座標変換用 outtext  テキスト出力マクロ
  
   [形式]
   linely_     (x1,y1, x2,y2)
   linetoly_   (x,y)
   putpixelly_ (x,y,c)
   movetoly_   (x,y)
   outtextxyly_(x,y,str)
   double x1,y1; LOGY座標
   double x2,y2; LOGY座標
   double x,y;   LOGY座標
   int c;        パレット番号
   char *str;    文字列
  
   [説明]
   これらの描画手続きはLOGY座標変換用のマクロです。
   LOGYグラフなどを簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・2次元ウィンドウ変換パッケージ graphr2_.h 
 */
#define linely_(x0,y0,x1,y1) \
        line_(x0,lytoy(y0),x1,lytoy(y1))
#define linetoly_(x,y) \
        lineto_(x,lytoy(y))
#define rectanglely_(x0,y0,x1,y1) \
        rectangle_(x0,lytoy(y0),x1,lytoy(y1))
#define barly_(x0,y0,x1,y1) \
        bar_(x0,lytoy(y0),x1,lytoy(y1))
#define putpixelly_(x,y,c) \
        putpixel_(x,lytoy(y),c)
#define putpointly_(x,y) \
        putpoint_(x,lytoy(y))
#define movetoly_(x,y) \
        moveto_(x,lytoy(y))
#define outtextxyly_(x,y,s) \
        outtextxy_(x,lytoy(y),s)

#if 0
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif

#endif
