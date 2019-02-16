/*
 * Source File < x11/palette.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

/*
 * standard functions to get and set palette
 */
struct palettetype *getdefaultpalette( void )
{
  static struct palettetype def;
  int c;
  
  def.size = XBGI->palette.size;
  for ( c=0; c<def.size; c++ )
    def.colors[c] = c;
  return &def;
}
void getpalette( struct palettetype *palette )
{
  *palette = XBGI->palette;
}
int getpalettesize( void )
{
  return XBGI->palette.size;
}
void setpalette( int colornum, int color );
void setallpalette( struct palettetype *palette )
{
  int c;

  XBGI->palette = *palette;
  for ( c=0; c<palette->size; c++ )
    setpalette( palette->colors[c], c ); 
}
void setpalette( int colornum, int color )
{
  XColor xcolor;
  unsigned short red, green, blue;
  
  switch( XBGI->gmode ){
  case X11MONO:
    XBGI->palette.size = 2;
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    color    = minmax( 0, color,    XBGI->palette.size-1 );
    XBGI->palette.colors[color] = (unsigned char)colornum;
#if 0 /* USE_COLORTABLE */
    XBGIColortable[XBGIPixels[colornum]] = color;
#endif
    XBGIPixels[color] = (colornum==0)?BlackPixel(XBGIDisplay,XBGIScreen):
      (colornum==XBGI->palette.size-1)?WhitePixel(XBGIDisplay,XBGIScreen):
	WhitePixel(XBGIDisplay,XBGIScreen);
    break;
  case X11SGRAY:
  case X11SCOLOR:
  case X11TCOLOR:
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    color    = minmax( 0, color,    XBGI->palette.size-1 );
    XBGI->palette.colors[color] = (unsigned char)colornum;
    xcolor.red   = XBGIRGB[colornum].red;
    xcolor.green = XBGIRGB[colornum].green;
    xcolor.blue  = XBGIRGB[colornum].blue;
    if ( XBGI->gerror != grNoInitGraph
	&& XBGIPixels[color] != BlackPixel(XBGIDisplay,XBGIScreen) )
      XFreeColors( XBGIDisplay, XBGIColormap, &XBGIPixels[color], 1, 0 );
    if ( XAllocColor(XBGIDisplay,XBGIColormap,&xcolor) != False )
      XBGIPixels[color] = xcolor.pixel;
    else {
      /* 1st failed */
      if ( XBGIColormap == DefaultColormap( XBGIDisplay, XBGIScreen ) ) {
	XBGIColormap = XCopyColormapAndFree( XBGIDisplay, XBGIColormap );
	/*XInstallColormap( XBGIDisplay, XBGIColormap );*/ 
	XSetWindowColormap( XBGIDisplay, XBGIRoot, XBGIColormap );
	if ( XAllocColor(XBGIDisplay,XBGIColormap,&xcolor) != False )
	  XBGIPixels[color] = xcolor.pixel;
	else {
	  XBGIPixels[color] = BlackPixel(XBGIDisplay,XBGIScreen);
	  Warning( "color allocation fault in own colormap" );
	}
      } else {
	XBGIPixels[color] = BlackPixel(XBGIDisplay,XBGIScreen);
	Warning( "color allocation fault in own colormap" );
      }
    }
#if 0 /* USE_COLORTABLE */
    XBGIColortable[XBGIPixels[color]] = color;
#endif
    break;
  case X11GRAY:
  case X11COLOR:
  case X11DCOLOR: /* ! */
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    color    = minmax( 0, color,    XBGI->palette.size-1 );
    XBGI->palette.colors[color] = (unsigned char)colornum;
    red   = XBGIRGB[colornum].red;
    green = XBGIRGB[colornum].green;
    blue  = XBGIRGB[colornum].blue;
    xcolor.pixel = XBGIPixels[color];
    xcolor.red   = red;
    xcolor.green = green;
    xcolor.blue  = blue;
    xcolor.flags = DoRed | DoGreen | DoBlue;
    XStoreColor( XBGIDisplay, XBGIColormap, &xcolor );
    XFlush( XBGIDisplay );
    break;
  }
}
void _setrgbpalette( int colornum,
                    unsigned short red,
                    unsigned short green,
                    unsigned short blue );
void setrgbpalette( int colornum, int red, int green, int blue )
{
  _setrgbpalette( colornum, 
                 minmax( 0, 65536*red  /XBGI->palette.size, 65536-1 ),
                 minmax( 0, 65536*green/XBGI->palette.size, 65536-1 ),
                 minmax( 0, 65536*blue /XBGI->palette.size, 65536-1 ) );
}
void _setrgbpalette( int colornum,
                    unsigned short red,
                    unsigned short green,
                    unsigned short blue )
{
  XColor xcolor;

  switch( XBGI->gmode ){
  case X11MONO:
    break;
  case X11SGRAY:
  case X11SCOLOR:
  case X11TCOLOR:
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    XBGIRGB[colornum].red   = red;
    XBGIRGB[colornum].green = green;
    XBGIRGB[colornum].blue  = blue;
    xcolor.red   = XBGIRGB[colornum].red;
    xcolor.green = XBGIRGB[colornum].green;
    xcolor.blue  = XBGIRGB[colornum].blue;
    if ( XBGI->gerror != grNoInitGraph
	&& XBGIPixels[colornum] != BlackPixel(XBGIDisplay,XBGIScreen) )
      XFreeColors( XBGIDisplay, XBGIColormap, &XBGIPixels[colornum], 1, 0 );
    if ( XAllocColor(XBGIDisplay,XBGIColormap,&xcolor) != False )
      XBGIPixels[colornum] = xcolor.pixel;
    else {
      /* 1st failed */
      if ( XBGIColormap == DefaultColormap( XBGIDisplay, XBGIScreen ) ) {
	XBGIColormap = XCopyColormapAndFree( XBGIDisplay, XBGIColormap );
	/*XInstallColormap( XBGIDisplay, XBGIColormap );*/ 
	XSetWindowColormap( XBGIDisplay, XBGIRoot, XBGIColormap );
	if ( XAllocColor(XBGIDisplay,XBGIColormap,&xcolor) != False )
	  XBGIPixels[colornum] = xcolor.pixel;
	else {
	  XBGIPixels[colornum] = BlackPixel(XBGIDisplay,XBGIScreen);
	  Warning( "color allocation fault in own colormap" );
	}
      } else {
	XBGIPixels[colornum] = BlackPixel(XBGIDisplay,XBGIScreen);
	Warning( "color allocation fault in own colormap" );
      }
    }
#if 0 /* USE_COLORTABLE */
    XBGIColortable[XBGIPixels[colornum]] = color;
#endif
    break;
  case X11GRAY:
  case X11COLOR:
  case X11DCOLOR: /* ! */
    colornum = minmax( 0, colornum, XBGI->palette.size-1 );
    XBGIRGB[colornum].red   = red;
    XBGIRGB[colornum].green = green;
    XBGIRGB[colornum].blue  = blue;
    xcolor.pixel = XBGIPixels[colornum];
    xcolor.red   = XBGIRGB[colornum].red;
    xcolor.green = XBGIRGB[colornum].green;
    xcolor.blue  = XBGIRGB[colornum].blue;
    xcolor.flags = DoRed | DoGreen | DoBlue;
    XStoreColor( XBGIDisplay, XBGIColormap, &xcolor );
    XFlush( XBGIDisplay );
    break;
  }
}











