/*
 * 3-dimensional graphic interface in graffit library < graphr3_.c >
 *
 * 3-dimensional Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphr3_.h>
#ifdef _XBGI_
#include "internal.h"
#endif

#define rp __RP

struct rotationporttype_ rp = {
  0.0, 0.0, 0.0,
  1.0, 1.0, 1.0,
  1.4,
  { 
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 }
  }
};

#ifdef CREATE_FUNCTION_FROM_MACRO
void (liner3_)(double x1,double y1,double z1,double x2,double y2,double z2)
{
  liner3_(x1,y1,z1,x2,y2,z2);
}
void (linetor3_)(double x,double y,double z)
{
  linetor3_(x,y,z);
}
void (putpixelr3_)(double x,double y,double z,int c)
{
  putpixelr3_(x,y,z,c);
}
void (putpointr3_)(double x,double y,double z)
{
  putpointr3_(x,y,z);
}
void (movetor3_)(double x,double y,double z)
{
  movetor3_(x,y,z);
}
void (outtextxyr3_)(double x,double y,double z,char *str)
{
  outtextxyr3_(x,y,z,str);
}
#endif /* CREATE_FUNCTION_FROM_MACRO */

void setrotationport_(double xf, double yf, double zf,
		      double xt, double yt, double zt)
{
  rp.ox = (xf+xt)/2;   rp.oy = (yf+yt)/2;   rp.oz = (zf+zt)/2;
  rp.mx = 1.0/(xt-xf); rp.my = 1.0/(yt-yf); rp.mz = 1.0/(zt-zf);
}
void setmagnify_(double rm)
{
  rp.mag = rm;
  setwindow_(-1.0/rm, -1.0/rm, 1.0/rm, 1.0/rm);
}
void setrotation_(double a, double b, double c)
{
  double ca, sa;
  double cb, sb;
  double cc, sc;

  ca = cos(a); sa = sin(a);
  cb = cos(b); sb = sin(b);
  cc = cos(c); sc = sin(c);
  rp.r[0][0]=cb*cc-sb*sa*sc; rp.r[0][1]=cb*sc+sb*sa*cc; rp.r[0][2]=-sb*ca;
  rp.r[1][0]=     -   ca*sc; rp.r[1][1]=         ca*cc; rp.r[1][2]=    sa;
  rp.r[2][0]=sb*cc+cb*sa*sc; rp.r[2][1]=sb*sc-cb*sa*cc; rp.r[2][2]= cb*ca;
}
extern void setrotatex_(double a)
{
  double ca, sa;
  int i, j;
  double r[3][3];

  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
      r[i][j] = rp.r[i][j];

  ca = cos(a); sa = sin(a);
  rp.r[0][1]=r[0][1]*ca-r[0][2]*sa; rp.r[0][2]=r[0][1]*sa+r[0][2]*ca; 
  rp.r[1][1]=r[1][1]*ca-r[1][2]*sa; rp.r[1][2]=r[1][1]*sa+r[1][2]*ca; 
  rp.r[2][1]=r[2][1]*ca-r[2][2]*sa; rp.r[2][2]=r[2][1]*sa+r[2][2]*ca; 
}
extern void setrotatey_(double b)
{
  double cb, sb;
  int i, j;
  double r[3][3];

  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
      r[i][j] = rp.r[i][j];

  cb = cos(b); sb = sin(b);
  rp.r[0][0]=r[0][0]*cb+r[0][2]*sb; rp.r[0][2]=-r[0][0]*sb+r[0][2]*cb; 
  rp.r[1][0]=r[1][0]*cb+r[1][2]*sb; rp.r[1][2]=-r[1][0]*sb+r[1][2]*cb; 
  rp.r[2][0]=r[2][0]*cb+r[2][2]*sb; rp.r[2][2]=-r[2][0]*sb+r[2][2]*cb; 
}
extern void setrotatez_(double c)
{
  double cc, sc;
  int i, j;
  double r[3][3];

  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
      r[i][j] = rp.r[i][j];
  cc = cos(c); sc = sin(c);
  rp.r[0][0]=r[0][0]*cc-r[0][1]*sc; rp.r[0][1]=r[0][0]*sc+r[0][1]*cc; 
  rp.r[1][0]=r[1][0]*cc-r[1][1]*sc; rp.r[1][1]=r[1][0]*sc+r[1][1]*cc; 
  rp.r[2][0]=r[2][0]*cc-r[2][1]*sc; rp.r[2][1]=r[2][0]*sc+r[2][1]*cc; 
}
void cuber3_(double xf, double yf, double zf,
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
  maxz = r3toz(xf, yf, zf);
  maxi = 0;
  for (i=1; i<8; i++) {
    x0 = (i/1%2)?xt:xf;
    y0 = (i/2%2)?yt:yf;
    z0 = (i/4%2)?zt:zf;
    z = r3toz(x0, y0, z0);
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
    liner3_(x0, y0, z0, x1, y1, z1);
  }
  setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
}
void boxr3_(double xf, double yf, double zf,
	    double xt, double yt, double zt, int c6[])
{
  int i, j, mini, fil;
  double x, y, z, xy[5*2], minz;
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
  minz = r3toz(xf, yf, zf);
  mini = 0;
  for (i=1; i<8; i++) {
    z = r3toz((i/1%2)?xt:xf,(i/2%2)?yt:yf,(i/4%2)?zt:zf);
    if (z<minz) {
      minz = z;
      mini = i;
    }
  }
  for (i=0; i<6; i++) {
    fil = 0;
    for (j=0; j<5; j++)
      if (s[i][j]==mini)
        fil = !0;
    if (fil) {
      for (j=0; j<5; j++) {
        x = r3tox((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
        y = r3toy((s[i][j]/1%2)?xt:xf,(s[i][j]/2%2)?yt:yf,(s[i][j]/4%2)?zt:zf);
        xy[2*j+0] = x;
        xy[2*j+1] = y;
      }
      setfillstyle(SOLID_FILL, c6?c6[i]:fs.color);
      fillpoly_(4, xy);
    }
  }
  setfillstyle(fs.pattern, fs.color);
}
void lefthandr3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg)
{
  double borderx = (xt-xf)*0.1, bordery = (yt-yf)*0.1, borderz = (zt-zf)*0.1;

  liner3_(xf-borderx, yf-bordery, zf-borderz,
           xf+borderx, yf-bordery, zf-borderz);
  liner3_(xf-borderx, yf-bordery, zf-borderz,
           xf-borderx, yf+bordery, zf-borderz);
  liner3_(xf-borderx, yf-bordery, zf-borderz,
           xf-borderx, yf-bordery, zf+borderz);
  if (flg) {
    outtextxyr3_(xf+borderx, yf-bordery, zf-borderz, "x");
    outtextxyr3_(xf-borderx, yf+bordery, zf-borderz, "y");
    outtextxyr3_(xf-borderx, yf-bordery, zf+borderz, "z");
  }
}
void linesr3_(int n, double *r3points)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      for (i=0; i<n; i++) {
	xpoints[i].x =
	  Xx(wvx(r3tox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(r3toy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
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
	    Xx(wvx(r3tox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(r3toy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
	wvx(r3tox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
      r2points[2*i+1] =
	wvy(r3toy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2]));
    }
    _lines(n, r2points);
    free(r2points);
  } else
#endif
  {
    int i;
    
    for (i=0; i<n-3; i++)
      liner3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2], 
	      r3points[3*(i+1)+0], r3points[3*(i+1)+1], r3points[3*(i+1)+2]);
  }
}
void putpixelsr3_(int n, double *r3points, int color)
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
	  Xx(wvx(r3tox(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
	xpoints[i].y =
	  Xy(wvy(r3toy(r3points[3*i+0],r3points[3*i+1],r3points[3*i+2])));
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
	    Xx(wvx(r3tox(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
	  xpoints[i].y =
	    Xy(wvy(r3toy(r3points[3*ii+0],r3points[3*ii+1],r3points[3*ii+2])));
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
      putpixelr3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2], color);
  }
}
void putpointsr3_(int n, double *r3points)
{
  int i;
  
  for (i=0; i<n; i++)
    putpointr3_(r3points[3*i+0], r3points[3*i+1], r3points[3*i+2]);
}
void nliner3_(int n, double *x, double *y, double *z)
{
#ifdef _XBGI_
  if (XBGI->gdriver == X11) {
    XPoint *xpoints;
    int i;
    
    if (n <= MAX_SAFE_XPOINTS) {
      xpoints = (XPoint *)malloc(n*sizeof(XPoint));
      for (i=0; i<n; i++) {
	xpoints[i].x = Xx(wvx(r3tox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(r3toy(x[i],y[i],z[i])));
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
	  xpoints[i].x = Xx(wvx(r3tox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(r3toy(x[ii],y[ii],z[ii])));
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
      liner3_(x[i], y[i], z[i], x[i+1], y[i+1], z[i+1]);
  }
}
void nputpixelr3_(int n, double *x, double *y, double *z, int color)
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
	xpoints[i].x = Xx(wvx(r3tox(x[i],y[i],z[i])));
	xpoints[i].y = Xy(wvy(r3toy(x[i],y[i],z[i])));
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
	  xpoints[i].x = Xx(wvx(r3tox(x[ii],y[ii],z[ii])));
	  xpoints[i].y = Xy(wvy(r3toy(x[ii],y[ii],z[ii])));
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
      putpixelr3_(x[i], y[i], z[i], color);
  }
}
void nputpointr3_(int n, double *x, double *y, double *z)
{
  int i;
  
  for (i=0; i<n; i++)
    putpointr3_(x[i], y[i], z[i]);
}
#define ZERO      1.0E-6
#define NEAR(a,b) (fabs((a)-(b))<ZERO)
#define FAR(a,b)  (!NEAR(a,b))
static /* designed and produced by junt */
double arc_sin_cos(double s, double c)
{
  double T, Ts, Tc;
  int fs, fc;

  Ts = asin(s);
  Tc = acos(c);
  fs = (Ts<0)?0:1;
  fc = (Tc>M_PI_2)?1:0;
  if (fs==1 && fc==0)
    T = Ts;
  else if (fs==1 && fc==1)
    T = Tc;
  else if (fs==0 && fc==0)
    T = 2.0*M_PI-Tc;
  else
    T = M_PI-Ts;
  return T;
}
void getrotation_(double *a, double *b, double *c)
{
  double ca, sa;
  double cb, sb;
  double cc, sc;
  double A, B, C;
  double r[3][3];
  int i, u, v;
  int hit;

  sa = rp.r[1][2];
  if (fabs(sa) == 1.0) { /* singular point of rotation x */
    ca = 0.0;
    A = arc_sin_cos(sa, ca);
    for (i=0; i<2; i++) {
      switch (i) {
      case 0:
	B = 0.0;
	sb = sin(B);
	cb = cos(B);
	C = arc_sin_cos(rp.r[0][1], rp.r[0][0]);
	sc = sin(C);
	cc = cos(C);
	break;
      case 1: default:
	C = 0.0;
	sc = sin(C);
	cc = cos(C);
	B = arc_sin_cos(rp.r[2][0], rp.r[0][0]);
	sb = sin(B);
	cb = cos(B);
	break;
      }
      r[0][0]= cb*cc-sb*sa*sc; r[0][1]= cb*sc+sb*sa*cc; r[0][2]=-sb*ca;
      r[1][0]=      -   ca*sc; r[1][1]=          ca*cc; r[1][2]=    sa;
      r[2][0]= sb*cc+cb*sa*sc; r[2][1]= sb*sc-cb*sa*cc; r[2][2]= cb*ca;
      hit = !0;
      for (u=0; u<3; u++) {
	for (v=0; v<3; v++) {
	  if (FAR(rp.r[u][v],r[u][v])) {
	    hit = 0;
	    break;
	  }
	}
      }
      if (hit) {
	*a = A;
	*b = B;
	*c = C;
	return;
      }
    }
  }
  {
    for (i=-1; i<=1; i+=2) {
      ca = sqrt(1.0 - sa*sa)*i;
      cb =  rp.r[2][2]/ca;
      cc =  rp.r[1][1]/ca;
      sb = -rp.r[0][2]/ca;
      sc = -rp.r[1][0]/ca;
      A = arc_sin_cos(sa, ca);
      B = arc_sin_cos(sb, cb);
      C = arc_sin_cos(sc, cc);
      r[0][0]= cb*cc-sb*sa*sc; r[0][1]= cb*sc+sb*sa*cc; r[0][2]=-sb*ca;
      r[1][0]=      -   ca*sc; r[1][1]=          ca*cc; r[1][2]=    sa;
      r[2][0]= sb*cc+cb*sa*sc; r[2][1]= sb*sc-cb*sa*cc; r[2][2]= cb*ca;
      hit = !0;
      for (u=0; u<3; u++) {
	for (v=0; v<3; v++) {
	  if (FAR(rp.r[u][v],r[u][v])) {
	    hit = 0;
	    break;
	  }
	}
      }
      if (hit) {
	*a = A;
	*b = B;
	*c = C;
	return;
      }
    }
  }
}
#undef ZERO
