/*
 * Source File < ps/fillrect.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to fill rectangle
 */
void bar( int left, int top, int right, int bottom )
{
  ps_xbgi_begin( "bar" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( "%d %d %d %d "BOX" "FILL"\n",
		   Xx(left), Xy(top), Xx(right), Xy(bottom) );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( "%d %d %d %d "BOX" "EOCLIP" "NEWPATH"\n",
		   Xx(left), Xy(top), Xx(right), Xy(bottom) );
    ps_xbgi_printf( "PAT PATSZ %d %d %d %d "PATFILL"\n",
		   min(Xx(left),Xx(right)), min(Xy(top),Xy(bottom)),
		   bottom-top, bottom-top );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
#if 0 /* fixed for incompatibility between X11 and PS since 19991225 */
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_put_miterlimit( 1.415 );
  ps_xbgi_printf( ""NEWPATH" %d %d %d %d "BOX" "STROKE"\n",
		 Xx(left), Xy(top), Xx(right), Xy(bottom) );
  ps_xbgi_put_miterlimit( 1 ); /* modified at 19991225 but not used */
  ps_xbgi_printf( ""GRESTORE"\n" );
#endif
  ps_xbgi_end( "bar" );
}
void bar3d( int left, int top, int right, int bottom, int depth, int topflag )
{
  /* ! */
}
/*
 * extented functions for high-quality graphics
 */
void _bar( double left, double top, double right, double bottom )
{
  ps_xbgi_begin( "_bar" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( "%g %g %g %g "BOX" "FILL"\n",
		   Xx(left), Xy(top), Xx(right), Xy(bottom) );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( "%g %g %g %g "BOX" "EOCLIP" "NEWPATH"\n",
		   Xx(left), Xy(top), Xx(right), Xy(bottom) );
    ps_xbgi_printf( "PAT PATSZ %g %g %g %g "PATFILL"\n",
		   min(Xx(left),Xx(right)), min(Xy(top),Xy(bottom)),
		   bottom-top, bottom-top );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
#if 0 /* fixed for incompatibility between X11 and PS since 19991225 */
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_put_miterlimit( 1.415 );
  ps_xbgi_printf( ""NEWPATH" %g %g %g %g "BOX" "STROKE"\n",
		 Xx(left), Xy(top), Xx(right), Xy(bottom) );
  ps_xbgi_put_miterlimit( 1 );
  ps_xbgi_printf( ""GRESTORE"\n" );
#endif
  ps_xbgi_end( "_bar" );
}
void _bar3d( double left, double top, double right, double bottom,
	    double depth, int topflag )
{
  /* ! */
}
