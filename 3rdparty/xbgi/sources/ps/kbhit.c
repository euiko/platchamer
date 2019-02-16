/*
 * Source File < kbhit.c >
 *
 * Standard Functions of Console I/O: on BGI for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

int kbhit( void )
{
  int c;

  fprintf( stderr, "kbhit[y/n]> " );
  fflush( stderr );
  c = getc( stdin );
  return c=='y';
}











