/*
 * Source File < common/writeops.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * standard function to set write operation
 */
void setwritemode( int op )
{
  XBGI->inherit_procedures->setwritemode( op );
}





