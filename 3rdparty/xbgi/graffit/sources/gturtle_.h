/*
 * 2-dimensional turtle graphic interface in graffit library < gturtle_.h >
 *
 * Turtle Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GTURTLE__H_
#define _GTURTLE__H_
#include <math.h>
#include <graphr2_.h>

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
   タートルグラフィックパッケージ

   これは2次元のワールド座標でタートルグラフィックを実現するパッケージです。
   move_で亀の軌跡の描画、setangle_で亀の向いている方角の設定、
   turn_で現在向いている方角から、亀の向いている方角を変えます。
   角度はラディアンで指定します。
   デグリーで指定したい場合は以下のように変換して下さい。

   turn_(RAD(20));
 */

extern void move_(double d);
extern void setangle_(double angle);
extern void turn_(double dangle);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GTURTLE_H_ */
