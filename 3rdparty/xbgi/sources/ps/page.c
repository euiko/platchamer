/*
 * Source File < ps/page.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions for page as drawing device
 */
void cleardevice( void )
{
  ps_xbgi_showpage();
}
void setactivepage( int page )
{
  XBGI->apage = minmax( 0, page, XBGI->npage-1 );
  /*NotSupported( "setactivepage()" );*/ /* ! */
}
void setvisualpage( int page )
{
  XBGI->vpage = minmax( 0, page, XBGI->npage-1 );
  /*NotSupported( "setvisualpage()" );*/ /* ! */
}
void restorecrtmode( void )
{
  NotSupported( "restorecrtmode()" );
}








