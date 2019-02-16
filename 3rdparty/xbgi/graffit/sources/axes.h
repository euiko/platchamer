/*
 * Axes utilities in graffit library < axes.h >
 *
 * Draw Axes on View Port for Borland Graphics Interface
 *
 * Copyright (C) 1991-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _AXES_H_
#define _AXES_H_
#include <graphics.h>

/*
   [名前]
   drawaxisl  --- 左Ｙ軸の描画
   drawaxist  --- 上Ｘ軸の描画
   drawaxisr  --- 右Ｙ軸の描画
   drawaxisb  --- 下Ｘ軸の描画
   
   [形式]
   drawaxis?(sep, ssep, len, bos)
   int sep;  長線の分割数
   int ssep; 短線の分割数
   int len;  目盛長さ
   int bos;  ビューポートを囲む枠幅
          
   [説明]
   例えば setviewport(30, 30, 130, 130, 0) を実行した後、

   drawaxisl(2, 2, 6, 10);

   とすると、ビューポート(30,30)-(130,130)の10ビット外側に、
   左Ｙ軸が描画されます。この場合、目盛は長線が2分割された位置に、
   短線も2分割された位置で描かれます。
 */
#define drawaxisl(s,ss,l,b) drawaxisy(AXIS_LEFT,  s,ss,l,b)
#define drawaxist(s,ss,l,b) drawaxisx(AXIS_TOP,   s,ss,l,b)
#define drawaxisr(s,ss,l,b) drawaxisy(AXIS_RIGHT, s,ss,l,b)
#define drawaxisb(s,ss,l,b) drawaxisx(AXIS_BOTTOM,s,ss,l,b)

/*
   [名前]
   drawaxeslb --- 左Ｙ軸と下Ｘ軸の描画

   [形式]
   drawaxeslb(sepx, ssepx, sepy, ssepy, len, bos)
   int sepx;  X軸、長線の分割数
   int ssepx; X軸、短線の分割数
   int sepy;  Y軸、長線の分割数
   int ssepy; Y軸、短線の分割数
   int len;   目盛長さ
   int bos;   ビューポートを囲む枠幅

   [説明]
   例えば setviewport(30, 30, 130, 130, 0) を実行した後、

   drawaxeslb(5, 2, 2, 1, 6, 10);

   とすると、ビューポート(30,30)-(130,130)の10ビット外側に、
   左Ｙ軸と下Ｘ軸が描画されます。
   この場合、X軸の目盛は長線が5分割された位置に、
   短線は2分割された位置で描かれます。
   Y軸の目盛は長線が2分割された位置に描かれます。
   短線は分割しないので描かれません。
 */
#define drawaxeslb(sx,ssx,sy,ssy,l,b) do {\
        drawaxisl(sy,ssy,l,b); drawaxisb(sx,ssx,l,b); } while(0)

/*
   [名前]
   drawaxisix --- 内Ｘ軸の描画
   drawaxisiy --- 内Ｙ軸の描画

   [形式]
   drawaxisi?(sep, ssep, len, bos)
   int sep;  長線の分割数
   int ssep; 短線の分割数
   int len;  目盛長さ
   int bos;  軸を描くビューポート座標位置
          
   [説明]
   例えば setviewport(30, 30, 130, 130, 0) を実行した後、

   drawaxisix(2, 0, 6, 50);

   とすると、ビューポート(30,30)-(130,130)の100X100の中の、
   Y=50の位置に中Ｘ軸が描画されます。
   この場合、目盛は長線が2分割された位置に描かれ、
   短線は描かれません。
 */
#define drawaxisix(s,ss,l,b) drawaxisx(AXIS_INSIDE,s,ss,l,b)
#define drawaxisiy(s,ss,l,b) drawaxisy(AXIS_INSIDE,s,ss,l,b)

