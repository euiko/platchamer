/*
 * n-dimensional stereographic interface in graffit library < graphsn_.h >
 *
 * n-Dimensional Stereo Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHSN__H_
#define _GRAPHSN__H_
#include <math.h>
#include <graphs3_.h>
#include <graphpn_.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef RAD
#define RAD(d) (M_PI/180*(d))
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   n次元ステレオグラフィック(n-dimensional Stereo Graphics)パッケージ
  
   これはn次元座標系を3次元座標系に変換し、さらに3次元の回転座標系に
   2種類の透視変換を施し、いわゆる立体視を実現するためのパッケージです。

   例えばディスプレイ上に仮想の超直方体(X:0..1,Y:0..2,Z:0..3,W:0..4)を描くには
   以下のようにします。

   double xf[4] = { 0, 0, 0, 0 };
   double xt[4] = { 1, 2, 3, 4 };
   setviewport_(0, 100, 0, 100, !0);   画面の100x100の領域を使う
   nhypermagnify_(1.5);                投影するときの拡大率
   nhyperrotationport_(4, xf, xt);     希望の回転領域を定義
   setrotation_(RAD(-15), RAD(20), 0); 回転角を指定(X,Y,Z軸)
   nhyperrotate_(0, 3, RAD(-15));      回転角を指定(XW軸)
   nhyperrotate_(1, 3, RAD(-30));      回転角を指定(YW軸)
   nhyperrotate_(2, 3, RAD(+10));      回転角を指定(ZW軸)
   cubesn_(4, xf, xt, !0);             回転領域と同じ直方体を描画

   この描画した超直方体を回転したい場合は nhyperrotation_ を再度指定し、
   cubesn_ を再描画することによって別の回転角の超直方体を描くことができます。
   ちなみにRADはデグリーをラジアンに変換するマクロです。
 */

/*
   [名前]
   linesn_      --- n次元ステレオグラフ用 line     直線描画
   linetosn_    --- n次元ステレオグラフ用 lineto   相対位置への直線描画
   putpixelsn_  --- n次元ステレオグラフ用 putpixel 点描画
   movetosn_    --- n次元ステレオグラフ用 moveto   カレントポイント移動
   outtextxysn_ --- n次元ステレオグラフ用 outtext  テキスト出力
 
   [形式]
   linesn_     (x1,x2)
   linetosn_   (x)
   putpixelsn_ (x,c)
   movetosn_   (x)
   outtextxysn_(x,str)
   double *x1; n次元座標(ベクトルで格納)
   double *x2; n次元座標(ベクトルで格納)
   double *x;  n次元座標(ベクトルで格納)
   int c;      パレット番号
   char *str;  文字列
 
   [説明]
   これらの描画手続きはn次元ステレオグラフ用の関数です。
   n次元の超空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元透視変換パッケージ graphr3_.h 
   ・3次元透視変換パッケージ graphp3_.h 
   ・3次元ステレオグラフパッケージ graphs3_.h
 */
extern void linesn_(double *x1, double *x2);
extern void linetosn_(double *x);
extern void putpixelsn_(double *x, int c);
extern void putpointsn_(double *x);
extern void movetosn_(double *x);
extern void outtextxysn_(double *x, char *str);

/*
   [名前]
   cubesn_ --- n次元ステレオグラフ用 cube 直方体の描画
 
   [形式]
   cubesn_(xf, xt, flg)
   double xf; 点1(ベクトルで格納)
   double xt; 点2(ベクトルで格納)
   int flg;   !0の場合は線分をカラー表示

   [説明]
   n次元の超空間に点1と点2を囲む超立方体をn次元ステレオグラフで
   描画します。
 */
extern void cubesn_(double *xf, double *xt, int flg);

/*
   [名前]
   linessn_     --- n次元ステレオグラフ用 lines     複数の直線描画関数
   putpixelssn_ --- n次元ステレオグラフ用 putpixels 複数の点描画関数

   [形式]
   linessn_    (np, rnpoints)
   putpixelssn_(np, rnpoints, c)
   int np;            指定する座標の数
   double **rnpoints; n次元座標群のベクトル列
   int c;             パレット番号

   [説明]
   n次元空間の直線や点を指定された数だけまとめて描画します。
   double型の行列 rnpoints にはn次元座標群を
   rnpoints[0..np-1][0..n-1] で格納して下さい。
 */
extern void linessn_(int np, double **rnpoints);
extern void putpixelssn_(int np, double **rnpoints, int c);
extern void putpointssn_(int np, double **rnpoints);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif 
