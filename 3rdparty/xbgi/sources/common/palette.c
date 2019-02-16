/*
 * Source File < common/palette.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to get and set palette
 */
struct palettetype *getdefaultpalette( void )
{
  return XBGI->inherit_procedures->getdefaultpalette();
}
void getpalette( struct palettetype *palette )
{
  XBGI->inherit_procedures->getpalette( palette );
}
int getpalettesize( void )
{
  return XBGI->inherit_procedures->getpalettesize();
}
void setallpalette( struct palettetype *palette )
{
  XBGI->inherit_procedures->setallpalette( palette );
}
void setpalette( int colornum, int color )
{
  XBGI->inherit_procedures->setpalette( colornum, color );
}
void setrgbpalette( int colornum, int red, int green, int blue )
{
  XBGI->inherit_procedures->setrgbpalette( colornum, red, green, blue );
}
void _setrgbpalette( int colornum,
                    unsigned short red,
                    unsigned short green,
                    unsigned short blue )
{
  XBGI->inherit_procedures->_setrgbpalette( colornum, red, green, blue );
}






