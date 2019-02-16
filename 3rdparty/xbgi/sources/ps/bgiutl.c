/*
 * Source File < ps/bgiutl.c >
 *
 * BGI Utilities Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

void bgivprintf( char *title, int textjust, char *fmt, va_list argptr )
{
}
void bgiprintf( char *title, int textjust, char *fmt, ... )
{
  va_list argptr;
  
  va_start( argptr, fmt );
  /* */
  va_end( argptr );
}
void bgigets( char *title, int maxlen, char *str )
{
}
void bgimenu( char *title, int menuc, char *menuv[], int *menui )
{
}






