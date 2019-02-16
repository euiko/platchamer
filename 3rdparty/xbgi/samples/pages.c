/*
 * Sample program for enhanced functions about page < pages.c >
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
  int i, mxx, mxy, mxx2, mxy2;
  char str[64];

  initgraph(&gd, &gm, "-npage 8");
  mxx = getmaxx();
  mxy = getmaxy();
  i = 0;
  do {
    setactivepage(i);
    setvisualpage(i);
    mxx2 = getmaxx();
    mxy2 = getmaxy();
    if (i==0 && (mxx!=mxx2 || mxy!=mxy2)) {
      setmaxx(mxx2);
      setmaxy(mxy2);
      mxx = mxx2;
      mxy = mxy2;
    }
    cleardevice();
    sprintf(str, "%d:%dx%d", i, mxx2+1, mxy2+1);
    outtextxy(10, 10, str);
    if (++i==8)
      i = 0;
  } while (getch() != 0x1b);
  closegraph();
  return 0;
}
