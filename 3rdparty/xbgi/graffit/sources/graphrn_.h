/*
 * n-dimensional graphic interface in graffit library < graphrn_.h >
 *
 * n-Dimensional Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHRN__H_
#define _GRAPHRN__H_
#include <math.h>
#include <graphr3_.h>

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
   n次元視点変換(n-dimensional Rotation Port Translation)パッケージ

   これはn次元座標系を3次元座標系に変換し、3次元変換パッケージ
   を内部で呼び出すことによってディスプレイにn次元空間を平行透視表示するための
   パッケージです。物体に遠近感を持たせた透視変換を行いたいときは、
   このパッケージではなく透視変換パッケージgraphpn_.hを使う必要があります。

   このパッケージの目的は任意のn次元空間をディスプレイに投影することです。
   任意のn次元空間であるのでそれは正立方体である必要はありません。
   ここで実数のn次元空間をn超回転領域(n-Hyper Rotation Port)と呼びます。
   このパッケージではこの回転領域を各軸成分で正規化し更に回転変換を施して
   3次元座標系に超立方体として投影します。
   例えばディスプレイ上に仮想の超直方体(X:0..1,Y:0..2,Z:0..3,W:0..4)を描くには
   以下のようにします。

   double xf[4] = { 0, 0, 0, 0 };
   double xt[4] = { 1, 2, 3, 4 };
   setviewport_(0, 100, 0, 100, !0);   画面の100x100の領域を使う
   hypermagnify_(1.5);                 投影するときの拡大率
   hyperrotationport_(4, xf, xt);      希望の回転領域を定義
   setrotation_(RAD(-15), RAD(20), 0); 回転角を指定(X,Y,Z軸)
   hyperrotate_(0, 3, RAD(-15));       回転角を指定(XW軸)
   hyperrotate_(1, 3, RAD(-30));       回転角を指定(YW軸)
   hyperrotate_(2, 3, RAD(+10));       回転角を指定(ZW軸)
   cubern_(4, xf, xt, !0);             回転領域と同じ直方体を描画

   この描画した超直方体を回転したい場合は hyperrotation_ を再度指定し、
   cubern_ を再描画することによって別の回転角の超直方体を描くことができます。
   ちなみにRADはデグリーをラジアンに変換するマクロです。
 */

struct hyperrotationporttype_ {
  double dim; /* n-dimensional rotation port */
  double *o;  /* region origin */
  double *m;  /* region magnify */
  double mag; /* rotation port magnify */
  double **r; /* rotation matrix */
  double **a; /* work matrix to rotate */
  double *x;  /* work to translate */
  double *y;  /* work to translate */
  double *z;  /* work to translate */
};

extern struct hyperrotationporttype_ __HR;

/*
   [名前]
   rntov --- n次元座標から投影された座標を求める関数

   [形式]
   rntov(src, dst)
   double *src; n次元座標(ベクトルで格納)
   double *dst; n次元座標(ベクトルで格納)

   [説明]
   hypermagnify_ や hyperrotate_ で指定された回転角で、
   n次元座標から回転されたn次元座標の座標をベクトルで求めます。
 */
extern void rntov(double *xsrc, double *xdst);

/*
   [名前]
   linern_      --- n次元視点変換用 line     直線描画関数
   linetorn_    --- n次元視点変換用 lineto   相対位置への直線描画関数
   putpixelrn_  --- n次元視点変換用 putpixel 点描画関数
   movetorn_    --- n次元視点変換用 moveto   カレントポイント移動関数
   outtextxyrn_ --- n次元視点変換用 outtext  テキスト出力関数

   [形式]
   linern_     (x1,x2)
   linetorn_   (x)
   putpixelrn_ (x,c)
   movetorn_   (x)
   outtextxyrn_(x,str)
   double *x1; n次元座標(ベクトルで格納)
   double *x2; n次元座標(ベクトルで格納)
   double *x;  n次元座標(ベクトルで格納)
   int c;      パレット番号
   char *str;  文字列
  
   [説明]
   これらの描画手続きはn次元視点変換用の関数です。
   n次元の超空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元透視変換パッケージ graphr3_.h 
 */
extern void linern_(double *x1, double *x2);
extern void linetorn_(double *x);
extern void putpixelrn_(double *x, int c);
extern void putpointrn_(double *x);
extern void movetorn_(double *x);
extern void outtextxyrn_(double *x, char *str);

/*
   [名前]
   hyperrotationport_ --- n次元透視視点変換用、座標定義域指定ルーチン

   [形式]
   hyperrotationport_(xf, xt)
   double *xf; 点1(ベクトルで格納)
   double *xt; 点2(ベクトルで格納)

   [説明]
   点1と点2を囲む超立方体をn次元透視視点変換する領域とします。
 */
extern void hyperrotationport_(int dim, double *xf, double *xt);

/*
   [名前]
   hypermagnify_ --- n次元透視視点変換用、拡大率指定ルーチン
  
   [形式]
   hypermagnify_(nhm)
   double nhm; 拡大率
  
   [説明]
   n次元の物体の描画を3次元に透視投影するときの拡大率を指定します。
   nhm = 1.0 のときが平行投影となりますが、三角関数の特性上
   実際にディスプレイに描画されたときに小さい感じがありますので、
   nhm = 1.5 ぐらいがちょうどいいでしょう。
 */
extern void hypermagnify_(double nhm);

/*
   [名前]
   hyperrotation_ --- n次元透視視点変換用、投影角指定ルーチン

   [形式]
   hyperrotation_(n, fa, ta, angle);
   int n;         回転の数
   int *fa, *ta;  回転軸の次元添字(faからtaへの回転)のリスト
   double *angle; 回転角のリスト

   [説明]
   n次元の物体の描画を3次元に透視投影するときの投影角を指定します。
 */
extern void hyperrotation_(int n, int *fx, int *tx, double *angle);

/*
   [名前]
   hyperrotate_ --- n次元透視視点変換用、任意軸回転ルーチン

   [形式]
   hyperrotation_(fa, ta, angle);
   int fa, ta;   回転軸の次元添字(faからtaへの回転)
   double angle; 回転角

   [説明]
   n次元の物体の描画を3次元に透視投影するときの回転角を指定します。
   カレントの投影角から指定された角度だけ回転します。
 */
extern void hyperrotate_(int fa, int ta, double angle);

/*
   [名前]
   cubern_ --- n次元視点変換用 cube 直方体の描画

   [形式]
   cubern_(xf, xt, flg)
   double xf; 点1(ベクトルで格納)
   double xt; 点2(ベクトルで格納)
   int flg;   !0の場合は線分をカラー表示

   [説明]
   n次元の超空間に点1と点2を囲む超立方体をn次元視点変換で描画します。
 */
extern void cubern_(double *xf, double *xt, int flg);

/*
   [名前]
   linesrn_     --- n次元視点変換用 lines     複数の直線描画関数
   putpixelsrn_ --- n次元視点変換用 putpixels 複数の点描画関数

   [形式]
   linesrn_    (np, rnpoints)
   putpixelsrn_(np, rnpoints, c)
   int np;            指定する座標の数
   double **rnpoints; n次元座標群のベクトル列
   int c;             パレット番号

   [説明]
   n次元空間の直線や点を指定された数だけまとめて描画します。
   double型の行列 rnpoints にはn次元座標群を
   rnpoints[0..np-1][0..n-1] で格納して下さい。
 */
extern void linesrn_(int np, double **rnpoints);
extern void putpixelsrn_(int np, double **rnpoints, int c);
extern void putpointsrn_(int np, double **rnpoints);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif 
