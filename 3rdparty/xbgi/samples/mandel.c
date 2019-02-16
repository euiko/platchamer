/*
 * Sample program for event-driven programing < mandel.c >
 *
 * ���٥�ȶ�ư���ץ���ߥ󥰤Τ���Υ���ץ�
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
 * �ޥ�ǥ�֥���
 *
 * \[f: C\to C\] �ˤ����ơ�\[f(z) = z^2 + a\] ��ɽ����� \[a\in C\] �ˤĤ��ơ�
 * �ϳط� \[z_{n+1} = f(z_n) + a\] ��ͤ��롥
 * �����ϳطϤ� \[z_0\] �� \[a\] ���ͤˤ�äơ����μ�«�ڤ�ȯ�������ޤ롥
 * �����Ǥ� \[z_0\] ���� \[O\] �ˤȤä� \[n = \infty\] �ˤ����Ƥ� \[z_n\] ��
 * ȯ�����ʤ� \[a\] �ν����ޥ�ǥ�֥���ȸƤ�.
 *
 * �ץ�����Ǥ� \[\infty\] �� ITIME��
 * ȯ���ȸ��ʤ��ͤ� \[|z|=DIVERGE(=10.0)\] �Ȥ��롥
 * �ޤ������� \[a\] �������� \[Re(a) \in [r1,r2], Im(a) \in [i1,i2]\]
 * �Ȥ��롥
 */

/*
 * \[Re(a)=x, Im(a)=y\] �Ȥ��� \[z_n\] ���ϳطϤ�
 * ȯ���˻�ä������֤��������롥
 * \[\infty\] �ȸ��ʤ��Ƥ��� ITIME �����ȯ�����ʤ��ä����ϡ�ITIME ���֤���
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
 * SIZE_XxSIZE_Y���ϰϤ�1���Ǥ�ޥ�ǥ�֥����ȯ�������˽��äƥڥ���Ȥ��롥
 * ���Υ롼����ϸƤФ�뤿�Ӥ�����̩�٤��⤯�ʤäƤ�����
 * X, Y �ϥӥ塼�ݡ��Ȥλ�����VWX, VWY ��ʪ����ɸ����������ɸ���Ѵ�����ޥ���
 * divide, (radius_x, radius_y), (draw_x, draw_y) �Ͻ���ΰ�ʬ�����
 * ʬ���ΰ��Ĺ���������ɤ�Ĥ֤��Ƥ���ʪ����ɸ�򼨤��Ƥ��롥
 */
int X, Y, SIZE_X, SIZE_Y, MAXCOLOR;
double r1 = -2.5, i1 = -1.5, r2 = 0.5, i2 = 1.5;
#define VWX(x) ((double)(x)/SIZE_X*(r2-r1)+r1)
#define VWY(y) ((double)(y)/SIZE_Y*(i2-i1)+i1)
int divide, radius_x, radius_y, draw_x, draw_y;
void drawing(void)
{
  double z_r, z_i;
  int n;
  
  radius_x = SIZE_X/divide;
  radius_y = SIZE_Y/divide;
  if (radius_x == 0 && radius_y ==0) return;

  z_r = VWX(draw_x+radius_x/2);
  z_i = VWY(draw_y+radius_y/2);
  n = mandel(z_r, z_i);
  if (MAXCOLOR>1)
    setfillstyle(SOLID_FILL, (ITIME-n)%(MAXCOLOR-1)+1);
  else
    setfillstyle(SOLID_FILL, (ITIME-n)%(MAXCOLOR+1));
  bar(draw_x, draw_y, draw_x+radius_x-1, draw_y+radius_y-1);

  draw_x += radius_x;
  if (draw_x > SIZE_X) {
    draw_x = 0;
    draw_y += radius_y;
    if (draw_y > SIZE_Y) {
      draw_y = 0;
      divide *= 2;
    }
  }
}

