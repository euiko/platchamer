/*
 * Source File < ps/getch.c >
 *
 * Standard Functions of Console I/O: on BGI for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

int getch( void )
{
  fprintf( stderr, "getch> " );
  fflush( stderr );
  return getc( stdin );
}











