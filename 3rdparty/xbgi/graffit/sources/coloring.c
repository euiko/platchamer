/*
 * Coloring interface in graffit library < coloring.c >
 *
 * Various Definitions of Color for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 2000 Taiji Yamada, AIHARA Electrical Engineering Co., Ltd.
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

#if defined(_XBGI_)||defined(PC98)||defined(FMR_)
#define BC(p,c) (((7&(p))&(1<<(c)))>>(c))
#else /* VGA, DOSVGA */
#define BC(p,c) ((((7&(p))&(1<<(c)))>>(c))*4)
#endif

#define co __CO

struct coloringtype_ co = {
  0, 15,
  0, 15,
  COLORING_RGB
};

static int huffmand(unsigned int c1, unsigned int c2)
{
  unsigned x = c1^c2;
  int d = 0;
  while (x != 0) {
    d += 1&x;
    x >>= 1;
  }
  return d;
}
#define CB(c) (7&(c))
#define CD(a,b) ((a==0||a==15||b==0||b==15)?1:huffmand(CB(a),CB(b)))
#define PV(v) max(0,v)

int coloringNc(int p1, int p2, int n, int *C, double c)
{
  struct palettetype p;
  int i, r, m;
  double *D = NULL;

  r = abs(p2-p1)+1;
  m = getmaxcolor();
  if (r == 1)
    return 0;

  if (0<n-1)
    D = malloc(sizeof(double)*(n-1));
  for (i=0; i<n-1; i++)
    D[i] = (double)(n-1)/((c<0)?-c:c*CD(C[i],C[i+1]));
  getpalette(&p);
  for (i=0; i<r; i++) {
    int j = 0;
    int R, G, B;

    R =      PV(m-(D[j  ]*i            ))*BC(C[j],2);
    G =      PV(m-(D[j  ]*i            ))*BC(C[j],1);
    B =      PV(m-(D[j  ]*i            ))*BC(C[j],0);
    for (j=1; j<n-1; j++) {
      if (i<r*j/(n-1)) {
	R += PV(m+(D[j-1]*(i-r*j/(n-1))))*BC(C[j],2);
	G += PV(m+(D[j-1]*(i-r*j/(n-1))))*BC(C[j],1);
	B += PV(m+(D[j-1]*(i-r*j/(n-1))))*BC(C[j],0);
      }
      else {
	R += PV(m-(D[j  ]*(i-r*j/(n-1))))*BC(C[j],2);
	G += PV(m-(D[j  ]*(i-r*j/(n-1))))*BC(C[j],1);
	B += PV(m-(D[j  ]*(i-r*j/(n-1))))*BC(C[j],0);
      }
    }
    if (0<n-1) {
      j = n-1;
      R +=   PV(m+(D[j-1]*(i-r)        ))*BC(C[j],2);
      G +=   PV(m+(D[j-1]*(i-r)        ))*BC(C[j],1);
      B +=   PV(m+(D[j-1]*(i-r)        ))*BC(C[j],0);
    }
    setrgbpalette(p.colors[p1+i*(p2-p1)/abs(p2-p1)], R, G, B);
  }
  if (0<n-1)
    free(D);
  return r;
}

