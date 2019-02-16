/*
 * Source File < common/kbhit.c >
 *
 * Standard Functions of Console I/O: on BGI for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

int kbhit( void )
{
  return XBGI->inherit_procedures->kbhit();
}




