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
 * SIZExSIZE���ϰϤ�1���Ǥ�ޥ�ǥ�֥����ȯ�������ˤ������äƥڥ���Ȥ��롥
 * ���Υ롼����ϸƤФ�뤿�Ӥ�����̩�٤��⤯�ʤäƤ�����
 * X, Y �ϥӥ塼�ݡ��Ȥλ�����VWX, VWY ��ʪ����ɸ����������ɸ���Ѵ�����ޥ���
 * divide, radius, draw_x, draw_y �Ͻ���ΰ�ʬ�����ʬ���ΰ��Ĺ����
 * �����ɤ�Ĥ֤��Ƥ���ʪ����ɸ�򼨤��Ƥ��롥
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
 * �ޥ����Υܥ���1�������ΰ�λ�������ꡤ�ܥ���1�������ΰ褬��ޤ롥
 * �����ƥޥ����Υܥ���2�ǻ��ꤵ�줿�ΰ�γ���򳫻Ϥ��롥
 * ESC�����ǽ�λ��'*'�����ǥѥ�åȤβ�ž��
 * '1','2','3'�ǥ��顼���ۿ��򴹤��뤳�Ȥ��Ǥ��롥
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
