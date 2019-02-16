/*
 * Source File < common/fillarc.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to fill arc
 */
void fillellipse( int x, int y, int xradius, int yradius )
{
  XBGI->inherit_procedures->fillellipse( x, y, xradius, yradius );
}
void pieslice( int x, int y, int stangle, int endangle, int radius )
{
  XBGI->inherit_procedures->pieslice( x, y, stangle, endangle, radius );
}
void sector( int x, int y, int stangle, int endangle,
            int xradius, int yradius )
{
  XBGI->inherit_procedures->sector( x, y, stangle, endangle, xradius, yradius );
}
/*
 * extented functions for high-quality graphics
 */
void _fillellipse( double x, double y, double xradius, double yradius )
{
  XBGI->inherit_procedures->_fillellipse( x, y, xradius, yradius );
}
void _pieslice( double x, double y, double stangle, double endangle,
	       double radius )
{
  XBGI->inherit_procedures->_pieslice( x, y, stangle, endangle, radius );
}
void _sector( double x, double y, double stangle, double endangle,
	     double xradius, double yradius )
{
  XBGI->inherit_procedures->_sector( x, y, stangle, endangle, xradius, yradius );
}
