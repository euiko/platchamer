/*
 * Sample program for event-driven programing in C++ < julia.c >
 *
 * ���٥�ȶ�ư���ץ���ߥ󥰤Τ���� C++ �ˤ�륵��ץ�
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
 * ����ꥢ����
 *
 * \[f: C \to C\] �ˤ����ơ�\[f(z) = z^3 + a\] �ˤĤ��ơ�
 * ������ \[f(z) = 0\] �˥˥塼�ȥ�ˡ��Ŭ�Ѥ���ȡ�
 * ������ \[z_{n+1} = z_n - f(z_n)/f'(z_n)f\] �����롥
 * �����ϳطϤ� \[z_0\] ���ͤˤ�äơ����뺬�ؤμ�«��ȯ���������ޤ롥
 * �����Ǥ� \[z_0\] ��ȯ�����ʤ�����ͤν���򥸥�ꥢ����ȸƤ֡�
 *
 * �ץ�����Ǥ� \[\infty\] �� ITIME��
 * ��«�Ȥߤʤ��ͤ� \[|z|=CONVERGE(=1.0e-6)\] �Ȥ��롥
 * �ޤ������� \[z_0\] �������� \[z_0 \in [z1,z2]\] �Ȥ��롥
 */

/*
 * \[z_n\] ���ϳطϤ���«�˻�ä������֤��������롥
 * \[\infty\] �ȸ��ʤ��Ƥ��� ITIME ����˼�«���ʤ��ä����ϡ�ITIME ���֤���
 * �ޤ����ɤβ�˼�«�������� INDEX ���֤���
 * ������� C �� INDEX ���ܤ˳�Ǽ����롥
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
 * SIZExSIZE���ϰϤ�1���Ǥ򥸥�ꥢ����μ�«�����ˤ������äƥڥ���Ȥ��롥
 * ���Υ롼����ϸƤФ�뤿�Ӥ�����̩�٤��⤯�ʤäƤ�����
 * X, Y �ϥӥ塼�ݡ��Ȥλ�����VWX, VWY ��ʪ����ɸ����������ɸ���Ѵ�����ޥ���
 * divide, radius, draw_x, draw_y �Ͻ���ΰ�ʬ�����ʬ���ΰ��Ĺ����
 * �����ɤ�Ĥ֤��Ƥ���ʪ����ɸ�򼨤��Ƥ��롥
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
