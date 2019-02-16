/*
 * Source File < ps/pixel.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard function to get and put pixel color
 */
unsigned getpixel( int x, int y )
{
  NotSupported( "getpixel()" );
  return 0;
}
void putpixel( int x, int y, int color )
{
  ps_xbgi_begin( "putpixel" );
  ps_xbgi_put_color( color );
  /*ps_xbgi_printf( ""NEWPATH" %d %d %d %d "BOX" "FILL"\n",
		 Xx(x), Xy(y), Xx(x+1), Xy(y+1) );*/
  ps_xbgi_printf( "%d %d "PUTPIXEL"\n", Xx(x), Xy(y) );
  ps_xbgi_end( "putpixel" );
}
void putpixels( int numpoints, int *points, int color )
{
  int i;

  ps_xbgi_begin( "putpixels" );
  ps_xbgi_put_color( color );
  for ( i=0; i<numpoints*2; i+=2 )
    /*ps_xbgi_printf( ""NEWPATH" %d %d %d %d "BOX" "FILL"\n",
		   Xx(points[i]), Xy(points[i+1]),
		   Xx(points[i]+1), Xy(points[i+1]+1) );*/
    ps_xbgi_printf( "%d %d "PUTPIXEL"\n", Xx(points[i]), Xy(points[i+1]) );
  ps_xbgi_end( "putpixels" );
}
/*
 * extented functions for high-quality graphics
 */
void _putpixels( int numpoints, double *points, int color )
{
  int i;

  ps_xbgi_begin( "putpixels" );
  ps_xbgi_put_color( color );
  for ( i=0; i<numpoints*2; i+=2 )
    /*ps_xbgi_printf( ""NEWPATH" %g %g %g %g "BOX" "FILL"\n",
		   Xx(points[i]-0.05), Xy(points[i+1]-0.05),
		   Xx(points[i]+0.05), Xy(points[i+1]+0.05) );*/ /* ! */
    ps_xbgi_printf( "%g %g "PUTDOT"\n", Xx(points[i]), Xy(points[i+1]) );
  ps_xbgi_end( "putpixels" );
}
unsigned _getpixel( double x, double y )
{
  return getpixel( x, y );
}
void _putpixel( double x, double y, int color )
{
  ps_xbgi_begin( "_putpixel" );
  ps_xbgi_put_color( color );
  /*ps_xbgi_printf( ""NEWPATH" %g %g %g %g "BOX" "FILL"\n",
		 Xx(x-0.05), Xy(y-0.05), Xx(x+0.05), Xy(y+0.05) );*/ /* ! */
  ps_xbgi_printf( "%g %g "PUTDOT"\n", Xx(x), Xy(y) );
  ps_xbgi_end( "_putpixel" );
}
