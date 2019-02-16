/*
 * n-dimensional perspective graphic interface in graffit < graphpn_.c >
 *
 * n-Dimensional Perspective Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphpn_.h>
#ifdef _XBGI_
#include "internal.h"
#endif

#define hr __HR
extern struct hyperrotationporttype_ hr;

#ifndef HAVE_ANR
#include "matrix.h"
#endif

void linepn_(double *x1, double *x2)
{
  rntov(x1, hr.x);
  rntov(x2, hr.y);
  linep3_(hr.x[0],hr.x[1],hr.x[2], hr.y[0],hr.y[1],hr.y[2]);  
}
void linetopn_(double *x)
{
  rntov(x, hr.x);
  linetop3_(hr.x[0],hr.x[1],hr.x[2]);
}
void putpixelpn_(double *x, int c)
{
  rntov(x, hr.x);
  putpixelp3_(hr.x[0],hr.x[1],hr.x[2], c);
}
void putpointpn_(double *x)
{
  rntov(x, hr.x);
  putpointp3_(hr.x[0],hr.x[1],hr.x[2]);
}
void movetopn_(double *x)
{
  rntov(x, hr.x);
  movetop3_(hr.x[0],hr.x[1],hr.x[2]);
}
void outtextxypn_(double *x, char *str)
{
  rntov(x, hr.x);
  outtextxyp3_(hr.x[0],hr.x[1],hr.x[2], str);
}
void cubepn_(double *xf, double *xt, int flg)
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
      linepn_(v[s[nsd*i+j][0]], v[s[nsd*i+j][1]]);
    }
  free_matrix(v, 0,nv-1, 0,dim-1);
  free_imatrix(s, 0,nsd*dim-1, 0,2);
  if (flg) setcolor(c);
}
void linespn_(int n, double **rnpoints)
{
  if (hr.dim < 1) return;
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      for (i=0; i<n; i++) {
	rntov(rnpoints[i], hr.x);
	xpoints[i].x = Xx(wvx(p3tox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(p3toy(hr.x[0],hr.x[1],hr.x[2])));
      }
      XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, n, CoordModeOrigin);
      free(xpoints);
    }
    else {
      int j, d, m, im, ii;

      xpoints = (XPoint *)malloc((MAX_SAFE_XPOINTS+1)*sizeof(XPoint));
      d = n/MAX_SAFE_XPOINTS, m = n%MAX_SAFE_XPOINTS;
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	if (j!=d) im++;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  rntov(rnpoints[ii], hr.x);
	  xpoints[i].x = Xx(wvx(p3tox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(p3toy(hr.x[0],hr.x[1],hr.x[2])));
	}
	XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		   xpoints, im, CoordModeOrigin);
      }
      free(xpoints);
    }
  }
  else if (XBGI->gdriver == PS) {
    double *r2points;
    int i;

    r2points = (double*)malloc(sizeof(double)*n*2);
    for (i=0; i<n; i++) {
      rntov(rnpoints[i], hr.x);
      r2points[2*i+0] = wvx(p3tox(hr.x[0],hr.x[1],hr.x[2]));
      r2points[2*i+1] = wvy(p3toy(hr.x[0],hr.x[1],hr.x[2]));
    }
    _lines(n, r2points);
    free(r2points);
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-1; i++)
      linepn_(rnpoints[i], rnpoints[i+1]);
  }
}
void putpixelspn_(int n, double **rnpoints, int c)
{
  if (hr.dim < 1) return;
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      XSetForeground(XBGIDisplay, XBGIPixelGC,
		     XBGIPixels[minmax(0,c,XBGI->palette.size-1)]);
      for (i=0; i<n; i++) {
	rntov(rnpoints[i], hr.x);
	xpoints[i].x = Xx(wvx(p3tox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(p3toy(hr.x[0],hr.x[1],hr.x[2])));
      }
      XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, n, CoordModeOrigin);
      free(xpoints);
    }
    else {
      int j, d, m, im, ii;

      xpoints = (XPoint *)malloc(MAX_SAFE_XPOINTS*sizeof(XPoint));
      XSetForeground(XBGIDisplay, XBGIPixelGC,
		     XBGIPixels[minmax(0,c,XBGI->palette.size-1)]);
      d = n/MAX_SAFE_XPOINTS, m = n%MAX_SAFE_XPOINTS;
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  rntov(rnpoints[ii], hr.x);
	  xpoints[i].x = Xx(wvx(p3tox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(p3toy(hr.x[0],hr.x[1],hr.x[2])));
	}
	XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		    xpoints, im, CoordModeOrigin);
      }
      free(xpoints);
    }
  } else
#endif
  {
    int i;
    
    for (i=0; i<n; i++)
      putpixelpn_(rnpoints[i], c);
  }
}
void putpointspn_(int n, double **rnpoints)
{
  int i;
  
  if (hr.dim < 1) return;
  for (i=0; i<n; i++)
    putpointpn_(rnpoints[i]);
}
#undef hr
