/*
 * 3-dimensional stereographic interface in graffit library < graphs3_.c >
 *
 * 3-Dimensional Stereo Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <graphs3_.h>
#ifdef _XBGI_
#include "internal.h"
#endif

#define sg __SG

static void ColorGlassSproc(void)
{
  sg.c = getcolor();
  getfillsettings(&sg.fs);
#ifdef _XBGI_
  getpointsettings(&sg.ps);
#endif
}
static void ColorGlassLproc(void)
{
  setcolor(LIGHTRED);
  /*setfillstyle(CLOSE_DOT_FILL, RED);*/ /* before 3.02 generic 19991023 */
  setfillstyle(CLOSE_DOT_FILL, LIGHTRED);
#ifdef _XBGI_ /* since version 3.02 generic 19991023 */
  setpointstyle(sg.ps.type, LIGHTRED, LIGHTRED, sg.ps.size);
#endif
}
static void ColorGlassRproc(void)
{
  setcolor(LIGHTBLUE);
  /*setfillstyle(CLOSE_DOT_FILL, BLUE);*/ /* before 3.02 generic 19991023 */
  setfillstyle(CLOSE_DOT_FILL, LIGHTBLUE);
#ifdef _XBGI_ /* since version 3.02 generic 19991023 */
  setpointstyle(sg.ps.type, LIGHTBLUE, LIGHTBLUE, sg.ps.size);
#endif
}
static void ColorGlassEproc(void)
{
  setcolor(sg.c);
  setfillstyle(sg.fs.pattern, sg.fs.color);
#ifdef _XBGI_ /* since version 3.02 generic 19991023 */
  setpointstyle(sg.ps.type, sg.ps.color, sg.ps.fillcolor, sg.ps.size);
#endif
}

void stereowidthimages(int width)
{
  sg.wi = width;
}
static void DoubleImageSproc(void)
{
  getviewsettings_(&sg.v);
}
static void DoubleImageLproc(void)
{
#ifdef _XBGI_
  if (XBGI->gdriver == PS) {
    setviewport_((sg.v.right+sg.v.left*3)/4-sg.wi/2,
		 (sg.v.bottom+sg.v.top*3)/4,
		 (sg.v.right*3+sg.v.left)/4-sg.wi/2,
		 (sg.v.bottom*3+sg.v.top)/4,
		 0);
  } else 
#endif
  {
    setviewport_((sg.v.right+sg.v.left*3)/4-sg.wi/2,
		 (sg.v.bottom+sg.v.top*3)/4,
		 (sg.v.right*3+sg.v.left)/4-sg.wi/2,
		 (sg.v.bottom*3+sg.v.top)/4,
		 sg.v.clip);
  }
}
static void DoubleImageRproc(void)
{
#ifdef _XBGI_
  if (XBGI->gdriver == PS) {
    setviewport_((sg.v.right+sg.v.left*3)/4+sg.wi/2,
		 (sg.v.bottom+sg.v.top*3)/4,
		 (sg.v.right*3+sg.v.left)/4+sg.wi/2,
		 (sg.v.bottom*3+sg.v.top)/4,
		 0);
  } else
#endif
  {
    setviewport_((sg.v.right+sg.v.left*3)/4+sg.wi/2,
		 (sg.v.bottom+sg.v.top*3)/4,
		 (sg.v.right*3+sg.v.left)/4+sg.wi/2,
		 (sg.v.bottom*3+sg.v.top)/4,
		 sg.v.clip);
  }
}
static void DoubleImageEproc(void)
{
  setviewport_(sg.v.left, sg.v.top, sg.v.right, sg.v.bottom, sg.v.clip);
}
static void NULLproc(void)
{
  ;
}
void setstereoprocedures(void (*start)(void),
			 void (*left)(void), void (*right)(void),
			 void (*end)(void))
{
  if (start != NULL) sg.start = start; else sg.start = NULLproc;
  if (left  != NULL) sg.left  = left;  else sg.left  = NULLproc;
  if (right != NULL) sg.right = right; else sg.right = NULLproc;
  if (end   != NULL) sg.end   = end;   else sg.end   = NULLproc;
}
void setstereotype(int type)
{
  switch (type) {
  case ColorGlass:
    setstereoprocedures(ColorGlassSproc,
			ColorGlassLproc, ColorGlassRproc,
			ColorGlassEproc);
    break;
  case DoubleImage:
    setstereoprocedures(DoubleImageSproc,
			DoubleImageLproc, DoubleImageRproc,
			DoubleImageEproc);
    break;
  }
}

struct stereographtype_ sg = {
  0.02,
  ColorGlassSproc,
  ColorGlassLproc,
  ColorGlassRproc,
  ColorGlassEproc,
  WHITE,
  { EMPTY_FILL, WHITE },
#ifdef _XBGI_ /* since version 3.02 generic 19991023 */
  { LOZENGE_POINT, WHITE, BLACK, 6 },
#endif
  { 0, 0, 639, 399, !0 },
  150
};

#ifdef CREATE_FUNCTION_FROM_MACRO
void (lines3_)(double x1,double y1,double z1,double x2,double y2,double z2)
{
  lines3_(x1,y1,z1,x2,y2,z2);
}
void (linetos3_)(double x,double y,double z)
{
  linetos3_(x,y,z);
}
void (putpixels3_)(double x,double y,double z,int c)
{
  putpixels3_(x,y,z,c);
}
void (putpoints3_)(double x,double y,double z)
{
  putpoints3_(x,y,z);
}
void (movetos3_)(double x,double y,double z)
{
  movetos3_(x,y,z);
}
void (outtextxys3_)(double x,double y,double z,char *str)
{
  outtextxys3_(x,y,z,str);
}
#endif /* CREATE_FUNCTION_FROM_MACRO */

