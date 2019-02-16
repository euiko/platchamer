/*
 * Sample program for enhanced functions about page < pages4.c >
 *
 * XBGI ページの仕様についてのサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#ifndef _XBGI_
#include <xbgi2bgi.h>
/* これで DOS 上でもコンパイル可能になるが、プログラムとしては意味をなさない */
#endif

int main(void)
{
  int gd = DETECT, gm;
  int i;
  char str[64];
  struct sizeset {
    int x, y, w, h;
  } page[4] = {
    {   0,   0, 300, 300 },
    { 100,   0, 100, 150 },
    {  50, 100, 200, 100 },
    { 150, 150, 150, 150 },
  };

  initgraph(&gd, &gm, "-npage 4 -geometry 300x300");
  for (i=0; i<4; i++) {
    setactivepage(i);
    setvisualpage(i);
    cleardevice();
    setgeometry(page[i].x, page[i].y, page[i].w, page[i].h);
    rectangle(0, 0, getmaxx(), getmaxy());
    sprintf(str, "page: %d", i);
    outtextxy(10, 10, str);
  }
  xbgiloop();
  closegraph();
  return 0;
}
