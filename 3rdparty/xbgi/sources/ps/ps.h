/*
 * Header File < ps.h >
 *
 * Enhanced Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _PS_H_
#define _PS_H_
#include <stdio.h>

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

typedef struct _Geometry {
  int showpage_count;
  int drawn;
  int x, y, width, height;
} Geometry;

typedef struct _FontStruct {
  char name[64];
  double tm[2][3];
} FontStruct;

typedef struct _Color {
  double red, green, blue;
} Color;

typedef struct _CurrentState {
  double linewidth;
  int linecap;
  int linejoin;
  double miterlimit;
  char dash[64];
  int dash_offset;
  Color color;
  char fillpat[64];
  int fillpatsz;
} CurrentState;

typedef struct _MediaCoordinate {
  char tag[64];
  int page_width, page_height;
  int orientation;
  double x, y;
  double factor;
} MediaCoordinate;

typedef struct _ps_xbgi {
  char title[64];
  int use_interp;
  char interp_name[64];
  FILE *interp_p;
  int use_file;
  char file_name[64];
  FILE *file_p;
  int encapsule;
  Geometry root;
  Geometry *wins;
  FontStruct *stroke_fonts[MAX_CHAR_FONT+1][MAX_CHAR_SIZE+1];
  FontStruct *bi_fonts[MAX_CHAR_SIZE+1];
  Color rgb[MAXCOLORS+1];
  double line_width;
  char dash[64];
  int dash_offset;
  char fillpat[64];
  int fillpatsz;
  CurrentState state;
  MediaCoordinate coordinate;
} ps_xbgi;

/*
 * Inheritor of xbgi for PostScript
 */
#define PSBGIsTitle(it)\
        (((ps_xbgi*)(it->inherit_members))->title)
#define PSBGIsUseInterp(it)\
        (((ps_xbgi*)(it->inherit_members))->use_interp)
#define PSBGIsInterpName(it)\
        (((ps_xbgi*)(it->inherit_members))->interp_name)
#define PSBGIsInterpP(it)\
        (((ps_xbgi*)(it->inherit_members))->interp_p)
#define PSBGIsUseFile(it)\
        (((ps_xbgi*)(it->inherit_members))->use_file)
#define PSBGIsFileName(it)\
        (((ps_xbgi*)(it->inherit_members))->file_name)
#define PSBGIsFileP(it)\
        (((ps_xbgi*)(it->inherit_members))->file_p)
#define PSBGIsEncapsule(it)\
        (((ps_xbgi*)(it->inherit_members))->encapsule)
#define PSBGIsRoot(it)\
        (((ps_xbgi*)(it->inherit_members))->root)
#define PSBGIsWins(it)\
        (((ps_xbgi*)(it->inherit_members))->wins)
#define PSBGIsStrokeFonts(it)\
        (((ps_xbgi*)(it->inherit_members))->stroke_fonts)
#define PSBGIsBiFonts(it)\
        (((ps_xbgi*)(it->inherit_members))->bi_fonts)
#define PSBGIsRGB(it)\
        (((ps_xbgi*)(it->inherit_members))->rgb)
#define PSBGIsLineWidth(it)\
        (((ps_xbgi*)(it->inherit_members))->line_width)
#define PSBGIsDash(it)\
        (((ps_xbgi*)(it->inherit_members))->dash)
#define PSBGIsDashOffset(it)\
        (((ps_xbgi*)(it->inherit_members))->dash_offset)
#define PSBGIsFillpat(it)\
        (((ps_xbgi*)(it->inherit_members))->fillpat)
#define PSBGIsFillpatsz(it)\
        (((ps_xbgi*)(it->inherit_members))->fillpatsz)
#define PSBGIsState(it)\
        (((ps_xbgi*)(it->inherit_members))->state)
#define PSBGIsCoordinate(it)\
        (((ps_xbgi*)(it->inherit_members))->coordinate)

/*
 * Inheritor of current xbgi for PostScript
 */
#define PSBGITitle       (PSBGIsTitle(XBGI))
#define PSBGIUseInterp   (PSBGIsUseInterp(XBGI))
#define PSBGIInterpName  (PSBGIsInterpName(XBGI))
#define PSBGIInterpP     (PSBGIsInterpP(XBGI))
#define PSBGIUseFile     (PSBGIsUseFile(XBGI))
#define PSBGIFileName    (PSBGIsFileName(XBGI))
#define PSBGIFileP       (PSBGIsFileP(XBGI))
#define PSBGIEncapsule   (PSBGIsEncapsule(XBGI))
#define PSBGIRoot        (PSBGIsRoot(XBGI))
#define PSBGIWins        (PSBGIsWins(XBGI))
#define PSBGIStrokeFonts (PSBGIsStrokeFonts(XBGI))
#define PSBGIBiFonts     (PSBGIsBiFonts(XBGI))
#define PSBGIRGB         (PSBGIsRGB(XBGI))
#define PSBGILineWidth   (PSBGIsLineWidth(XBGI))
#define PSBGIDash        (PSBGIsDash(XBGI))
#define PSBGIDashOffset  (PSBGIsDashOffset(XBGI))
#define PSBGIFillpat     (PSBGIsFillpat(XBGI))
#define PSBGIFillpatsz   (PSBGIsFillpatsz(XBGI))
#define PSBGIState       (PSBGIsState(XBGI))
#define PSBGICoordinate  (PSBGIsCoordinate(XBGI))

/*
 * special services depending on this driver
 */
/* no service */

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _PS_H_ */





