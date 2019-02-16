/*
 * Source File < ps/arc.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to draw arc
 */
void arc( int x, int y, int stangle, int endangle, int radius )
{
  XBGI->arcset.x        = x;
  XBGI->arcset.y        = y;
  XBGI->arcset.stangle  = stangle;
  XBGI->arcset.endangle = endangle;
  XBGI->arcset.xradius  = radius;
  XBGI->arcset.yradius  = radius;
  ps_xbgi_begin( "arc" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %d %d %d %d %d %d "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, radius, radius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "arc" );
}
void circle( int x, int y, int radius )
{
  ps_xbgi_begin( "circle" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %d %d 0 360 %d %d "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), radius, radius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "circle" );
}
void ellipse( int x, int y, int stangle, int endangle,
             int xradius, int yradius )
{
  ps_xbgi_begin( "ellipse" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %d %d %d %d %d %d "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, xradius, yradius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "ellipse" );
}
/*
 * extented functions for high-quality graphics
 */
void _arc( double x, double y, double stangle, double endangle,
	  double radius )
{
  XBGI->arcset.x        = x;
  XBGI->arcset.y        = y;
  XBGI->arcset.stangle  = stangle;
  XBGI->arcset.endangle = endangle;
  XBGI->arcset.xradius  = radius;
  XBGI->arcset.yradius  = radius;
  ps_xbgi_begin( "_arc" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %g %g %g %g %g %g "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, radius, radius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_arc" );
}
void _circle( double x, double y, double radius )
{
  ps_xbgi_begin( "_circle" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %g %g 0 360 %g %g "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), radius, radius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_circle" );
}
void _ellipse( double x, double y, double stangle, double endangle,
	      double xradius, double yradius )
{
  ps_xbgi_begin( "_ellipse" );
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %g %g %g %g %g %g "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, xradius, yradius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_ellipse" );
}
