/*
 * Sample program for standard and enhanced functions < carpet.c >
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

void carpet(int n, int x, int y, int l)
{
  int i, j;

  if (n < 0)
    return;
  setfillstyle(SOLID_FILL, (9+n)%16);
  bar(x+l/3, y+l/3, x+l/3*2-1, y+l/3*2-1);
  rectangle(x+l/3, y+l/3, x+l/3*2-1, y+l/3*2-1);
  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
      if (i!=1 || i!=j)
        carpet(n-1, x+l/3*i, y+l/3*j, l/3);
}
int do_carpet(void)
{
  int n = 3, x = 20, y = 20, l = 216;
  carpet(n, x, y, l);
  return !0;
}
int main(void)
{
  int gd = DETECT, gm;

  initgraph(&gd, &gm, "-geometry 256x256 -title carpet");
  cleardevice();

  do_carpet();

  set_expose_handler(do_carpet);
  xbgiloop();
  closegraph();
  return 0;
}