/*
   [名前]
   drawaxesi --- 内Ｘ軸と内Ｙ軸の描画

   [形式]
   drawaxesi(sepx, ssepx, sepy, ssepy, len, bosx, bosy)
   int sepx;  X軸、長線の分割数
   int ssepx; X軸、短線の分割数
   int sepy;  Y軸、長線の分割数
   int ssepy; Y軸、短線の分割数
   int len;   目盛長さ
   int bosx;  X軸を描くビューポート座標位置
   int bosy;  Y軸を描くビューポート座標位置

   [説明]
   例えば setviewport(30, 30, 130, 130, 0) を実行した後、

   drawaxesi(0, 0, 0, 0, 6, 50, 10);

   とすると、ビューポート(30,30)-(130,130)の100X100の中の、
   Y=50の位置に中Ｘ軸が描画され、X=10の位置に中Ｙ軸が描画されます。
   この場合、目盛は描かれません。
 */
#define drawaxesi(sx,ssx,sy,ssy,l,bx,by) do {\
        drawaxisix(sx,ssx,l,bx); drawaxisiy(sy,ssy,l,by); }while(0)

enum axis_positions {
  AXIS_LEFT   = 0, /* 左Ｙ軸 */
  AXIS_RIGHT  = 1, /* 右Ｙ軸 */
  AXIS_TOP    = 0, /* 上Ｘ軸 */
  AXIS_BOTTOM = 1, /* 下Ｘ軸 */
  AXIS_INSIDE = 2, /* 内XY軸 */
};

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [名前]
   drawaxisx --- ビューポートへＸ軸の描画

   [形式]
   void drawaxisx(apos, sep, ssep, len, bos)
   int apos; 座標軸位置タイプ
   int sep;  長線の分割数
   int ssep; 短線の分割数
   int len;  目盛長さ
   int bos;  位置タイプが AXIS_INSIDE の場合、軸を描画する中位置座標
             位置タイプが AXIS_INSIDE 以外は、ビューポートを囲む枠幅

   [説明]
   setviewport で定義されたビューポートにＸ軸を描画。

   apos には以下の位置タイプのいずれかを指定します。

   enum axis_positions {
     AXIS_TOP    = 0, 上Ｘ軸
     AXIS_BOTTOM = 1, 下Ｘ軸
     AXIS_INSIDE = 2, 内Ｘ軸
   };

   bos には位置タイプが AXIS_TOP、AXIS_BOTTOM のいずれかの場合は、
   ビューポートを囲む余裕幅(ビット数)を指定します。
   位置タイプが AXIS_INSIDE の場合 bos には、
   軸を描画する中位置座標を指定します。
 */
void drawaxisx(int apos, int sep, int ssep, int len, int bos);

/*
   [名前]
   drawaxisy --- ビューポートへＹ軸の描画

   [形式]
   void drawaxisy(apos, sep, ssep, len, bos)
   int apos; 座標軸位置タイプ
   int sep;  長線の分割数
   int ssep; 短線の分割数
   int len;  目盛長さ
   int bos;  位置タイプが AXIS_INSIDE の場合、軸を描画する中位置座標
             位置タイプが AXIS_INSIDE 以外は、ビューポートを囲む枠幅

   [説明]
   setviewport で定義されたビューポートにＹ軸を描画。
   apos には以下の位置タイプのいずれかを指定します。

   enum axis_positions {
     AXIS_LEFT   = 0, 左Ｙ軸
     AXIS_RIGHT  = 1, 右Ｙ軸
     AXIS_INSIDE = 2, 内Ｙ軸
   };
   
   bos には位置タイプが AXIS_LEFT、AXIS_RIGHT のいずれかの場合は、
   ビューポートを囲む余裕幅(ビット数)を指定します。
   位置タイプが AXIS_INSIDE の場合 bos には、
   軸を描画する中位置座標を指定します。
 */
void drawaxisy(int apos, int sep, int ssep, int len, int bos);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
