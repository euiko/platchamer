/*
 * Source File < common/id.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced functions for multi-graphic system using graph id
 */
int graphnumber( void )
{
  return XBGI->id;
}
void selectgraph( int id )
{
  xbgi *ptr = XBGIS;

  while ( ptr != NULL ){
    if ( ptr->id == id ){
      XBGI = ptr;
      return;
    }
    ptr = ptr->next;
  }
}
void termgraph( int id )
{
  xbgi *ptr = XBGIS;

  while ( ptr != NULL ){
    if ( ptr->id == id ){
      destroygraph( ptr );
      return;
    }
    ptr = ptr->next;
  }
}





