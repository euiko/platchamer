/*
 * Sample program for event-driven programing < mandel.c >
 *
 * イベント駆動型プログラミングのためのサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <graphics.h>
#include <coloring.h>

#ifdef _XBGI_
#define PD "-title MandelSet -geometry 500x500 -ncolor 100"
#else
#include <xbgi2bgi.h>
#define PD "c:/borlandc/bgi"
#endif

/*
 * マンデルブロ集合
 *
 * \[f: C\to C\] において，\[f(z) = z^2 + a\] で表される \[a\in C\] について，
 * 力学系 \[z_{n+1} = f(z_n) + a\] を考える．
 * この力学系は \[z_0\] と \[a\] の値によって，その収束及び発散がきまる．
 * ここでは \[z_0\] を原点 \[O\] にとって \[n = \infty\] においても \[z_n\] が
 * 発散しない \[a\] の集合をマンデルブロ集合と呼ぶ.
 *
 * プログラム上では \[\infty\] を ITIME，
 * 発散と見なす値を \[|z|=DIVERGE(=10.0)\] とする．
 * また，求める \[a\] の定義域は \[Re(a) \in [r1,r2], Im(a) \in [i1,i2]\]
 * とする．
 */

/*
 * \[Re(a)=x, Im(a)=y\] として \[z_n\] の力学系が
 * 発散に至ったくり返し回数を求める．
 * \[\infty\] と見なしている ITIME 以内に発散しなかった場合は，ITIME を返す．
 */
int ITIME = 100;
double DIVERGE = 10.0;
int mandel(double x, double y)
{
  int i;
  double xs, ys, zx, zy;

  xs = 0.0;
  ys = 0.0;
  for (i=0; i<ITIME; i++) {
    zx = xs*xs - ys*ys + x;
    zy = 2.0 * xs * ys + y;
    xs = zx;
    ys = zy;
    if ((xs*xs + ys*ys) > DIVERGE)
      break;
  }
  return i;
}

/*
 * SIZExSIZEの範囲の1画素をマンデルブロ集合の発散特性にしたがってペイントする．
 * このルーチンは呼ばれるたびに描画密度が高くなっていく．
 * X, Y はビューポートの始点．VWX, VWY は物理座標から論理座標へ変換するマクロ．
 * divide, radius, draw_x, draw_y は順に領域分割数，分割領域の長さ，
 * 現在塗りつぶしている物理座標を示している．
 */
int X, Y, SIZE, MAXCOLOR;
double r1 = -2.5, i1 = -1.5, r2 = 0.5, i2 = 1.5;
#define VWX(x) ((double)(x)/SIZE*(r2-r1)+r1)
#define VWY(y) ((double)(y)/SIZE*(i2-i1)+i1)
int divide, radius, draw_x, draw_y;
void drawing(void)
{
  double z_r, z_i;
  int n;
  
  radius = SIZE/divide;
  if (radius == 0) return;

  z_r = VWX(draw_x+radius/2);
  z_i = VWY(draw_y+radius/2);
  n = mandel(z_r, z_i);
  if (MAXCOLOR>1)
    setfillstyle(SOLID_FILL, (ITIME-n)%(MAXCOLOR-1)+1);
  else
    setfillstyle(SOLID_FILL, (ITIME-n)%(MAXCOLOR+1));
  bar(draw_x, draw_y, draw_x+radius-1, draw_y+radius-1);

  draw_x += radius;
  if (draw_x > SIZE) {
    draw_x = 0;
    draw_y += radius;
    if (draw_y > SIZE) {
      draw_y = 0;
      divide *= 2;
    }
  }
}

/*
 * マウスのボタン1押下で領域の始点を指定，ボタン1解放で領域が定まる．
 * そしてマウスのボタン2で指定された領域の拡大を開始する．
 * ESCキーで終了．'*'キーでパレットの回転．
 * '1','2','3'でカラーの配色を換えることができる．
 */
int prs_x, prs_y, prs_flag = 0;
int rls_x, rls_y, rls_flag = 0;
int mov_x, mov_y, mov_flag = 0;

int button_press(int button, int x, int y)
{
  if (button == 1) {
    if (mov_flag)
      rectangle(prs_x, prs_y, mov_x, mov_y);
    prs_x = x - X;
    prs_y = y - Y;
    prs_flag = !0;
    rls_flag = 0;
    mov_flag = 0;
  }
  else if (button == 2)
    if (prs_flag && rls_flag) {
      r1 = VWX(prs_x);
      i1 = VWY(prs_y);
      r2 = VWX(rls_x);
      i2 = VWY(rls_y);
      draw_x = 0;
      draw_y = 0;
      divide = 2;
      prs_flag = 0;
      rls_flag = 0;
      mov_flag = 0;
    }
  return !0;
}
int button_release(int button, int x, int y)
{
  if (button == 1 && prs_flag) {
    if (prs_x != rls_x && prs_y != rls_y) {
      rls_x = x - X;
      rls_y = y - Y;
      rls_flag = !0;
    }
    else {
      prs_flag = 0;
      mov_flag = 0;
    }
  }
  else
    prs_flag = 0;
  return !0;
}
int mouse_motion(int button, int x, int y)
{
  if (button == 1 && prs_flag) {
    if (!mov_flag) {
      mov_x = prs_x;
      mov_y = prs_y;
    }
    mov_flag = !0;
    rectangle(prs_x, prs_y, mov_x, mov_y);
    rectangle(prs_x, prs_y, x - X, y - Y);
    mov_x = x - X;
    mov_y = y - Y;
  }
  return !0;
}
int key_press(int c)
{
  switch (c) {
  case '*': rotate_colors(1, MAXCOLOR-1); break;
  case '1': coloring (1, MAXCOLOR-1); break;
  case '2': coloring2(1, MAXCOLOR-1, WHITE, BLACK); break;
  case '3': coloring3(1, MAXCOLOR-1, RED, GREEN, BLUE); break;
  case 0x1b: return 0;
  }
  return !0;
}
int configure(void)
{
  static int size = 0;

  SIZE = min(getmaxx(),getmaxy()) + 1;
  if (SIZE != size) {
    setsizexy(getmaxx()+1,getmaxy()+1);
    X = (getmaxx()+1)/2 - SIZE/2;
    Y = (getmaxy()+1)/2 - SIZE/2;
    setviewport(X, Y, X+SIZE-1, Y+SIZE-1, !0);
    cleardevice();
    size = SIZE;
    divide = 2;
    draw_x = 0;
    draw_y = 0;
  }
  MAXCOLOR = getmaxcolor();
  if (MAXCOLOR - 2 > ITIME)
    ITIME = MAXCOLOR - 2;
  setcolor(MAXCOLOR);
  setwritemode(XOR_PUT);
  prs_flag = 0;
  rls_flag = 0;
  mov_flag = 0;
  draw_x = 0;
  draw_y = 0;
  return !0;
}
int noevent(void)
{
  if (!mov_flag)
    drawing();
  return !0;
}

/*
 * メインでイベント手続きの設定を行う
 */
int main(void)
{
  int gd = DETECT, gm;

  initgraph(&gd, &gm, PD);
  coloring(1, getmaxcolor()-1);

  set_button_press_handler(button_press);
  set_button_release_handler(button_release);
  set_mouse_motion_handler(mouse_motion);
  set_key_press_handler(key_press);
  set_configure_handler(configure);
  set_noevent_handler(noevent);
  
  configure();
  xbgiloop(); /* イベントループ */

  closegraph();
  return 0;
}
