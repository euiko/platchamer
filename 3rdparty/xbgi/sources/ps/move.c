/*
 * Source File < ps/move.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions for current point
 */
int getx( void )
{
  return XBGI->cp.x;
}
int gety( void )
{
  return XBGI->cp.y;
}
void moverel( int dx, int dy )
{
  XBGI->cp.x += dx;
  XBGI->cp.y += dy;
}
void moveto( int x, int y )
{
  XBGI->cp.x = x;
  XBGI->cp.y = y;
}
/*
 * extented functions for high-quality graphics
 */
double _getx( void )
{
  return XBGI->cp.x;
}
double _gety( void )
{
  return XBGI->cp.y;
}
void _moverel( double dx, double dy )
{
  XBGI->cp.x += dx;
  XBGI->cp.y += dy;
}
void _moveto( double x, double y )
{
  XBGI->cp.x = x;
  XBGI->cp.y = y;
}
