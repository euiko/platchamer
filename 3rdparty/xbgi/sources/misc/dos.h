/*
 * Header File < dos.h >
 *
 * Standard Functions of DOS.H only about delay(): Borland C/C++ compiler
 *
 * Copyright (c) 1992-94 Tokyo Denki University, Taiji Yamada
 */
#ifndef _DOS_H_
#define _DOS_H_

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

extern void delay(
#if NeedFunctionPrototypes
  unsigned long ms
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _DOS_H_ */

