/*
 * Source File < ps/arcinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to get and set arc settings
 */
void getarccoords( struct arccoordstype *arccoords )
{
  double stangle, endangle;
  
  stangle  = (double)(XBGI->arcset.stangle)* M_PI/180;
  endangle = (double)(XBGI->arcset.endangle)*M_PI/180;

  arccoords->x      = XBGI->arcset.x;
  arccoords->y      = XBGI->arcset.y;
  arccoords->xstart = XBGI->arcset.x + (int)(cos(stangle)
					     *XBGI->arcset.xradius);
  arccoords->ystart = XBGI->arcset.y - (int)(sin(stangle)
					     *XBGI->arcset.yradius);
  arccoords->xend   = XBGI->arcset.x + (int)(cos(endangle)
					     *XBGI->arcset.xradius);
  arccoords->yend   = XBGI->arcset.y - (int)(sin(endangle)
					     *XBGI->arcset.yradius);
}
void getaspectratio( int *xasp, int *yasp )
{
  *xasp = 10000; *yasp = 10000;
}
void setaspectratio( int xasp, int yasp )
{
  ReservedFuture( "setaspectratio()" );
}





