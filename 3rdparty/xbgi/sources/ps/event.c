/*
 * Source File < ps/event.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * event looper for simple event programing
 */
void xbgiloop( void )
{
  Notice( "in xbgiloop()" );
  fprintf( stderr, "xbgiloop> " );
  fflush( stderr );
}
/*
 * is event
 */
int isevent( void )
{
  int c;

  fprintf( stderr, "isevent[y/n]> " );
  fflush( stderr );
  c = getc( stdin );
  return c=='y';
}







