/*
 * Sample program for event-driven programing < draw.c >
 *
 * ���٥�ȶ�ư���ץ���ߥ󥰤Τ���Υ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <outtext.h>

/*
   �⤷��XBGI �Ǥʤ����ꥸ�ʥ�� BGI �ǡ�XBGI �γ�ĥ��ǽ��Ȥ�������
   �⤷����̵�����������Ȥ��ˤϡ����󥯥롼�ɥե����� xbgi2bgi.h ��Ȥ��Ȥ褤��
   �ä˥��٥�ȥ롼�פǤ��� xbgiloop �� DOS �˥��ݡ��Ȥ����Τǡ�
   DOS �ǥ��٥�ȶ�ư���ץ���ब�¹ԤǤ���褦�ˤʤ롣
 */
#ifndef _XBGI_
#include <xbgi2bgi.h>
#endif

/*
   ɽ xbgiloop �ؤΥ��٥�ȥץ�������λ���
   ----------------------------------------------------------------------------
   ���٥�Ȥμ���          �ץ����������ؿ�       �ץ�������ΰ����ΰ�̣
   ----------------------------------------------------------------------------
   �ޥ����ܥ���β���      set_button_press_handler   �����ܥ����ֹ�, x, y��ɸ
   �ޥ����ܥ���β���      set_button_release_handler �����ܥ����ֹ�, x, y��ɸ
   �ޥ����⡼�����        set_mouse_motion_handler   �ܥ������, x, y��ɸ
   �ޥ����Υڡ�������*     set_page_enter_handler     �����ڡ����ֹ�
   �ޥ����Υڡ���Υæ*     set_page_leave_handler     Υæ�ڡ����ֹ�
   �����β���              set_key_press_handler      ��������
   ������ɥ���¤�Ѳ�*     set_configure_handler      �ʤ�
   ������ɥ��������ݡ���* set_expose_handler         �ʤ�
   ���٥�Ȥʤ�            set_noevent_handler        �ʤ�
   ----------------------------------------------------------------------------
   (��) ���٤ƤΥ��٥�ȥץ�������� int ����������뤳�ȡ�
   ���Υ��٥�ȥץ������㤬�����֤������� xbgiloop �ϥ롼�פ򽪤��롣
   �ޤ���`*' �Υ��٥�Ȥ� DOS �Ѥ� xbgiloop �Ǥϰ�̣��ʤ��ʤ���
 */

int main(void)
{
  int gd = DETECT, gm;
  int button_press(int button, int x, int y);
  int mouse_motion(int button_status, int x, int y);
  int key_press(int key);
  int configure(void);
  
  initgraph(&gd, &gm, "c:/borlandc/bgi");
  cleardevice();

  set_button_press_handler(button_press);
  set_button_release_handler(NULL);
  set_mouse_motion_handler(mouse_motion);
  set_key_press_handler(key_press);
  set_configure_handler(configure);
  set_noevent_handler(NULL);
  xbgiloop();

  closegraph();
  return 0;
}

int line_width = 1, line_color = 15;
int pressed_flag = 0, start_x, start_y;

int button_press(int button, int x, int y)
{
  if (button == 1 && !pressed_flag) {
    pressed_flag = !0;
    start_x = x;
    start_y = y;
  }
  else if (button == 1 && pressed_flag) {
    setcolor(line_color);
    line(start_x, start_y, x, y);
    pressed_flag = !0;
    start_x = x;
    start_y = y;
  }
  else if (button == 2 || button == 3)
    pressed_flag = 0;
  return !0;
}
int mouse_motion(int button_status, int x, int y)
{
  static char mouse_info[64] = "XXX,XXX";

  if (button_status == 0) {
    setfillstyle(SOLID_FILL, getbkcolor());
    bar(0, 0, textwidth(mouse_info), textheight(mouse_info));
    sprintf(mouse_info, "%3d,%3d", x, y);
    outtextxy(0, 0, mouse_info);
  }
  return !0;
}
int key_press(int key)
{
  line_color = getcolor();
  switch (key) {
  case '8': line_width = min(line_width+1,10); break;
  case '2': line_width = max(0,line_width-1); break;
  case '6': line_color = min(line_color+1,15); break;
  case '4': line_color = max(0,line_color-1); break;
  case 0x1b: return 0; /* ESC �����ǥץ���ཪλ */
  }
  setlinestyle(SOLID_LINE, 0, line_width);
  setcolor(line_color);
  return !0;
}
int configure(void)
{
  int width, height;

  getsizexy(&width, &height);
  setsizexy(width, height);
  cleardevice();
  pressed_flag = 0;
  return !0;
}
