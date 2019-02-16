/*
 * Source File < ps/color.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"
#if 0
char ps_xbgi_scolor_names[MAXCOLORS][64] = {
#include "colors/scolor.def"
};
#endif

/*
 * standard functions to get and set color
 */
int getcolor( void )
{
  return XBGI->color;
}
int getbkcolor( void )
{
  return XBGI->bkcolor;
}
int getmaxcolor( void )
{
  return XBGI->palette.size-1;
}
void setcolor( int color )
{
  XBGI->color = minmax( 0, color, XBGI->palette.size-1 );
}
void setbkcolor( int color )
{
  XBGI->bkcolor = minmax( 0, color, XBGI->palette.size-1 );
}
void setmaxcolor( int c )
{
  int i, cc;
  unsigned long plane_mask;
  struct rgbtype {
    unsigned short red, green, blue;
  } rgb[8] = {
    { 0, 0, 0 },
    { 0, 0, 1 },
    { 0, 1, 0 },
    { 0, 1, 1 },
    { 1, 0, 0 },
    { 1, 0, 1 },
    { 1, 1, 0 },
    { 1, 1, 1 },
  };

  switch( XBGI->gmode ){
  case PSMONO:
    break;
  case PSGRAY:
  case PSCOLOR:
    if ( c<1 || MAXCOLORS<c ) return;
    XBGI->palette.size = c + 1;
    for ( i=0; i<XBGI->palette.size; i++ ){
      XBGI->palette.colors[i] = i;
    }
    if ( XBGI->colornames && XBGI->gerror == grNoInitGraph ){
      /* color name setting at graph booting */
      ;
    }else{
      /* normal algorithum color setting */
      for ( i=0; i<XBGI->palette.size/8; i++ )
        for ( cc=0; cc<8; cc++ )
          setrgbpalette( 8*i+cc,
                        8*(i+1)*rgb[cc].red,
                        8*(i+1)*rgb[cc].green,
                        8*(i+1)*rgb[cc].blue );
      for ( i=1; i<XBGI->palette.size/8; i++ )
        setrgbpalette( 8*i+0, 4*(i+1), 4*(i+1), 4*(i+1) );
      cc = XBGI->palette.size/2;
      for ( i=0; i<XBGI->palette.size/8; i++ )
        setrgbpalette( 8*i+7, cc+4*(i+1), cc+4*(i+1), cc+4*(i+1) );
    }
    break;
  }
}









