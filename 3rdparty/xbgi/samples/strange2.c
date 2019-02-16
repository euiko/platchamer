/*
 * Sample program of stereo R^3 library for both BGI and XBGI < strange2.c >
 *
 * ステレオ R^3 ライブラリ graphs3_.h のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <graphs3_.h> /* R^3空間をステレオでサポートするインクルードファイル */
#include <conio.h>
#define POINTSPARLOOP 1500

int STEREO_TYPE = ColorGlass; /* 列挙型 { ColorGlass, DoubleImage } */

int MAXCOLOR;

#define A  2.5
#define B  0.4
#define C -0.6
#define D -2.5
double E = 1.0;

void strange(void)
{
  int t;
  double x, y, z;
  double xx, yy, zz;
  double p[3*POINTSPARLOOP];
  
  x = y = z = 0.0;
  t = 0;
  while (!kbhit()) {
    for (t=0; t<POINTSPARLOOP; t++) {
      /*
       * [参考文献]
       *
       * Clifford A. Pickover 著, 高橋 時市郎・内藤 昭三 訳,
       * 「コンピュータ・カオス・フラクタル」, 第10章, 白揚社
       */
      xx =   sin(A*y) - z*cos(B*x);
      yy = z*sin(C*x) -   cos(D*y);
      zz =              E*sin(x);
      x = xx;
      y = yy;
      z = zz;
      if (MAXCOLOR>1)
	setcolor(t%(MAXCOLOR-1)+1);
      else
	setcolor(WHITE);
      /*putpixels3_(x, y, z, t%(MAXCOLOR-1)+1);*/ /* 左目右目、同時に描く */
      p[t*3+0] = x;
      p[t*3+1] = y;
      p[t*3+2] = z;
    }
    setcolor(LIGHTCYAN);
    putpixelss3_(POINTSPARLOOP, p, LIGHTCYAN); /* 左目右目、同時に描く */
  }
}

int main(void)
{
  int gd = DETECT, gm, key = 'r';
  int ROTX = -15, ROTY = 10, ROTZ = 0; /* 回転角 */
  double SX = 0.0, SY = 0.0; /* 中心 */
  double DST = 1.0; /* 距離 */
  int W = 150; /* 2枚の画像の配置幅 */

  initgraph_(&gd, &gm, "-geometry 400x400 -title strange -bkcolor 0");
  MAXCOLOR = getmaxcolor();
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
    case 'g': DST  = 1.0; break;
    case 'n': E += 0.01; break;
    case 'p': E -= 0.01; break;
    case 'T': STEREO_TYPE = (STEREO_TYPE+1)%2;
    case '<': W -= 10; break;
    case '>': W += 10; break;
    case '.': W = 150; break;
    }
    switch (key) {
    case 'r':
    case '2': case '8': case '4': case '6': case '5':
    case 'x': case 'e': case 's': case 'd': case 'c':
    case 'f': case 'g': case 'b':
    case 'n': case 'p':
    case 'T':
    case '<': case '>': case '.':
      setviewport_(0, 0, 400-1, 400-1, !0);
      setwindow_(-1.0-SX, 1.0-SY, 1.0-SX, -1.0-SY);
      setrotationport_(-2, -2, -2, 2, 2, 2); /* 回転座標の大きさの指定 */
      setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* 回転角の指定 */
      setdistance_(DST);
      setstereotype(STEREO_TYPE);
      stereowidthimages(W);
      cleardevice();
      setcolor(MAXCOLOR);
      cubes3_(-2, -2, -2, 2, 2, 2, !0); /* 左目右目、同時に描く */
      strange(); 
      break;
    }
  } while ((key=getch()) != 0x1b);
  closegraph();
  return 0;
}
