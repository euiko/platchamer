/*
 * 3-dimensional stereographic interface in graffit library < graphs3_.h >
 *
 * 3-Dimensional Stereo Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHS3__H_
#define _GRAPHS3__H_
#include <graphics.h>
#include <graphr2_.h>
#include <graphs3_.h>
#include <graphp3_.h>

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
   3次元ステレオグラフィック(3-dimensional Stereo Graphics)パッケージ
  
   これは3次元座標系に2種類の透視変換を施す、
   いわゆる立体視を実現するためのパッケージです。
   描画命令の末尾に'sl_'を付加したものが左視点画像用の描画命令、
   'sr_'を付加したものが右視点画像用の描画命令です。
   また左視点、右視点同時描画命令も用意されており、描画命令の末尾に's3_'を
   付加した名称になっています。デフォルト値で左視点変換に赤色をセット、
   右視点変換に青色をセットを行います。これは変更可能です。

   例えばディスプレイ上にステレオグラフィックで直方体(X:0..1,Y:0..2,Z:0..3)を
   描くには以下のようにします。

   setviewport_(0, 100, 0, 100, !0);   画面の100x100の領域を使う
   setmagnify(1.5);                    投影するときの拡大率
   setrotationport_(0, 0, 0, 1, 2, 3); 希望の回転座標系を定義
   setrotation_(RAD(-15), RAD(20), 0); 回転角を指定
   setdistance_(0.5);                  視点距離を指定
   stereodistance_(0.5);               ステレオグラフ視点距離を指定
   cubes3_(0, 0, 0, 1, 2, 3, !0);      回転座標系と同じ直方体を描画

   以下のように立体視の手法を変更できます。

   setstereotype(ColorGlass);  色メガネ立体視
   setstereotype(DoubleImage); 2画像立体視

   また、以下のようにユーザー定義の立体視用手続きを指定できます。

   setstereoprocedures(start_proc, left_proc, right_proc, end_proc);

   2画像立体視のときは、以下のように幅を変更できます。

   stereowidthimages(width);

   widthが負なら交差法になります。
 */

struct stereographtype_ {
  double dist;                /* stereo distance */
  void (*start)(void);        /* start procedure */
  void (*left) (void);        /* left procedure */
  void (*right)(void);        /* right procedure */
  void (*end)  (void);        /* end procedure */
  int c;                      /* keep current color */
  struct fillsettingstype fs; /* keep current fill settings */
#ifdef _XBGI_
  struct pointsettingstype ps; /* keep current point settings */
#endif
  struct viewporttype_ v;     /* keep current viewport settings */
  int wi;                     /* width between double images (bits) */
};

extern struct stereographtype_ __SG;

enum { ColorGlass, DoubleImage };

/*
   [名前]
   sltox --- 3次元座標から左目へ透視投影されたX座標を求めるマクロ
   sltoy --- 3次元座標から左目へ透視投影されたY座標を求めるマクロ
   sltoz --- 3次元座標から左目へ透視投影されたZ座標を求めるマクロ

   [形式]
   sltox(x,y,z)
   sltoy(x,y,z)
   sltoz(x,y,z)
   double x, y, z; 3次元座標

   [説明]
   setmagnify_ や setrotation_ で指定された回転角で、3次元座標から
   左目へ透視投影変換された3次元座標の各々の座標を求めます。
 */
#define sltox(x,y,z) ((r3tox(x,y,z)+__SG.dist)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define sltoy(x,y,z) p3toy(x,y,z)
#define sltoz(x,y,z) p3toz(x,y,z)

/*
   [名前]
   linesl_      --- 3次元左目透視変換用 line     直線描画
   linetosl_    --- 3次元左目透視変換用 lineto   相対位置への直線描画
   putpixelsl_  --- 3次元左目透視変換用 putpixel 点描画
   movetosl_    --- 3次元左目透視変換用 moveto   カレントポイント移動
   outtextxysl_ --- 3次元左目透視変換用 outtext  テキスト出力

   [形式]
   linesl_     (x1,y1,z1, x2,y2,z2)
   linetosl_   (x,y,z)
   putpixelsl_ (x,y,z,c)
   movetosl_   (x,y,z)
   outtextxysl_(x,y,z,str)
   double x1,y1,z1; 3次元座標
   double x2,y2,z2; 3次元座標
   double x,y,z;    3次元座標
   int c;           パレット番号
   char *str;       文字列

   [説明]
   これらの描画手続きは3次元左目透視変換用のマクロです。
   3次元の空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元透視変換パッケージ graphp3_.h
 */
