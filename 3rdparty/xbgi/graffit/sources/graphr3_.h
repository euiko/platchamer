/*
 * 3-dimensional graphic interface in graffit library < graphr3_.h >
 *
 * 3-dimensional Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHR3__H_
#define _GRAPHR3__H_
#include <math.h>
#include <graphr2_.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef RAD
#define RAD(d) (M_PI/180*(d))
#endif
#ifndef DEG
#define DEG(r) (180.0/M_PI*(r))
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   3次元視点変換(3-dimensional Rotation Port Translation)パッケージ
  
   これは3次元座標系をワールド座標系に変換し、ウィンドウ変換パッケージ
   を内部で呼び出すことによってディスプレイに3次元空間を平行透視表示するための
   パッケージです。物体に遠近感を持たせた透視変換を行いたいときは、
   このパッケージではなく透視変換パッケージgraphp3_.hを使う必要があります。
  
   このパッケージの目的は任意の3次元空間をディスプレイに投影することです。
   任意の3次元空間であるのでそれは立方体である必要はありません。
   ここで実数の3次元空間を回転領域(Rotation Port)と呼びます。
   このパッケージではこの回転領域を各軸成分で正規化し更に回転変換を施して
   ワールド座標系に立方体として投影します。
   例えばディスプレイ上に仮想の直方体(X:0..1,Y:0..2,Z:0..3)を描くには
   以下のようにします。

   setviewport_(0, 100, 0, 100, !0);   画面の100x100の領域を使う
   setmagnify_(1.5);                   投影するときの拡大率
   setrotationport_(0, 0, 0, 1, 2, 3); 希望の回転領域を定義
   setrotation_(RAD(-15), RAD(20), 0); 回転角を指定
   cuber3_(0, 0, 0, 1, 2, 3, !0);      回転領域と同じ直方体を描画

   setviewport_には投影画像が歪まないよう正方形領域を指定します。
   この描画した直方体を回転したい場合はsetrotationを再度指定し、
   cuber3_を再描画することによって別の回転角の直方体を描くことができます。
   ちなみにRADはデグリーをラジアンに変換するマクロです。
 */

struct rotationporttype_ {
  double ox, oy, oz;
  double mx, my, mz;
  double mag;
  double r[3][3];
};

extern struct rotationporttype_ __RP;

/*
   [名前]
   r3tox --- 3次元座標から投影されたX座標を求めるマクロ
   r3toy --- 3次元座標から投影されたY座標を求めるマクロ
   r3toz --- 3次元座標から投影されたZ座標を求めるマクロ

   [形式]
   r3tox(x,y,z)
   r3toy(x,y,z)
   r3toz(x,y,z)
   double x, y, z; 4次元座標

   [説明]
   setmagnify_ や setrotation_ で指定された回転角で、
   3次元座標から回転された3次元座標の各々の座標を求めます。
 */
#define r3tox(x,y,z) (__RP.mx*((x)-__RP.ox)*__RP.r[0][0]\
                     +__RP.my*((y)-__RP.oy)*__RP.r[1][0]\
                     +__RP.mz*((z)-__RP.oz)*__RP.r[2][0])
#define r3toy(x,y,z) (__RP.mx*((x)-__RP.ox)*__RP.r[0][1]\
                     +__RP.my*((y)-__RP.oy)*__RP.r[1][1]\
                     +__RP.mz*((z)-__RP.oz)*__RP.r[2][1])
#define r3toz(x,y,z) (__RP.mx*((x)-__RP.ox)*__RP.r[0][2]\
                     +__RP.my*((y)-__RP.oy)*__RP.r[1][2]\
                     +__RP.mz*((z)-__RP.oz)*__RP.r[2][2])

/*
   [名前]
   liner3_      --- 3次元視点変換用 line     直線描画マクロ
   linetor3_    --- 3次元視点変換用 lineto   相対位置への直線描画マクロ
   putpixelr3_  --- 3次元視点変換用 putpixel 点描画マクロ
   movetor3_    --- 3次元視点変換用 moveto   カレントポイント移動マクロ
   outtextxyr3_ --- 3次元視点変換用 outtext  テキスト出力マクロ

   [形式]
   liner3_     (x1,y1,z1, x2,y2,z2)
   linetor3_   (x,y,z)
   putpixelr3_ (x,y,z,c)
   movetor3_   (x,y,z)
   outtextxyr3_(x,y,z,str)
   double x1,y1,z1; 3次元座標
   double x2,y2,z2; 3次元座標
   double x,y,z;    3次元座標
   int c;           パレット番号
   char *str;       文字列

   [説明]
   これらの描画手続きは3次元視点変換用のマクロです。
   3次元の超空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・2次元ウィンドウ変換パッケージ graphr2_.h 
 */
