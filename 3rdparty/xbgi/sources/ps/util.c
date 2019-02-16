/*
 * Source File < ps/util.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * official enhanced function to save to x bitmap file
 */
int savemonographtofile( char *filename, char *option )
{
  NotSupported( "savemonographtofile()" );
  return 0;
}
/*
 * official enhanced function to save to x pixmap file
 */
int savegraphtofile( char *filename, char *option )
{
  NotSupported( "savegraphtofile()" );
  return 0;
}
/*
 * official enhanced function to save drawing procedure by postscript
 */
int saveexposetofile( char *filename, char *option )
{
  int status = 0;

  NotSupported( "saveexposetofile() is not supported in PS" );
  return status;
}
