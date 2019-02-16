/*
 * Sample program for setmaxcolor, setmaxx, setmaxy < colors.c >
 *
 * XBGI ��ĥ��ǽ��setmaxcolor, setmaxx, setmaxy �Υ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>

/*
   �⤷��XBGI �Ǥʤ����ꥸ�ʥ�� BGI ��, XBGI �γ�ĥ��ǽ��Ȥ�������
   �⤷����̵�����������Ȥ��ˤϡ����󥯥롼�ɥե����� xbgi2bgi.h ��Ȥ��Ȥ褤��
   �����Ǥϡ�XBGI �γ�ĥ��ǽ��̵�������뤿��˥��󥯥롼�ɤ���Ƥ��롣
 */
#ifndef _XBGI_
#include <xbgi2bgi.h>
#endif

int WIDTH, HEIGHT, NCOLOR;

void bars(void)
{
  int i, j;

  for (i=0; i<NCOLOR/8; i++) {
    for (j=0; j<8; j++) {
      setfillstyle(SOLID_FILL, 8*i+j);
      bar(WIDTH*j/8, HEIGHT*i/(NCOLOR/8),
          WIDTH*(j+1)/8-1, HEIGHT*(i+1)/(NCOLOR/8)-1);
    }
  }
  /* �ºݤˤϡ����Υ롼����λϤ�ˡ�getmaxx, getmaxy �ʤɤ�Ȥäơ�
     ������ɥ��Υ������������ľ�������褷�������褤��*/
}
int main(void)
{
  char c;
  int gd = DETECT, gm;

  initgraph(&gd, &gm, "");
  settitle("colors");
  seticonname("colors");
  WIDTH  = getmaxx()+1;
  HEIGHT = getmaxy()+1;
  NCOLOR = getmaxcolor()+1;
  cleardevice();
  bars();
  while ((c=getch()) != 0x1b) {
    switch (c) {
    case '+':
      /*NCOLOR = min(NCOLOR+8, 256);*/
      NCOLOR = min(NCOLOR+8, 254);
      setmaxcolor(NCOLOR-1);
      break;
    case '-':
      NCOLOR = max(8, NCOLOR-8);
      setmaxcolor(NCOLOR-1);
      break;
    case '4':
      WIDTH  = max(8, WIDTH-8);
      setmaxx(WIDTH);
      break;
    case '6':
      WIDTH  = min(WIDTH+8, 1024);
      setmaxx(WIDTH);
      break;
    case '8':
      HEIGHT = max(8, HEIGHT-8);
      setmaxy(HEIGHT);
      break;
    case '2':
      HEIGHT = min(HEIGHT+8, 800);
      setmaxy(HEIGHT);
      break;
    }
    bars();
  }
  closegraph();
  return 0;
}
