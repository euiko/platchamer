/*
 * Linear Geometry Calculations < matrix.h >
 *
 * 行列ベクトル演算の基本ルーチン
 *
 * Copyright (C) 1992-1995 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef Float
#define Float double
#endif

#define NR_END 1 /* it's for compatibility to Numerical Recipes in C */
static Float *vector(long nl, long nh)
{
  Float *v;

  v = (Float*)malloc(sizeof(Float)*(nh - nl + 1 + NR_END));
  if (!v)
    return NULL;
  return v - nl + NR_END;
}
static void free_vector(Float *v, long nl, long nh)
{
  free(v + nl - NR_END);
}
static Float **matrix(long nrl, long nrh, long ncl, long nch)
{
  long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  Float **m, **tmp;

  tmp = m = (Float**)malloc(sizeof(Float*)*(nrow + NR_END));
  if (!m)
    return NULL;
  m += NR_END;
  m -= nrl;
  m[nrl] = (Float*)malloc(sizeof(Float)*(nrow * ncol + NR_END));
  if (!m[nrl]) {
    free(tmp);
    return NULL;
  }
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for (i=nrl+1; i<=nrh; i++)
    m[i] = m[i - 1] + ncol;

  return m;
}
static void free_matrix(Float **m, long nrl, long nrh, long ncl, long nch)
{
  free(m[nrl] + ncl - NR_END);
  free(m + nrl - NR_END);
}
static int **imatrix(long nrl, long nrh, long ncl, long nch)
{
  long i, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
  int **m, **tmp;

  tmp = m = (int**)malloc(sizeof(int*)*(nrow + NR_END));
  if (!m)
    return NULL;
  m += NR_END;
  m -= nrl;

  m[nrl] = (int*)malloc(sizeof(int)*(nrow * ncol + NR_END));
  if (!m[nrl]) {
    free(tmp);
    return NULL;
  }
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for (i = nrl + 1; i <= nrh; i++)
    m[i] = m[i - 1] + ncol;

  return m;
}
static void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
{
  free(m[nrl] + ncl - NR_END);
  free(m + nrl - NR_END);
}
#undef NR_END
static void cp_vector(long nl, long nh,
		      Float *a, Float *b)
{
  long i;

  for (i=nl; i<=nh; i++)
    b[i] = a[i];
}
static void cp_matrix(long nrl, long nrh, long ncl, long nch,
		      Float **a, Float **b)
{
  long i, j;

  for (i=nrl; i<=nrh; i++)
    for (j=ncl; j<=nch; j++)
      b[i][j] = a[i][j];
}
static void square_matrix_mult_vector(long nl, long nh,
				      Float **a, Float *b, Float *c)
{
  long i, j;
  Float s, *tmp = vector(nl, nh);
  
  cp_vector(nl, nh, b, tmp);
  for (i=nl; i<=nh; i++) {
    s = 0.0;
    for (j=nl; j<=nh; j++)
      s = s + a[i][j]*tmp[j];
    c[i] = s;
  }
  free_vector(tmp, nl, nh);
}
static void vector_mult_square_matrix(long nl, long nh,
				      Float *a, Float **b, Float *c)
{
  long i, j;
  Float s, *tmp = vector(nl, nh);

  cp_vector(nl, nh, a, tmp);
  for (i=nl; i<=nh; i++) {
    s = 0.0;
    for (j=nl; j<=nh; j++)
      s = s + tmp[j]*b[i][j];
    c[i] = s;
  }
  free_vector(tmp, nl, nh);
}
#define _matrix_mult_matrix_(a_nrl,a_nrh,a_ncl,a_nch,b_ncl,b_nch,a,b,c) \
do {\
  long i, j, k;\
  for (i=a_nrl; i<=a_nrh; i++) {\
    for (j=b_ncl; j<=b_nch; j++) {\
      c[i][j] = 0.0;\
      for (k=a_ncl; k<=a_nch; k++) {\
        c[i][j] += a[i][k]*b[k][j];\
      }\
    }\
  }\
} while(0)
static void square_matrix_mult_matrix(long nl, long nh,
				      Float **a, Float **b, Float **c)
{
  Float **C;

  C = (((a == c) || (b==c))?matrix(nl, nh, nl, nh):c);
  _matrix_mult_matrix_(nl, nh, nl, nh, nl, nh, a, b, C);
  if ((a == c) || (b == c)) {
    cp_matrix(nl, nh, nl, nh, C, c);
    free_matrix(C, nl, nh, nl, nh);
  }
}
static int ipow2(int n)
{
  static int i, first = !0;
  static int table[16];

  if (first) {
    for (i=0; i<16; i++)
      table[i] = 0;
    first = 0;
  }
  if (n<16) {
    if (!table[n])
      table[n] = (n==0)?1:2*ipow2(n-1);
    return table[n];
  }
  return 1; /* overflow over 16 */
}
