/*
 * Sample program for enhanced functions about multi-graphics < recurse.c >
 *
 * XBGI 拡張機能、複数のグラフィック環境のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>

/*
   このプログラムは XBGI の拡張機能のうち、DOS 上ではサポートされない
   拡張機能である、「複数のグラフィック環境の構築」のためのサンプルである。
 */
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
void mandara(int n, int x, int y, int l)
{
  int i, j;

  if (n < 0)
    return;
  setfillstyle(SOLID_FILL, (9+n)%16);
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

  initgraph(&gd, &gm, "-geometry 256x256 -title recursive_carpet");
  cleardevice();
  carpet(n, x, y, l);

  initgraph(&gd, &gm, "-geometry 256x256 -title recursive_mandara");
  cleardevice();
  mandara(n, x, y, l);

  xbgiloop();
  closegraph();
  closegraph();
  return 0;
}
