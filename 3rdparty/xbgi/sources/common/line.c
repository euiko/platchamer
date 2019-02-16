/*
 * Source File < common/line.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced functions to draw lines
 */
void lines( int numpoints, int *points )
{
  XBGI->inherit_procedures->lines( numpoints, points );
}
/*
 * standard functions to draw line
 */
void line( int x1, int y1, int x2, int y2 )
{
  XBGI->inherit_procedures->line( x1, y1, x2, y2 );
}
void linerel( int dx, int dy )
{
  XBGI->inherit_procedures->linerel( dx, dy );
}
void lineto( int x, int y )
{
  XBGI->inherit_procedures->lineto( x, y );
}
/*
 * extented functions for high-quality graphics
 */
void _lines( int numpoints, double *points )
{
  XBGI->inherit_procedures->_lines( numpoints, points );
}
void _line( double x1, double y1, double x2, double y2 )
{
  XBGI->inherit_procedures->_line( x1, y1, x2, y2 );
}
void _linerel( double dx, double dy )
{
  XBGI->inherit_procedures->_linerel( dx, dy );
}
void _lineto( double x, double y )
{
  XBGI->inherit_procedures->_lineto( x, y );
}
