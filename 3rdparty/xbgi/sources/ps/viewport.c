/*
 * Source File < ps/viewport.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions for viewport as virtual drawing device
 */
void clearviewport( void )
{
  int left, top, right, bottom;
  
  left   = XBGI->viewport.left;
  top    = XBGI->viewport.top;
  right  = XBGI->viewport.right;
  bottom = XBGI->viewport.bottom;
  if ( XBGI->viewport.clip ) {
    ps_xbgi_begin( "clearviewport with clip" );
    ps_xbgi_put_color( XBGI->bkcolor );
    ps_xbgi_printf( ""NEWPATH" %d %d %d %d "BOX" "FILL"\n",
		   /*Xx(left), Xy(top), Xx(right), Xy(bottom) );*/
		   Xx(0), Xy(0), Xx(right-left), Xy(bottom-top) );
    ps_xbgi_end( "clearviewport with clip" );
  } else
    cleardevice();
}
void setviewport( int left, int top, int right, int bottom, int clip )
{
  XBGI->viewport.left   = min( left, right );
  XBGI->viewport.top    = min( top, bottom );
  XBGI->viewport.right  = max( left, right );
  XBGI->viewport.bottom = max( top, bottom );
  XBGI->viewport.clip   = clip;
  if ( XBGI->viewport.clip ) {
#if 0 /* reserved future since version 3.02 generic 19991024 */
    if ( PSBGIRoot.drawn ) {
      ps_xbgi_begin( "setviewport with clip" );
      ps_xbgi_printf( ""NEWPATH" %d %d %d %d "BOX" "CLIP"\n",
		     /*Xx(left), Xy(top), Xx(right), Xy(bottom) );*/
		     Xx(0), Xy(0), Xx(right-left), Xy(bottom-top) );
      ps_xbgi_end( "setviewport with clip" );
    }
#endif
  }
}
void getviewsettings( struct viewporttype *viewport )
{
  *viewport = XBGI->viewport;
}
