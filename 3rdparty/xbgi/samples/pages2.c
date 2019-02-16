/*
 * Sample program for enhanced functions about page < pages2.c >
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
  int i, xsize, ysize, xsize2, ysize2;
  char str[64];

  initgraph(&gd, &gm, "-npage 8");
  getsizexy(&xsize, &ysize);
  i = 0;
  do {
    setactivepage(i);
    setvisualpage(i);
    getsizexy(&xsize2, &ysize2);
    if (i==0 && (xsize!=xsize2 || ysize!=ysize2)) {
      setsizexy(xsize2, ysize2);
      xsize = xsize2;
      ysize = ysize2;
    }
    cleardevice();
    sprintf(str, "%d:%dx%d", i, xsize2, ysize2);
    outtextxy(10, 10, str);
    if (++i==8)
      i = 0;
  } while (getch() != 0x1b);
  closegraph();
  return 0;
}
