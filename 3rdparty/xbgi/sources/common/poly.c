/*
 * Source File < common/poly.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard function to draw polygon
 */
void drawpoly( int numpoints, int *polypoints )
{
  XBGI->inherit_procedures->drawpoly( numpoints, polypoints );
}
/*
 * extented functions for high-quality graphics
 */
void _drawpoly( int numpoints, double *polypoints )
{
  XBGI->inherit_procedures->_drawpoly( numpoints, polypoints );
}
