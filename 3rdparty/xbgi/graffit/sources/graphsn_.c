/*
 * n-dimensional stereographic interface in graffit library < graphsn_.c >
 *
 * n-Dimensional Stereo Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphsn_.h>
#ifdef _XBGI_
#include "internal.h"
#endif

#define sg __SG
extern struct stereographtype_ sg;
#define hr __HR
extern struct hyperrotationporttype_ hr;

#ifndef HAVE_ANR
#include "matrix.h"
#endif

void linesn_(double *x1, double *x2)
{
  rntov(x1, hr.x);
  rntov(x2, hr.y);
  lines3_(hr.x[0],hr.x[1],hr.x[2], hr.y[0],hr.y[1],hr.y[2]);  
}
void linetosn_(double *x)
{
  rntov(x, hr.x);
  linetos3_(hr.x[0],hr.x[1],hr.x[2]);
}
void putpixelsn_(double *x, int c)
{
  rntov(x, hr.x);
  putpixels3_(hr.x[0],hr.x[1],hr.x[2], c);
}
void putpointsn_(double *x)
{
  rntov(x, hr.x);
  putpoints3_(hr.x[0],hr.x[1],hr.x[2]);
}
void movetosn_(double *x)
{
  rntov(x, hr.x);
  movetos3_(hr.x[0],hr.x[1],hr.x[2]);
}
void outtextxysn_(double *x, char *str)
{
  rntov(x, hr.x);
  outtextxys3_(hr.x[0],hr.x[1],hr.x[2], str);
}
void cubesn_(double *xf, double *xt, int flg)
{
  int dim, nv, ns, nsd;
  int i, j, k, a, b;
  double **v;
  int **s;
  int c = 0;

  if (flg) c = getcolor();
  if (hr.dim < 1) return;
  dim = hr.dim;
  nv = ipow2(dim);
  v = matrix(0,nv-1, 0,dim-1);
  nsd = ipow2(dim-1);
  ns = nsd*dim;
  s = imatrix(0,nsd*dim-1, 0,2);
  for (i=0; i<nv; i++)
    for (j=0; j<dim; j++)
      v[i][j] = (i/ipow2(j)%2)?xt[j]:xf[j];
  for (i=0; i<dim; i++)
    for (j=0; j<nsd; j++) {
      a = b = 0;
      for (k=0; k<dim; k++) {
        a = ((i>k)?(j/ipow2(k)%2):(i==k)?0:(j/ipow2(k-1)%2))+2*a;
        b = ((i>k)?(j/ipow2(k)%2):(i==k)?1:(j/ipow2(k-1)%2))+2*b;
      }
      s[nsd*i+j][0] = a;
      s[nsd*i+j][1] = b;
    }
  for (i=0; i<dim; i++)
    for (j=0; j<nsd; j++) {
      if (flg)
        setcolor(i%getmaxcolor()+1);
      linesn_(v[s[nsd*i+j][0]], v[s[nsd*i+j][1]]);
    }
  free_matrix(v, 0,nv-1, 0,dim-1);
  free_imatrix(s, 0,nsd*dim-1, 0,2);
  if (flg) setcolor(c);
}
void linessn_(int n, double **rnpoints)
{
  if (hr.dim < 1) return;
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      sg.start();
      sg.left();
      for (i=0; i<n; i++) {
	rntov(rnpoints[i], hr.x);
	xpoints[i].x = Xx(wvx(sltox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(sltoy(hr.x[0],hr.x[1],hr.x[2])));
      }
      XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, n, CoordModeOrigin);
      sg.right();
      for (i=0; i<n; i++) {
	rntov(rnpoints[i], hr.x);
	xpoints[i].x = Xx(wvx(srtox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(srtoy(hr.x[0],hr.x[1],hr.x[2])));
      }
      XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, n, CoordModeOrigin);
      sg.end();
      free(xpoints);
    }
    else {
      int j, d, m, im, ii;

      xpoints = (XPoint *)malloc((MAX_SAFE_XPOINTS+1)*sizeof(XPoint));
      sg.start();
      sg.left();
      d = n/MAX_SAFE_XPOINTS, m = n%MAX_SAFE_XPOINTS;
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	if (j!=d) im++;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  rntov(rnpoints[ii], hr.x);
	  xpoints[i].x = Xx(wvx(sltox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(sltoy(hr.x[0],hr.x[1],hr.x[2])));
	}
	XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		   xpoints, im, CoordModeOrigin);
      }
      sg.right();
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	if (j!=d) im++;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  rntov(rnpoints[ii], hr.x);
	  xpoints[i].x = Xx(wvx(srtox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(srtoy(hr.x[0],hr.x[1],hr.x[2])));
	}
	XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		   xpoints, im, CoordModeOrigin);
      }
      sg.end();
      free(xpoints);
    }
  }
  else if (XBGI->gdriver == PS) {
    double *r2points;
    int i;
    
    r2points = (double*)malloc(sizeof(double)*n*2);
    sg.start();
    sg.left();
    for (i=0; i<n; i++) {
      rntov(rnpoints[i], hr.x);
      r2points[2*i+0] = wvx(sltox(hr.x[0],hr.x[1],hr.x[2]));
      r2points[2*i+1] = wvy(sltoy(hr.x[0],hr.x[1],hr.x[2]));
    }
    _lines(n, r2points);
    sg.right();
    for (i=0; i<n; i++) {
      rntov(rnpoints[i], hr.x);
      r2points[2*i+0] = wvx(srtox(hr.x[0],hr.x[1],hr.x[2]));
      r2points[2*i+1] = wvy(srtoy(hr.x[0],hr.x[1],hr.x[2]));
    }
    _lines(n, r2points);
    sg.end();
    free(r2points);
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-1; i++)
      linesn_(rnpoints[i], rnpoints[i+1]);
  }
}
void putpixelssn_(int n, double **rnpoints, int c)
{
  if (hr.dim < 1) return;
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
   
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      sg.start();
      sg.left();
      XSetForeground(XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->color]);
      for (i=0; i<n; i++) {
	rntov(rnpoints[i], hr.x);
	xpoints[i].x = Xx(wvx(sltox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(sltoy(hr.x[0],hr.x[1],hr.x[2])));
      }
      XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, n, CoordModeOrigin);
      sg.right();
      XSetForeground(XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->color]);
      for (i=0; i<n; i++) {
	rntov(rnpoints[i], hr.x);
	xpoints[i].x = Xx(wvx(srtox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(srtoy(hr.x[0],hr.x[1],hr.x[2])));
      }
      XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, n, CoordModeOrigin);
      sg.end();
      free(xpoints);
    }
    else {
      int j, d, m, im, ii;

      xpoints = (XPoint *)malloc(MAX_SAFE_XPOINTS*sizeof(XPoint));
      sg.start();
      sg.left();
      XSetForeground(XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->color]);
      d = n/MAX_SAFE_XPOINTS, m = n%MAX_SAFE_XPOINTS;
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  rntov(rnpoints[ii], hr.x);
	  xpoints[i].x = Xx(wvx(sltox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(sltoy(hr.x[0],hr.x[1],hr.x[2])));
	}
	XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		    xpoints, im, CoordModeOrigin);
      }
      sg.right();
      XSetForeground(XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->color]);
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  rntov(rnpoints[ii], hr.x);
	  xpoints[i].x = Xx(wvx(srtox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(srtoy(hr.x[0],hr.x[1],hr.x[2])));
	}
	XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		    xpoints, im, CoordModeOrigin);
      }
      sg.end();
      free(xpoints);
    }
  } else
#endif
  {
    int i;
    
    for (i=0; i<n; i++)
      putpixelsn_(rnpoints[i], c);
  }
}
void putpointssn_(int n, double **rnpoints)
{
  int i;
  
  if (hr.dim < 1) return;
  for (i=0; i<n; i++)
    putpointsn_(rnpoints[i]);
}
#undef hr
#undef sg
