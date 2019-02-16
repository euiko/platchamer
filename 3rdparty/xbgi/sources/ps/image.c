/*
 * Source File < ps/image.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to get and put image
 */
unsigned imagesize( int left, int top, int right, int bottom )
{
  return (unsigned)(2 + (abs(right-left)+1)*(abs(bottom-top)+1));
}
void getimage( int left, int top, int right, int bottom, void *bitmap )
{
  NotSupported( "getimage()" );
}
void putimage( int left, int top, void *bitmap, int op )
{
  NotSupported( "putimage()" );
}
/*
 * extented functions for high-quality graphics
 */
void _getimage( double left, double top, double right, double bottom,
	       void *bitmap )
{
  getimage( left, top, right, bottom, bitmap );
}
void _putimage( double left, double top, void *bitmap, int op )
{
  putimage( left, top, bitmap, op );
}
