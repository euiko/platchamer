/*
 * Source File < common/fillinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to get and set fillsettings
 */
void getfillsettings( struct fillsettingstype *fillinfo )
{
  XBGI->inherit_procedures->getfillsettings( fillinfo );
}
void getfillpattern( char *pattern )
{
  XBGI->inherit_procedures->getfillpattern( pattern );
}
void setfillstyle( int pattern, int color )
{
  XBGI->inherit_procedures->setfillstyle( pattern, color );
}
void setfillpattern( char *upattern, int color )
{
  XBGI->inherit_procedures->setfillpattern( upattern, color );
}





