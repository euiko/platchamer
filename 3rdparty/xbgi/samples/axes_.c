/*
 * Sample program of double-type axes library for both BGI and XBGI < axes_.c >
 *
 * 浮動小数点版、軸描画用ライブラリ axes_.h のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <axes_.h>

int main(int argc, char *argv[])
{
  int gd = DETECT, gm;

  initgraph(&gd, &gm, "-geometry 600x600 -ncolor 16 -color 15 -bkcolor 0");
  cleardevice();
  setviewport_(50, 50, 550, 550, 0);
  setwindow_(-1.0, 10.0, 1.0, -10.0);
  setfillstyle(SOLID_FILL, BLUE);
  settextstyle(SMALL_FONT, HORIZ_DIR, 1);
  bar_(-1.0, 10, 1.0, -10); drawaxisl_(2, 2, 6, 10);
  getch(); cleardevice();
  bar_(-1.0, 10, 1.0, -10); drawaxeslb_(5, 2, 2, 1, 6, 10);
  getch(); cleardevice();
  bar_(-1.0, 10, 1.0, -10); drawaxisix_(2, 0, 6, 0.0);
  getch(); cleardevice();
  bar_(-1.0, 10, 1.0, -10); drawaxesi_(0, 0, 0, 0, 6, 0.0, -0.8);
  getch(); cleardevice();
  closegraph();
  return 0;
}
