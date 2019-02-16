/*
 * Source File < x11/fillarc.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions to fill arc
 */
void fillellipse( int x, int y, int xradius, int yradius )
{
  XFillArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
           Xx( x - xradius ), Xy( y - yradius ) , 2 * xradius, 2 * yradius,
           0, 64 * ( 360 - 0 ) );
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - xradius ), Xy( y - yradius ) , 2 * xradius, 2 * yradius,
           0, 64 * ( 360 - 0 ) );
}
void pieslice( int x, int y, int stangle, int endangle, int radius )
{
  double stangle2, endangle2;
  struct arccoordstype arccoords;
  struct arcsettingstype arcset;

  arcset.x        = x;
  arcset.y        = y;
  arcset.stangle  = stangle;
  arcset.endangle = endangle;
  arcset.xradius  = radius;
  arcset.yradius  = radius;

  stangle2  = (double)arcset.stangle* M_PI/180;
  endangle2 = (double)arcset.endangle*M_PI/180;

  arccoords.x      = arcset.x;
  arccoords.y      = arcset.y;
  arccoords.xstart = arcset.x + (int)((double)arcset.xradius*cos(stangle2 ));
  arccoords.ystart = arcset.y - (int)((double)arcset.yradius*sin(stangle2 ));
  arccoords.xend   = arcset.x + (int)((double)arcset.xradius*cos(endangle2));
  arccoords.yend   = arcset.y - (int)((double)arcset.yradius*sin(endangle2));

  XFillArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           64 * stangle, 64 * ( endangle - stangle ) );
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           64 * stangle, 64 * ( endangle - stangle ) );
  line( arccoords.xstart, arccoords.ystart, arccoords.x, arccoords.y );
  line( arccoords.xend,   arccoords.yend,   arccoords.x, arccoords.y );
}
void sector( int x, int y, int stangle, int endangle,
            int xradius, int yradius )
{
  XFillArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
           Xx( x - xradius ), Xy( y - yradius ), 2 * xradius, 2 * yradius,
           64 * stangle, 64 * ( endangle - stangle ) );
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - xradius ), Xy( y - yradius ), 2 * xradius, 2 * yradius,
           64 * stangle, 64 * ( endangle - stangle ) );
}
/*
 * extented functions for high-quality graphics
 */
void _fillellipse( double x, double y, double xradius, double yradius )
{
  fillellipse( x, y, xradius, yradius );
}
void _pieslice( double x, double y, double stangle, double endangle,
	       double radius )
{
  double stangle2, endangle2;
  struct arccoordstype arccoords;
  struct arcsettingstype arcset;

  arcset.x        = x;
  arcset.y        = y;
  arcset.stangle  = stangle;
  arcset.endangle = endangle;
  arcset.xradius  = radius;
  arcset.yradius  = radius;

  stangle2  = (double)arcset.stangle* M_PI/180;
  endangle2 = (double)arcset.endangle*M_PI/180;

  arccoords.x      = arcset.x;
  arccoords.y      = arcset.y;
  arccoords.xstart = arcset.x + (int)((double)arcset.xradius*cos(stangle2 ));
  arccoords.ystart = arcset.y - (int)((double)arcset.yradius*sin(stangle2 ));
  arccoords.xend   = arcset.x + (int)((double)arcset.xradius*cos(endangle2));
  arccoords.yend   = arcset.y - (int)((double)arcset.yradius*sin(endangle2));

  XFillArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIFillGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           64 * stangle, 64 * ( endangle - stangle ) );
  XDrawArc( XBGIDisplay, XBGIWins[XBGI->apage], XBGIDrawGC,
           Xx( x - radius ), Xy( y - radius ), 2 * radius, 2 * radius,
           64 * stangle, 64 * ( endangle - stangle ) );
  line( arccoords.xstart, arccoords.ystart, arccoords.x, arccoords.y );
  line( arccoords.xend,   arccoords.yend,   arccoords.x, arccoords.y );
}
void _sector( double x, double y, double stangle, double endangle,
	     double xradius, double yradius )
{
  sector( x, y, stangle, endangle, xradius, yradius );
}
