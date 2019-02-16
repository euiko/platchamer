/*
 * Source File < x11/fillinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

#include "bitmaps/fill/empty.xbm"
#include "bitmaps/fill/solid.xbm"
#include "bitmaps/fill/line.xbm"
#include "bitmaps/fill/ltslsh.xbm"
#include "bitmaps/fill/slsh.xbm"
#include "bitmaps/fill/bkslsh.xbm"
#include "bitmaps/fill/ltbkslsh.xbm"
#include "bitmaps/fill/hatch.xbm"
#include "bitmaps/fill/xhatch.xbm"
#include "bitmaps/fill/intleave.xbm"
#include "bitmaps/fill/widedot.xbm"
#include "bitmaps/fill/closedot.xbm"
#include "bitmaps/fill/user.xbm"
static char *fill_bits[USER_FILL+1] = {
  empty_bits,
  solid_bits,
  line_bits,
  ltslsh_bits,
  slsh_bits,
  bkslsh_bits,
  ltbkslsh_bits,
  hatch_bits,
  xhatch_bits,
  intleave_bits,
  widedot_bits,
  closedot_bits,
  user_bits,
};

/*
 * standard functions to get and set fillsettings
 */
void getfillsettings( struct fillsettingstype *fillinfo )
{
  *fillinfo = XBGI->fillset;
}
void getfillpattern( char *pattern )
{
  int i;

  for ( i=0; i<8; i++ )
    pattern[i] = fill_bits[XBGI->fillset.pattern][i];
}
void setfillstyle( int pattern, int color )
{
  Pixmap pm_fill;

  XBGI->fillset.pattern = minmax( 0, pattern, USER_FILL );
  XBGI->fillset.color   = minmax( 0, color, XBGI->palette.size-1 );
  XSetForeground( XBGIDisplay, XBGIFillGC, XBGIPixels[XBGI->fillset.color] );
  switch( XBGI->fillset.pattern ){
  case EMPTY_FILL:
    pm_fill = XCreateBitmapFromData( XBGIDisplay, XBGIRoot,
                                    fill_bits[XBGI->fillset.pattern], 8, 8 );
    XSetStipple( XBGIDisplay, XBGIFillGC, pm_fill );
    XSetFillStyle( XBGIDisplay, XBGIFillGC, FillStippled );
    break;
  case SOLID_FILL:
    XSetForeground( XBGIDisplay, XBGIFillGC,
                   XBGIPixels[XBGI->fillset.color] );
    XSetFillStyle( XBGIDisplay, XBGIFillGC, FillSolid );
    break;
  case LINE_FILL:
  case LTSLASH_FILL:
  case SLASH_FILL:
  case BKSLASH_FILL:
  case LTBKSLASH_FILL:
  case HATCH_FILL:
  case XHATCH_FILL:
  case INTERLEAVE_FILL:
  case WIDE_DOT_FILL:
  case CLOSE_DOT_FILL:
  case USER_FILL:
    pm_fill = XCreateBitmapFromData( XBGIDisplay, XBGIRoot,
                                    fill_bits[XBGI->fillset.pattern], 8, 8 );
    XSetStipple( XBGIDisplay, XBGIFillGC, pm_fill );
    XSetFillStyle( XBGIDisplay, XBGIFillGC, FillOpaqueStippled );
    break;
  }
}
void setfillpattern( char *upattern, int color )
{
  int i;
  Pixmap pm_fill;

  XBGI->fillset.pattern = USER_FILL;
  XBGI->fillset.color   = minmax( 0, color, XBGI->palette.size-1 );
  for ( i=0; i<8; i++ )
    user_bits[i] = upattern[i];
  XSetForeground( XBGIDisplay, XBGIFillGC, XBGIPixels[XBGI->fillset.color] );
  pm_fill = XCreateBitmapFromData( XBGIDisplay, XBGIRoot,
                                  user_bits, 8, 8 );
  XSetStipple( XBGIDisplay, XBGIFillGC, pm_fill );
  XSetFillStyle( XBGIDisplay, XBGIFillGC, FillOpaqueStippled );
}











