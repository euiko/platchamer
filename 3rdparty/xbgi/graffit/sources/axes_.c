/*
 * Axes utilities for R^2 graphics in graffit library < axes_.c >
 *
 * Draw Axes on Window Port for Borland Graphics Interface
 *
 * Copyright (C) 1991-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <axes_.h>
#include <outtext_.h>

#define AXIS_FLOAT_FORMAT "%g"

void drawaxisx_(int apos, int sep, int ssep, int len, double bos)
{
  float width, height;
  int i;
  struct viewporttype cv;
  struct windowtype_ cw;
  struct textsettingstype ct;
  
  getviewsettings(&cv);
  getwindowsettings_(&cw);
  gettextsettings(&ct);
  width  = cv.right  - cv.left + 1;
  height = cv.bottom - cv.top  + 1;
  switch (apos) {
  case AXIS_TOP:
    line(0, -(bos+len), width/*-1*/, -(bos+len));
    settextjustify(CENTER_TEXT, BOTTOM_TEXT);
    break;
  case AXIS_BOTTOM:
    line(0, height-1+bos+len, width/*-1*/, height-1+bos+len);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    break;
  case AXIS_INSIDE:
    line_(vwx(0), bos, vwx(width/*-1*/), bos);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    break;
  }
  i = 0;
  while (i<sep*ssep) {
    switch (apos) {
    case AXIS_TOP:
      line(width/(sep*ssep)*i, -(bos+len/2),
           width/(sep*ssep)*i, -(bos+len));
      break;
    case AXIS_BOTTOM:
      line(width/(sep*ssep)*i, height-1+bos+len/2,
           width/(sep*ssep)*i, height-1+bos+len);
      break;
    case AXIS_INSIDE:
      line_(vwx(width/(sep*ssep)*i), bos-y_f(len/4),
	    vwx(width/(sep*ssep)*i), bos+y_f(len/4+1));
      break;
    }
    i++;
  }
  i = 0;
  while (i<sep) {
    switch (apos) {
    case AXIS_TOP:
      line(width/sep*i, -bos, width/sep*i, -(bos+len));
      outtextxyf(width/sep*i, -(bos+len)-1,
                 AXIS_FLOAT_FORMAT, cw.left+(cw.right-cw.left)/sep*i);
      break;
    case AXIS_BOTTOM:
      line(width/sep*i, height+bos, width/sep*i, height+bos+len);
      outtextxyf(width/sep*i, height+bos+len,
                 AXIS_FLOAT_FORMAT, cw.left+(cw.right-cw.left)/sep*i);
      break;
    case AXIS_INSIDE:
      line_(vwx(width/sep*i), bos-y_f(len/2),
	    vwx(width/sep*i), bos+y_f(len/2+1));
      outtextxyf_(vwx(width/sep*i), bos+y_f(len/2+1),
		  AXIS_FLOAT_FORMAT, cw.left+(cw.right-cw.left)/sep*i);
      break;
    }      
    i++;
  }
  if (sep != 0)
    switch (apos) {
    case AXIS_TOP:
      line(width/sep*i-1, -bos, width/sep*i-1, -(bos+len));
      outtextxyf(width/sep*i-1, -(bos+len)-1,
		 AXIS_FLOAT_FORMAT, cw.left+(cw.right-cw.left)/sep*i);
      break;
    case AXIS_BOTTOM:
      line(width/sep*i-1, height+bos, width/sep*i-1, height+bos+len);
      outtextxyf(width/sep*i-1, height+bos+len,
		 AXIS_FLOAT_FORMAT, cw.left+(cw.right-cw.left)/sep*i);
      break;
    case AXIS_INSIDE:
      line_(vwx(width/sep*i-1), bos-y_f(len/2),
	    vwx(width/sep*i-1), bos+y_f(len/2+1));
      outtextxyf_(vwx(width/sep*i-1), bos+y_f(len/2+1),
		  AXIS_FLOAT_FORMAT, cw.left+(cw.right-cw.left)/sep*i);
      break;
    }
  settextstyle(ct.font, ct.direction, ct.charsize);
  settextjustify(ct.horiz, ct.vert);
}

