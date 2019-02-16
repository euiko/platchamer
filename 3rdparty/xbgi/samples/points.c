/*
 * Test program for put points < points.c >
 *
 * ポイント描画のテストプログラム
 *
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <graphics.h>

#ifndef _XBGI_
void xbgiloop(void) { (void)getchar(); }
#endif

int main(void)
{
  int gd = DETECT, gm;
  int i, points[20];
  double rpoints[20];
  
  initgraph(&gd, &gm, "-geometry 600x600");
  setcolor(BLACK);
  setbkcolor(WHITE);
  cleardevice();

  setfillstyle(SOLID_FILL, BLACK);
  bar(40, 40, 60, 60);
  putpoint(50, 50);

  setpointstyle(LOZENGE_POINT, BLACK, LIGHTRED, 6);
  putpoint(100, 80);
  setpointstyle(CROSS_POINT, BLACK, LIGHTRED, 6);
  putpoint(110, 80);
  setpointstyle(SQUARE_POINT, BLACK, LIGHTRED, 6);
  putpoint(120, 80);
  setpointstyle(XCROSS_POINT, BLACK, LIGHTRED, 6);
  putpoint(130, 80);
  setpointstyle(TRIANGLE_POINT, BLACK, LIGHTRED, 6);
  putpoint(140, 80);
  setpointstyle(ASTERISK_POINT, BLACK, LIGHTRED, 6);
  putpoint(150, 80);
  setpointstyle(CIRCLE_POINT, BLACK, LIGHTRED, 6);
  putpoint(160, 80);
  setpointstyle(CHECKMARK_POINT, BLACK, LIGHTRED, 6);
  putpoint(170, 80);

  setpointstyle(LOZENGE_POINT, BLACK, WHITE, 6);
  _putpoint(100.5, 100);
  setpointstyle(CROSS_POINT, BLACK, WHITE, 6);
  _putpoint(110.5, 100);
  setpointstyle(SQUARE_POINT, BLACK, WHITE, 6);
  _putpoint(120.5, 100);
  setpointstyle(XCROSS_POINT, BLACK, WHITE, 6);
  _putpoint(130.5, 100);
  setpointstyle(TRIANGLE_POINT, BLACK, WHITE, 6);
  _putpoint(140.5, 100);
  setpointstyle(ASTERISK_POINT, BLACK, WHITE, 6);
  _putpoint(150.5, 100);
  setpointstyle(CIRCLE_POINT, BLACK, WHITE, 6);
  _putpoint(160.5, 100);
  setpointstyle(CHECKMARK_POINT, BLACK, WHITE, 6);
  _putpoint(170.5, 100);

  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=100-10*i; }
  setpointstyle(LOZENGE_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=120-10*i; }
  setpointstyle(CROSS_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=140-10*i; }
  setpointstyle(SQUARE_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=160-10*i; }
  setpointstyle(XCROSS_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=180-10*i; }
  setpointstyle(TRIANGLE_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=200-10*i; }
  setpointstyle(ASTERISK_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=220-10*i; }
  setpointstyle(CIRCLE_POINT, BLACK, BLACK, 6);
  putpoints(10, points);
  for (i=0;i<10;i++) { points[i*2]=200+10*i;points[i*2+1]=240-10*i; }
  setpointstyle(CHECKMARK_POINT, BLACK, BLACK, 6);
  putpoints(10, points);

  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=300-10*i; }
  setpointstyle(LOZENGE_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=320-10*i; }
  setpointstyle(CROSS_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=340-10*i; }
  setpointstyle(SQUARE_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=360-10*i; }
  setpointstyle(XCROSS_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=380-10*i; }
  setpointstyle(TRIANGLE_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=400-10*i; }
  setpointstyle(ASTERISK_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=420-10*i; }
  setpointstyle(CIRCLE_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);
  for (i=0;i<10;i++) { rpoints[i*2]=200+10*i+0.5;rpoints[i*2+1]=440-10*i; }
  setpointstyle(CHECKMARK_POINT, BLACK, BLACK, 6);
  _putpoints(10, rpoints);

  xbgiloop();
  closegraph();
  return 0;
}
