/*
 * Sample program to introduce to xbgi & Japanese Text < hello2.c >
 *
 * XBGI 始めのサンプルおよび日本語の表示
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>

#ifndef _XBGI_
void xbgiloop(void) { (void)getchar(); }
#endif

int main(void)
{
  int gd = DETECT, gm, cx, cy;
  int l = 300, tri[8];
  
  initgraph(&gd, &gm, "");
  cx = (getmaxx()+1)/2;
  cy = (getmaxy()+1)/2;
  setcolor(getbkcolor());
  setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  setfillstyle(SOLID_FILL, LIGHTGREEN);
  bar(cx-l/2, cy-l/2, cx+l/2, cy+l/2);
  setfillstyle(SOLID_FILL, LIGHTRED);
  fillellipse(cx, cy, l/2, l/2);
  setfillstyle(SOLID_FILL, LIGHTBLUE);
  tri[0] = cx,               tri[1] = cy - l/2;
  tri[2] = cx + l/4*3/1.732, tri[3] = cy + l/4;
  tri[4] = cx - l/4*3/1.732, tri[5] = cy + l/4;
  tri[6] = cx,               tri[7] = cy - l/2;
  fillpoly(3, tri);
  drawpoly(4, tri);
  outtextxy(cx, cy, "ようこそ XBGI へ");
  cy += textheight("H");
  outtextxy(cx, cy, "漢字(JIS,MS漢字,EUC)");
  xbgiloop();
  closegraph();
  return 0;
}
