/*
 * Source File < common/color.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to get and set color
 */
int getcolor( void )
{
  return XBGI->inherit_procedures->getcolor();
}
int getbkcolor( void )
{
  return XBGI->inherit_procedures->getbkcolor();
}
int getmaxcolor( void )
{
  return XBGI->inherit_procedures->getmaxcolor();
}
void setcolor( int color )
{
  XBGI->inherit_procedures->setcolor( color );
}
void setbkcolor( int color )
{
  XBGI->inherit_procedures->setbkcolor( color );
}
void setmaxcolor( int c )
{
  XBGI->inherit_procedures->setmaxcolor( c );
}