/*
 * �ޥ����Υܥ���1�������ΰ�λ�������ꡤ�ܥ���1�������ΰ褬��ޤ롥
 * �����ƥޥ����Υܥ���2�ǻ��ꤵ�줿�ΰ�γ���򳫻Ϥ��롥
 * ESC�����ǽ�λ��'*'�����ǥѥ�åȤβ�ž��
 * '1','2','3'�ǥ��顼���ۿ��򴹤��뤳�Ȥ��Ǥ��롥
 */
struct squeak {
  int x, y;
  int flag;
} press = {0,0,0}, release = {0,0,0}, motion = {0,0,0};

int button_press(int button, int x, int y)
{
  if (button == 1) {
    if (motion.flag)
      rectangle(press.x, press.y, motion.x, motion.y);
    press.x = x - X;
    press.y = y - Y;
    press.flag = !0;
    release.flag = 0;
    motion.flag = 0;
  }
  else if (button == 2)
    if (press.flag && release.flag) {
      r1 = VWX(press.x);
      i1 = VWY(press.y);
      r2 = VWX(release.x);
      i2 = VWY(release.y);
      draw_x = 0;
      draw_y = 0;
      divide = 2;
      press.flag = 0;
      release.flag = 0;
      motion.flag = 0;
    }
  return !0;
}
int button_release(int button, int x, int y)
{
  if (button == 1 && press.flag) {
    if (press.x != release.x && press.y != release.y) {
      release.x = x - X;
      release.y = y - Y;
      release.flag = !0;
    }
    else {
      press.flag = 0;
      motion.flag = 0;
    }
  }
  else
    press.flag = 0;
  return !0;
}
int mouse_motion(int button, int x, int y)
{
  if (button == 1 && press.flag) {
    if (!motion.flag) {
      motion.x = press.x;
      motion.y = press.y;
    }
    motion.flag = !0;
    rectangle(press.x, press.y, motion.x, motion.y);
    rectangle(press.x, press.y, x - X, y - Y);
    motion.x = x - X;
    motion.y = y - Y;
  }
  return !0;
}
int key_press(int c)
{
  switch (c) {
  case '*': rotate_colors(1, MAXCOLOR-1); break;
  case 'c':
    { /* since 20001215 */
      static int coloringkind = COLORING_RGB;

      coloringkind = (coloringkind+1)%N_COLORING;
      setcoloringtype(coloringkind);
    }
    coloring(1, MAXCOLOR-1);
    break;
  case '1': coloring (1, MAXCOLOR-1); break;
  case '2': coloring2(1, MAXCOLOR-1, WHITE, BLACK); break;
  case '3': coloring3(1, MAXCOLOR-1, RED, GREEN, BLUE); break;
  case 0x1b: return 0;
  }
  return !0;
}
int configure(void)
{
  static int size_x = 0, size_y = 0;

  SIZE_X = getmaxx() + 1;
  SIZE_Y = getmaxy() + 1;
  if (SIZE_X != size_x || SIZE_Y != size_y) {
    setsizexy(getmaxx()+1,getmaxy()+1);
    X = (getmaxx()+1)/2 - SIZE_X/2;
    Y = (getmaxy()+1)/2 - SIZE_Y/2;
    setviewport(X, Y, X+SIZE_X-1, Y+SIZE_Y-1, !0);
    cleardevice();
    size_x = SIZE_X;
    size_y = SIZE_Y;
    divide = 2;
    draw_x = 0;
    draw_y = 0;
  }
  MAXCOLOR = getmaxcolor();
  if (MAXCOLOR - 2 > ITIME)
    ITIME = MAXCOLOR - 2;
  setcolor(MAXCOLOR);
  setwritemode(XOR_PUT);
  press.flag = 0;
  release.flag = 0;
  motion.flag = 0;
  draw_x = 0;
  draw_y = 0;
  return !0;
}
int noevent(void)
{
  if (!motion.flag)
    drawing();
  return !0;
}

/*
 * �ᥤ��ǥ��٥�ȼ�³���������Ԥ�
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
  xbgiloop(); /* ���٥�ȥ롼�� */

  closegraph();
  return 0;
}
