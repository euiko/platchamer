/*
 * Source File < common/init.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"

/*
 * official enhanced function to initialize graphic system
 */
void _initgraph( int argc, char *argv[], char *pd )
{
  _creategraph( argc, argv, pd );
}
/*
 * standard functions to initialize and close graphic system
 */
void initgraph( int *graphdriver, int *graphmode, char *pathtodriver )
{
  creategraph( graphdriver, graphmode, pathtodriver );
}
void graphdefaults( void )
{
  int i;
  int x, y, width, height;
  struct arcsettingstype arcset = { 0, 0, 0, 360, 100, 100 };

  XBGI->arcset = arcset;
  for ( i=0; i<XBGI->npage; i++ ){
    setactivepage( i );
    getgeometry( &x, &y, &width, &height );
    setviewport( 0, 0, width-1, height-1, 0 ); 
    setcolor( XBGI->color );
    setbkcolor( XBGI->bkcolor );
    cleardevice();
  }
#if 0 /* unknown bugs */
  setvisualpage( XBGI->vpage );
  setactivepage( XBGI->apage );
#else
  setvisualpage( 0 );
  setactivepage( 0 );
#endif
  setlinestyle( SOLID_LINE, 0, NORM_WIDTH );
  settextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  settextjustify( LEFT_TEXT, TOP_TEXT );
  setfillstyle( SOLID_FILL, WHITE );
  setpointstyle( LOZENGE_POINT, WHITE, WHITE, 6 );
  moveto( 0, 0 );
}
void closegraph( void )
{
  destroygraph( XBGI );
}








