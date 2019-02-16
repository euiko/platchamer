/*
 * Source File < ps/fillarc.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions to fill arc
 */
void fillellipse( int x, int y, int xradius, int yradius )
{
  ps_xbgi_begin( "fillellipse" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%d %d 0 360 %d %d "ELLIPSE"\n",
		   Xx(x), Xy(y), xradius, yradius );
    ps_xbgi_printf( "%d %d "LINETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( ""FILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%d %d 0 360 %d %d "ELLIPSE"\n",
		   Xx(x), Xy(y), xradius, yradius );
    ps_xbgi_printf( "%d %d "LINETO" "EOCLIP" "NEWPATH"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "PAT PATSZ %d %d %d %d "PATFILL"\n",
		   min(Xx(x-xradius),Xx(x+xradius)),
		   min(Xy(y-yradius),Xy(y+yradius)),
		   2*xradius, 2*yradius );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %d %d 0 360 %d %d "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), xradius, yradius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "fillellipse" );
}
void pieslice( int x, int y, int stangle, int endangle, int radius )
{
  ps_xbgi_begin( "pieslice" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%d %d %d %d %d %d "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, radius, radius );
    ps_xbgi_printf( "%d %d "LINETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( ""FILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%d %d %d %d %d %d "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, radius, radius );
    ps_xbgi_printf( "%d %d "LINETO" "EOCLIP" "NEWPATH"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "PAT PATSZ %d %d %d %d "PATFILL"\n",
		   min(Xx(x-radius),Xx(x+radius)),
		   min(Xy(y-radius),Xy(y+radius)),
		   2*radius, 2*radius );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %d %d %d %d %d %d "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, radius, radius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "pieslice" );
}
void sector( int x, int y, int stangle, int endangle,
            int xradius, int yradius )
{
  ps_xbgi_begin( "sector" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%d %d %d %d %d %d "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, xradius, yradius );
    ps_xbgi_printf( "%d %d "LINETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( ""FILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%d %d "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%d %d %d %d %d %d "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, xradius, yradius );
    ps_xbgi_printf( "%d %d "LINETO" "EOCLIP" "NEWPATH"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "PAT PATSZ %d %d %d %d "PATFILL"\n",
		   min(Xx(x-xradius),Xx(x+xradius)),
		   min(Xy(y-yradius),Xy(y+yradius)),
		   2*xradius, 2*yradius );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %d %d %d %d %d %d "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, xradius, yradius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "sector" );
}
/*
 * extented functions for high-quality graphics
 */
void _fillellipse( double x, double y, double xradius, double yradius )
{
  ps_xbgi_begin( "_fillellipse" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%g %g 0 360 %g %g "ELLIPSE"\n",
		   Xx(x), Xy(y), xradius, yradius );
    ps_xbgi_printf( "%g %g "LINETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( ""FILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%g %g 0 360 %g %g "ELLIPSE"\n",
		   Xx(x), Xy(y), xradius, yradius );
    ps_xbgi_printf( "%g %g "LINETO" "EOCLIP" "NEWPATH"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "PAT PATSZ %g %g %g %g "PATFILL"\n",
		   min(Xx(x-xradius),Xx(x+xradius)),
		   min(Xy(y-yradius),Xy(y+yradius)),
		   2*xradius, 2*yradius );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %g %g 0 360 %g %g "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), xradius, yradius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_fillellipse" );
}
void _pieslice( double x, double y, double stangle, double endangle,
	       double radius )
{
  ps_xbgi_begin( "_pieslice" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%g %g %g %g %g %g "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, radius, radius );
    ps_xbgi_printf( "%g %g "LINETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( ""FILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%g %g %g %g %g %g "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, radius, radius );
    ps_xbgi_printf( "%g %g "LINETO" "EOCLIP" "NEWPATH"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "PAT PATSZ %g %g %g %g "PATFILL"\n",
		   min(Xx(x-radius),Xx(x+radius)),
		   min(Xy(y-radius),Xy(y+radius)),
		   2*radius, 2*radius );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %g %g %g %g %g %g "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, radius, radius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_pieslice" );
}
void _sector( double x, double y, double stangle, double endangle,
	     double xradius, double yradius )
{
  ps_xbgi_begin( "_sector" );
  switch ( XBGI->fillset.pattern ) {
  case EMPTY_FILL:
    break;
  case SOLID_FILL:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%g %g %g %g %g %g "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, xradius, yradius );
    ps_xbgi_printf( "%g %g "LINETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( ""FILL"\n" );
    break;
  default:
    ps_xbgi_put_color( XBGI->fillset.color );
    ps_xbgi_put_fillpat( PSBGIFillpat, PSBGIFillpatsz );
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( ""NEWPATH"\n" );
    ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "%g %g %g %g %g %g "ELLIPSE"\n",
		   Xx(x), Xy(y), stangle, endangle, xradius, yradius );
    ps_xbgi_printf( "%g %g "LINETO" "EOCLIP" "NEWPATH"\n", Xx(x), Xy(y) );
    ps_xbgi_printf( "PAT PATSZ %g %g %g %g "PATFILL"\n",
		   min(Xx(x-xradius),Xx(x+xradius)),
		   min(Xy(y-yradius),Xy(y+yradius)),
		   2*xradius, 2*yradius );
    ps_xbgi_printf( ""GRESTORE"\n" );
    break;
  }
  ps_xbgi_put_linewidth( PSBGILineWidth );
  ps_xbgi_put_dash( PSBGIDash, PSBGIDashOffset );
  ps_xbgi_put_color( XBGI->color );
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( ""NEWPATH" %g %g %g %g %g %g "ELLIPSE" "STROKE"\n",
		 Xx(x), Xy(y), stangle, endangle, xradius, yradius );
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_sector" );
}
