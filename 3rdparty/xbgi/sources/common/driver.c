/*
 * Source File < common/driver.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"
#include "option.h"

static char *graphics_drivers_name[MAXGRAPHICSDRIVER+1] = {
  "DETECT",
  "X11",
  "PS",
  "PIX",
  "VIX",
};
static char *graphics_mode_name[MAXGRAPHICSDRIVER+1][MAXGRAPHICSMODE+1] = {
  { "",        "",         "",        "",          "",         "",          ""          },
  { "X11MONO", "X11SGRAY", "X11GRAY", "X11SCOLOR", "X11COLOR", "X11TCOLOR", "X11DCOLOR" },
  { "PSMONO",  "PSGRAY",   "",        "",          "",         "PSCOLOR",   ""          },
  { "PIXMONO", "PIXSGRAY", "PIXGRAY", "PIXSCOLOR", "PIXCOLOR", "PIXTCOLOR", "PIXDCOLOR" },
  { "VIXMONO", "VIXGRAY",  "",        "",          "",         "VIXCOLOR",  ""          }
};

/*
 * registered enhanced function for graphics driver and mode
 */
char *getdriversname( int driver_number )
{
  switch( driver_number ){
  case DETECT:
  case X11:
  case PS:
  case PIX:
  case VIX:
    return graphics_drivers_name[driver_number];
  }
  return NULL;
}
int getdrivernumber( char *driver_name )
{
  int i;

  if ( driver_name == NULL )
    return DETECT;
  for ( i=X11; i<=MAXGRAPHICSDRIVER; i++ )
    if ( strcmp(graphics_drivers_name[i],driver_name)==0 )
      return i;
  return DETECT;
}
int getmodenumber( char *mode_name )
{
  int i = (XBGI!=NULL)?(XBGI->gdriver):X11, j;

  if ( mode_name == NULL )
    return -1;
  for ( j=X11MONO; j<=MAXGRAPHICSMODE; j++ )
    if ( strcmp(graphics_mode_name[minmax(X11,i,MAXGRAPHICSDRIVER)][j],mode_name)==0 )
      return j;
  return -1;
}
/*
 * standard functions for graphics driver and mode
 */
char *getdrivername( void )
{
  return getdriversname( XBGI->gdriver );
}
int getgraphmode( void )
{
  return XBGI->gmode;
}
void setgraphmode( int gmode )
{
  XBGI->gmode = gmode;
  switch( XBGI->gmode ){
  case X11MONO:
    setmaxcolor( (XBGI->palette.size=XBGI->ncolor=2)-1 );
    break;
  case X11SGRAY:
  case X11GRAY:
  case X11SCOLOR:
  case X11COLOR:
  case X11TCOLOR:
  case X11DCOLOR:
    setmaxcolor( (XBGI->palette.size=XBGI->ncolor)-1 );
    break;
  }
}
char *getmodename( int mode_number )
{
  int i = (XBGI!=NULL)?(XBGI->gdriver):X11;

  if ( X11MONO <= mode_number && mode_number <= MAXGRAPHICSMODE )
    return graphics_mode_name[minmax(X11,i,MAXGRAPHICSDRIVER)][mode_number];
  return NULL;
}
int getmaxmode( void )
{
  return X11DCOLOR;
}
void getmoderange( int graphdriver, int *lomode, int *himode )
{
  NotSupported( "getmoderange()" );
}
unsigned setgraphbufsize( unsigned bufsize )
{
  NotSupported( "setgraphbufsize()" );
  return 0;
}
void _graphfreemem( void *ptr, unsigned size )
{
  NotSupported( "_graphfreemem()" );
}
void *_graphgetmem( unsigned size )
{
  NotSupported( "_graphgetmem()" );
  return NULL;
}
int installuserdriver( char *name, int (*detect)( void ) )
{
  ReservedFuture( "installuserdriver()" );
  return 0;
}
int registerbgidriver( void (*driver)( void ) )
{
  XBGI_CURRENT_DRIVER = driver;
  return grOk;
}
int registerfarbgidriver( void *driver )
{
  XBGI_CURRENT_DRIVER = driver;
  return grOk;
}
void detectgraph( int *graphdriver, int *graphmode )
{
  /*
   * case of detecting before initgraph, always X11 and X11COLOR
   */
  if ( XBGIS == NULL || XBGI->inherit_members == NULL ){
    *graphdriver = X11;
    *graphmode   = X11COLOR;
    return;
  }
  XBGI->inherit_procedures->detectgraph( graphdriver, graphmode );
}





