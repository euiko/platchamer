/*
 * Source File < ps/flood.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard function to fill flood
 */
void floodfill( int x, int y, int border )
{
  NotSupported( "floodfill()" );
}
/*
 * extented functions for high-quality graphics
 */
void _floodfill( double x, double y, int border )
{
  floodfill( x, y, border );
}
