/*
 * Source File < ps/request.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * official enhanced functions to flush or sync request
 */
void xflush( void )
{
  ps_xbgi_flush();
}
void xsync( void )
{
  ps_xbgi_flush();
}








