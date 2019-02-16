/*
 * Source File < ps/config.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard functions for configuration of graphics environment
 */
int getmaxx( void )
{
  if ( XBGI->apage == 0 )
    return PSBGIRoot.width-1;
  else
    return PSBGIWins[XBGI->apage].width-1;
}
int getmaxy( void )
{
  if ( XBGI->apage == 0 )
    return PSBGIRoot.height-1;
  else
    return PSBGIWins[XBGI->apage].height-1;
}
/*
 * official enhanced functions for configuration of graphics environment
 */
void setmaxx( int maxx )
{
  int i;

  if ( maxx <= 0 ) return;
  if ( XBGI->apage == 0 ){
    PSBGIRoot.width = maxx+1;
    for ( i=0; i<XBGI->npage; i++ )
      PSBGIWins[i].width = maxx+1;
  }else{
    PSBGIWins[XBGI->apage].width = maxx+1;
  }
  cleardevice();
}
void setmaxy( int maxy )
{
  int i;

  if ( maxy <= 0 ) return;
  if ( XBGI->apage == 0 ){
    PSBGIRoot.height = maxy+1;
    for ( i=0; i<XBGI->npage; i++ )
      PSBGIWins[i].height = maxy+1;
  }else{
    PSBGIWins[XBGI->apage].height = maxy+1;
  }
  cleardevice();
}
void getsizexy( int *xsize, int *ysize )
{
  int width, height;

  if ( XBGI->apage == 0 ){
    width  = PSBGIRoot.width;
    height = PSBGIRoot.height;
  }else{
    width  = PSBGIWins[XBGI->apage].width;
    height = PSBGIWins[XBGI->apage].height;
  }
  *xsize = width;
  *ysize = height;
}
void setsizexy( int xsize, int ysize )
{
  int i;
  
  if ( XBGI->apage == 0 ){
    for ( i=0; i<XBGI->npage; i++ ){
      PSBGIWins[i].width  = xsize;
      PSBGIWins[i].height = ysize;
    }
    PSBGIRoot.width  = xsize;
    PSBGIRoot.height = ysize;
  }else{
    PSBGIWins[XBGI->apage].width  = xsize;
    PSBGIWins[XBGI->apage].height = ysize;
  }
  cleardevice();
}
void getgeometry( int *x, int *y, int *width, int *height )
{
  *x = PSBGIWins[XBGI->apage].x;
  *y = PSBGIWins[XBGI->apage].y;
  *width  = PSBGIWins[XBGI->apage].width;
  *height = PSBGIWins[XBGI->apage].height;
}
void setgeometry( int x, int y, int width, int height )
{
  PSBGIWins[XBGI->apage].x = x;
  PSBGIWins[XBGI->apage].y = y;
  PSBGIWins[XBGI->apage].width  = width;
  PSBGIWins[XBGI->apage].height = height;
  cleardevice();
}
void settitle( char *title )
{
  strncpy( PSBGITitle, title, min(64,strlen(title)) );
}
void seticonname( char *filename )
{
  NotSupported( "seticonname()" );
}
int seticon( char *filename )
{
  NotSupported( "seticon()" );
  return 0;
}
void setbackingstore( int flg )
{
  NotSupported( "setbackingstore()" );
}








