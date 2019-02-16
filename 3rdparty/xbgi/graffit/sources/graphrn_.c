/*
 * n-dimensional graphic interface in graffit library < graphrn_.c >
 *
 * n-Dimensional Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphrn_.h>
#ifdef _XBGI_
#include "internal.h"
#endif

#define hr __HR
struct hyperrotationporttype_ hr = {
  0, NULL, NULL, 1.0, NULL, NULL, NULL, NULL, NULL
};

#ifndef HAVE_ANR
#include "matrix.h"
#endif

void rntov(double *xsrc, double *xdst)
{
  int i;

  if (hr.dim < 1) return;
  for (i=0; i<hr.dim; i++)
    hr.z[i] = hr.m[i]*(xsrc[i]-hr.o[i]);
  square_matrix_mult_vector(0, hr.dim-1, hr.r, hr.z, xdst);
}
void hyperrotationport_(int dim, double *xf, double *xt)
{
  int i, j;
  
  if (hr.dim != dim && hr.o != NULL) {
    free_vector(hr.o, 0, hr.dim-1);
    free_vector(hr.m, 0, hr.dim-1);
    free_vector(hr.x, 0, hr.dim-1);
    free_vector(hr.y, 0, hr.dim-1);
    free_vector(hr.z, 0, hr.dim-1);
    free_matrix(hr.r, 0, hr.dim-1, 0, hr.dim-1);
    free_matrix(hr.a, 0, hr.dim-1, 0, hr.dim-1);
    hr.o = NULL;
    hr.m = NULL;
    hr.x = NULL;
    hr.y = NULL;
    hr.z = NULL;
    hr.r = NULL;
    hr.a = NULL;
  }
  if (hr.o == NULL) {
    hr.o = vector(0, dim-1);
    hr.m = vector(0, dim-1);
    hr.x = vector(0, dim-1);
    hr.y = vector(0, dim-1);
    hr.z = vector(0, dim-1);
    hr.r = matrix(0, dim-1, 0, dim-1);
    hr.a = matrix(0, dim-1, 0, dim-1);
    for (i=0; i<dim; i++)
      for (j=0; j<dim; j++)
	hr.r[i][j] = (i==j)?1.0:0.0;
  }
  /* initialize */
  for (i=0; i<dim; i++)
    hr.o[i] = (xf[i]+xt[i])/2;
  for (i=0; i<dim; i++)
    hr.m[i] = 1.0/(xt[i]-xf[i]);
  hr.dim = dim;
}
void hypermagnify_(double hrm)
{
  hr.mag = hrm;
  setrotationport_(-0.5/hrm, -0.5/hrm, -0.5/hrm, 0.5/hrm, 0.5/hrm, 0.5/hrm);
}
void hyperrotate_(int fx, int tx, double angle)
{
  double ca, sa;
  int i, j;
  
  if (hr.dim < 1) return;
  if (fx < 0 || hr.dim <= fx) return;
  if (tx < 0 || hr.dim <= tx) return;
  ca = cos(angle);
  sa = sin(angle);
  for (i=0; i<hr.dim; i++)
    for (j=0; j<hr.dim; j++)
      hr.a[i][j] = (i==j)?1.0:0.0;
  hr.a[fx][fx] =  ca;
  hr.a[fx][tx] = -sa;
  hr.a[tx][fx] =  sa;
  hr.a[tx][tx] =  ca;
  square_matrix_mult_matrix(0, hr.dim-1, hr.r, hr.a, hr.r);
}
void hyperrotation_(int n, int *fx, int *tx, double *angle)
{
  int i, j;

  if (hr.dim < 1) return;
  for (i=0; i<hr.dim; i++)
    for (j=0; j<hr.dim; j++)
      hr.r[i][j] = (i==j)?1.0:0.0;
  for (i=0; i<n; i++)
    hyperrotate_(fx[i], tx[i], angle[i]);
}
void linern_(double *x1, double *x2)
{
  if (hr.dim < 1) return;
  rntov(x1, hr.x);
  rntov(x2, hr.y);
  liner3_(hr.x[0],hr.x[1],hr.x[2], hr.y[0],hr.y[1],hr.y[2]);  
}
void linetorn_(double *x)
{
  if (hr.dim < 1) return;
  rntov(x, hr.x);
  linetor3_(hr.x[0],hr.x[1],hr.x[2]);
}
void putpixelrn_(double *x, int c)
{
  if (hr.dim < 1) return;
  rntov(x, hr.x);
  putpixelr3_(hr.x[0],hr.x[1],hr.x[2], c);
}
void putpointrn_(double *x)
{
  if (hr.dim < 1) return;
  rntov(x, hr.x);
  putpointr3_(hr.x[0],hr.x[1],hr.x[2]);
}
void movetorn_(double *x)
{
  rntov(x, hr.x);
  movetor3_(hr.x[0],hr.x[1],hr.x[2]);
}
void outtextxyrn_(double *x, char *str)
{
  rntov(x, hr.x);
  outtextxyr3_(hr.x[0],hr.x[1],hr.x[2], str);
}
void cubern_(double *xf, double *xt, int flg)
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
      linern_(v[s[nsd*i+j][0]], v[s[nsd*i+j][1]]);
    }
  free_matrix(v, 0,nv-1, 0,dim-1);
  free_imatrix(s, 0,nsd*dim-1, 0,2);
  if (flg) setcolor(c);
}
void linesrn_(int n, double **rnpoints)
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
	xpoints[i].x = Xx(wvx(r3tox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(r3toy(hr.x[0],hr.x[1],hr.x[2])));
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
	  xpoints[i].x = Xx(wvx(r3tox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(r3toy(hr.x[0],hr.x[1],hr.x[2])));
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
      r2points[2*i+0] = wvx(r3tox(hr.x[0],hr.x[1],hr.x[2]));
      r2points[2*i+1] = wvy(r3toy(hr.x[0],hr.x[1],hr.x[2]));
    }
    _lines(n, r2points);
    free(r2points);
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-1; i++)
      linern_(rnpoints[i], rnpoints[i+1]);
  }
}
void putpixelsrn_(int n, double **rnpoints, int c)
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
	xpoints[i].x = Xx(wvx(r3tox(hr.x[0],hr.x[1],hr.x[2])));
	xpoints[i].y = Xy(wvy(r3toy(hr.x[0],hr.x[1],hr.x[2])));
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
	  xpoints[i].x = Xx(wvx(r3tox(hr.x[0],hr.x[1],hr.x[2])));
	  xpoints[i].y = Xy(wvy(r3toy(hr.x[0],hr.x[1],hr.x[2])));
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
      putpixelrn_(rnpoints[i], c);
  }
}
void putpointsrn_(int n, double **rnpoints)
{
  int i;
    
  if (hr.dim < 1) return;
  for (i=0; i<n; i++)
    putpointrn_(rnpoints[i]);
}
#undef hr
