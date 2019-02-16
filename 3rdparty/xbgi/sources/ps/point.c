/*
 * Source File < ps/point.c >
 *
 * Enhanced Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * official enhanced functions to draw point[s]
 */
void putpoints( int numpoints, int *points )
{
  int i;
  
  ps_xbgi_begin( "putpoints" );
  switch ( XBGI->pointset.type ) {
  case LOZENGE_POINT: default:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %d %d %d "LOZENGEPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case CROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %d %d %d "CROSSPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  case SQUARE_POINT:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %d %d %d "SQUAREPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case XCROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %d %d %d "XCROSSPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  case TRIANGLE_POINT:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %d %d %d "TRIANGLEPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case ASTERISK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %d %d %d "ASTERISKPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  case CIRCLE_POINT:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %d %d %d "CIRCLEPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case CHECKMARK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %d %d %d "CHECKMARKPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  }
  ps_xbgi_end( "putpoints" );
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
  ps_xbgi_begin( "putpoint" );
  switch ( XBGI->pointset.type ) {
  case LOZENGE_POINT: default:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "LOZENGEPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case CROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "CROSSPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  case SQUARE_POINT:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "SQUAREPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case XCROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "XCROSSPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  case TRIANGLE_POINT:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "TRIANGLEPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case ASTERISK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "ASTERISKPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  case CIRCLE_POINT:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "CIRCLEPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case CHECKMARK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %d %d %d "CHECKMARKPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  }
  ps_xbgi_end( "putpoint" );
}
/*
 * extented functions for high-quality graphics
 */
void _putpoints( int numpoints, double *points )
{
  int i;
  
  ps_xbgi_begin( "_putpoints" );
  switch ( XBGI->pointset.type ) {
  case LOZENGE_POINT: default:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %g %g %d "LOZENGEPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case CROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %g %g %d "CROSSPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  case SQUARE_POINT:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %g %g %d "SQUAREPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case XCROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %g %g %d "XCROSSPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  case TRIANGLE_POINT:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %g %g %d "TRIANGLEPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case ASTERISK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %g %g %d "ASTERISKPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  case CIRCLE_POINT:
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_put_color( XBGI->pointset.fillcolor );
      ps_xbgi_printf( ""NEWPATH" %g %g %d "CIRCLEPOINT"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
      ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
      ps_xbgi_put_color( XBGI->pointset.color );
      ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
      ps_xbgi_put_dash( "[]", 0 );
      ps_xbgi_printf( ""STROKE"\n" );
    }
    break;
  case CHECKMARK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    for ( i=0; i<numpoints*2; i+=2 ) {
      ps_xbgi_printf( ""NEWPATH" %g %g %d "CHECKMARKPOINT" "STROKE"\n",
		     Xx(points[i]), Xy(points[i+1]), XBGI->pointset.size );
    }
    break;
  }
  ps_xbgi_end( "_putpoints" );
}
void _putpoint( double x, double y )
{
  ps_xbgi_begin( "_putpoint" );
  switch ( XBGI->pointset.type ) {
  case LOZENGE_POINT: default:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "LOZENGEPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case CROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "CROSSPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  case SQUARE_POINT:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "SQUAREPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case XCROSS_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "XCROSSPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  case TRIANGLE_POINT:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "TRIANGLEPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case ASTERISK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "ASTERISKPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  case CIRCLE_POINT:
    ps_xbgi_put_color( XBGI->pointset.fillcolor );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "CIRCLEPOINT"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    ps_xbgi_printf( ""GSAVE" "FILL" "GRESTORE"\n" );
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 0 ); /* fine stroke since 19991225 */
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""STROKE"\n" );
    break;
  case CHECKMARK_POINT:
    ps_xbgi_put_color( XBGI->pointset.color );
    ps_xbgi_put_linewidth( 1 );
    ps_xbgi_put_dash( "[]", 0 );
    ps_xbgi_printf( ""NEWPATH" %g %g %d "CHECKMARKPOINT" "STROKE"\n",
		   Xx(x), Xy(y), XBGI->pointset.size );
    break;
  }
  ps_xbgi_end( "_putpoint" );
}
