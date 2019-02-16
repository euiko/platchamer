/*
 * Source File < ps/rect.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to draw rectangle
 */
void rectangle( int left, int top, int right, int bottom )
{
  ps_xbgi_begin( "rectangle" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_put_miterlimit( 1.415 );
  ps_xbgi_printf( ""NEWPATH" %d %d %d %d "BOX" "STROKE"\n",
		 Xx(left), Xy(top), Xx(right), Xy(bottom) );
  ps_xbgi_put_miterlimit( 1 );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "rectangle" );
}
/*
 * extented functions for high-quality graphics
 */
void _rectangle( double left, double top, double right, double bottom )
{
  ps_xbgi_begin( "_rectangle" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_put_miterlimit( 1.415 );
  ps_xbgi_printf( ""NEWPATH" %g %g %g %g "BOX" "STROKE"\n",
		 Xx(left), Xy(top), Xx(right), Xy(bottom) );
  ps_xbgi_put_miterlimit( 1 );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_rectangle" );
}
