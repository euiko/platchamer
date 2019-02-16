/*
 * Source File < common/viewport.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions for viewport as virtual drawing device
 */
void clearviewport( void )
{
  XBGI->inherit_procedures->clearviewport();
}
void setviewport( int left, int top, int right, int bottom, int clip )
{
  XBGI->inherit_procedures->setviewport( left, top, right, bottom, clip );
}
void getviewsettings( struct viewporttype *viewport )
{
  XBGI->inherit_procedures->getviewsettings( viewport );
}





