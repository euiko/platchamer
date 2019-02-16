/*
 * Source File < common/pixel.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced functions to draw pixels
 */
void putpixels( int numpoints, int *points, int color )
{
  XBGI->inherit_procedures->putpixels( numpoints, points, color );
}
/*
 * standard function to get and put pixel color
 */
unsigned getpixel( int x, int y )
{
  return XBGI->inherit_procedures->getpixel( x, y );
}
void putpixel( int x, int y, int color )
{
  XBGI->inherit_procedures->putpixel( x, y, color );
}
/*
 * extented functions for high-quality graphics
 */
void _putpixels( int numpoints, double *points, int color )
{
  XBGI->inherit_procedures->_putpixels( numpoints, points, color );
}
unsigned _getpixel( double x, double y )
{
  return XBGI->inherit_procedures->_getpixel( x, y );
}
void _putpixel( double x, double y, int color )
{
  XBGI->inherit_procedures->_putpixel( x, y, color );
}





