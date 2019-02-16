/*
 * Axes utilities for R^2 graphics in graffit library < axes_.h >
 *
 * Draw Axes on Window Port for Borland Graphics Interface
 *
 * Copyright (C) 1991-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _AXES__H_
#define _AXES__H_
#include <graphr2_.h>
#include <axes.h>

/*
   [名前]
   drawaxisl_  --- 左Ｙ軸の描画
   drawaxist_  --- 上Ｘ軸の描画
   drawaxisr_  --- 右Ｙ軸の描画
   drawaxisb_  --- 下Ｘ軸の描画

   [形式]
   drawaxis?_(sep, ssep, len, bos)
   int sep;  長線の分割数
   int ssep; 短線の分割数
   int len;  目盛長さ
   int bos;  ビューポートを囲む枠幅
          
   [説明]
   例えば setviewport_(30, 30, 130, 130, 0) を実行した後、
   setwindow_(-1.0, 10.0, 1.0, -10.0) で仮想的な座標値を指定し、

   drawaxisl_(2, 2, 6, 10);

   とすると、ビューポート(30,30)-(130,130)の10ビット外側に、
   左Ｙ軸が描画されます。
   この場合、目盛は長線が2分割された位置に、
   短線も2分割された位置で描かれます。
   目盛が描かれた座標には、仮想的な座標値による目盛がふられます。
 */
#define drawaxisl_(s,ss,l,b) drawaxisy_(AXIS_LEFT,  s,ss,l,b)
#define drawaxist_(s,ss,l,b) drawaxisx_(AXIS_TOP,   s,ss,l,b)
#define drawaxisr_(s,ss,l,b) drawaxisy_(AXIS_RIGHT, s,ss,l,b)
#define drawaxisb_(s,ss,l,b) drawaxisx_(AXIS_BOTTOM,s,ss,l,b)

/*
   [名前]
   drawaxeslb_ --- 左Ｙ軸と下Ｘ軸の描画

   [形式]
   drawaxeslb_(sepx, ssepx, sepy, ssepy, len, bos)
   int sepx;  X軸、長線の分割数
   int ssepx; X軸、短線の分割数
   int sepy;  Y軸、長線の分割数
   int ssepy; Y軸、短線の分割数
   int len;   目盛長さ
   int bos;   ビューポートを囲む枠幅
          
   [説明]
   例えば setviewport_(30, 30, 130, 130, 0) を実行した後、
   setwindow_(-1.0, 10.0, 1.0, -10.0) で仮想的な座標値を指定し、

   drawaxeslb_(5, 2, 2, 1, 6, 10);

   とすると、ビューポート(30,30)-(130,130)の10ビット外側に、
   左Ｙ軸と下Ｘ軸が描画されます。
   この場合、X軸の目盛は長線が5分割された位置に、
   短線は2分割された位置で描かれます。
   Y軸の目盛は長線が2分割された位置に描かれます。
   短線は分割しないので描かれません。
   目盛が描かれた座標には、仮想的な座標値による目盛がふられます。
 */
#define drawaxeslb_(sx,ssx,sy,ssy,l,b) do{\
        drawaxisb_(sx,ssx,l,b);drawaxisl_(sy,ssy,l,b);}while(0)

/*
   [名前]
   drawaxisix_ --- 内Ｘ軸の描画
   drawaxisiy_ --- 内Ｙ軸の描画

   [形式]
   drawaxisi?_(sep, ssep, len, bos)
   int sep;  長線の分割数
   int ssep; 短線の分割数
   int len;  目盛長さ
   int bos;  軸を描くビューポート座標位置

   [説明]
   例えば setviewport_(30, 30, 130, 130, 0) を実行した後、
   setwindow_(-1.0, 10.0, 1.0, -10.0) で仮想的な座標値を指定し、

   drawaxisix_(2, 0, 6, 0.0);

   とすると、ビューポート(30,30)-(130,130)の100X100の中の、
   仮想的な座標Y=0.0の位置に中Ｘ軸が描画されます。
   この場合、目盛は長線が2分割された位置に描かれ、
   短線は描かれません。
   目盛が描かれた座標には、仮想的な座標値による目盛がふられます。
 */
#define drawaxisix_(s,ss,l,b) drawaxisx_(AXIS_INSIDE,s,ss,l,b)
#define drawaxisiy_(s,ss,l,b) drawaxisy_(AXIS_INSIDE,s,ss,l,b)

