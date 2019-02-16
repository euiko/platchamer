/*
 * Sample program for standard and enhanced functions < mandara.c >
 *
 * XBGI 基本機能と拡張機能のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>

#ifndef _XBGI_
#define xbgiloop (void)getchar
#endif

void mandara(int n, int x, int y, int l)
{
  int i, j;

  if (n < 0)
    return;
  /*setfillstyle(SOLID_FILL, (9+n)%16);*/
  setfillstyle((3+n)%USER_FILL, (9+n)%16);
  fillellipse(x+l/2, y+l/2, l/2-1, l/2-1);
  circle(x+l/2, y+l/2, l/2-1);
  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
      if (i==1 || j==1)
        mandara(n-1, x+l/3*i, y+l/3*j, l/3);
}
int main(void)
{
  int gd = DETECT, gm;
  int n = 3, x = 20, y = 20, l = 216;

  initgraph(&gd, &gm, "-geometry 256x256 -title mandara");
  cleardevice();

  mandara(n, x, y, l);

  xbgiloop();
  closegraph();
  return 0;
}
