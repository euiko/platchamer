/*
 * Sample program for enhanced functions about page < pages3.c >
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
  int i, c;
  char str[64];

  initgraph(&gd, &gm, "-npage 3");
  for (i=0; i<3; i++) {
    setactivepage(i);
    sprintf(str, "page: %d", i);
    outtextxy(10, 10, str);
  }
  i = 0;
  while ((c=getch()) != 0x1b) {
    switch (c) {
    case '8':
      if (i < 3)
        setvisualpage(++i);
      break;
    case '2':
      if (0 < i)
        setvisualpage(--i);
      break;
    }
  }
  closegraph();
  return 0;
}
