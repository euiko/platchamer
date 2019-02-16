/*
 * Source File < common/config.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions for configuration of graphics environment
 */
int getmaxx( void )
{
  return XBGI->inherit_procedures->getmaxx();
}
int getmaxy( void )
{
  return XBGI->inherit_procedures->getmaxy();
}
/*
 * official enhanced functions for configuration of graphics environment
 */
void setmaxx( int maxx )
{
  XBGI->inherit_procedures->setmaxx( maxx );
}
void setmaxy( int maxy )
{
  XBGI->inherit_procedures->setmaxy( maxy );
}
void getsizexy( int *xsize, int *ysize )
{
  XBGI->inherit_procedures->getsizexy( xsize, ysize );
}
void setsizexy( int xsize, int ysize )
{
  XBGI->inherit_procedures->setsizexy( xsize, ysize );
}
void getgeometry( int *x, int *y, int *width, int *height )
{
  XBGI->inherit_procedures->getgeometry( x, y, width, height );
}
void setgeometry( int x, int y, int width, int height )
{
  XBGI->inherit_procedures->setgeometry( x, y, width, height );
}
void settitle( char *title )
{
  XBGI->inherit_procedures->settitle( title );
}
void seticonname( char *filename )
{
  XBGI->inherit_procedures->seticonname( filename );
}
int seticon( char *filename )
{
  return XBGI->inherit_procedures->seticon( filename );
}
void setbackingstore( int flg )
{
  XBGI->inherit_procedures->setbackingstore( flg );
}





