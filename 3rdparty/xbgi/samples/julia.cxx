/*
 * Sample program for event-driven programing in C++ < julia.c >
 *
 * イベント駆動型プログラミングのための C++ によるサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <complex>
#include <graphics.h>
#include <coloring.h>
using std::complex;

#ifdef _XBGI_
#define PD "-title JuliaSet -geometry 500x500 -ncolor 100"
#else
#include <xbgi2bgi.h>
#define PD "c:/borlandc/bgi"
#endif

/*
 * ジュリア集合
 *
 * \[f: C \to C\] において，\[f(z) = z^3 + a\] について，
 * 方程式 \[f(z) = 0\] にニュートン法を適用すると，
 * 漸化式 \[z_{n+1} = z_n - f(z_n)/f'(z_n)f\] を得る．
 * この力学系は \[z_0\] の値によって，ある根への収束か発散かがきまる．
 * ここでは \[z_0\] が発散しない初期値の集合をジュリア集合と呼ぶ．
 *
 * プログラム上では \[\infty\] を ITIME，
 * 収束とみなす値を \[|z|=CONVERGE(=1.0e-6)\] とする．
 * また，求める \[z_0\] の定義域は \[z_0 \in [z1,z2]\] とする．
 */

/*
 * \[z_n\] の力学系が収束に至ったくり返し回数を求める．
 * \[\infty\] と見なしている ITIME 以内に収束しなかった場合は，ITIME を返す．
 * また，どの解に収束したかを INDEX に返し，
 * 解は配列 C の INDEX 番目に格納される．
 */
int ITIME = 50;
double CONVERGE = 1.0e-6;
complex<double> A(1.0, 0.0);
complex<double> *C = NULL;
int N = 0, INDEX;
int julia(complex<double> z0)
{
  int i, j;
  complex<double> zn1, zn = z0;

  if (abs(zn) == 0.0)
    return ITIME;
  for (i=0; i<ITIME; i++) {
    zn1 = 2.0*zn/complex<double>(3.0, 0.0) + A/zn/zn/complex<double>(3.0, 0.0);
    if (abs(zn1-zn) < abs(zn)*CONVERGE) {
      for (j=0; j<N; j++)
        if (abs(zn1-C[j]) < CONVERGE) {
          INDEX = j;
          return i;
        }
      if (j==N) {
        N++;
        if (C == NULL)
          C = (complex<double> *)malloc(N*sizeof(complex<double>));
        else
          C = (complex<double> *)realloc(C, N*sizeof(complex<double>));
        C[j] = zn1;
        INDEX = j;
      }
      return i;
    }
    zn = zn1;
  }
  return ITIME;
}

/*
 * SIZExSIZEの範囲の1画素をジュリア集合の収束特性にしたがってペイントする．
 * このルーチンは呼ばれるたびに描画密度が高くなっていく．
 * X, Y はビューポートの始点．VWX, VWY は物理座標から論理座標へ変換するマクロ．
 * divide, radius, draw_x, draw_y は順に領域分割数，分割領域の長さ，
 * 現在塗りつぶしている物理座標を示している．
 */
int X, Y, SIZE, MAXCOLOR;
complex<double> z1(-1.5, -1.5), z2(1.5, 1.5);
#define VWX(x) ((double)(x)/SIZE*(real(z2)-real(z1))+real(z1))
#define VWY(y) ((double)(y)/SIZE*(imag(z2)-imag(z1))+imag(z1))
int divide, radius, draw_x, draw_y;
void drawing(void)
{
  radius = SIZE/divide;
  if (radius == 0)
    return;

  complex<double> z(VWX(draw_x+radius/2), VWY(draw_y+radius/2));
  int n = julia(z);
  setfillstyle(SOLID_FILL, (ITIME-n)%(MAXCOLOR-1)+1);
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
      z1 = complex<double>(VWX(prs_x), VWY(prs_y));
      z2 = complex<double>(VWX(rls_x), VWY(rls_y));
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
