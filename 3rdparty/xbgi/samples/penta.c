/*
 * Sample program of turtle graphics for both BGI and XBGI < strange2.c >
 *
 * タートルグラフィックスライブラリ gturtle_.h のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <math.h>
#include <gturtle_.h>

void main(void)
{
  int a = 0, n = 0, i, j, A = 2, N = 10;
  double deg = 72.0;
  int gd = DETECT, gm, c = 0;

  initgraph_(&gd, &gm, "");
  setcolor(BLACK);
  setbkcolor(WHITE);
  cleardevice();
  moveto_(200, 200);
  setangle_(0);
  
  for (i=0; i<=100; i++) {
    if (++a > A)
      a = 1;
    for (j=1; j<=5+a; j++) {
      setcolor(c=(c+1)%7+7);
      move_(20);
      turn_(RAD(deg));
    }
    setcolor(c=(c+1)%7+7);
    move_(20);
    deg = -deg;
    turn_(RAD(deg));
    if (++n > N) {
      a = -a;
      n = 0;
    }
  }
  xbgiloop();
  closegraph_();
}
