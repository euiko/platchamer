/*
 * Source File < x11/viewport.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions for viewport as virtual drawing device
 */
void clearviewport( void )
{
  if ( XBGI->viewport.clip )
    XClearArea( XBGIDisplay, XBGIWins[XBGI->apage],
               XBGI->viewport.left, XBGI->viewport.top, 
               XBGI->viewport.right - XBGI->viewport.left + 1,
               XBGI->viewport.bottom - XBGI->viewport.top + 1, False );
  else
    cleardevice();
}
void setviewport( int left, int top, int right, int bottom, int clip )
{
  XRectangle rec;

  XBGI->viewport.left   = min( left, right );
  XBGI->viewport.top    = min( top, bottom );
  XBGI->viewport.right  = max( left, right );
  XBGI->viewport.bottom = max( top, bottom );
  XBGI->viewport.clip   = clip;
  if ( XBGI->viewport.clip ){
    rec.x = XBGI->viewport.left;
    rec.y = XBGI->viewport.top;
    rec.width  = XBGI->viewport.right - XBGI->viewport.left + 1;
    rec.height = XBGI->viewport.bottom - XBGI->viewport.top + 1;
    XSetClipRectangles( XBGIDisplay, XBGIDrawGC,  0, 0, &rec, 1, YXSorted );
    XSetClipRectangles( XBGIDisplay, XBGIFillGC,  0, 0, &rec, 1, YXSorted );
    XSetClipRectangles( XBGIDisplay, XBGIPixelGC, 0, 0, &rec, 1, YXSorted );
    XSetClipRectangles( XBGIDisplay, XBGIImageGC, 0, 0, &rec, 1, YXSorted );
  }else{
    XSetClipMask( XBGIDisplay, XBGIDrawGC,  None );
    XSetClipMask( XBGIDisplay, XBGIFillGC,  None );
    XSetClipMask( XBGIDisplay, XBGIPixelGC, None );
    XSetClipMask( XBGIDisplay, XBGIImageGC, None );
  }
}
void getviewsettings( struct viewporttype *viewport )
{
  *viewport = XBGI->viewport;
}











