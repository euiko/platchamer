/*
 * Source File < common/request.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced functions to flush or sync request
 */
void xflush( void )
{
  XBGI->inherit_procedures->xflush();
}
void xsync( void )
{
  XBGI->inherit_procedures->xsync();
}





