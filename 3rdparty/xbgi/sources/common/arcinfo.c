/*
 * Source File < common/arcinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to get and set arc settings
 */
void getarccoords( struct arccoordstype *arccoords )
{
  XBGI->inherit_procedures->getarccoords( arccoords );
}
void getaspectratio( int *xasp, int *yasp )
{
  XBGI->inherit_procedures->getaspectratio( xasp, yasp );
}
void setaspectratio( int xasp, int yasp )
{
  XBGI->inherit_procedures->setaspectratio( xasp, yasp );
}





