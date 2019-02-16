/*
 * 2-dimensional graphic interface in graffit library < graphr2_.c >
 *
 * R^2 Window Port for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <graphr2_.h>
#ifdef _XBGI_
#include <graphix.h>
#endif
#ifdef _XBGI_
#include "internal.h"
#endif

#define w __W
#define v __V

struct windowtype_ w = { 0, 0, 639, 399, 639, 399 };
struct viewporttype_ v = { 0, 0, 639, 399, !0 };

#ifdef CREATE_FUNCTION_FROM_MACRO

void (arc_)(double x,double y,double stt,double end,double r)
{
  arc_(x,y,stt,end,r);
}

void (bar_)(double x1,double y1,double x2,double y2)
{
  bar_(x1,y1,x2,y2);
}

void (bar3d_)(double x1,double y1,double x2,double y2,double w,int flg)
{
  bar3d_(x1,y1,x2,y2,w,flg);
}

void (circle_)(double x,double y,double r)
{
  circle_(x,y,r);
}

#if 0
void (closegraph_)(void)
{
  closegraph_();
}
void (clearviewport_)(void)
{
  clearviewport_();
}
#endif

void (ellipse_)(double x,double y,double stt,double end,double xr,double yr)
{
  ellipse_(x,y,stt,end,xr,yr);
}

void (fillellipse_)(double x,double y,double xr,double yr)
{
  fillellipse_(x,y,xr,yr);
}

void (floodfill_)(double x,double y,int border)
{
  floodfill_(x,y,border);
}

void (getimage_)(double x1,double y1,double x2,double y2,void *bm)
{
  getimage_(x1,y1,x2,y2,bm);
}

double (getmaxx_)(void)
{
  return getmaxx_();
}

double (getmaxy_)(void)
{
  return getmaxy_();
}

int (getpixel_)(double x,double y)
{
  return getpixel(wvx(x),wvy(y));
}

double (getx_)(void)
{
  return vwx(getx());
}

double (gety_)(void)
{
  return vwy(gety());
}

int (imagesize_)(x1,y1,x2,y2)
{
  return imagesize(wvx(x1),wvy(y1),wvx(x2),wvy(y2));
}

void (line_)(double x1,double y1,double x2,double y2)
{
  line_(x1,y1,x2,y2);
}

void (lineto_)(double x,double y)
{
  lineto_(x,y);
}

void (moverel_)(double dx,double dy)
{
  moverel_(dx,dy);
}

void (moveto_)(double x,double y)
{
  moveto_(x,y);
}

void (outtextxy_)(double x,double y,char *textstring)
{
  outtextxy_(x,y,textstring);
}

void (pieslice_)(double x,double y,double stt,double end,double r)
{
  pieslice_(x,y,stt,end,r);
}

void (putimage_)(double x,double y,void *bm,int op)
{
  putimage_(x,y,bm,op);
}

void (putpixel_)(double x,double y,int c)
{
  putpixel_(x,y,c);
}

void (putpoint_)(double x,double y)
{
  putpoint_(x,y);
}

void (rectangle_)(double x1,double y1,double x2,double y2)
{
  rectangle_(x1,y1,x2,y2);
}

void (sector_)(double x,double y,double stt,double end,double xr,double yr)
{
  sector_(x,y,stt,end,xr,yr);
}

void (setaspectratio_)(double x,double y)
{
  setaspectratio_(x,y);
}

void (setusercharsize_)(double x,double dx,double y,double dy)
{
  setusercharsize_(x,dx,y,dy);
}

double (textheight_)(char *xxx)
{
  return x_f(textheight(xxx));
}

double (textwidth_)(char *xxx)
{
  return y_f(textwidth(xxx));
}

#endif /* CREATE_FUNCTION_FROM_MACRO */

void drawpoly_(int n, double *dp)
{
#ifndef _XBGI_
  int i, *ip;
  
  ip = (int*)malloc(sizeof(int)*2*n);
  for (i=0; i<2*n; i++)
    ip[i] = (i%2==0)?wvx(dp[i]):wvy(dp[i]);
  drawpoly(n, ip);
  free(ip);
#else
  int i;
  double *p;
  
  p = (double*)malloc(sizeof(double)*2*n);
  for (i=0; i<2*n; i++)
    p[i] = (i%2==0)?wvx(dp[i]):wvy(dp[i]);
  _drawpoly(n, p);
  free(p);
#endif
}

void fillpoly_(int n, double *dp)
{
#ifndef _XBGI_
  int i, *ip;

  ip = (int*)malloc(sizeof(int)*2*n);
  for (i=0; i<2*n; i++)
    ip[i] = (i%2==0)?wvx(dp[i]):wvy(dp[i]);
  fillpoly(n, ip);
  free(ip);
#else
  int i;
  double *p;

  p = (double*)malloc(sizeof(double)*2*n);
  for (i=0; i<2*n; i++)
    p[i] = (i%2==0)?wvx(dp[i]):wvy(dp[i]);
  _fillpoly(n, p);
  free(p);
#endif
}