int coloring2c(int p1, int p2, int c1, int c2, double c)
{
  int C[] = { c1, c2 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}
int coloring3c(int p1, int p2, int c1, int c2, int c3, double c)
{
  int C[] = { c1, c2, c3 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}
int coloring4c(int p1, int p2, int c1, int c2, int c3, int c4, double c)
{
  int C[] = { c1, c2, c3, c4 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}
int coloring5c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, double c)
{
  int C[] = { c1, c2, c3, c4, c5 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}
int coloring6c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, int c6, double c)
{
  int C[] = { c1, c2, c3, c4, c5, c6 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}
int coloring7c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, int c6, int c7, double c)
{
  int C[] = { c1, c2, c3, c4, c5, c6, c7 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}
int coloring8c(int p1, int p2, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8, double c)
{
  int C[] = { c1, c2, c3, c4, c5, c6, c7, c8 };
  return coloringNc(p1, p2, sizeof(C)/sizeof(int), C, c);
}

void setcoloringtype(int kind)
{
  co.coloringkind = kind;
}

char *coloring_kind_name[] = {
  "CMY", /*0.5*/
  "MRYWGCB",
  /*"RGB",*/
  "RGB", /*0.7*/
  /*"RGBK",*/ /*0.8*/
  "RGBK", /*0.9*/
  /*"RGBW",*/ /*0.9*/
  "RYGCB",
  /*"RYGCB",*/ /*0.9*/
  "RYGCBK",
  "RYGCBM",
  /*"RYGCMB",*/ /*-1*/
  /*"RYGCMB",*/
  /*"RYGKCBM",*/
  "WMRYGCBK",
  /*"WRGB",*/
  /*"WRGB",*/ /*0.8*/
  "WRGB", /*0.9*/
  "WRYGCBK",
  "WYGCBMRK",
  "YMC", /*0.5*/
  "YRMKBCG",
  NULL,
};

int coloring(int p1, int p2)
{
  int r = 0;

  switch (co.coloringkind) {
  case COLORING_RGB:
    /*r = coloring3c(p1, p2, RED, GREEN, BLUE, 1);*/
    r = coloring3c(p1, p2, RED, GREEN, BLUE, 0.7);
    break;
  case COLORING_CMY:
    r = coloring3c(p1, p2, CYAN, MAGENTA, YELLOW, 0.5);
    break;
  case COLORING_YMC:
    r = coloring3c(p1, p2, YELLOW, MAGENTA, CYAN, 0.5);
    break;
  case COLORING_RGBK:
    /*r = coloring4c(p1, p2, RED, GREEN, BLUE, BLACK, 0.8);*/ /*-_-*/
    r = coloring4c(p1, p2, RED, GREEN, BLUE, BLACK, 0.9);
    /*r = coloring4c(p1, p2, RED, GREEN, BLUE, WHITE, 0.9);*/
    break;
  case COLORING_WRGB:
    /*r = coloring4c(p1, p2, WHITE, RED, GREEN, BLUE, 0.8);*/ /*-_-*/
    r = coloring4c(p1, p2, WHITE, RED, GREEN, BLUE, 0.9); /*-_-*/
    /*r = coloring4c(p1, p2, WHITE, RED, GREEN, BLUE, 1);*/ /*-_-*/
    break;
  case COLORING_RYGCB:
    r = coloring5c(p1, p2, RED, YELLOW, GREEN, CYAN, BLUE, 1);
    /*r = coloring5c(p1, p2, RED, YELLOW, GREEN, CYAN, BLUE, 0.9);*/ /*-_-*/
    break;
  case COLORING_RYGCBM:
    r = coloring6c(p1, p2, RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA, 1);
    break;
  /*case COLORING_RYGCMB:*/
    /*r = coloring6c(p1, p2, RED, YELLOW, GREEN, CYAN, MAGENTA, BLUE, 1);*/
    /*r = coloring6c(p1, p2, RED, YELLOW, GREEN, CYAN, MAGENTA, BLUE, -1);*/
    /*r = coloring6c(p1, p2, RED, YELLOW, GREEN, CYAN, MAGENTA, BLUE, 0);*/ /*!*/
    break;
  case COLORING_RYGCBK:
    r = coloring6c(p1, p2, RED, YELLOW, GREEN, CYAN, BLUE, BLACK, 1);
    break;
  case COLORING_WRYGCBK:
    r = coloring7c(p1, p2, WHITE, RED, YELLOW, GREEN, CYAN, BLUE, BLACK, 1.0);
    break;
  case COLORING_MRYWGCB:
    r = coloring7c(p1, p2, MAGENTA, RED, YELLOW, WHITE, GREEN, CYAN, BLUE, 1.0);
    break;
  case COLORING_YRMKBCG:
    r = coloring7c(p1, p2, YELLOW, RED, MAGENTA, BLACK, BLUE, CYAN, GREEN, 1.0);
    break;
  case COLORING_WMRYGCBK:
    r = coloring8c(p1, p2, WHITE, MAGENTA, RED, YELLOW, GREEN, CYAN, BLUE, BLACK, 1.0);
    break;
  case COLORING_WYGCBMRK:
    r = coloring8c(p1, p2, WHITE, YELLOW, GREEN, CYAN, BLUE, MAGENTA, RED, BLACK, 1.0);
    break;
  default:
    r = coloring2(p1, p2, BLACK, WHITE);
    break;
  }
  return r;
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
                  (m-i)*BC(c1,2)+(m-r+i+1)*BC(c2,2),
                  (m-i)*BC(c1,1)+(m-r+i+1)*BC(c2,1),
                  (m-i)*BC(c1,0)+(m-r+i+1)*BC(c2,0));
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
		    s*(h-j)*BC(c1,2)+s*(j+1)*BC(c2,2)+s*(i+1)*BC(c3,2),
		    s*(h-j)*BC(c1,1)+s*(j+1)*BC(c2,1)+s*(i+1)*BC(c3,1),
		    s*(h-j)*BC(c1,0)+s*(j+1)*BC(c2,0)+s*(i+1)*BC(c3,0));
  return v*h;
}

int coloringN(int p1, int p2, int n, int *C)
{
  struct palettetype p;
  int i, j, r = abs(p2-p1)+1;

  if (r == 1)
    return 0;
  getpalette(&p);
  for (i=0; i<r/n; i++)
    for (j=0; j<n; j++)
      setrgbpalette(p.colors[p1+(n*i+j)*(p2-p1)/abs(p2-p1)],
                    n*(i+1)*BC(C[j],2),
                    n*(i+1)*BC(C[j],1),
                    n*(i+1)*BC(C[j],0));
  return r/n*n;
}

void swap_colors(int p1, int p2)
{
#if 0 /* defined(_XBGI_) */
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
