/*
 * Sample program for primary design specifier < clock.c >
 *
 * XBGI ��ĥ��ǽ���ץ饤�ޥ�ǥ��������ҤΥ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <graphics.h>
#include <conio.h>

#ifndef _XBGI_
void xflush(void) {} /* ���ꥸ�ʥ� BGI �ʤ� xflush() ����ߡ��� */
#endif

int main(void)
{
  int gd = DETECT, gm;
  time_t clock;
  struct tm *tm;
  char str[64], fmt[64] = "%Y/%m/%d %X";

  /* ���Τ褦�� pd �ΤȤ���˥��ץ����ʸ��������Ǥ��� */
  initgraph(&gd, &gm, "-geometry 200x100+10+10 -title clock");
  settextjustify(CENTER_TEXT, CENTER_TEXT);
  cleardevice();
  while (!kbhit() || getch() != 0x1b) {
    time(&clock);
    tm = localtime(&clock);
    strftime(str, 64, fmt, tm);
    outtextxy(getmaxx()/2, getmaxy()/2, str);
    xflush();
    sleep(1);
    clearviewport();
  }
  closegraph();
  return 0;
}
