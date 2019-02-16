/*
 * Source File < common/point.c >
 *
 * Enhanced Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced functions to draw point[s]
 */
void putpoints( int numpoints, int *points )
{
  XBGI->inherit_procedures->putpoints( numpoints, points );
}
void getpointsettings( struct pointsettingstype *pointinfo )
{
  XBGI->inherit_procedures->getpointsettings( pointinfo );
}
void setpointstyle( int type, int color, int fillcolor, int size )
{
  XBGI->inherit_procedures->setpointstyle( type, color, fillcolor, size );
}
void putpoint( int x, int y )
{
  XBGI->inherit_procedures->putpoint( x, y );
}
/*
 * extented functions for high-quality graphics
 */
void _putpoints( int numpoints, double *points )
{
  XBGI->inherit_procedures->_putpoints( numpoints, points );
}
void _putpoint( double x, double y )
{
  XBGI->inherit_procedures->_putpoint( x, y );
}
