/*
 * Header File < graphix/x11.h >
 *
 * Enhanced Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _GRAPHIX_X11_H_
#define _GRAPHIX_X11_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define MAX_SAFE_XPOINTS (16384-1)

#ifndef NeedFunctionPrototypes
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define NeedFunctionPrototypes 1
#  else
#    define NeedFunctionPrototypes 0
#  endif
#endif

#ifndef __P
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define __P(p) p
#  else
#    define __P(p)
#  endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct _x11_xbgi {
  Display *display;
#if 0 /* USE_DEFAULT_VISUAL */
#else
  Visual *visual;
  int depth;
#endif
  Colormap colormap;
  unsigned long background;
  unsigned long foreground;
  unsigned long bottom_shadow;
  unsigned long top_shadow;
  GC default_gc;
  XFontStruct *font_struct;
  Window root;
  Drawable *wins;
  GC draw_gc;
  GC fill_gc;
  GC pixel_gc;
  GC image_gc;
  XFontStruct *stroke_fonts[MAX_CHAR_FONT+1][MAX_CHAR_SIZE+1];
  XFontStruct *bi_fonts[MAX_CHAR_SIZE+1];
  XFontSet multi_fonts[MAX_CHAR_SIZE+1];
#if 0 /* USE_COLORTABLE */
  unsigned char colortable[MAXCOLORS+1];
#endif
  unsigned long pixels[MAXCOLORS+1];
  XColor rgb[MAXCOLORS+1];
  XEvent event;
} x11_xbgi;

/*
 * Inheritor of xbgi for X
 */
#define XBGIsDisplay(it)\
        (((x11_xbgi*)(it->inherit_members))->display)
#define XBGIsScreen(it)\
        (DefaultScreen(XBGIsDisplay(it)))
#if 0 /* USE_DEFAULT_VISUAL */
#define XBGIsVisual(it)\
        (DefaultVisual(XBGIsDisplay(it),XBGIsScreen(it)))
#define XBGIsDepth(it)\
        (DefaultDepth(XBGIsDisplay(it),XBGIsScreen(it)))
#else
#define XBGIsVisual(it)\
        (((x11_xbgi*)(it->inherit_members))->visual)
#define XBGIsDepth(it)\
        (((x11_xbgi*)(it->inherit_members))->depth)
#endif
#define XBGIsVisualClass(it)\
        (XBGIsVisual(it)->class)
#define XBGIsColormap(it)\
        (((x11_xbgi*)(it->inherit_members))->colormap)
#define XBGIsBackground(it)\
        (((x11_xbgi*)(it->inherit_members))->background)
#define XBGIsForeground(it)\
        (((x11_xbgi*)(it->inherit_members))->foreground)
#define XBGIsBottomShadow(it)\
        (((x11_xbgi*)(it->inherit_members))->bottom_shadow)
#define XBGIsTopShadow(it)\
        (((x11_xbgi*)(it->inherit_members))->top_shadow)
#define XBGIsDefaultGC(it)\
        (((x11_xbgi*)(it->inherit_members))->default_gc)
#define XBGIsFontStruct(it)\
        (((x11_xbgi*)(it->inherit_members))->font_struct)
#define XBGIsRoot(it)\
        (((x11_xbgi*)(it->inherit_members))->root)
#define XBGIsWins(it)\
        (((x11_xbgi*)(it->inherit_members))->wins)
#define XBGIsDrawGC(it)\
        (((x11_xbgi*)(it->inherit_members))->draw_gc)
#define XBGIsFillGC(it)\
        (((x11_xbgi*)(it->inherit_members))->fill_gc)
#define XBGIsPixelGC(it)\
        (((x11_xbgi*)(it->inherit_members))->pixel_gc)
#define XBGIsImageGC(it)\
        (((x11_xbgi*)(it->inherit_members))->image_gc)
#define XBGIsStrokeFonts(it)\
        (((x11_xbgi*)(it->inherit_members))->stroke_fonts)
#define XBGIsBiFonts(it)\
        (((x11_xbgi*)(it->inherit_members))->bi_fonts)
#define XBGIsMultiFonts(it)\
        (((x11_xbgi*)(it->inherit_members))->multi_fonts)
#define XBGIsColortable(it)\
        (((x11_xbgi*)(it->inherit_members))->colortable)
#define XBGIsPixels(it)\
        (((x11_xbgi*)(it->inherit_members))->pixels)
#define XBGIsRGB(it)\
        (((x11_xbgi*)(it->inherit_members))->rgb)
#define XBGIsEvent(it)\
        (((x11_xbgi*)(it->inherit_members))->event)

/*
 * Inheritor of current xbgi for X
 */
#define XBGIDisplay      (XBGIsDisplay(XBGI))
#define XBGIScreen       (XBGIsScreen(XBGI))
#define XBGIVisual       (XBGIsVisual(XBGI))
#define XBGIDepth        (XBGIsDepth(XBGI))
#define XBGIVisualClass  (XBGIsVisualClass(XBGI))
#define XBGIColormap     (XBGIsColormap(XBGI))
#define XBGIBackground   (XBGIsBackground(XBGI))
#define XBGIForeground   (XBGIsForeground(XBGI))
#define XBGIBottomShadow (XBGIsBottomShadow(XBGI))
#define XBGITopShadow    (XBGIsTopShadow(XBGI))
#define XBGIDefaultGC    (XBGIsDefaultGC(XBGI))
#define XBGIFontStruct   (XBGIsFontStruct(XBGI))
#define XBGIRoot         (XBGIsRoot(XBGI))
#define XBGIWins         (XBGIsWins(XBGI))
#define XBGIDrawGC       (XBGIsDrawGC(XBGI))
#define XBGIFillGC       (XBGIsFillGC(XBGI))
#define XBGIPixelGC      (XBGIsPixelGC(XBGI))
#define XBGIImageGC      (XBGIsImageGC(XBGI))
#define XBGIStrokeFonts  (XBGIsStrokeFonts(XBGI))
#define XBGIBiFonts      (XBGIsBiFonts(XBGI))
#define XBGIMultiFonts   (XBGIsMultiFonts(XBGI))
#define XBGIColortable   (XBGIsColortable(XBGI))
#define XBGIPixels       (XBGIsPixels(XBGI))
#define XBGIRGB          (XBGIsRGB(XBGI))
#define XBGIEvent        (XBGIsEvent(XBGI))

/*
 * special services depending on this driver
 */
#ifdef _XtIntrinsic_h
xbgi *XbgiSimpleCreateFromWidget( Widget w );
#endif

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GRAPHIX_X11_H_ */




