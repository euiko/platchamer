/*
 * Test program for text justify < texttest.c >
 *
 * テキスト表示位置のテストプログラム
 *
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>
#include <conio.h>

#ifndef _XBGI_
void xbgiloop(void) { (void)getchar(); }
#endif

int main(void)
{
  int gd = DETECT, gm, cx, cy;
  
  initgraph(&gd, &gm, "-geometry 600x600");
  cx = (getmaxx()+1)/2;
  cy = (getmaxy()+1)/2;
  setcolor(BLACK);
  setbkcolor(WHITE);
  setfillstyle(SOLID_FILL, getcolor());
  cleardevice();

  settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);

  settextjustify(LEFT_TEXT, TOP_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(LEFT_TEXT, TOP_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(LEFT_TEXT, CENTER_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(LEFT_TEXT, CENTER_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(LEFT_TEXT, BOTTOM_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(LEFT_TEXT, BOTTOM_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(CENTER_TEXT, TOP_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(CENTER_TEXT, TOP_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(CENTER_TEXT, CENTER_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(CENTER_TEXT, CENTER_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(CENTER_TEXT, BOTTOM_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(CENTER_TEXT, BOTTOM_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(RIGHT_TEXT, TOP_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(RIGHT_TEXT, TOP_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(RIGHT_TEXT, CENTER_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(RIGHT_TEXT, CENTER_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(RIGHT_TEXT, BOTTOM_TEXT);");
  (void)getch(); cleardevice();

  settextstyle(DEFAULT_FONT, VERT_DIR, 0);

  settextjustify(LEFT_TEXT, TOP_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(LEFT_TEXT, TOP_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(LEFT_TEXT, CENTER_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(LEFT_TEXT, CENTER_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(LEFT_TEXT, BOTTOM_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(LEFT_TEXT, BOTTOM_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(CENTER_TEXT, TOP_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(CENTER_TEXT, TOP_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(CENTER_TEXT, CENTER_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(CENTER_TEXT, CENTER_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(CENTER_TEXT, BOTTOM_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(CENTER_TEXT, BOTTOM_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(RIGHT_TEXT, TOP_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(RIGHT_TEXT, TOP_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(RIGHT_TEXT, CENTER_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(RIGHT_TEXT, CENTER_TEXT);");
  (void)getch(); cleardevice();

  settextjustify(RIGHT_TEXT, BOTTOM_TEXT);
  bar(cx-1, cy-1, cx+1, cy+1);
  outtextxy(cx, cy, "テキスト位置(RIGHT_TEXT, BOTTOM_TEXT);");
  (void)getch(); cleardevice();

  closegraph();
  return 0;
}
