/*
 * Sample program of int-type axes library for both BGI and XBGI < axes.c >
 *
 * 整数版、軸描画用ライブラリ axes.h のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <axes.h>

int main(int argc, char *argv[])
{
  int gd = DETECT, gm;

  initgraph(&gd, &gm, "-geometry 600x600 -ncolor 16 -color 15 -bkcolor 0");
  cleardevice();
  setviewport(50, 50, 550, 550, 0);
  setfillstyle(SOLID_FILL, GREEN);
  bar(0, 0, 500, 500); drawaxisl(2, 2, 6, 10);
  getch(); cleardevice();
  bar(0, 0, 500, 500); drawaxeslb(5, 2, 2, 1, 6, 10);
  getch(); cleardevice();
  bar(0, 0, 500, 500); drawaxisix(2, 0, 6, 50);
  getch(); cleardevice();
  bar(0, 0, 500, 500); drawaxesi(0, 0, 0, 0, 6, 50, 10);
  getch(); cleardevice();
  closegraph();
  return 0;
}
