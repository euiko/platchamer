/*
 * Source File < ps/palette.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to get and set palette
 */
struct palettetype *getdefaultpalette( void )
{
  static struct palettetype def;
  int c;
  
  def.size = XBGI->palette.size;
  for ( c=0; c<def.size; c++ )
    def.colors[c] = c;
  return &def;
}
void getpalette( struct palettetype *palette )
{
  *palette = XBGI->palette;
}
int getpalettesize( void )
{
  return XBGI->palette.size;
}
void setpalette( int colornum, int color );
void setallpalette( struct palettetype *palette )
{
  int c;

  XBGI->palette = *palette;
  for ( c=0; c<palette->size; c++ )
    setpalette( palette->colors[c], c ); 
}
void setpalette( int colornum, int color )
{
  switch( XBGI->gmode ){
  case PSMONO:
  case PSGRAY:
  case PSCOLOR:
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    color    = minmax( 0, color,    XBGI->palette.size-1 );
    XBGI->palette.colors[color] = (unsigned char)colornum;
    break;
  }
}
void _setrgbpalette( int colornum,
                    unsigned short red,
                    unsigned short green,
                    unsigned short blue );
void setrgbpalette( int colornum, int red, int green, int blue )
{
  _setrgbpalette( colornum, 
                 minmax( 0, 65536*red  /XBGI->palette.size, 65536-1 ),
                 minmax( 0, 65536*green/XBGI->palette.size, 65536-1 ),
                 minmax( 0, 65536*blue /XBGI->palette.size, 65536-1 ) );
}
void _setrgbpalette( int colornum,
                    unsigned short red,
                    unsigned short green,
                    unsigned short blue )
{
  switch( XBGI->gmode ){
  case PSMONO:
  case PSGRAY:
  case PSCOLOR:
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    PSBGIRGB[colornum].red   = (double)red  /65535;
    PSBGIRGB[colornum].green = (double)green/65535;
    PSBGIRGB[colornum].blue  = (double)blue /65535;
    break;
  }
}











