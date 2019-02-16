/*
 * Source File < x11/misc.c >
 *
 * Misc Functions for X11: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"
#ifdef ENABLE_XPMLIB
#  include <X11/xpm.h>
#endif

int XSetIconFromPixmap( Display *d, Window r,
                       Pixmap pm, unsigned int w, unsigned int h )
{
  int i, j, n;
  XIconSize *is;
  int status;
  Bool wok = False, hok = False;
  XWMHints wmh;
  
  status = XGetIconSizes( d, r, &is, &n );
  if ( status == 0 ) return 0;
  for ( i=0; i<n; i++ ){
    for ( j=is[i].min_width; j<=is[i].max_width; j+=is[i].width_inc )
      if ( w == j ){
        wok = True;
        break;
      }
    for ( j=is[i].min_height; j<=is[i].max_height; j+=is[i].height_inc )
      if ( h == j ){
        hok = True;
        break;
      }
  }
  if ( wok && hok ){
    wmh.flags = IconPixmapHint;
    wmh.icon_pixmap = pm;
    XSetWMHints( d, r, &wmh );
    return !0;
  }else{
    return 0;
  }
}

void bgipoints2XPoints( int n, int polypoints[], XPoint *xpoints )
{
  int i;

  for ( i=0; i<n; i++ ){
    xpoints->x = Xx( *polypoints++ );
    xpoints->y = Xy( *polypoints++ );
    xpoints++;
  }
}

void _bgipoints2XPoints( int n, double polypoints[], XPoint *xpoints )
{
  int i;

  for ( i=0; i<n; i++ ){
    xpoints->x = Xx( *polypoints++ );
    xpoints->y = Xy( *polypoints++ );
    xpoints++;
  }
}
