/*
 * routines to analyse japanese code and draw X 16 bit text < x11/japanese.h >
 *
 * ���ܸ쥳���ɤ���Ϥ���X��16�ӥå�ʸ�������Ϥ��뤿��Υ롼����
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _JAPANESE_H_
#define _JAPANESE_H_
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
  // ʸ����򥳡���Ƚ�ꤷ�ʤ���ѿ�ʸ����16�ӥå�ʸ������Ϥ��Ƥ����ؿ� //
  void XDrawBiString(
    Display *d, Drawable w, GC gc,
    XFontStruct *afs,              // �ѿ�ʸ���Υե���ȹ�¤�� //
    XFontStruct *bfs,              // 16�ӥå�ʸ���Υե���ȹ�¤�� //
    int x, int y,
    char *string, int len          // len �� string �ΥХåե�Ĺ //
  );

  // ʸ����򥳡���Ƚ�ꤷ�ʤ���ѿ�ʸ����16�ӥå�ʸ��������׻�����ؿ� //
  int XBiTextWidth(
    XFontStruct *afs,              // �ѿ�ʸ���Υե���ȹ�¤�� //
    XFontStruct *bfs,              // 16�ӥå�ʸ���Υե���ȹ�¤�� //
    char *string, int len          // len �� string �ΥХåե�Ĺ //
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
 * XDrawBiString for japanese
 */
extern void XDrawBiString(
#if NeedFunctionPrototypes
  Display *__d, Drawable __w, GC __gc,
  XFontStruct *__afs, XFontStruct *__bfs,
  int __x, int __y, char *__string, int __len
#endif
);

/*
 * XBiTextWidth for japanese
 */
extern int XBiTextWidth(
#if NeedFunctionPrototypes
  XFontStruct *__afs, XFontStruct *__bfs,
  char *__string, int __len
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif








