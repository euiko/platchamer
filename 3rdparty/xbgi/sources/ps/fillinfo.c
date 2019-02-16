/*
 * Source File < ps/fillinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

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
  XBGI->fillset.pattern = minmax( 0, pattern, USER_FILL );
  XBGI->fillset.color   = minmax( 0, color, XBGI->palette.size-1 );
  if ( XBGI->fillset.pattern != SOLID_FILL
      && XBGI->fillset.pattern != EMPTY_FILL ) {
    int i;
    char pat[64], tmp[64];
    
    strcpy( pat, "<" );
    for ( i=0; i<8; i++ ) {
      sprintf( tmp, "%02x", (fill_bits[XBGI->fillset.pattern][i]&0x00ff) );
      strcat( pat, tmp );
    }
    strcat( pat, ">" );
    strcpy( PSBGIFillpat, pat );
    PSBGIFillpatsz = 8;
  }
}
void setfillpattern( char *upattern, int color )
{
  int i;

  XBGI->fillset.pattern = USER_FILL;
  XBGI->fillset.color   = minmax( 0, color, XBGI->palette.size-1 );
  for ( i=0; i<8; i++ )
    user_bits[i] = upattern[i];
  setfillstyle( USER_FILL, color );
}











