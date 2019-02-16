/*
 * 2-dimensional graphic interface in graffit library < graphr2_.h >
 *
 * R^2 Window Port for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHR2__H_
#define _GRAPHR2__H_
#include <graphics.h>

/*
   ウィンドウ変換(Window Translation)パッケージ
  
   これは2次元のワールド座標系からディスプレイのスクリーン座標系へ変換し、
   ワールド座標系によるグラフィック画面へのアクセスを可能にするパッケージです。
   Turbo/Borland CのBGIではスクリーン座標系(viewport)をサポートしているため、
   このスクリーン座標系にワールド座標系を変換しています。

   このパッケージでは通常処理系に用意されている整数型のグラフィックルーチン上に
   高速かつ簡便な実数型グラフィックをサポートすることを目的としています。
   例えばBGIの直線描画命令'line'を実数型でアクセスする場合には、
   描画命令にアンダーバー'_'を付加した'line_'を用いることによってワールド座標に
   アクセスすることができます。
   そのワールド座標系の指定にはsetviewport_とsetwindow_を呼び出します.
   例えばディスプレイの領域(vx:100..200,vy:50..150)を
   実数領域(wx:-1..1,wy:2..-2)として表現したければ、
   以下のようにスクリーン座標系とワールド座標系を指定します。

   setviewport_(100.0, 50.0, 200.0, 150.0, !0)
   setwindow_(-1.0, 2.0, 1.0, -2.0)

   いずれもleft,top,right,bottomの順で指定することに注意してください。
   ただし、setviewport_とsetwindow_の呼び出し順序は上の例の逆でもかまいません。
   ちなみに、setviewport_の最後の引数はクリッピングを行う場合に真を指定します。
   これらの座標系を指定した後line_,putpixel_,bar_などの実数型の描画命令を
   実行してください。

   このウィンドウ変換パッケージには以下の拡張パッケージが用意されています。

   タートルグラフィックスパッケージ ....... gturtle_.h
   片対数、両対数パッケージ ............... graphl2_.h
   3次元視点変換パッケージ ................ graphr3_.h
   3次元透視変換パッケージ ................ graphp3_.h
   3次元ステレオグラフパッケージ .......... graphs3_.h
   4次元視点変換パッケージ ................ graphr4_.h
   4次元透視変換パッケージ ................ graphp4_.h
   4次元ステレオグラフパッケージ .......... graphs4_.h

   いずれも実数を扱うという意味でインクルードファイル名にアンダーバー'_'を
   付加した名称になっています。
 */

struct windowtype_ {
  double left, top, right, bottom;
  double mx, my;
};

struct viewporttype_ {
  double left, top, right, bottom;
  int clip;
};

extern struct windowtype_ __W;
extern struct viewporttype_ __V;

#ifndef _XBGI_
#define wvx(x) ((int)(((x)-__W.left)*__W.mx))
#define wvy(y) ((int)(((y)-__W.top)*__W.my))
#define f_x(x) ((int)((x)*__W.mx))
#define f_y(y) ((int)((y)*__W.my))
#define vwx(x) ((double)(x)/__W.mx+__W.left)
#define vwy(y) ((double)(y)/__W.my+__W.top)
#define x_f(x) ((double)(x)/__W.mx)
#define y_f(y) ((double)(y)/__W.my)
#else
#define wvx(x) ((((x)-__W.left)*__W.mx))
#define wvy(y) ((((y)-__W.top)*__W.my))
#define f_x(x) (((x)*__W.mx))
#define f_y(y) (((y)*__W.my))
#define vwx(x) ((x)/__W.mx+__W.left)
#define vwy(y) ((y)/__W.my+__W.top)
#define x_f(x) ((x)/__W.mx)
#define y_f(y) ((y)/__W.my)
#endif

#ifndef _XBGI_
#define arc_(x,y,stt,end,r) arc(wvx(x),wvy(y),(int)stt,(int)end,f_x(r))
#else
#define arc_(x,y,stt,end,r) _arc(wvx(x),wvy(y),stt,end,f_x(r))
#endif

#ifndef _XBGI_
#define bar_(x1,y1,x2,y2) bar(wvx(x1),wvy(y1),wvx(x2),wvy(y2))
#else
#define bar_(x1,y1,x2,y2) _bar(wvx(x1),wvy(y1),wvx(x2),wvy(y2))
#endif

#ifndef _XBGI_
#define bar3d_(x1,y1,x2,y2,w,flg) bar3d(wvx(x1),wvy(y1),wvx(x2),wvy(y2),f_x(w),flg)
#else
#define bar3d_(x1,y1,x2,y2,w,flg) _bar3d(wvx(x1),wvy(y1),wvx(x2),wvy(y2),f_x(w),flg)
#endif

#ifndef _XBGI_
#define circle_(x,y,r) circle(wvx(x),wvy(y),f_x(r))
#else
#define circle_(x,y,r) _circle(wvx(x),wvy(y),f_x(r))
#endif

#define closegraph_ closegraph
#define clearviewport_ clearviewport

#ifndef _XBGI_
#define ellipse_(x,y,stt,end,xr,yr) ellipse(wvx(x),wvy(y),(int)stt,(int)end,f_x(xr),f_y(yr))
#else
#define ellipse_(x,y,stt,end,xr,yr) _ellipse(wvx(x),wvy(y),stt,end,f_x(xr),f_y(yr))
#endif

