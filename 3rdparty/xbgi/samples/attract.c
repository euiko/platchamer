/*
 * Sample program of R^2 and color library for both BGI and XBGI < attract.c >
 *
 * R^2 �饤�֥�� graphr2_.h�����顼��󥰥饤�֥�� coloring.h �Υ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <setjmp.h>
#include <conio.h>
#include <graphics.h>
#include <graphr2_.h> /* R^2���֤򥵥ݡ��Ȥ��륤�󥯥롼�ɥե����� */
#include <coloring.h> /* �ѥ�åȤ򰷤�����Υġ��� */

#define BTIME 500
#define ITIME 100
int MAXCOLOR;
jmp_buf jumper;

/*
 * [����ʸ��]
 *
 * F. Aicardi and S. Invernizzi,
 *  ``Memory effects in discrete dynamical systems,''
 *  International Journal of Bifurcation and Chaos, 2, 4, 815-830, 1992.
 *
 * R. M. May,
 *  ``Simple mathematical models with very complicated dynamics,''
 *  Nature, 261, 459-467, 1976.
 */
double A, B = 0.8, X0, X1, X2;
#define F(x) A*(x)*(1.0-(x))
#define G(x1,x0) F((1.0-B)*x1+B*x0)

void iterate(void)
{
  int t;
  
  for (t=0; t<10; t++) {
    X2 = G(X1,X0);
    X0 = X1;
    X1 = X2;
  }
  for (t=0; t<ITIME; t++) {
    X2 = G(X1,X0);
    if (MAXCOLOR>1)
      putpixel_(X1, X2, t%(MAXCOLOR-1)+1); /* ������ɸ�ؤ����� */
    else
      putpixel_(X1, X2, MAXCOLOR); /* ������ɸ�ؤ����� */
    X0 = X1;
    X1 = X2;
    if (kbhit() && getch() == 0x1b)
      longjmp(jumper, 1);
  }
}

void bifurcate(void)
{
  int b;

  for (b=0; b<BTIME; b++) {
    A = 3.0 + (4.0-3.0)*b/BTIME;
    X0 = 0.1;
    X1 = 0.2;
    iterate();
  }
}

int main(void)
{
  int gd = DETECT, gm;
  int jump_val;

  initgraph_(&gd, &gm, "-geometry 400x400");
  MAXCOLOR = getmaxcolor();
  coloring(1, MAXCOLOR-1); /* RGB����ǡ�����󥫥顼�κ��� */
  setviewport_(0, 0, 400-1, 400-1, !0); /* ʪ����ɸ����� */
  setwindow_(0.0, 1.0, 1.0, 0.0); /* ������ɸ����� */

  jump_val = setjmp(jumper);
  if (jump_val == 0) {
    bifurcate();
    (void)getch();
  }

  closegraph_();
  return 0;
}
