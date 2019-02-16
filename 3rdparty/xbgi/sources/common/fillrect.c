/*
 * Source File < common/fillrect.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to fill rectangle
 */
void bar( int left, int top, int right, int bottom )
{
  XBGI->inherit_procedures->bar( left, top, right, bottom );
}
void bar3d( int left, int top, int right, int bottom, int depth, int topflag )
{
  XBGI->inherit_procedures->bar3d( left, top, right, bottom, depth, topflag );
}
/*
 * extented functions for high-quality graphics
 */
void _bar( double left, double top, double right, double bottom )
{
  XBGI->inherit_procedures->_bar( left, top, right, bottom );
}
void _bar3d( double left, double top, double right, double bottom,
	    double depth, int topflag )
{
  XBGI->inherit_procedures->_bar3d( left, top, right, bottom, depth, topflag );
}
