/*
 * Source File < common/lineinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard function for get and set line settings
 */
void getlinesettings( struct linesettingstype *lineinfo )
{
  XBGI->inherit_procedures->getlinesettings( lineinfo );
}
void setlinestyle( int linestyle, unsigned upattern, int thickness )
{
  XBGI->inherit_procedures->setlinestyle( linestyle, upattern, thickness );
}





