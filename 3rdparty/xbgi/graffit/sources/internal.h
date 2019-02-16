#ifndef _INTERNAL_H_
#define _INTERNAL_H_
#include <stdio.h>
#include <graphix.h>
#include <x11.h>

#define minmax(a,x,b) ((((a)<=(x))&&((x)<=(b)))?(x):(((x)<(a))?(a):(b)))
#define Xx(x) (XBGI->viewport.left+(x))
#define Xy(y) (XBGI->viewport.top +(y))
#define xX(x) ((x)-XBGI->viewport.left)
#define yX(y) ((y)-XBGI->viewport.top )

extern xbgi *XBGI;

#endif /* _INTERNAL_H_ */

