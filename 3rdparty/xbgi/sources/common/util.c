/*
 * Source File < common/util.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced function to save to x bitmap file
 */
int savemonographtofile( char *filename, char *option )
{
  return XBGI->inherit_procedures->savemonographtofile( filename, option );
}
int (savegraphtoxbm)( char *filename ) /* for compatibility */
{
  return savegraphtoxbm( filename );
}
/*
 * official enhanced function to save to x pixmap file
 */
int savegraphtofile( char *filename, char *option )
{
  return XBGI->inherit_procedures->savegraphtofile( filename, option );
}
int (savegraphtoxpm)( char *filename ) /* for compatibility */
{
  return savegraphtoxpm( filename );
}
/*
 * official enhanced function to save drawing procedure by postscript
 */
int saveexposetofile( char *filename, char *option )
{
  return XBGI->inherit_procedures->saveexposetofile( filename, option );
}
int (saveexposetops)( char *filename, char *option ) /* for compatibility */
{
  return saveexposetops( filename, option );
}