#define linesl_(x1,y1,z1,x2,y2,z2) \
        line_(sltox(x1,y1,z1),sltoy(x1,y1,z1), \
              sltox(x2,y2,z2),sltoy(x2,y2,z2))
#define linetosl_(x,y,z) \
        lineto_(sltox(x,y,z),sltoy(x,y,z))
#define putpixelsl_(x,y,z,c) \
        putpixel_(sltox(x,y,z),sltoy(x,y,z),c)
#define putpointsl_(x,y,z) \
        putpoint_(sltox(x,y,z),sltoy(x,y,z))
#define movetosl_(x,y,z) \
        moveto_(sltox(x,y,z),sltoy(x,y,z))
#define outtextxysl_(x,y,z,str) \
        outtextxy_(sltox(x,y,z),sltoy(x,y,z),str)

/*
   [名前]
   srtox --- 3次元座標から右目へ透視投影されたX座標を求めるマクロ
   srtoy --- 3次元座標から右目へ透視投影されたY座標を求めるマクロ
   srtoz --- 3次元座標から右目へ透視投影されたZ座標を求めるマクロ

   [形式]
   srtox(x,y,z)
   srtoy(x,y,z)
   srtoz(x,y,z)
   double x, y, z; 3次元座標

   [説明]
   setmagnify_ や setrotation_ で指定された回転角で、3次元座標から
   右目へ透視投影変換された3次元座標の各々の座標を求めます。
 */
#define srtox(x,y,z) ((r3tox(x,y,z)-__SG.dist)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define srtoy(x,y,z) p3toy(x,y,z)
#define srtoz(x,y,z) p3toz(x,y,z)

/*
   [名前]
   linesr_      --- 3次元右目透視変換用 line     直線描画
   linetosr_    --- 3次元右目透視変換用 lineto   相対位置への直線描画
   putpixelsr_  --- 3次元右目透視変換用 putpixel 点描画
   movetosr_    --- 3次元右目透視変換用 moveto   カレントポイント移動
   outtextxysr_ --- 3次元右目透視変換用 outtext  テキスト出力

   [形式]
   linesr_     (x1,y1,z1, x2,y2,z2)
   linetosr_   (x,y,z)
   putpixelsr_ (x,y,z,c)
   movetosr_   (x,y,z)
   outtextxysr_(x,y,z,str)
   double x1,y1,z1; 3次元座標
   double x2,y2,z2; 3次元座標
   double x,y,z;    3次元座標
   int c;           パレット番号
   char *str;       文字列

   [説明]
   これらの描画手続きは3次元右目透視変換用のマクロです。
   3次元の空間の図形を簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元透視変換パッケージ graphp3_.h
 */
#define linesr_(x1,y1,z1,x2,y2,z2) \
        line_(srtox(x1,y1,z1),srtoy(x1,y1,z1), \
              srtox(x2,y2,z2),srtoy(x2,y2,z2))
#define linetosr_(x,y,z) \
        lineto_(srtox(x,y,z),srtoy(x,y,z))
#define putpixelsr_(x,y,z,c) \
        putpixel_(srtox(x,y,z),srtoy(x,y,z),c)
#define putpointsr_(x,y,z) \
        putpoint_(srtox(x,y,z),srtoy(x,y,z))
#define movetosr_(x,y,z) \
        moveto_(srtox(x,y,z),srtoy(x,y,z))
#define outtextxysr_(x,y,z,str) \
        outtextxy_(srtox(x,y,z),srtoy(x,y,z),str)

