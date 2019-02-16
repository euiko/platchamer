/*
 * Sample program of stereo R^3 library for both BGI and XBGI < strange2.c >
 *
 * ���ƥ쥪 R^3 �饤�֥�� graphs3_.h �Υ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <graphs3_.h> /* R^3���֤򥹥ƥ쥪�ǥ��ݡ��Ȥ��륤�󥯥롼�ɥե����� */
#include <conio.h>
#define POINTSPARLOOP 1500

int STEREO_TYPE = ColorGlass; /* ��� { ColorGlass, DoubleImage } */

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
       * [����ʸ��]
       *
       * Clifford A. Pickover ��, �ⶶ ����Ϻ����ƣ ���� ��,
       * �֥���ԥ塼�������������ե饯�����, ��10��, ���ȼ�
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
      /*putpixels3_(x, y, z, t%(MAXCOLOR-1)+1);*/ /* ���ܱ��ܡ�Ʊ�������� */
      p[t*3+0] = x;
      p[t*3+1] = y;
      p[t*3+2] = z;
    }
    setcolor(LIGHTCYAN);
    putpixelss3_(POINTSPARLOOP, p, LIGHTCYAN); /* ���ܱ��ܡ�Ʊ�������� */
  }
}

int main(void)
{
  int gd = DETECT, gm, key = 'r';
  int ROTX = -15, ROTY = 10, ROTZ = 0; /* ��ž�� */
  double SX = 0.0, SY = 0.0; /* �濴 */
  double DST = 1.0; /* ��Υ */
  int W = 150; /* 2��β����������� */

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
      setrotationport_(-2, -2, -2, 2, 2, 2); /* ��ž��ɸ���礭���λ��� */
      setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* ��ž�Ѥλ��� */
      setdistance_(DST);
      setstereotype(STEREO_TYPE);
      stereowidthimages(W);
      cleardevice();
      setcolor(MAXCOLOR);
      cubes3_(-2, -2, -2, 2, 2, 2, !0); /* ���ܱ��ܡ�Ʊ�������� */
      strange(); 
      break;
    }
  } while ((key=getch()) != 0x1b);
  closegraph();
  return 0;
}
