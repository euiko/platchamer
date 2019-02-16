/*
 * routines to analyse japanese code and draw PS 16 bit text < ps/japanese.h >
 *
 * ���ܸ쥳���ɤ���Ϥ���PS��16�ӥå�ʸ�������Ϥ��뤿��Υ롼����
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _JAPANESE_H_
#define _JAPANESE_H_
#include "ps_p.h"

/*
  // ʸ����򥳡���Ƚ�ꤷ�ʤ���ѿ�ʸ����16�ӥå�ʸ�������ɤ���Ϥ���ؿ� //
  void ps_xbgi_put_bi_string(
    char *string, int len // len �� string �ΥХåե�Ĺ //
  );

  // ʸ����򥳡���Ƚ�ꤷ�ʤ���ѿ�ʸ����16�ӥå�ʸ��������׻�����ؿ� //
  int ps_xbgi_bi_text_width(
    char *string, int len // len �� string �ΥХåե�Ĺ //
  );
 */

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

/*
 * ps_xbgi_put_bi_string for japanese
 */
extern void ps_xbgi_put_bi_string(
#if NeedFunctionPrototypes
  char *__string, int __len
#endif
);

/*
 * ps_xbgi_bi_text_width for japanese
 */
extern int ps_xbgi_bi_text_width(
#if NeedFunctionPrototypes
  char *__string, int __len
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif









