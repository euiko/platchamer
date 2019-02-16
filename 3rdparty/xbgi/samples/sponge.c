/*
 * Sample program of perspective R^3 library for both BGI and XBGI < sponge.c >
 *
 * 遠近法 R^3 ライブラリ graphp3_.h のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <graphp3_.h> /* 遠近感つきR^3空間をサポートするインクルードファイル */
#include <conio.h>

void sponge(int n, double x, double y, double z, double l)
{
  int i, j, k;
  int c[6];

  if (n <= 0)
    return;
  c[0] = c[2] = c[4] = (10+n)%16, c[1] = c[3] = c[5] = (10+n)%16 - 8;
  boxp3_(x+l/6, y+l/6, z+l/6, x-l/6, y-l/6, z-l/6, c); /* 箱を描く */
  for (i=-1; i<2; i+=1)
    for (j=-1; j<2; j+=1)
      for (k=-1; k<2; k+=1)
        if (i!=0 || j!=0 || k!=0)
          sponge(n-1, x+l/3*i, y+l/3*j, z+l/3*k, l/3);
}

int main(void)
{
  int gd = DETECT, gm;
  int n = 2, key = 'r';
  double x = 0, y = 0, z = 0, l = 1;
  int ROTX = -15, ROTY = 10, ROTZ = 0; /* 回転角 */
  double SX = 0.0, SY = 0.0; /* 中心 */
  double DST = 0.2; /* 距離 */

  initgraph_(&gd, &gm, "-geometry 400x400 -title sponge");
  cleardevice();

  do {
    switch (key) {
    case 'r': cleardevice(); break;
    case '2': ROTX -= 5; ROTX = (ROTX+360)%360; break;
    case '8': ROTX += 5; ROTX = (ROTX+360)%360; break;
    case '4': ROTY += 5; ROTY = (ROTY+360)%360; break;
    case '6': ROTY -= 5; ROTY = (ROTY+360)%360; break;
    case '5': ROTX = ROTY = 0.0; break;
    case 'x': SY -= 0.05; break;
    case 'e': SY += 0.05; break;
    case 's': SX -= 0.05; break;
    case 'd': SX += 0.05; break;
    case 'c': SX = SY = 0.0; break;
    case 'f': DST *= 0.9; break;
    case 'b': DST *= 1.1; break;
    case 'g': DST  = 0.2; break;
    case 'n': n = min(n+1,3); break;
    case 'p': n = max(0,n-1); break;
    }
    switch (key) {
    case 'r':
    case '2': case '8': case '4': case '6': case '5':
    case 'x': case 'e': case 's': case 'd': case 'c':
    case 'f': case 'g': case 'b':
    case 'n': case 'p':
      setviewport_(0, 0, 400-1, 400-1, !0);
      setwindow_(-1.0-SX, 1.0-SY, 1.0-SX, -1.0-SY);
      setrotationport_(-1, -1, -1, 1, 1, 1); /* 回転座標の大きさの指定 */
      setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* 回転角の指定 */
      setdistance_(DST);
      cleardevice();
      sponge(n, x, y, z, l); 
      break;
    }
  } while ((key=getch()) != 0x1b);
  closegraph();
  return 0;
}
