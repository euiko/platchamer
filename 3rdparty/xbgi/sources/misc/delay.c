/*
 * Source File < delay.c >
 *
 * Standard Functions of DOS.H: Borland C/C++ compiler
 *
 * Copyright (c) 1992-94 Tokyo Denki University, Taiji Yamada
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include "dos.h"

void delay( unsigned long ms )
{
  unsigned long us = ms*1000;
  struct timeval tval;

  tval.tv_sec  = us/1000000L;
  tval.tv_usec = us%1000000L;
  select( 0, NULL, NULL, NULL, &tval );
}
