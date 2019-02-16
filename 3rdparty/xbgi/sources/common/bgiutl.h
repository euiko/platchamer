/*
 * Header File < common/bgiutl.h >
 *
 * Utilities Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _BGIUTL_H_
#define _BGIUTL_H_
#include <stdarg.h>

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

extern void bgivprintf(
#if NeedFunctionPrototypes
  char *__title, int __textjust, char *__fmt, va_list __argptr
#endif
);

extern void bgiprintf(
#if NeedFunctionPrototypes
  char *__title, int __textjust, char *__fmt, ...
#endif
);

extern void bgigets(
#if NeedFunctionPrototypes
  char *__title, int __maxlen, char *__str
#endif
);

extern void bgimenu(
#if NeedFunctionPrototypes
  char *__title, int __menuc, char *__menuv[], int *__menui
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _BGIUTL_H_ */


