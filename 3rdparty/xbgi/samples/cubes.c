/*
 * Sample program of R^n library for both BGI and XBGI < cubes.c >
 *
 * R^n �饤�֥�� graphrn_.h �Υ���ץ�
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
#include <graphrn_.h> /* n���������Ѵ��ѥå����� */
#include <graphpn_.h> /* n����Ʃ���Ѵ��ѥå����� */
#include <graphsn_.h> /* n�������ƥ쥪����եѥå����� */
#include <conio.h>

/* 0:�����Ѵ���1:Ʃ���Ѵ���2:���ƥ쥪�����I��3:���ƥ쥪�����II */
int view_type = 0;

/* 0:���г��ٲ�ž��1:���г��ٲ�ž */
int rot_type = 0;

int dim = 4;

int main(int argc, char *argv[])
{
  /*int gd = DETECT, gm;*/
  int key = 'r', i, j;
  double ROTX = 90.0, ROTY = 0.0, ROTZ = 0.0; /* ��ž�� */
  double rx, ry, rz;
  int DELTA_ROT = 3; /* ��ž������ */
  double SX = 0.0, SY = 0.0; /* �濴 */
  double MAG = 1.0; /* 2������ɸ�γ���Ψ */
  double DST = 0.5; /* ��Υ */
  int W = 150; /* 2��β����������� */
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
  hyperrotationport_(dim, xf, xt); /* ��ž�ΰ�λ��� */
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
      setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* ��ž�Ѥλ��� */
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
      hyperrotationport_(dim, xf, xt); /* ��ž�ΰ�λ��� */
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
	setrotation_(RAD(ROTX), RAD(ROTY), RAD(ROTZ)); /* ��ž�Ѥλ��� */
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
