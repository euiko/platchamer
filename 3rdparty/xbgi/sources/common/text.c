/*
 * Source File < common/text.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard function to out text on graphics
 */
void outtext( char *textstring )
{
  XBGI->inherit_procedures->outtext( textstring );
}
void outtextxy( int x, int y, char *textstring )
{
  XBGI->inherit_procedures->outtextxy( x, y, textstring );
}
/*
 * extented functions for high-quality graphics
 */
void _outtextxy( double x, double y, char *textstring )
{
  XBGI->inherit_procedures->_outtextxy( x, y, textstring );
}
