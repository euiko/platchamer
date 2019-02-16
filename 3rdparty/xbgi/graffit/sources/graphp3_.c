/*
 * 3-dimensional perspective graphic interface in graffit < graphp3_.c >
 *
 * 3-Dimensional Perspective Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <graphp3_.h>
#ifdef _XBGI_
#include "internal.h"
#endif

#define pp __PP

struct perspectivetype_ pp = {
  1.0,
  2.5
};

#ifdef CREATE_FUNCTION_FROM_MACRO
void (linep3_)(double x1,double y1,double z1,double x2,double y2,double z2)
{
  linep3_(x1,y1,z1,x2,y2,z2);
}
void (linetop3_)(double x,double y,double z)
{
  linetop3_(x,y,z);
}
void (putpixelp3_)(double x,double y,double z,int c)
{
  putpixelp3_(x,y,z,c);
}
void (putpointp3_)(double x,double y,double z)
{
  putpointp3_(x,y,z);
}
void (movetop3_)(double x,double y,double z)
{
  movetop3_(x,y,z);
}
void (outtextxyp3_)(double x,double y,double z,char *str)
{
  outtextxyp3_(x,y,z,str);
}
#endif /* CREATE_FUNCTION_FROM_MACRO */

void setdistance_(double d)
{
  pp.dist = 1.0/d;
}
void setdeformation_(double d)
{
  pp.deform = d;
}
void cubep3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg)
{
  int i, maxi;
  double x0, y0, z0, x1, y1, z1, maxz, z;
  static int l[12][2] = {
    { 0, 1 }, { 0, 2 }, { 0, 4 },
    { 1, 3 }, { 1, 5 },
    { 2, 3 },
    { 5, 4 },
    { 6, 4 }, { 6, 2 },
    { 7, 6 }, { 7, 5 }, { 7, 3 }, 
  };
  struct linesettingstype ls;

  getlinesettings(&ls);
  maxz = p3toz(xf, yf, zf);
  maxi = 0;
  for (i=1; i<8; i++) {
    x0 = (i/1%2)?xt:xf;
    y0 = (i/2%2)?yt:yf;
    z0 = (i/4%2)?zt:zf;
    z = p3toz(x0, y0, z0);
    if (z>maxz) {
      maxz = z;
      maxi = i;
    }
  }
  for (i=0; i<12; i++) {
    x0 = (l[i][0]/1%2)?xt:xf; x1 = (l[i][1]/1%2)?xt:xf;
    y0 = (l[i][0]/2%2)?yt:yf; y1 = (l[i][1]/2%2)?yt:yf;
    z0 = (l[i][0]/4%2)?zt:zf; z1 = (l[i][1]/4%2)?zt:zf;
    if (flg && (l[i][0]==maxi || l[i][1]==maxi))
      setlinestyle(DOTTED_LINE, 0, NORM_WIDTH);
    else
      setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    linep3_(x0, y0, z0, x1, y1, z1);
  }
  setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
}
void boxp3_(double xf, double yf, double zf, double xt,
                   double yt, double zt, int c6[])
{
  int i, j, fil[6];
  double x, y, z, xy[5*2], xyz[3][3], A[3], B[3];
  static int s[6][5] = {
    { 0, 1, 3, 2, 0 },
    { 0, 2, 6, 4, 0 },
    { 0, 4, 5, 1, 0 },
    { 1, 5, 7, 3, 1 },
    { 3, 7, 6, 2, 3 },
    { 4, 6, 7, 5, 4 },
  };
  struct fillsettingstype fs;
  
  getfillsettings(&fs);
  for (i=0; i<6; i++) {
    for (j=0; j<3; j++) {
      x = p3tox((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
      y = p3toy((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
      z = p3toz((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
      xyz[j][0] = x;
      xyz[j][1] = y;
      xyz[j][2] = z;
    }
    A[0] = xyz[1][0] - xyz[0][0];
    A[1] = xyz[1][1] - xyz[0][1];
    /*A[2] = xyz[1][2] - xyz[0][2];*/
    B[0] = xyz[2][0] - xyz[1][0];
    B[1] = xyz[2][1] - xyz[1][1];
    /*B[2] = xyz[2][2] - xyz[1][2];*/
    fil[i] = A[0]*B[1]-A[1]*B[0]<0;
  }
  for (i=0; i<6; i++) {
    if (fil[i]) {
      for (j=0; j<5; j++) {
        x = p3tox((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
        y = p3toy((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
        z = p3toz((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
        xy[2*j+0] = x;
        xy[2*j+1] = y;
      }
      setfillstyle(fs.pattern, c6?c6[i]:fs.color);
      fillpoly_(4, xy);
    }
  }
  setfillstyle(fs.pattern, fs.color);
}
void lefthandp3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg)
{
  double borderx = (xt-xf)*0.1, bordery = (yt-yf)*0.1, borderz = (zt-zf)*0.1;

  linep3_(xf-borderx, yf-bordery, zf-borderz,
           xf+borderx, yf-bordery, zf-borderz);
  linep3_(xf-borderx, yf-bordery, zf-borderz,
           xf-borderx, yf+bordery, zf-borderz);
  linep3_(xf-borderx, yf-bordery, zf-borderz,
           xf-borderx, yf-bordery, zf+borderz);
  if (flg) {
    outtextxyp3_(xf+borderx, yf-bordery, zf-borderz, "x");
    outtextxyp3_(xf-borderx, yf+bordery, zf-borderz, "y");
    outtextxyp3_(xf-borderx, yf-bordery, zf+borderz, "z");
  }
}
void linesp3_(int n, double *r3points)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n * sizeof(XPoint));
      for (i=0; i<n; i++) {
	xpoints[i].x =
	  Xx(wvx(p3tox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(p3toy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
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
	  xpoints[i].x =
	    Xx(wvx(p3tox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(p3toy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
      r2points[2*i+0] =
	wvx(p3tox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
      r2points[2*i+1] =
	wvy(p3toy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
    }
    _lines(n, r2points);
    free(r2points);
  } else 
#endif
  {
    int i;
    
    for (i=0; i<n-3; i++)
      linep3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2], 
	      r3points[3*(i+1)+0], r3points[3*(i+1)+1], r3points[3*(i+1)+2]);
  }
}
void putpixelsp3_(int n, double *r3points, int color)
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
	xpoints[i].x =
	  Xx(wvx(p3tox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(p3toy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
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
	  xpoints[i].x =
	    Xx(wvx(p3tox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(p3toy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
      putpixelp3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2], color);
  }
}
void putpointsp3_(int n, double *r3points)
{
  int i;
  
  for (i=0; i<n; i++)
    putpointp3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2]);
}
void nlinep3_(int n, double *x, double *y, double *z)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;

    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(p3tox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(p3toy(x[i],y[i],z[i])));
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
	  xpoints[i].x = Xx(wvx(p3tox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(p3toy(x[ii],y[ii],z[ii])));
	}
	XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		   xpoints, im, CoordModeOrigin);
      }
      free(xpoints);
    }
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-3; i++)
      linep3_(x[i],y[i],z[i], x[i+1],y[i+1],z[i+1]);
  }
}
void nputpixelp3_(int n, double *x, double *y, double *z, int color)
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
	xpoints[i].x = Xx(wvx(p3tox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(p3toy(x[i],y[i],z[i])));
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
	  xpoints[i].x = Xx(wvx(p3tox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(p3toy(x[ii],y[ii],z[ii])));
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
      putpixelp3_(x[i], y[i], z[i], color);
  }
}
void nputpointp3_(int n, double *x, double *y, double *z)
{
  int i;
    
  for (i=0; i<n; i++)
    putpointp3_(x[i], y[i], z[i]);
}