/*
   [名前]
   lines3_      --- 3次元両目透視変換用 line     直線描画
   linetos3_    --- 3次元両目透視変換用 lineto   相対位置への直線描画
   putpixels3_  --- 3次元両目透視変換用 putpixel 点描画
   movetos3_    --- 3次元両目透視変換用 moveto   カレントポイント移動
   outtextxys3_ --- 3次元両目透視変換用 outtext  テキスト出力

   [形式]
   lines3_     (x1,y1,z1, x2,y2,z2)
   linetos3_   (x,y,z)
   putpixels3_ (x,y,z,c)
   movetos3_   (x,y,z)
   outtextxys3_(x,y,z,str)
   double x1,y1,z1; 3次元座標
   double x2,y2,z2; 3次元座標
   double x,y,z;    3次元座標
   int c;           パレット番号
   char *str;       文字列

   [説明]
   これらの描画手続きは3次元両目透視変換用のマクロです。
   3次元の空間の図形を立体視で簡単に描画することができます。
   これらの描画手続きは以下のパッケージ上で動作しています。

   ・3次元透視変換パッケージ graphp3_.h
 */
#define lines3_(x1,y1,z1,x2,y2,z2) \
                               do{__SG.start(); \
                                  __SG.left(); linesl_(x1,y1,z1,x2,y2,z2); \
                                  __SG.right();linesr_(x1,y1,z1,x2,y2,z2); \
                                  __SG.end();} while(0)
#define linetos3_(x,y,z)       do{__SG.start(); \
                                  __SG.left(); linetosl_(x,y,z); \
                                  __SG.right();linetosr_(x,y,z); \
                                  __SG.end();} while(0)
#define putpixels3_(x,y,z,c)   do{__SG.start(); \
                                  __SG.left(); putpixelsl_(x,y,z,getcolor()); \
                                  __SG.right();putpixelsr_(x,y,z,getcolor()); \
                                  __SG.end();} while(0)
#define putpoints3_(x,y,z)     do{__SG.start(); \
                                  __SG.left(); putpointsl_(x,y,z); \
                                  __SG.right();putpointsr_(x,y,z); \
                                  __SG.end();} while(0)
#define movetos3_(x,y,z)       do{__SG.start(); \
                                  __SG.left(); movetosl_(x,y,z); \
                                  __SG.right();movetosr_(x,y,z); \
                                  __SG.end();} while(0)
#define outtextxys3_(x,y,z,str) \
                               do{__SG.start(); \
                                  __SG.left(); outtextxysl_(x,y,z,str); \
                                  __SG.right();outtextxysr_(x,y,z,str); \
                                  __SG.end();} while(0)

extern void stereowidthimages(int width);

extern void setstereoprocedures(void (*start)(void),
                                void (*left)(void),
                                void (*right)(void),
                                void (*end)(void));

extern void setstereotype(int type);

/*
   [名前]
   stereodistance_ --- 3次元ステレオグラフ用、両眼距離指定ルーチン

   [形式]
   stereodistance_(d)
   double d; 両眼距離

   [説明]
   両眼距離 d は正の実数です。ほぼ d = 0.02 ぐらいが推奨値です。
 */
extern void stereodistance_(double d);

/*
   [名前]
   cubes3_ --- 3次元ステレオグラフ用 cube 直方体の描画

   [形式]
   cubes3_(xf,yf,zf, xt,yt,zt, flg)
   double xf,yf,zf; 点1
   double xt,yt,zt; 点2
   int flg;         未使用

   [説明]
   3次元の空間に点1と点2を囲む立方体を3次元ステレオグラフで描画します。
 */
extern void cubes3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg);

extern void boxs3_(double xf, double yf, double zf, double xt,
                   double yt, double zt, int c6[]);

extern void lefthands3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg);

/*
   [名前]
   liness3_     --- 3次元ステレオグラフ用 lines     複数の直線描画関数
   putpixelss3_ --- 3次元ステレオグラフ用 putpixels 複数の点描画関数

   [形式]
   liness3_    (n, r3points)
   putpixelss3_(n, r3points, c)
   int n;            指定する座標の数
   double *r3points; 3次元座標群の並び
   int c;            パレット番号

   [説明]
   3次元空間の直線や点を指定された数だけまとめて描画します。
   double型の配列 r3points には3次元座標群をベタ並びで格納して下さい。
 */
extern void liness3_(int n, double *r3points);
extern void putpixelss3_(int n, double *r3points, int c);
extern void putpointss3_(int n, double *r3points);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GRAPHS3__H_ */
