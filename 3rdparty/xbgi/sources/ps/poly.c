/*
 * Source File < ps/poly.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard function to draw polygon
 */
void drawpoly( int numpoints, int *points )
{
  int i;

  ps_xbgi_begin( "drawpoly" );
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
  ps_xbgi_end( "drawpoly" );
}
/*
 * extented functions for high-quality graphics
 */
void _drawpoly( int numpoints, double *points )
{
  int i;

  ps_xbgi_begin( "_drawpoly" );
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
  ps_xbgi_end( "_drawpoly" );
}
