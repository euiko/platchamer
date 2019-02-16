/*
 * Header File < misc.h >
 *
 * Misc Functions for X11: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _MISC_H_
#define _MISC_H_
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#ifndef NeedFunctionPrototypes
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define NeedFunctionPrototypes 1
#  else
#    define NeedFunctionPrototypes 0
#  endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern int XSetIconFromPixmap(
#if NeedFunctionPrototypes
  Display *__d, Window __r, Pixmap __pm, unsigned int __w, unsigned int __h
#endif
);

void bgipoints2XPoints(
#if NeedFunctionPrototypes
  int __n, int __polypoints[], XPoint *__xpoints
#endif
);

void _bgipoints2XPoints(
#if NeedFunctionPrototypes
  int __n, double __polypoints[], XPoint *__xpoints
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _MISC_H_ */








