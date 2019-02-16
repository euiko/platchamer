/*
 * Source File < common/move.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions for current point
 */
int getx( void )
{
  return XBGI->inherit_procedures->getx();
}
int gety( void )
{
  return XBGI->inherit_procedures->gety();
}
void moverel( int dx, int dy )
{
  XBGI->inherit_procedures->moverel( dx, dy );
}
void moveto( int x, int y )
{
  XBGI->inherit_procedures->moveto( x, y );
}
/*
 * extented functions for high-quality graphics
 */
double _getx( void )
{
  return XBGI->inherit_procedures->_getx();
}
double _gety( void )
{
  return XBGI->inherit_procedures->_gety();
}
void _moverel( double dx, double dy )
{
  XBGI->inherit_procedures->_moverel( dx, dy );
}
void _moveto( double x, double y )
{
  XBGI->inherit_procedures->_moveto( x, y );
}