#ifndef _XBGI_
#define fillellipse_(x,y,xr,yr) fillellipse(wvx(x),wvy(y),f_x(xr),f_y(yr))
#else
#define fillellipse_(x,y,xr,yr) _fillellipse(wvx(x),wvy(y),f_x(xr),f_y(yr))
#endif

#ifndef _XBGI_
#define floodfill_(x,y,border) floodfill(wvx(x),wvy(y),border)
#else
#define floodfill_(x,y,border) _floodfill(wvx(x),wvy(y),border)
#endif

#ifndef _XBGI_
#define getimage_(x1,y1,x2,y2,bm) getimage(wvx(x1),wvy(y1),wvx(x2),wvy(y2),bm)
#else
#define getimage_(x1,y1,x2,y2,bm) _getimage(wvx(x1),wvy(y1),wvx(x2),wvy(y2),bm)
#endif

#define getmaxx_() (double)getmaxx()
#define getmaxy_() (double)getmaxy()

#ifndef _XBGI_
#define getpixel_(x,y) getpixel(wvx(x),wvy(y))
#else
#define getpixel_(x,y) _getpixel(wvx(x),wvy(y))
#endif

#ifndef _XBGI_
#define getx_() vwx(getx())
#else
#define getx_() vwx(_getx())
#endif

#ifndef _XBGI_
#define gety_() vwy(gety())
#else
#define gety_() vwy(_gety())
#endif

#define imagesize_(x1,y1,x2,y2) imagesize(wvx(x1),wvy(y1),wvx(x2),wvy(y2))

#ifndef _XBGI_
#define line_(x1,y1,x2,y2) line(wvx(x1),wvy(y1),wvx(x2),wvy(y2))
#else
#define line_(x1,y1,x2,y2) _line(wvx(x1),wvy(y1),wvx(x2),wvy(y2))
#endif

#ifndef _XBGI_
#define linerel_(dx,dy) linerel(f_x(dx),f_y(dy))
#else
#define linerel_(dx,dy) _linerel(f_x(dx),f_y(dy))
#endif

#ifndef _XBGI_
#define lineto_(x,y) lineto(wvx(x),wvy(y))
#else
#define lineto_(x,y) _lineto(wvx(x),wvy(y))
#endif

#ifndef _XBGI_
#define moverel_(dx,dy) moverel(f_x(dx),f_x(dy))
#else
#define moverel_(dx,dy) _moverel(f_x(dx),f_x(dy))
#endif

#ifndef _XBGI_
#define moveto_(x,y) moveto(wvx(x),wvy(y))
#else
#define moveto_(x,y) _moveto(wvx(x),wvy(y))
#endif

#ifndef _XBGI_
#define outtextxy_(x,y,textstring) outtextxy(wvx(x),wvy(y),textstring)
#else
#define outtextxy_(x,y,textstring) _outtextxy(wvx(x),wvy(y),textstring)
#endif

#ifndef _XBGI_
#define pieslice_(x,y,stt,end,r) pieslice(wvx(x),wvy(y),(int)stt,(int)end,f_x(r))
#else
#define pieslice_(x,y,stt,end,r) _pieslice(wvx(x),wvy(y),stt,end,f_x(r))
#endif

#ifndef _XBGI_
#define putimage_(x,y,bm,op) putimage(wvx(x),wvy(y),bm,op)
#else
#define putimage_(x,y,bm,op) _putimage(wvx(x),wvy(y),bm,op)
#endif

#ifndef _XBGI_
#define putpixel_(x,y,c) putpixel(wvx(x),wvy(y),c)
#else
#define putpixel_(x,y,c) _putpixel(wvx(x),wvy(y),c)
#endif

#ifndef _XBGI_
#define putpoint_(x,y) putpoint(wvx(x),wvy(y))
#else
#define putpoint_(x,y) _putpoint(wvx(x),wvy(y))
#endif

#ifndef _XBGI_
#define rectangle_(x1,y1,x2,y2) rectangle(wvx(x1),wvy(y1),wvx(x2),wvy(y2))
#else
#define rectangle_(x1,y1,x2,y2) _rectangle(wvx(x1),wvy(y1),wvx(x2),wvy(y2))
#endif

#ifndef _XBGI_
#define sector_(x,y,stt,end,xr,yr) sector(wvx(x),wvy(y),(int)stt,(int)end,f_x(xr),f_y(yr))
#else
#define sector_(x,y,stt,end,xr,yr) _sector(wvx(x),wvy(y),stt,end,f_x(xr),f_y(yr))
#endif

#define setaspectratio_(x,y) setaspectratio(f_x(x),f_y(y))

#define setusercharsize_(x,dx,y,dy) setusercharsize(f_x(x),f_x(dx),f_y(y),f_y(dy))

#define textheight_(xxx) x_f(textheight(xxx))

#define textwidth_(xxx) y_f(textwidth(xxx))

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void drawpoly_(int n, double *dp);

extern void fillpoly_(int n, double *dp);

extern void setviewport_(double left, double top,
			 double right, double bottom, int clip);

extern void setwindow_(double left, double top, double right, double bottom);

extern void initgraph_(int *gd, int *gm, char *gp);

#ifdef _GRAPHIX_H_
extern xbgi *creategraph_(int *gd, int *gm, char *gp);
#endif

extern void getwindowsettings_(struct windowtype_ *wt);

extern void getviewsettings_(struct viewporttype_ *vt);

extern void setviewportclip(int clip);

extern void lines_(int n, double *r2points);

extern void putpixels_(int n, double *r2points, int c);

extern void putpoints_(int n, double *r2points);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
