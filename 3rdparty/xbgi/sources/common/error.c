/*
 * Source File < common/error.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions of error messenger
 */
int graphresult( void )
{
  return XBGI->inherit_procedures->graphresult();
}
char *grapherrormsg( int errorcode )
{
  return XBGI->inherit_procedures->grapherrormsg( errorcode );
}