void stereodistance_(double d)
{
  sg.dist = (1.0/d)/100;
}

void cubes3_(double xf, double yf, double zf,
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
    lines3_(x0, y0, z0, x1, y1, z1);
  }
  setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
}

void boxs3_(double xf, double yf, double zf, double xt,
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
  sg.start();
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
      sg.left(); fillpoly_(4, xy);
      sg.right(); fillpoly_(4, xy);
    }
  }
  sg.end();
  setfillstyle(fs.pattern, fs.color);
}

void lefthands3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg)
{
  double borderx = (xt-xf)*0.1, bordery = (yt-yf)*0.1, borderz = (zt-zf)*0.1;

  lines3_(xf-borderx, yf-bordery, zf-borderz,
           xf+borderx, yf-bordery, zf-borderz);
  lines3_(xf-borderx, yf-bordery, zf-borderz,
           xf-borderx, yf+bordery, zf-borderz);
  lines3_(xf-borderx, yf-bordery, zf-borderz,
           xf-borderx, yf-bordery, zf+borderz);
  if (flg) {
    outtextxys3_(xf+borderx, yf-bordery, zf-borderz, "x");
    outtextxys3_(xf-borderx, yf+bordery, zf-borderz, "y");
    outtextxys3_(xf-borderx, yf-bordery, zf+borderz, "z");
  }
}
void liness3_(int n, double *r3points)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
  
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      sg.start();
      sg.left();
      for (i=0; i<n; i++) {
	xpoints[i].x =
	  Xx(wvx(sltox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(sltoy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
      }
      XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, n, CoordModeOrigin);
      sg.right();
      for (i=0; i<n; i++) {
	xpoints[i].x =
	  Xx(wvx(srtox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(srtoy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
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
	  xpoints[i].x =
	    Xx(wvx(sltox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(sltoy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
	  xpoints[i].x =
	    Xx(wvx(srtox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(srtoy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
      r2points[2*i+0] =
	wvx(sltox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
      r2points[2*i+1] =
	wvy(sltoy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
    }
    _lines(n, r2points);
    sg.right();
    for (i=0; i<n; i++) {
      r2points[2*i+0] =
	wvx(srtox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
      r2points[2*i+1] =
	wvy(srtoy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
    }
    _lines(n, r2points);
    sg.end();
    free(r2points);
  } else
#endif
  {
    int i;

    for (i=0; i<n-3; i++)
      lines3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2], 
	      r3points[3*(i+1)+0], r3points[3*(i+1)+1], r3points[3*(i+1)+2]);
  }
}
void putpixelss3_(int n, double *r3points, int color)
{
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
	xpoints[i].x =
	  Xx(wvx(sltox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(sltoy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
      }
      XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, n, CoordModeOrigin);
      sg.right();
      XSetForeground(XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->color]);
      for (i=0; i<n; i++) {
	xpoints[i].x =
	  Xx(wvx(srtox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(srtoy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
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
	  xpoints[i].x =
	    Xx(wvx(sltox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(sltoy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
	  xpoints[i].x =
	    Xx(wvx(srtox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(srtoy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
      putpixels3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2], color);
  }
}
void putpointss3_(int n, double *r3points)
{
  int i;
  
  for (i=0; i<n; i++)
    putpoints3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2]);
}
void nlines3_(int n, double *x, double *y, double *z)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      sg.start();
      sg.left();
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(sltox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(sltoy(x[i],y[i],z[i])));
      }
      XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		 xpoints, n, CoordModeOrigin);
      sg.right();
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(srtox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(srtoy(x[i],y[i],z[i])));
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
	  xpoints[i].x = Xx(wvx(sltox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(sltoy(x[ii],y[ii],z[ii])));
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
	  xpoints[i].x = Xx(wvx(srtox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(srtoy(x[ii],y[ii],z[ii])));
	}
	XDrawLines(XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
		   xpoints, im, CoordModeOrigin);
      }
      sg.end();
      free(xpoints);
    }
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-3; i++)
      lines3_(x[i], y[i], z[i], x[i+1], y[i+1], z[i+1]);
  }
}
void nputpixels3_(int n, double *x, double *y, double *z, int color)
{
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
	xpoints[i].x = Xx(wvx(sltox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(sltoy(x[i],y[i],z[i])));
      }
      XDrawPoints(XBGIDisplay, XBGIWins[XBGI->apage], XBGIPixelGC,
		  xpoints, n, CoordModeOrigin);
      sg.right();
      XSetForeground(XBGIDisplay, XBGIPixelGC, XBGIPixels[XBGI->color]);
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(srtox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(srtoy(x[i],y[i],z[i])));
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
	  xpoints[i].x = Xx(wvx(sltox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(sltoy(x[ii],y[ii],z[ii])));
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
	  xpoints[i].x = Xx(wvx(srtox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(srtoy(x[ii],y[ii],z[ii])));
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
      putpixels3_(x[i], y[i], z[i], color);
  }
}
void nputpoints3_(int n, double *x, double *y, double *z)
{
  int i;
    
  for (i=0; i<n; i++)
    putpoints3_(x[i], y[i], z[i]);
}