/*
   [名前]
   drawaxesi_ --- 内Ｘ軸と内Ｙ軸の描画

   [形式]
   drawaxesi_(sepx, ssepx, sepy, ssepy, len, bosx, bosy)
   int sepx;  X軸、長線の分割数
   int ssepx; X軸、短線の分割数
   int sepy;  Y軸、長線の分割数
   int ssepy; Y軸、短線の分割数
   int len;   目盛長さ
   int bosx;  X軸を描くビューポート座標位置
   int bosy;  Y軸を描くビューポート座標位置
          
   [説明]
   例えば setviewport_(30, 30, 130, 130, 0) を実行した後、
   setwindow_(-1.0, 10.0, 1.0, -10.0) で仮想的な座標値を指定し、

   drawaxesi_(0, 0, 0, 0, 6, 0.0, -0.8);

   とすると、ビューポート(30,30)-(130,130)の100X100の中の、
   仮想的な座標Y=0.0の位置に中Ｘ軸が描画され、
   仮想的な座標X=-0.8の位置に中Ｙ軸が描画されます。
   この場合、目盛は描かれません。
   目盛が描かれた座標には、仮想的な座標値による目盛がふられます。
 */
#define drawaxesi_(sx,ssx,sy,ssy,l,bx,by) do{\
        drawaxisix_(sx,ssx,l,bx);drawaxisiy_(sy,ssy,l,by);}while(0)

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [名前]
   drawaxisx_ --- ウィンドウポートへＸ軸の描画

   [形式]
   void drawaxisx_(apos, sep, ssep, len, bos)
   int apos;     座標軸位置タイプ
   int sep;      長線の分割数
   int ssep;     短線の分割数
   int len;      目盛長さ
   double bos;   位置タイプが AXIS_INSIDE の場合、軸を描画する中位置座標
                 位置タイプが AXIS_INSIDE 以外は、ビューポートを囲む枠幅

   [説明]
   setviewport_ と setwindow_ で定義されたウィンドウポートにＸ軸を描画。
   長線の目盛を描画された座標にはグラフィック文字で座標値が描かれます。

   apos には以下の位置タイプのいずれかを指定します。

   enum axis_positions {
     AXIS_TOP    = 0, 上Ｘ軸
     AXIS_BOTTOM = 1, 下Ｘ軸
     AXIS_INSIDE = 2, 内Ｘ軸
   };

   bos には位置タイプが AXIS_TOP、AXIS_BOTTOM のいずれかの場合は、
   ウィンドウポートを囲む余裕幅(ビット数)を指定します。
   位置タイプが AXIS_INSIDE の場合 bos には、
   軸を描画する中位置座標を指定します。
   これは setwindow_ で指定した仮想的な座標を指定します。
   目盛が描かれた座標には、仮想的な座標値による目盛がふられます。
 */
extern void drawaxisx_(int apos, int sep, int ssep, int len, double bos);

/*
   [名前]
   drawaxisy_ --- ウィンドウポートへＹ軸の描画

   [形式]
   void drawaxisy_(apos, sep, ssep, len, bos)
   int apos;     座標軸位置タイプ
   int sep;      長線の分割数
   int ssep;     短線の分割数
   int len;      目盛長さ
   double bos;   位置タイプが AXIS_INSIDE の場合、軸を描画する中位置座標
                 位置タイプが AXIS_INSIDE 以外は、ビューポートを囲む枠幅

   [説明]
   setviewport_ と setwindow_ で定義されたウィンドウポートにＹ軸を描画。
   長線の目盛を描画された座標にはグラフィック文字で座標値が描かれます。

   apos には以下の位置タイプのいずれかを指定します。

   enum axis_positions {
     AXIS_LEFT   = 0, 左Ｙ軸
     AXIS_RIGHT  = 1, 右Ｙ軸
     AXIS_INSIDE = 2, 内Ｙ軸
   };

   bos には位置タイプが AXIS_LEFT、AXIS_RIGHT のいずれかの場合は、
   ウィンドウポートを囲む余裕幅(ビット数)を指定します。
   位置タイプが AXIS_INSIDE の場合 bos には、
   軸を描画する中位置座標を指定します。
   これは setwindow_ で指定した仮想的な座標を指定します。
   目盛が描かれた座標には、仮想的な座標値による目盛がふられます。
 */
extern void drawaxisy_(int apos, int sep, int ssep, int len, double bos);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
