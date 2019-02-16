/*
 * Axes utilities in graffit library < axes.c >
 *
 * Draw Axes on View Port for Borland Graphics Interface
 *
 * Copyright (C) 1991-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <axes.h>

void drawaxisx(int apos, int sep, int ssep, int len, int bos)
{
  float width, height;
  int i;
  struct viewporttype cv;
  
  getviewsettings(&cv);
  width  = cv.right  - cv.left + 1;
  height = cv.bottom - cv.top  + 1;
  switch (apos) {
  case AXIS_TOP:
    height = 0; bos*=-1; len*=-1;
  case AXIS_BOTTOM:
    line(0, height+bos+len, width/*-1*/, height+bos+len);
    break;
  case AXIS_INSIDE:
    height = 0;
    line(0, height+bos, width/*-1*/, height+bos);
    break;
  }
  i = 0;
  while (i<sep*ssep) {
    switch (apos) {
    case AXIS_LEFT: case AXIS_RIGHT:
      line(width/(sep*ssep)*i, height+bos+len/2,
           width/(sep*ssep)*i, height+bos+len);
      break;
    case AXIS_INSIDE:
      line(width/(sep*ssep)*i, height+bos-len/4,
           width/(sep*ssep)*i, height+bos+len/4+1);
      break;
    }
    i++;
  }
  i = 0;
  while (i<sep) {
    switch (apos) {
    case AXIS_LEFT: case AXIS_RIGHT:
      line(width/sep*i, height+bos, width/sep*i, height+bos+len);
      break;
    case AXIS_INSIDE:
      line(width/sep*i, height+bos-len/2, width/sep*i, height+bos+len/2+1);
      break;
    }      
    i++;
  }
  if (sep != 0)
    switch (apos) {
    case AXIS_LEFT: case AXIS_RIGHT:
      line(width/sep*i-1, height+bos,
	   width/sep*i-1, height+bos+len);
      break;
    case AXIS_INSIDE:
      line(width/sep*i-1, height+bos-len/2,
	   width/sep*i-1, height+bos+len/2+1);
      break;
    }
}

void drawaxisy(int apos, int sep, int ssep, int len, int bos)
{
  float width, height;
  int i;
  struct viewporttype cv;

  getviewsettings(&cv);
  width  = cv.right  - cv.left + 1;
  height = cv.bottom - cv.top  + 1;
  switch (apos) {
  case AXIS_LEFT:
    width = 0; bos*=-1; len*=-1;
  case AXIS_RIGHT:
    line(width+bos+len, 0, width+bos+len, height/*-1*/);
    break;
  case AXIS_INSIDE:
    width = 0;
    line(width+bos, 0, width+bos, height/*-1*/);
    break;
  }
  i = 0;
  while (i<sep*ssep) {
    switch (apos) {
    case AXIS_LEFT: case AXIS_RIGHT:
      line(width+bos+len/2, height/(sep*ssep)*i,
           width+bos+len, height/(sep*ssep)*i);
      break;
    case AXIS_INSIDE:
      line(width+bos-len/4, height/(sep*ssep)*i,
           width+bos+len/4+1, height/(sep*ssep)*i);
      break;
    }
    i++;
  }
  i = 0;
  while (i<sep) {
    switch (apos) {
    case AXIS_LEFT: case AXIS_RIGHT:
      line(width+bos, height/sep*i, width+bos+len, height/sep*i);
      break;
    case AXIS_INSIDE:
      line(width+bos-len/2, height/sep*i, width+bos+len/2+1, height/sep*i);
      break;
    }
    i++;
  }
  if (sep != 0)
    switch (apos) {
    case AXIS_LEFT: case AXIS_RIGHT:
      line(width+bos, height/sep*i-1,
	   width+bos+len, height/sep*i-1);
      break;
    case AXIS_INSIDE:
      line(width+bos-len/2, height/sep*i-1,
	   width+bos+len/2+1, height/sep*i-1);
      break;
    }
}
