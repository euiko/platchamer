/*
 * Source File < ps/line.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * official enhanced functions to draw lines
 */
void lines( int numpoints, int *points )
{
  int i;

  ps_xbgi_begin( "lines" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH"\n" );
  i = 0;
  if ( numpoints>0 )
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(points[i]), Xy(points[i+1]) );
  for ( i=2; i<numpoints*2; i+=2 )
    ps_xbgi_printf( "%d %d "LINETO"\n", Xx(points[i]), Xy(points[i+1]) );
  ps_xbgi_printf( ""STROKE"\n" );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "lines" );
}
/*
 * standard functions to draw line
 */
void line( int x1, int y1, int x2, int y2 )
{
  ps_xbgi_begin( "line" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH"\n" );
  ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x1), Xy(y1) );
  ps_xbgi_printf( "%d %d "LINETO"\n", Xx(x2), Xy(y2) );
  ps_xbgi_printf( ""STROKE"\n" );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "line" );
}
void linerel( int dx, int dy )
{
  line( XBGI->cp.x, XBGI->cp.y, XBGI->cp.x + dx, XBGI->cp.y + dy );
  XBGI->cp.x += dx;
  XBGI->cp.y += dy;
}
void lineto( int x, int y )
{
  line( XBGI->cp.x, XBGI->cp.y, x, y );
  XBGI->cp.x = x;
  XBGI->cp.y = y;
}
/*
 * extented functions for high-quality graphics
 */
void _lines( int numpoints, double *points )
{
  int i;

  ps_xbgi_begin( "_lines" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH"\n" );
  i = 0;
  if ( numpoints>0 )
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(points[i]), Xy(points[i+1]) );
  for ( i=2; i<numpoints*2; i+=2 )
    ps_xbgi_printf( "%g %g "LINETO"\n", Xx(points[i]), Xy(points[i+1]) );
  ps_xbgi_printf( ""STROKE"\n" );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_lines" );
}
void _line( double x1, double y1, double x2, double y2 )
{
  ps_xbgi_begin( "_line" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH"\n" );
  ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x1), Xy(y1) );
  ps_xbgi_printf( "%g %g "LINETO"\n", Xx(x2), Xy(y2) );
  ps_xbgi_printf( ""STROKE"\n" );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_line" );
}
void _linerel( double dx, double dy )
{
  _line( XBGI->cp.x, XBGI->cp.y, XBGI->cp.x + dx, XBGI->cp.y + dy );
  XBGI->cp.x += dx;
  XBGI->cp.y += dy;
}
void _lineto( double x, double y )
{
  _line( XBGI->cp.x, XBGI->cp.y, x, y );
  XBGI->cp.x = x;
  XBGI->cp.y = y;
}
