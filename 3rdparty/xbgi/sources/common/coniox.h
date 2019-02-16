/*
 * Header File < common/coniox.h >
 *
 * Enhanced Functions: Borland Console I/O for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _CONIOX_H_
#define _CONIOX_H_

#include "graphix.h"
#include "conio.h"

typedef struct _xconio {
  int ***vm;
  struct text_info textinfo;
} xconio;

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

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* No Enhanced Function for XConio System. This header is for registration. */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _CONIOX_H_ */

