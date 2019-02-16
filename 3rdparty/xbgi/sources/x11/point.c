/*
 * Source File < x11/point.c >
 *
 * Enhanced Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * official enhanced functions to draw point[s]
 */
void putpoints( int numpoints, int *points )
{
  int i;

  for ( i=0; i<numpoints*2; i+=2 )
    putpoint( points[i], points[i+1] );
}
void getpointsettings( struct pointsettingstype *pointinfo )
{
  *pointinfo = XBGI->pointset;
}
void setpointstyle( int type, int color, int fillcolor, int size )
{
  XBGI->pointset.type = type;
  XBGI->pointset.color = color;
  XBGI->pointset.fillcolor = fillcolor;
  XBGI->pointset.size = size;
}
void putpoint( int x, int y )
{
  int cx = getx(), cy = gety();
  int color = getcolor();
  struct linesettingstype ls;
  struct fillsettingstype fs;
  double size = XBGI->pointset.size;

  getlinesettings( &ls );
  getfillsettings( &fs );
  setlinestyle( SOLID_LINE, 0, 1 );
  switch ( XBGI->pointset.type ) {
  case LOZENGE_POINT:
    {
      int lozenge[5*2];

      lozenge[0] = 0,		lozenge[1] = -size/2;
      lozenge[2] = -size/2,	lozenge[3] = 0;
      lozenge[4] = 0,		lozenge[5] = size/2;
      lozenge[6] = size/2,	lozenge[7] = 0;
      lozenge[8] = 0,		lozenge[9] = -size/2;

      lozenge[0] += x,		lozenge[1] += y;
      lozenge[2] += x,		lozenge[3] += y;
      lozenge[4] += x,		lozenge[5] += y;
      lozenge[6] += x,		lozenge[7] += y;
      lozenge[8] += x,		lozenge[9] += y;

      setcolor( XBGI->pointset.color );
      setfillstyle( SOLID_FILL, XBGI->pointset.fillcolor );
      fillpoly( 5, lozenge );
    }
    break;
  case CROSS_POINT:
    {
      int cross[4*2];

      cross[0] = 0,		cross[1] = -size/2;
      cross[2] = 0,		cross[3] = size/2;
      cross[4] = -size/2,	cross[5] = 0;
      cross[6] = size/2,	cross[7] = 0;

      cross[0] += x,		cross[1] += y;
      cross[2] += x,		cross[3] += y;
      cross[4] += x,		cross[5] += y;
      cross[6] += x,		cross[7] += y;

      setcolor( XBGI->pointset.color );
      line( cross[0],cross[1], cross[2],cross[3] );
      line( cross[4],cross[5], cross[6],cross[7] );
    }
    break;
  case SQUARE_POINT:
    {
      int square[5*2];

      square[0] = -size/2,	square[1] = -size/2;
      square[2] = -size/2,	square[3] = size/2;
      square[4] = size/2,	square[5] = size/2;
      square[6] = size/2,	square[7] = -size/2;
      square[8] = -size/2,	square[9] = -size/2;

      square[0] += x,		square[1] += y;
      square[2] += x,		square[3] += y;
      square[4] += x,		square[5] += y;
      square[6] += x,		square[7] += y;
      square[8] += x,		square[9] += y;

      setcolor( XBGI->pointset.color );
      setfillstyle( SOLID_FILL, XBGI->pointset.fillcolor );
      /*fillpoly( 5, square );*/
      bar( square[0],square[1], square[4],square[5] );
      rectangle( square[0],square[1], square[4],square[5] );
    }
    break;
  case XCROSS_POINT:
    {
      int xcross[4*2];

      xcross[0] = -size/2,	xcross[1] = -size/2;
      xcross[2] = size/2,	xcross[3] = size/2;
      xcross[4] = size/2,	xcross[5] = -size/2;
      xcross[6] = -size/2,	xcross[7] = size/2;

      xcross[0] += x,		xcross[1] += y;
      xcross[2] += x,		xcross[3] += y;
      xcross[4] += x,		xcross[5] += y;
      xcross[6] += x,		xcross[7] += y;

      setcolor( XBGI->pointset.color );
      line( xcross[0],xcross[1], xcross[2],xcross[3] );
      line( xcross[4],xcross[5], xcross[6],xcross[7] );
    }
    break;
  case TRIANGLE_POINT:
    {
      int triangle[4*2];

      triangle[0] = 0,		triangle[1] = -size*1.7320508/3;
      triangle[2] = -size/2,	triangle[3] = size*1.7320508/6;
      triangle[4] = size/2,	triangle[5] = size*1.7320508/6;
      triangle[6] = 0,		triangle[7] = -size*1.7320508/3;

      triangle[0] += x,		triangle[1] += y;
      triangle[2] += x,		triangle[3] += y;
      triangle[4] += x,		triangle[5] += y;
      triangle[6] += x,		triangle[7] += y;

      setcolor( XBGI->pointset.color );
      setfillstyle( SOLID_FILL, XBGI->pointset.fillcolor );
      fillpoly( 4, triangle );
    }
    break;
  case ASTERISK_POINT:
    {
      int asterisk[8*2];

      asterisk[0] = 0,		asterisk[1] = -size/2;
      asterisk[2] = 0,		asterisk[3] = size/2;
      asterisk[4] = -size/2,	asterisk[5] = 0;
      asterisk[6] = size/2,	asterisk[7] = 0;
      asterisk[8] = -size/2,	asterisk[9] = -size/2;
      asterisk[10] = size/2,	asterisk[11] = size/2;
      asterisk[12] = size/2,	asterisk[13] = -size/2;
      asterisk[14] = -size/2,	asterisk[15] = size/2;

      asterisk[0] += x,		asterisk[1] += y;
      asterisk[2] += x,		asterisk[3] += y;
      asterisk[4] += x,		asterisk[5] += y;
      asterisk[6] += x,		asterisk[7] += y;
      asterisk[8] += x,		asterisk[9] += y;
      asterisk[10] += x,	asterisk[11] += y;
      asterisk[12] += x,	asterisk[13] += y;
      asterisk[14] += x,	asterisk[15] += y;

      setcolor( XBGI->pointset.color );
      line( asterisk[0],asterisk[1], asterisk[2],asterisk[3] );
      line( asterisk[4],asterisk[5], asterisk[6],asterisk[7] );
      line( asterisk[8],asterisk[9], asterisk[10],asterisk[11] );
      line( asterisk[12],asterisk[13], asterisk[14],asterisk[15] );
    }
    break;
  case CIRCLE_POINT:
    {
      setcolor( XBGI->pointset.color );
      setfillstyle( SOLID_FILL, XBGI->pointset.fillcolor );
      fillellipse( x,y, size/2, size/2 );
    }
    break;
  case CHECKMARK_POINT:
    {
      int checkmark[3*2];

      checkmark[0] = -size/2,	checkmark[1] = 0;
      checkmark[2] = -size/4,	checkmark[3] = size/2;
      checkmark[4] = size/2,	checkmark[5] = -size/2;

      checkmark[0] += x,	checkmark[1] += y;
      checkmark[2] += x,	checkmark[3] += y;
      checkmark[4] += x,	checkmark[5] += y;

      setcolor( XBGI->pointset.color );
      line( checkmark[0],checkmark[1], checkmark[2],checkmark[3] );
      line( checkmark[2],checkmark[3], checkmark[4],checkmark[5] );
    }
    break;
  }
  moveto( cx, cy );
  setcolor( color );
  setlinestyle( ls.linestyle, ls.upattern, ls.thickness );
  setfillstyle( fs.pattern, fs.color );
}
/*
 * extented functions for high-quality graphics
 */
void _putpoints( int numpoints, double *points )
{
  int i;

  for ( i=0; i<numpoints*2; i+=2 )
    _putpoint( points[i], points[i+1] );
}
void _putpoint( double x, double y )
{
  putpoint( x, y );
}