void drawaxisy_(int apos, int sep, int ssep, int len, double bos)
{
  float width, height;
  int i;
  struct viewporttype cv;
  struct windowtype_ cw;
  struct textsettingstype ct;

  getviewsettings(&cv);
  getwindowsettings_(&cw);
  gettextsettings(&ct);
  width  = cv.right  - cv.left + 1;
  height = cv.bottom - cv.top  + 1;
  switch (apos) {
  case AXIS_LEFT:
    line(-(bos+len), 0, -(bos+len), height/*-1*/);
    settextjustify(RIGHT_TEXT, CENTER_TEXT);
    break;
  case AXIS_RIGHT:
    line(width-1+bos+len, 0, width-1+bos+len, height/*-1*/);
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    break;
  case AXIS_INSIDE:
    line_(bos, vwy(0), bos, vwy(height/*-1*/));
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    break;
  }
  i = 0;
  while (i<sep*ssep) {
    switch (apos) {
    case AXIS_LEFT:
      line(-(bos+len/2), height/(sep*ssep)*i,
           -(bos+len), height/(sep*ssep)*i);
      break;
    case AXIS_RIGHT:
      line(width-1+bos+len/2, height/(sep*ssep)*i,
           width-1+bos+len, height/(sep*ssep)*i);
      break;
    case AXIS_INSIDE:
      line_(bos-x_f(len/4), vwy(height/(sep*ssep)*i),
           bos+x_f(len/4+1), vwy(height/(sep*ssep)*i));
      break;
    }
    i++;
  }
  i = 0;
  while (i<sep) {
    switch (apos) {
    case AXIS_LEFT:
      line(-bos, height/sep*i, -(bos+len), height/sep*i);
      outtextxyf(-(bos+len)-1, height/sep*i,
                 AXIS_FLOAT_FORMAT, cw.top+(cw.bottom-cw.top)/sep*i);
      break;
    case AXIS_RIGHT:
      line(width-1+bos, height/sep*i, width-1+bos+len, height/sep*i);
      outtextxyf(width+bos+len+2, height/sep*i, 
                 AXIS_FLOAT_FORMAT, cw.top+(cw.bottom-cw.top)/sep*i);
      break;
    case AXIS_INSIDE:
      line_(bos-x_f(len/2), vwy(height/sep*i),
	    bos+x_f(len/2+1), vwy(height/sep*i));
      outtextxyf_(bos+x_f(len/2+1+2), vwy(height/sep*i),
		  AXIS_FLOAT_FORMAT, cw.top+(cw.bottom-cw.top)/sep*i);
      break;
    }
    i++;
  }
  if (sep != 0)
    switch (apos) {
    case AXIS_LEFT:
      line(-bos, height/sep*i-1, -(bos+len), height/sep*i-1);
      outtextxyf(-(bos+len)-1, height/sep*i-1,
		 AXIS_FLOAT_FORMAT, cw.top+(cw.bottom-cw.top)/sep*i);
      break;
    case AXIS_RIGHT:
      line(width-1+bos, height/sep*i-1, width-1+bos+len, height/sep*i-1);
      outtextxyf(width+bos+len+2, height/sep*i-1, 
		 AXIS_FLOAT_FORMAT, cw.top+(cw.bottom-cw.top)/sep*i);
      break;
    case AXIS_INSIDE:
      line_(bos-x_f(len/2), vwy(height/sep*i-1),
	    bos+x_f(len/2+1), vwy(height/sep*i-1));
      outtextxyf_(bos+x_f(len/2+1+2), vwy(height/sep*i-1),
		 AXIS_FLOAT_FORMAT, cw.top+(cw.bottom-cw.top)/sep*i);
      break;
    }
  settextstyle(ct.font, ct.direction, ct.charsize);
  settextjustify(ct.horiz, ct.vert);
}



