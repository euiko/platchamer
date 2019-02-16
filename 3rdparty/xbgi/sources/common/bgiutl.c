/*
 * Source File < common/bgiutl.c >
 *
 * BGI Utilities Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

void bgivprintf( char *title, int textjust, char *fmt, va_list argptr )
{
  XBGI->inherit_procedures->bgivprintf( title, textjust, fmt, argptr );
}
void bgiprintf( char *title, int textjust, char *fmt, ... )
{
  va_list argptr;
  
  va_start( argptr, fmt );
  XBGI->inherit_procedures->bgivprintf( title, textjust, fmt, argptr );
  va_end( argptr );
}
void bgigets( char *title, int maxlen, char *str )
{
  XBGI->inherit_procedures->bgigets( title, maxlen, str );
}
void bgimenu( char *title, int menuc, char *menuv[], int *menui )
{
  XBGI->inherit_procedures->bgimenu( title, menuc, menuv, menui );
}





