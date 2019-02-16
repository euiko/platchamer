/*
 * Sample program for enhanced functions about multi-graphics < message.c >
 *
 * XBGI ��ĥ��ǽ��ʣ���Υ���ե��å��Ķ� graphix.h �Υ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <graphix.h>
/*
   XBGI �� graphix.h �򥤥󥯥롼�ɤ��롣
   ����ȡ�XBGI �Υ���ե��å����֥������Ȥ����뤳�Ȥ��Ǥ���褦�ˤʤꡢ
   ���� graphics.h ����� X �˴ؤ���إå��ե�����⥤�󥯥롼�ɤ���롣
   DOS ��Ǥϳ�ĥ��ǽ��̵�������뤿��� graphix.h ���Ѱդ���Ƥ��롣
 */
int main(int argc, char *argv[])
{
  xbgi *gr1, *gr2; 
  int gd = DETECT, gm;
  int i, x = 220, meswidth;
  char message[64] = "usage ... % message mes_str";

  if (argc > 1) {
    strcpy(message, argv[1]);
    for (i=2; i<argc; i++) {
      strcat(message, " ");
      strcat(message, argv[i]);
    }
  }
  
  gr1 = creategraph(&gd, &gm, "-geometry 100x50");
  /*settextstyle(TRIPLEX_FONT, HORIZ_DIR, 0);*/
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  cleardevice();

  gr2 = creategraph(&gd, &gm, "-geometry 100x50");
  /*settextstyle(TRIPLEX_FONT, HORIZ_DIR, 0);*/
  settextjustify(LEFT_TEXT, CENTER_TEXT);
  cleardevice();

  meswidth = textwidth(message);
  while (!kbhit()) {
    if (--x < -meswidth)
      x = 220;

    currentgraph(gr1);
    cleardevice();
    outtextxy(x, 25, message);
    xflush();
    
    currentgraph(gr2);
    cleardevice();
    outtextxy(x-120, 25, message);
    xflush();

    delay(50);
  }
  destroygraph(gr2);
  destroygraph(gr1);
  return 0;
}
