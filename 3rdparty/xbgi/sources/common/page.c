/*
 * Source File < common/page.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions for page as drawing device
 */
void cleardevice( void )
{
  XBGI->inherit_procedures->cleardevice();
}
void setactivepage( int page )
{
  XBGI->inherit_procedures->setactivepage( page );
}
void setvisualpage( int page )
{
  XBGI->inherit_procedures->setvisualpage( page );
}
void restorecrtmode( void )
{
  XBGI->inherit_procedures->restorecrtmode();
}





