/*
 * Sample program for event-driven programing < draw.c >
 *
 * イベント駆動型プログラミングのためのサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <outtext.h>

/*
   もし、XBGI でなくオリジナルの BGI で、XBGI の拡張機能を使いたい、
   もしくは無効化したいときには、インクルードファイル xbgi2bgi.h を使うとよい。
   特にイベントループである xbgiloop が DOS にサポートされるので、
   DOS でイベント駆動型プログラムが実行できるようになる。
 */
#ifndef _XBGI_
#include <xbgi2bgi.h>
#endif

/*
   表 xbgiloop へのイベントプロシージャの指定
   ----------------------------------------------------------------------------
   イベントの種類          プロシージャ指定関数       プロシージャの引数の意味
   ----------------------------------------------------------------------------
   マウスボタンの押下      set_button_press_handler   押下ボタン番号, x, y座標
   マウスボタンの解放      set_button_release_handler 解放ボタン番号, x, y座標
   マウスモーション        set_mouse_motion_handler   ボタン状態, x, y座標
   マウスのページ侵入*     set_page_enter_handler     侵入ページ番号
   マウスのページ離脱*     set_page_leave_handler     離脱ページ番号
   キーの押下              set_key_press_handler      押下キー
   ウィンドウ構造変化*     set_configure_handler      なし
   ウィンドウエキスポーズ* set_expose_handler         なし
   イベントなし            set_noevent_handler        なし
   ----------------------------------------------------------------------------
   (注) すべてのイベントプロシージャは int 型で宣言すること。
   そのイベントプロシージャが偽を返した場合に xbgiloop はループを終える。
   また、`*' のイベントは DOS 用の xbgiloop では意味をなさない。
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
  case 0x1b: return 0; /* ESC キーでプログラム終了 */
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
