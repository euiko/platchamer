/*
 * Source File < common/textinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard functions to get and set text settings
 */
int textheight( char *textstring )
{
  return XBGI->inherit_procedures->textheight( textstring );
}
int textwidth( char *textstring )
{
  return XBGI->inherit_procedures->textwidth( textstring );
}
void gettextsettings( struct textsettingstype *texttypeinfo )
{
  return XBGI->inherit_procedures->gettextsettings( texttypeinfo );
}
void settextstyle( int font, int direction, int charsize )
{
  XBGI->inherit_procedures->settextstyle( font, direction, charsize );
}
void settextjustify( int horiz, int vert )
{
  XBGI->inherit_procedures->settextjustify( horiz, vert );
}
void setusercharsize( int multx, int divx, int multy, int divy )
{
  XBGI->inherit_procedures->setusercharsize( multx, divx, multy, divy );
}
int installuserfont( char *name )
{
  return XBGI->inherit_procedures->installuserfont( name );
}
int registerbgifont( void (*font)(void) )
{
  return XBGI->inherit_procedures->registerbgifont( font );
}
int registerfarbgifont( void *font )
{
  return XBGI->inherit_procedures->registerfarbgifont( font );
}





