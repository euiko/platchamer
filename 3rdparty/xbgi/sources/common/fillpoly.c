/*
 * Source File < common/fillpoly.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard function to fill polygon
 */
void fillpoly( int numpoints, int *polypoints )
{
  XBGI->inherit_procedures->fillpoly( numpoints, polypoints );
}
/*
 * extented functions for high-quality graphics
 */
void _fillpoly( int numpoints, double *polypoints )
{
  XBGI->inherit_procedures->_fillpoly( numpoints, polypoints );
}
