/*
 * Dummy header for Borland Graphics Interface on dos < graphix.h >
 *
 * Absorption of differences between BGI and enhanced functions in xbgi
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _GRAPHIX_H_
#define _GRAPHIX_H_
#include <malloc.h>
#include <graphics.h>
#include <xbgi2bgi.h>

typedef struct _xbgi {
  int id;
} xbgi;

static xbgi *XBGI = NULL;

static xbgi *creategraph(int *gdriver, int *gmode, char *pathtodriver)
{
  initgraph(gdriver, gmode, pathtodriver);
  XBGI = (xbgi*)malloc(sizeof(xbgi));
  return XBGI;
}
static xbgi *thisgraph(void){ return XBGI; }
static void destroygraph(xbgi *this){ free(this); closegraph(); }
static void currentgraph(xbgi *this){ XBGI = this; }

#endif
