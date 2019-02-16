/*
 * 3-dimensional perspective graphic interface in graffit < graphp3_.h >
 *
 * 3-Dimensional Perspective Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHP3__H_
#define _GRAPHP3__H_
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
   3次元透視変換(3-dimensional Perspective Translation)パッケージ

   これは3次元座標系をワールド座標系に変換し、さらに透視変換によって
   視点距離による物体の遠近感を表現するパッケージです。
   このパッケージは3次元視点変換パッケージ(graphr3_.h)上で動作します。
   さらにこれらを混在して使用できるので、インタラクティブに視点変換、透視変換
   を切り替えることも可能です。

   観察者の視点距離を指定するにはsetdistance_(d)を使います。
   距離dの値は正の実数です。負の値を指定すると縦横が反転されてしまいます。
   また距離dが零であることは視点と物体が同一座標にあることになり、
   数値計算上ではオーバーフローになってしまうので注意してください。

   例えばディスプレイ上に仮想の直方体(X:0..1,Y:0..2,Z:0..3)を視点距離0.5で
   透視変換して表示させたいのであれば以下のようにします。

   setviewport_(0, 100, 0, 100, !0);   画面の100x100の領域を使う
   setmagnify_(1.5);                   投影するときの拡大率
   setrotationport_(0, 0, 0, 1, 2, 3); 希望の回転領域を定義
   setrotation(RAD(-15), RAD(20), 0);  回転角を指定
   setdistance_(0.5);                  視点距離を指定
   cubep3_(0, 0, 0, 1, 2, 3, !0);      回転領域と同じ直方体を描画
 */

struct perspectivetype_ {
  double dist;
  double deform;
};

extern struct perspectivetype_ __PP;

/*
   [名前]
   p3tox --- 3次元座標から透視投影されたX座標を求めるマクロ
   p3toy --- 3次元座標から透視投影されたY座標を求めるマクロ
   p3toz --- 3次元座標から透視投影されたZ座標を求めるマクロ

   [形式]
   p3tox(x,y,z)
   p3toy(x,y,z)
   p3toz(x,y,z)
   double x, y, z; 3次元座標

   [説明]
   setmagnify_ や setrotation_ で指定された回転角で、
   3次元座標から透視投影変換された3次元座標の各々の座標を求めます。
 */
#define p3tox(x,y,z) (r3tox(x,y,z)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define p3toy(x,y,z) (r3toy(x,y,z)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define p3toz(x,y,z) (__PP.dist*(2.0-__PP.dist/(r3toz(x,y,z)+__PP.deform)))

/*
   [名前]
   linep3_      --- 3次元透視変換用 line     直線描画マクロ
   linetop3_    --- 3次元透視変換用 lineto   相対位置への直線描画マクロ
   putpixelp3_  --- 3次元透視変換用 putpixel 点描画マクロ
   movetop3_    --- 3次元透視変換用 moveto   カレントポイント移動マクロ
   outtextxyp3_ --- 3次元透視変換用 outtext  テキスト出力マクロ

   [形式]
   linep3_     (x1,y1,z1, x2,y2,z2)
   linetop3_   (x,y,z)
   putpixelp3_ (x,y,z,c)
   movetop3_   (x,y,z)
   outtextxyp3_(x,y,z,str)
   double x1,y1,z1; 3次元座標
   double x2,y2,z2; 3次元座標
   double x,y,z;    3次元座標
   int c;           パレット番号
   char *str;       文字列

   [説明]
   これらの描画手続きは3次元透視変換用のマクロです。
   3次元の空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元視点変換パッケージ graphr3_.h 
 */
#define linep3_(x1,y1,z1,x2,y2,z2) \
        line_(p3tox(x1,y1,z1),p3toy(x1,y1,z1), \
	      p3tox(x2,y2,z2),p3toy(x2,y2,z2))
#define linetop3_(x,y,z) \
	lineto_(p3tox(x,y,z),p3toy(x,y,z))
#define putpixelp3_(x,y,z,c) \
        putpixel_(p3tox(x,y,z),p3toy(x,y,z),c)
#define putpointp3_(x,y,z) \
        putpoint_(p3tox(x,y,z),p3toy(x,y,z))
#define movetop3_(x,y,z) \
        moveto_(p3tox(x,y,z),p3toy(x,y,z))
#define outtextxyp3_(x,y,z,str) \
        outtextxy_(p3tox(x,y,z),p3toy(x,y,z),str)

/*
   [名前]
   setdistance_ --- 3次元透視変換用、視点距離指定ルーチン

   [形式]
   setdistance_(d)
   double d; 視点距離

   [説明]
   視点距離 d は正の実数です。ほぼ d = 0.5 ぐらいが推奨値です。
   これを小さくすると3次元の物体が近く見え、
   逆に大きくすると遠く見えるようになります。
 */
extern void setdistance_(double d);

/*
   [名前]
   setdeformation_ --- 3次元透視変換用、デフォルメ定数指定ルーチン

   [形式]
   setdeformation_(d)
   double d; デフォルメ定数

   [説明]
   デフォルメ定数 d は正の実数です。ほぼ d = 2.5 ぐらいが推奨値です。
   これを小さくすると遠近法の強調度合が高まります。
 */
extern void setdeformation_(double d);

/*
   [名前]
   cubep3_ --- 3次元透視変換用 cube 直方体の描画

   [形式]
   cubep3_(xf,yf,zf, xt,yt,zt, flg)
   double xf,yf,zf; 点1
   double xt,yt,zt; 点2
   int flg;         未使用

   [説明]
   3次元の空間に点1と点2を囲む立方体を3次元透視変換で描画します。
 */
extern void cubep3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg);

extern void boxp3_(double xf, double yf, double zf, double xt,
                   double yt, double zt, int c6[]);

extern void lefthandp3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg);

/*
   [名前]
   linesp3_     --- 3次元透視変換用 lines     複数の直線描画関数
   putpixelsp3_ --- 3次元透視変換用 putpixels 複数の点描画関数

   [形式]
   linesp3_    (n, r3points)
   putpixelsp3_(n, r3points, c)
   int n;            指定する座標の数
   double *r3points; 3次元座標群の並び
   int c;            パレット番号

   [説明]
   3次元空間の直線や点を指定された数だけまとめて描画します。
   double型の配列 r3points には3次元座標群をベタ並びで格納して下さい。
 */
extern void linesp3_(int n, double *r3points);
extern void putpixelsp3_(int n, double *r3points, int c);
extern void putpointsp3_(int n, double *r3points);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
