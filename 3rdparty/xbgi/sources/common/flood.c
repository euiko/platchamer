/*
 * Source File < common/flood.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard function to fill flood
 */
void floodfill( int x, int y, int border )
{
  XBGI->inherit_procedures->floodfill( x, y, border );
}
/*
 * extented functions for high-quality graphics
 */
void _floodfill( double x, double y, int border )
{
  XBGI->inherit_procedures->_floodfill( x, y, border );
}
