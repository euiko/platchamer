/*
 * Source File < common/arc.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to draw arc
 */
void arc( int x, int y, int stangle, int endangle, int radius )
{
  XBGI->inherit_procedures->arc( x, y, stangle, endangle, radius );
}
void circle( int x, int y, int radius )
{
  XBGI->inherit_procedures->circle( x, y, radius );
}
void ellipse( int x, int y, int stangle, int endangle,
             int xradius, int yradius )
{
  XBGI->inherit_procedures->ellipse( x, y, stangle, endangle, xradius, yradius );
}
/*
 * extented functions for high-quality graphics
 */
void _arc( double x, double y, double stangle, double endangle,
	  double radius )
{
  XBGI->inherit_procedures->_arc( x, y, stangle, endangle, radius );
}
void _circle( double x, double y, double radius )
{
  XBGI->inherit_procedures->_circle( x, y, radius );
}
void _ellipse( double x, double y, double stangle, double endangle,
	      double xradius, double yradius )
{
  XBGI->inherit_procedures->_ellipse( x, y, stangle, endangle, xradius, yradius );
}
