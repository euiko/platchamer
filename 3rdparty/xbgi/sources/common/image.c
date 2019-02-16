/*
 * Source File < common/image.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to get and put image
 */
unsigned imagesize( int left, int top, int right, int bottom )
{
  return XBGI->inherit_procedures->imagesize( left, top, right, bottom );
}
void getimage( int left, int top, int right, int bottom, void *bitmap )
{
  XBGI->inherit_procedures->getimage( left, top, right, bottom, bitmap );
}
void putimage( int left, int top, void *bitmap, int op )
{
  XBGI->inherit_procedures->putimage( left, top, bitmap, op );
}
/*
 * extented functions for high-quality graphics
 */
void _getimage( double left, double top, double right, double bottom,
	       void *bitmap )
{
  XBGI->inherit_procedures->_getimage( left, top, right, bottom, bitmap );
}
void _putimage( double left, double top, void *bitmap, int op )
{
  XBGI->inherit_procedures->_putimage( left, top, bitmap, op );
}