#define liner3_(x1,y1,z1,x2,y2,z2) \
        line_(r3tox(x1,y1,z1),r3toy(x1,y1,z1),\
	      r3tox(x2,y2,z2),r3toy(x2,y2,z2))
#define linetor3_(x,y,z) \
	lineto_(r3tox(x,y,z),r3toy(x,y,z))
#define putpixelr3_(x,y,z,c) \
	putpixel_(r3tox(x,y,z),r3toy(x,y,z),c)
#define putpointr3_(x,y,z) \
	putpoint_(r3tox(x,y,z),r3toy(x,y,z))
#define movetor3_(x,y,z) \
	moveto_(r3tox(x,y,z),r3toy(x,y,z))
#define outtextxyr3_(x,y,z,str) \
	outtextxy_(r3tox(x,y,z),r3toy(x,y,z),str)

/*
   [名前]
   setrotationport_ --- 3次元透視視点変換用、座標定義域指定ルーチン

   [形式]
   setrotationport_(xf,yf,zf, xt,yt,zt)
   double xf,yf,zf; 点1
   double xt,yt,zt; 点2

   [説明]
   点1と点2を囲む立方体を3次元透視視点変換する領域とします。
 */
extern void setrotationport_(double xf, double yf, double zf,
                             double xt, double yt, double zt);

/*
   [名前]
   setmagnify_ --- 3次元透視視点変換用、拡大率指定ルーチン

   [形式]
   hypermagnify_(rm)
   double rm; 拡大率

   [説明]
   3次元の物体の描画を2次元に透視投影するときの拡大率を指定します。
   rm = 1.0 のときが平行投影となりますが、三角関数の特性上
   実際にディスプレイに描画されたときに小さい感じがありますので、
   rm = 1.5 ぐらいがちょうどいいでしょう。
 */
extern void setmagnify_(double rm);

/*
   [名前]
   setrotation_ --- 3次元透視視点変換用、投影角指定ルーチン

   [形式]
   setrotation_(a, b, c);
   double a; X軸回転角(ラジアン)
   double b; Y軸回転角(ラジアン)
   double c; Z軸回転角(ラジアン)

   [説明]
   3次元の物体の描画を2次元に透視投影するときの投影角を指定します。
 */
extern void setrotation_(double a, double b, double c);

/*
   [名前]
   setrotatex_ --- 3次元透視視点変換用、X軸回転ルーチン
   setrotatey_ --- 3次元透視視点変換用、Y軸回転ルーチン
   setrotatez_ --- 3次元透視視点変換用、Z軸回転ルーチン

   [形式]
   setrotatex_(d);
   setrotatey_(d);
   setrotatez_(d);
   double d; 回転角(ラジアン)

   [説明]
   3次元の物体の描画を2次元に透視投影するときの回転角を指定します。
   カレントの投影角から指定された角度だけ回転します。
 */
extern void setrotatex_(double d);
extern void setrotatey_(double d);
extern void setrotatez_(double d);

/*
   [名前]
   cuber3_ --- 3次元視点変換用 cube 直方体の描画

   [形式]
   cuber3_(xf,yf,zf, xt,yt,zt, flg)
   double xf,yf,zf; 点1
   double xt,yt,zt; 点2
   int flg;         未使用

   [説明]
   3次元の空間に点1と点2を囲む立方体を3次元視点変換で描画します。
 */
extern void cuber3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg);

extern void boxr3_(double xf, double yf, double zf,
                   double xt, double yt, double zt, int c6[]);

extern void lefthandr3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg);

/*
   [名前]
   linesr3_     --- 3次元視点変換用 lines     複数の直線描画関数
   putpixelsr3_ --- 3次元視点変換用 putpixels 複数の点描画関数

   [形式]
   linesr3_    (n, r3points)
   putpixelsr3_(n, r3points, c)
   int n;            指定する座標の数
   double *r3points; 3次元座標群の並び
   int c;            パレット番号

   [説明]
   3次元空間の直線や点を指定された数だけまとめて描画します。
   double型の配列 r3points には3次元座標群をベタ並びで格納して下さい。
 */
extern void linesr3_(int n, double *r3points);
extern void putpixelsr3_(int n, double *r3points, int c);
extern void putpointsr3_(int n, double *r3points);

/*
   [名前]
   getrotation_ --- 3次元透視投影変換用カレント投影角取得関数

   [形式]
   getrotation_(a, b, c)
   double *a, *b, *c; カレント投影角取得のためのポインタ

   [説明]
   setrotation_ や setrotatex_, setrotatey_, setrotatey_ などで
   回転させた視点、つまりカレントの回転行列から、
   Y-X-Z軸回転の絶対角回転角度a, b, cをラディアンで返します。
 */
extern void getrotation_(double *a, double *b, double *c);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
