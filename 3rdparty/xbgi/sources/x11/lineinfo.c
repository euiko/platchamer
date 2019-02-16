/*
 * Source File < x11/lineinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

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
  int i, c, ns, flg;
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
  static char dotted[] = { 1, 3 };
  static char center[] = { 1, 3, 4, 3 };
  static char dashed[] = { 7, 4 };
  char usrbit[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int offset = 0, n = 0;

  XBGI->lineset.linestyle = linestyle;
  XBGI->lineset.upattern  = upattern;
  XBGI->lineset.thickness = thickness;
  switch( linestyle ){
  case SOLID_LINE:
    break;
  case DOTTED_LINE:
    XSetDashes( XBGIDisplay, XBGIDrawGC, 0, dotted, 2 );
    break;
  case CENTER_LINE:
    XSetDashes( XBGIDisplay, XBGIDrawGC, 0, center, 4 );
    break;
  case DASHED_LINE:
    XSetDashes( XBGIDisplay, XBGIDrawGC, 0, dashed, 2 );
    break;
  case USERBIT_LINE:
    upattern2xlinestyle( upattern, &offset, usrbit, &n );
    if ( n != 0 )
      XSetDashes( XBGIDisplay, XBGIDrawGC, offset, usrbit, n );
    else{
      NotSupported( "setlinestyle( USERBIT_LINE, pattern == 0, )" );
      linestyle = SOLID_LINE;
    }
    break;
  }
  XSetLineAttributes( XBGIDisplay, XBGIDrawGC, thickness,
                     ((linestyle==SOLID_LINE)?LineSolid:LineOnOffDash),
                     CapButt, JoinBevel );
}