void setviewport_(double left, double top,
		  double right, double bottom, int clip)
{
  setviewport((int)left, (int)top, (int)right, (int)bottom, clip);
  v.left   = left;
  v.top    = top;
  v.right  = right;
  v.bottom = bottom;
  v.clip   = clip;
  w.mx = (v.right-v.left)/(w.right-w.left);
  w.my = (v.bottom-v.top)/(w.bottom-w.top);
}

void setwindow_(double left, double top, double right, double bottom)
{
  w.left   = left;
  w.top    = top;
  w.right  = right;
  w.bottom = bottom;
  w.mx = (v.right-v.left)/(w.right-w.left);
  w.my = (v.bottom-v.top)/(w.bottom-w.top);
}

void initgraph_(int *gd, int *gm, char *gp)
{
  int gerr;

  initgraph(gd, gm, gp);
  gerr = graphresult();
  if (gerr != grOk) return;
  setviewport_(0, 0, getmaxx_(), getmaxy_(), !0);
  setwindow_(0, 0, getmaxx_(), getmaxy_());
}

#ifdef _XBGI_
xbgi *creategraph_(int *gd, int *gm, char *gp)
{
  int gerr;
  xbgi *this;

  this = creategraph(gd, gm, gp);
  gerr = graphresult();
  if (gerr != grOk) return NULL;
  setviewport_(0, 0, getmaxx_(), getmaxy_(), !0);
  setwindow_(0, 0, getmaxx_(), getmaxy_());
  return(this);
}
#endif

void getwindowsettings_(struct windowtype_ *wp)
{
  *wp = w;
}

void getviewsettings_(struct viewporttype_ *vp)
{
  *vp = v;
}

void setviewportclip(int clip)
{
  struct viewporttype cv;

  getviewsettings(&cv);
  setviewport(cv.left, cv.top, cv.right, cv.bottom, clip);
}

void lines_(int n, double *r2points)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;

    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(r2points[2*i+0]));
	xpoints[i].y = Xy(wvy(r2points[2*i+1]));
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
	  xpoints[i].x = Xx(wvx(r2points[2*ii+0]));
	  xpoints[i].y = Xy(wvy(r2points[2*ii+1]));
	}
	XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		   xpoints, im, CoordModeOrigin);
      }
      free(xpoints);
    }
  }
  else if (XBGI->gdriver == PS) {
    double *_r2points;
    int i;
    
    _r2points = (double*)malloc(sizeof(double)*n*2);
    for (i=0; i<n; i++) {
      _r2points[2*i+0]
	= wvx(r2points[2*i+0]);
      _r2points[2*i+1]
	= wvy(r2points[2*i+1]);
    }
    _lines(n, _r2points);
    free(_r2points);
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-2; i++)
      line_(r2points[2*i+0], r2points[2*i+1],
	    r2points[2*(i+1)+0], r2points[2*(i+1)+1]);
  }
}

void putpixels_(int n, double *r2points, int color)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      XSetForeground(XBGIDisplay, XBGIPixelGC,
		     XBGIPixels[minmax(0,color,XBGI->palette.size-1)]);
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(r2points[2*i+0]));
	xpoints[i].y = Xy(wvy(r2points[2*i+1]));
      }
      XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, n, CoordModeOrigin);
      free(xpoints);
    }
    else {
      int j, d, m, im, ii;

      xpoints = (XPoint *)malloc(MAX_SAFE_XPOINTS*sizeof(XPoint));
      XSetForeground(XBGIDisplay, XBGIPixelGC,
		     XBGIPixels[minmax(0,color,XBGI->palette.size-1)]);
      d = n/MAX_SAFE_XPOINTS, m = n%MAX_SAFE_XPOINTS;
      for (j=0; j<(m?(d+1):d); j++) {
	im = (j!=d)?MAX_SAFE_XPOINTS:m;
	for (i=0; i<im; i++) {
	  ii = MAX_SAFE_XPOINTS*j + i;
	  xpoints[i].x = Xx(wvx(r2points[2*ii+0]));
	  xpoints[i].y = Xy(wvy(r2points[2*ii+1]));
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
      putpixel_(r2points[2*i+0], r2points[2*i+1], color);
  }
}

void putpoints_(int n, double *dp)
{
#ifndef _XBGI_
  int i, *ip;

  ip = (int*)malloc(sizeof(int)*2*n);
  for (i=0; i<2*n; i++)
    ip[i] = (i%2==0)?wvx(dp[i]):wvy(dp[i]);
  putpoints(n, ip);
  free(ip);
#else
  int i;
  double *p;

  p = (double*)malloc(sizeof(double)*2*n);
  for (i=0; i<2*n; i++)
    p[i] = (i%2==0)?wvx(dp[i]):wvy(dp[i]);
  _putpoints(n, p);
  free(p);
#endif
}

#undef w
#undef v
