/*
 * Sample program of R^n library for both BGI and XBGI < cubes.c >
 *
 * R^n ライブラリ graphrn_.h のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <graphrn_.h> /* n次元視点変換パッケージ */
#include <graphpn_.h> /* n次元透視変換パッケージ */
#include <graphsn_.h> /* n次元ステレオグラフパッケージ */
#include <conio.h>

/* 0:視点変換、1:透視変換、2:ステレオグラフI、3:ステレオグラフII */
int view_type = 0;

/* 0:絶対角度回転、1:相対角度回転 */
int rot_type = 0;

int dim = 4;

int main(int argc, char *argv[])
{
  /*int gd = DETECT, gm;*/
  int key = 'r', i, j;
  double ROTX = 90.0, ROTY = 0.0, ROTZ = 0.0; /* 回転角 */
  double rx, ry, rz;
  int DELTA_ROT = 3; /* 回転微小角 */
  double SX = 0.0, SY = 0.0; /* 中心 */
  double MAG = 1.0; /* 2次元座標の拡大率 */
  double DST = 0.5; /* 距離 */
  int W = 150; /* 2枚の画像の配置幅 */
  double *xf = NULL;
  double *xt = NULL;
  xf = (double*)malloc(dim*sizeof(double));
  xt = (double*)malloc(dim*sizeof(double));
  for (i=0; i<dim; i++)
    xf[i] = -1.0*(i+1);
  for (i=0; i<dim; i++)
    xt[i] =  1.0*(i+1);

  _initgraph(argc, argv, "-geometry 400x400 -title sponge");
  /*initgraph(&gd, &gm, "-geometry 400x400 -title sponge");*/
  hyperrotationport_(dim, xf, xt); /* 回転領域の指定 */
  cleardevice();

  do {
    switch (key) {
    case 'r': cleardevice(); break;
    case '2': ROTX -= DELTA_ROT; break;
    case '8': ROTX += DELTA_ROT; break;
    case '4': ROTY += DELTA_ROT; break;
    case '6': ROTY -= DELTA_ROT; break;
    case '-': ROTZ -= DELTA_ROT; break;
    case '+': ROTZ += DELTA_ROT; break;
    case '5': ROTX = 90.0; ROTY = ROTZ = 0.0; break;
    case 'x': SY -= 0.05; break;
    case 'e': SY += 0.05; break;
    case 's': SX -= 0.05; break;
    case 'd': SX += 0.05; break;
    case 'c': SX = SY = 0.0; break;
    case 'f': DST *= 0.9; MAG *= 1.1; break;
    case 'b': DST *= 1.1; MAG *= 0.9; break;
    case 'g': DST  = 0.2; MAG  = 1.5; break;
    case '<': W -= 10; break;
    case '>': W += 10; break;
    case '.': W = 150; break;
    case 'n': dim = min(dim+1,10); break;
    case 'p': dim = max(2,dim-1); break;
    case 'T': view_type = (view_type+1)%4; break;
    case 'R':
      rot_type = (rot_type+1)%2;
      getrotation_(&rx, &ry, &rz);
      ROTX = DEG(rx);
      ROTY = DEG(ry);
      ROTZ = DEG(rz);
      setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* 回転角の指定 */
      break;
    }
    switch (key) {
    case 'n': case 'p':
      xf = (double*)realloc(xf,dim*sizeof(double));
      xt = (double*)realloc(xt,dim*sizeof(double));
      for (i=0; i<dim; i++)
	xf[i] = -1.0*(i+1);
      for (i=0; i<dim; i++)
	xt[i] =  1.0*(i+1);
      hyperrotationport_(dim, xf, xt); /* 回転領域の指定 */
      break;
    }
    switch (key) {
    case '*':
      for (i=0; i<dim; i++)
	for (j=0; j<dim; j++)
	  if (i != j)
	    hyperrotate_(i, j, RAD(DELTA_ROT)/3);
      break;
    case '/':
      for (i=0; i<dim; i++)
	for (j=0; j<dim; j++)
	  if (i != j)
	    hyperrotate_(i, j, -RAD(DELTA_ROT)/3);
      break;
    }
    switch (key) {
    case 'r':
    case '2': case '8': case '4': case '6': case '-': case '+': case '5':
    case 'x': case 'e': case 's': case 'd': case 'c':
    case 'f': case 'g': case 'b':
    case '<': case '>': case '.':
    case 'n': case 'p':
    case '*': case '/':
    case 'T':
    case 'R':
      setviewport_(0, 0, 400-1, 400-1, !0);
      setwindow_((-1.0-SX)/MAG, (1.0-SY)/MAG, (1.0-SX)/MAG, (-1.0-SY)/MAG);
      switch (rot_type) {
      case 0:
	setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* 回転角の指定 */
	break;
      case 1:
	switch (key) {
	case '2': setrotatex_(-RAD(DELTA_ROT)); break;
	case '8': setrotatex_(RAD(DELTA_ROT)); break;
	case '4': setrotatey_(RAD(DELTA_ROT)); break;
	case '6': setrotatey_(-RAD(DELTA_ROT)); break;
	case '-': setrotatez_(-RAD(DELTA_ROT)); break;
	case '+': setrotatez_(RAD(DELTA_ROT)); break;
	}
	/*getrotation_(&rx, &ry, &rz);
	ROTX = DEG(rx);
	ROTY = DEG(ry);
	ROTZ = DEG(rz);
	setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ));*/
	break;
      }
      setdistance_(DST);
      cleardevice();
      switch (view_type) {
      case 0:
	cubern_(xf, xt, !0);
	break;
      case 1:
	cubepn_(xf, xt, !0);
	break;
      case 2:
	setstereotype(ColorGlass);
	cubesn_(xf, xt, !0);
	break;
      case 3:
	setstereotype(DoubleImage);
	stereowidthimages(W);
	cubesn_(xf, xt, !0);
	break;
      }
      break;
    }
  } while ((key=getch()) != 0x1b);
  closegraph();
  return 0;
}
