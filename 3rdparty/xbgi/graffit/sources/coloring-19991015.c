/*
 * Coloring interface in graffit library < coloring.c >
 *
 * Various Definitions of Color for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#include <stdlib.h>
#include <math.h>
#include <coloring.h>
#ifdef _XBGI_
#include "internal.h"
#include <ps.h>
#endif

#if 0 /*defined(__cplusplus) || defined(c_plusplus)*/
template <class T>
inline T max(T __a, T __b)
{
  return (__a>__b)?__a:__b;
}
template <class T>
inline T min(T __a, T __b)
{
  return (__a>__b)?__b:__a;
}
#else
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)>(b))?(b):(a))
#endif
#endif

static int BASEC[8][3] = {
#if defined(_XBGI_)||defined(PC98)||defined(FMR_)
  {0, 0, 0},
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 1},
  {1, 0, 0},
  {1, 0, 1},
  {1, 1, 0},
  {1, 1, 1},
#else /* VGA, DOSVGA */
  {0, 0, 0},
  {0, 0, 4},
  {0, 4, 0},
  {0, 4, 4},
  {4, 0, 0},
  {4, 0, 4},
  {4, 4, 0},
  {4, 4, 4},
#endif
};

#define co __CO

struct coloringtype_ co = {
  0, 15,
  0, 15
};

int coloringCCCD(int p1, int p2, int c1, int c2, int c3, double d)
{
  struct palettetype p;
  int i, r, m;

  r = abs(p2-p1)+1;
  m = getmaxcolor();
  d = 1.0/d;
  if (r == 1)
    return 0;
  getpalette(&p);
  for (i=0; i<r; i++) {
    setrgbpalette(p.colors[p1+i*(p2-p1)/abs(p2-p1)],
      max(m-(int)(d*i),0)*BASEC[c1][0]+
      max((i<r/2)?(m+(int)(d*(i-r/2))):(m-(int)(d*(i-r/2))),0)*BASEC[c2][0]+
      max(m+(int)(d*(i-r)),0)*BASEC[c3][0],
      max(m-(int)(d*i),0)*BASEC[c1][1]+
      max((i<r/2)?(m+(int)(d*(i-r/2))):(m-(int)(d*(i-r/2))),0)*BASEC[c2][1]+
      max(m+(int)(d*(i-r)),0)*BASEC[c3][1],
      max(m-(int)(d*i),0)*BASEC[c1][2]+
      max((i<r/2)?(m+(int)(d*(i-r/2))):(m-(int)(d*(i-r/2))),0)*BASEC[c2][2]+
      max(m+(int)(d*(i-r)),0)*BASEC[c3][2]);
  }
  return r;
}

int coloring(int p1, int p2)
{
  return coloringCCCD(p1, p2, RED, GREEN, BLUE, 0.7);
}

int coloring2(int p1, int p2, int c1, int c2)
{
  struct palettetype p;
  int i, r, m;

  r = abs(p2-p1)+1;
  m = getmaxcolor();
  if (r == 1)
    return 0;
  getpalette(&p);
  for (i=0; i<r; i++)
    setrgbpalette(p.colors[p1+i*(p2-p1)/abs(p2-p1)],
                  (m-i)*BASEC[c1%8][0]+(m-r+i+1)*BASEC[c2%8][0],
                  (m-i)*BASEC[c1%8][1]+(m-r+i+1)*BASEC[c2%8][1],
                  (m-i)*BASEC[c1%8][2]+(m-r+i+1)*BASEC[c2%8][2]);
  return r;
}

void co_coloring(int p1, int p2, double r1, double r2)
{
  co.r1 = r1; co.r2 = r2;
  co.p1 = p1; co.p2 = p2;
}
int getcolor_(double r)
{
  int c;

  c = (int)((r-co.r1)/(co.r2-co.r1)*(co.p2-co.p1+1)) + co.p1;
  return max(min(co.p2,c),co.p1);
}
void setcolor_(double r)
{
  setcolor(getcolor_(r));
}

int getlog10color_(double r)
{
  int c;

  c = (int)(log(r/co.r1)/log(co.r2/co.r1)*(co.p2-co.p1+1)) + co.p1;
  return max(min(co.p2,c),co.p1);
}
void setlog10color_(double r)
{
  setcolor(getlog10color_(r));
}

int coloring3(int p1, int p2, int c1, int c2, int c3)
{
  struct palettetype p;
  int i, j, v, h, s, r;

  r = abs(p2-p1)+1;
  if (r == 1)
    return 0;
  getpalette(&p);
  v = (int)sqrt((double)r);
  h = r/v;
  s = h;
  for (i=0; i<v; i++)
    for (j=0; j<h; j++)
      setrgbpalette(p.colors[p1+(h*i+j)*(p2-p1)/abs(p2-p1)],
       s*(h-j)*BASEC[c1%8][0]+s*(j+1)*BASEC[c2%8][0]+s*(i+1)*BASEC[c3%8][0],
       s*(h-j)*BASEC[c1%8][1]+s*(j+1)*BASEC[c2%8][1]+s*(i+1)*BASEC[c3%8][1],
       s*(h-j)*BASEC[c1%8][2]+s*(j+1)*BASEC[c2%8][2]+s*(i+1)*BASEC[c3%8][2]);
  return v*h;
}

int coloringN(int p1, int p2, int n, int *cs)
{
  struct palettetype p;
  int i, j, r = abs(p2-p1)+1;

  if (r == 1)
    return 0;
  getpalette(&p);
  for (i=0; i<r/n; i++)
    for (j=0; j<n; j++)
      setrgbpalette(p.colors[p1+(n*i+j)*(p2-p1)/abs(p2-p1)],
                    n*(i+1)*BASEC[cs[j]%8][0],
                    n*(i+1)*BASEC[cs[j]%8][1],
                    n*(i+1)*BASEC[cs[j]%8][2]);
  return r/n*n;
}

void swap_colors(int p1, int p2)
{
#ifdef 0 /*_XBGI_*/
  if (XBGI->gdriver == X11 && (XBGI->gmode != X11COLOR)) {
    XBGIPixels[0] = WhitePixel(XBGIDisplay,XBGIScreen);
    XBGIPixels[XBGI->palette.size-1] = BlackPixel(XBGIDisplay,XBGIScreen);
  }
  else if (XBGI->gdriver == PS) {
    PSBGIRGB[0].red = 1;
    PSBGIRGB[0].green = 1;
    PSBGIRGB[0].blue = 1;
    PSBGIRGB[XBGI->palette.size-1].red = 0;
    PSBGIRGB[XBGI->palette.size-1].green = 0;
    PSBGIRGB[XBGI->palette.size-1].blue = 0;
  } /*else*/
#endif
  {
    struct palettetype p;
    int wk;

    getpalette(&p);
    wk = p.colors[p1];
    p.colors[p1] = p.colors[p2];
    p.colors[p2] = wk;
/*#if !defined(_XBGI_)&&!defined(PC98)&&!defined(FMR_)
    if (p1 == 0 || p2 == getmaxcolor())
      return;
#endif*/
    setallpalette(&p);
  }
}

void rotate_colors(int p1, int p2)
{
  struct palettetype p;
  int i, wk, r;

  r = abs(p2-p1)+1;
  getpalette(&p);
  wk = p.colors[p2];
  for (i=r-2; i>=0; i--)
    p.colors[p1+i+1] = p.colors[p1+i];
  p.colors[p1] = wk;
  setallpalette(&p);
}

#undef co
