/*
 * Source File < ps/lineinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard function for get and set line settings
 */
void getlinesettings( struct linesettingstype *lineinfo )
{
  *lineinfo = XBGI->lineset;
}
static void upattern2xlinestyle( unsigned upattern,
                                int *offset, char *usrbit, int *n )
{
  int i, j, c, ns, flg;
  unsigned long ul;

  ul = (unsigned long)upattern*0x10000 + upattern;
  ns = 0;
  while ( (!(ul&(0x80000000>>ns)))&&(ns<32) ) ns++;
  if ( ns == 32 ){
    *n = 0;
    return;
  }
  upattern = (ul<<ns)>>16;
  *offset = i = c = 0;
  flg = !0;
  while ( i < 16-ns ){
    if ( flg ){
      if ( !(upattern&(0x8000>>i)) ){
        c++;
        flg = !flg;
      }
      usrbit[c]++;
    }else{
      if ( upattern&(0x8000>>i) ){
        c++;
        flg = !flg;
      }
      usrbit[c]++;
    }
    i++;
  }
  c++;
  if ( ns > 0 ){
    if ( !flg ){
      usrbit[c] = 1; /* ? */
      c++;
    }
    usrbit[c] = ns;
    c++;
    *offset = c-1;
  }
  *n = c;
}
void setlinestyle( int linestyle, unsigned upattern, int thickness )
{
  char usrbit[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int offset = 0, n = 0;

  XBGI->lineset.linestyle = linestyle;
  XBGI->lineset.upattern  = upattern;
  XBGI->lineset.thickness = thickness;
  switch( linestyle ){
  case SOLID_LINE:
    strcpy( PSBGIDash, "[]" );
    PSBGIDashOffset = 0;
    break;
  case DOTTED_LINE:
    strcpy( PSBGIDash, "[1 3]" );
    PSBGIDashOffset = 0;
    break;
  case CENTER_LINE:
    strcpy( PSBGIDash, "[1 3 4 3]" );
    PSBGIDashOffset = 0;
    break;
  case DASHED_LINE:
    strcpy( PSBGIDash, "[7 4]" );
    PSBGIDashOffset = 0;
    break;
  case USERBIT_LINE:
    upattern2xlinestyle( upattern, &offset, usrbit, &n );
    if ( n != 0 ) {
      int i;
      char dash[64], tmp[64];

      strcpy( dash, "[" );
      for ( i=0; i<n; i++ ) {
	sprintf( tmp, "%d", (int)usrbit[i] );
	strcat( dash, tmp );
	if ( i!=n-1) strcat( dash, " " );
      }
      strcat( dash, "]" );
      strcpy( PSBGIDash, dash );
      PSBGIDashOffset = offset;
    } else {
      NotSupported( "setlinestyle( USERBIT_LINE, pattern == 0, )" );
      linestyle = SOLID_LINE;
    }
    break;
  }
#if 1 /* fine stroke since 19991225 */
  PSBGILineWidth = 1.0*thickness;
#else
  PSBGILineWidth = (thickness<=1)?0.1:1.0*thickness;
#endif
}
