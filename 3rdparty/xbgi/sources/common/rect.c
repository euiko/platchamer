/*
 * Source File < common/rect.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to draw rectangle
 */
void rectangle( int left, int top, int right, int bottom )
{
  XBGI->inherit_procedures->rectangle( left, top, right, bottom );
}
/*
 * extented functions for high-quality graphics
 */
void _rectangle( double left, double top, double right, double bottom )
{
  XBGI->inherit_procedures->_rectangle( left, top, right, bottom );
}
