/*
 * Source File < ps/fillpoly.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard function to fill polygon
 */
void fillpoly( int numpoints, int *points )
{
  int i;
  int minX = 0, minY = 0, maxX = 639, maxY = 399;

  ps_xbgi_begin( "fillpoly" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    i = 0;
    if ( numpoints>0 )
      ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(points[i]), Xy(points[i+1]) );
    for ( i=2; i<numpoints*2; i+=2 )
      ps_xbgi_printf( "%d %d "LINETO"\n", Xx(points[i]), Xy(points[i+1]) );
    ps_xbgi_printf( ""CLOSEPATH" "EOFILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""NEWPATH"\n" );
    i = 0;
    if ( numpoints>0 )
      ps_xbgi_printf( "%d %d "MOVETO"\n",
		     (minX=maxX=Xx(points[i])), (minY=maxY=Xy(points[i+1])) );
    for ( i=2; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( "%d %d "LINETO"\n", Xx(points[i]), Xy(points[i+1]) );
      minX = min(minX,Xx(points[i])); minY = min(minY,Xy(points[i+1]));
      maxX = max(maxX,Xx(points[i])); maxY = max(maxY,Xy(points[i+1]));
    }
    ps_xbgi_printf( ""CLOSEPATH"\n" );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""EOCLIP" "NEWPATH"\n" );
    ps_xbgi_printf( "PAT PATSZ %d %d %d %d "PATFILL"\n",
		   minX, minY, maxX-minX, maxY-minY );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
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
  ps_xbgi_printf( ""CLOSEPATH" "STROKE"\n" );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "fillpoly" );
}
/*
 * extented functions for high-quality graphics
 */
void _fillpoly( int numpoints, double *points )
{
  int i;
  double minX = 0, minY = 0, maxX = 639, maxY = 399;

  ps_xbgi_begin( "_fillpoly" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    i = 0;
    if ( numpoints>0 )
      ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(points[i]), Xy(points[i+1]) );
    for ( i=2; i<numpoints*2; i+=2 )
      ps_xbgi_printf( "%d %d "LINETO"\n", Xx(points[i]), Xy(points[i+1]) );
    ps_xbgi_printf( ""CLOSEPATH" "EOFILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""NEWPATH"\n" );
    i = 0;
    if ( numpoints>0 )
      ps_xbgi_printf( "%g %g "MOVETO"\n",
		     (minX=maxX=Xx(points[i])), (minY=maxY=Xy(points[i+1])) );
    for ( i=2; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( "%g %g "LINETO"\n", Xx(points[i]), Xy(points[i+1]) );
      minX = min(minX,Xx(points[i])); minY = min(minY,Xy(points[i+1]));
      maxX = max(maxX,Xx(points[i])); maxY = max(maxY,Xy(points[i+1]));
    }
    ps_xbgi_printf( ""CLOSEPATH"\n" );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""EOCLIP" "NEWPATH"\n" );
    ps_xbgi_printf( "PAT PATSZ %g %g %g %g "PATFILL"\n",
		   minX, minY, maxX-minX, maxY-minY );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
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
  ps_xbgi_printf( ""CLOSEPATH" "STROKE"\n" );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_fillpoly" );
}
