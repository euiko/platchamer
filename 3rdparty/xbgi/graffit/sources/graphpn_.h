/*
 * n-dimensional perspective graphic interface in graffit < graphpn_.h >
 *
 * n-Dimensional Perspective Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHPN__H_
#define _GRAPHPN__H_
#include <math.h>
#include <graphp3_.h>
#include <graphrn_.h>

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
   n次元透視変換(n-dimentinal Perspective Translation)パッケージ
  
   これはn次元座標系を3次元座標系に変換し、3次元透視変換パッケージ
   を内部で呼び出すことによってディスプレイにn次元空間を遠近感表示するための
   パッケージです。
   このパッケージはn次元視点変換パッケージ(graphrn_.h)上で動作します。
   さらにこれらを混在して使用できるので、インタラクティブに視点変換、透視変換
   を切り替えることも可能です。

   観察者の視点距離を指定するにはsetdistance_(d)を使います。
   距離dの値は正の実数です。負の値を指定すると縦横が反転されてしまいます。
   また距離dが零であることは視点と物体が同一座標にあることになり、
   数値計算上ではオーバーフローになってしまうので注意してください。

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
   cubepn_(4, xf, xt, !0);             回転領域と同じ直方体を描画

   この描画した超直方体を回転したい場合は nhyperrotation_ を再度指定し、
   cubepn_ を再描画することによって別の回転角の超直方体を描くことができます。
   ちなみにRADはデグリーをラジアンに変換するマクロです。
 */

/*
   [名前]
   linepn_      --- n次元透視変換用 line     直線描画関数
   linetopn_    --- n次元透視変換用 lineto   相対位置への直線描画関数
   putpixelpn_  --- n次元透視変換用 putpixel 点描画関数
   movetopn_    --- n次元透視変換用 moveto   カレントポイント移動関数
   outtextxypn_ --- n次元透視変換用 outtext  テキスト出力関数

   [形式]
   linepn_     (x1,x2)
   linetopn_   (x)
   putpixelpn_ (x,c)
   movetopn_   (x)
   outtextxypn_(x,str)
   double *x1; n次元座標(ベクトルで格納)
   double *x2; n次元座標(ベクトルで格納)
   double *x;  n次元座標(ベクトルで格納)
   int c;      パレット番号
   char *str;  文字列

   [説明]
   これらの描画手続きはn次元透視変換用の関数です。
   n次元の超空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元透視変換パッケージ graphr3_.h 
 */
extern void linepn_(double *x1, double *x2);
extern void linetopn_(double *x);
extern void putpixelpn_(double *x, int c);
extern void putpointpn_(double *x);
extern void movetopn_(double *x);
extern void outtextxypn_(double *x, char *str);

/*
   [名前]
   cubepn_ --- n次元透視変換用 cube 直方体の描画

   [形式]
   cubepn_(xf, xt, flg)
   double xf; 点1(ベクトルで格納)
   double xt; 点2(ベクトルで格納)
   int flg;   !0の場合は線分をカラー表示

   [説明]
   n次元の超空間に点1と点2を囲む超立方体をn次元透視変換で描画します。
 */
extern void cubepn_(double *xf, double *xt, int flg);

/*
   [名前]
   linespn_     --- n次元透視変換用 lines     複数の直線描画関数
   putpixelspn_ --- n次元透視変換用 putpixels 複数の点描画関数

   [形式]
   linespn_    (np, rnpoints)
   putpixelspn_(np, rnpoints, c)
   int np;            指定する座標の数
   double **rnpoints; n次元座標群のベクトル列
   int c;             パレット番号

   [説明]
   n次元空間の直線や点を指定された数だけまとめて描画します。
   double型の行列 rnpoints にはn次元座標群を
   rnpoints[0..np-1][0..n-1] で格納して下さい。
 */
extern void linespn_(int np, double **rnpoints);
extern void putpixelspn_(int np, double **rnpoints, int c);
extern void putpointspn_(int np, double **rnpoints);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif 
