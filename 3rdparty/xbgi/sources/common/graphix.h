/*
 * Header File < common/graphix.h >
 *
 * Enhanced Functions: Borland Graphics Interface for Multi-devices
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _GRAPHIX_H_
#define _GRAPHIX_H_

#include <stdarg.h>
#include "coniox.h"
#include "graphics.h"

#ifndef NeedFunctionPrototypes
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define NeedFunctionPrototypes 1
#  else
#    define NeedFunctionPrototypes 0
#  endif
#endif

#ifndef __P
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define __P(p) p
#  else
#    define __P(p)
#  endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef struct _xbgi_procedures {
/* event.c ------------------------ event looper for simple event programing */
  /* common procedures
  void set_button_press_handler( int (*handler)(int button,int x,int y) );
  void set_button_release_handler( int (*handler)(int button,int x,int y) );
  void set_mouse_motion_handler( int (*handler)(int button,int x,int y) );
  void set_page_enter_handler( int (*handler)(int page) );
  void set_page_leave_handler( int (*handler)(int page) );
  void set_key_press_handler( int (*handler)(int key) );
  void set_configure_handler( int (*handler)(void) );
  void set_expose_handler( int (*handler)(void) );
  void set_noevent_handler( int (*handler)(void) );*/
  /* inheritable and programable procedures */
  int (*button_press_handler)__P(( int button, int x, int y ));
  int (*button_release_handler)__P(( int button, int x, int y ));
  int (*mouse_motion_handler)__P(( int button_state, int x, int y ));
  int (*page_enter_handler)__P(( int page ));
  int (*page_leave_handler)__P(( int page ));
  int (*key_press_handler)__P(( int key ));
  int (*configure_handler)__P(( void ));
  int (*expose_handler)__P(( void ));
  int (*noevent_handler)__P(( void ));
  /* inheritable procedures */
  void (*xbgiloop)__P(( void ));
  int (*isevent)__P(( void ));
/* request.c ------------------------------------------------- request flush */
  /* inheritable procedures */
  void (*xflush)__P(( void ));
  void (*xsync)__P(( void ));
/* config.c -------------------------- configuration of graphics environment */
  /* inheritable procedures */
  int (*getmaxx)__P(( void ));
  int (*getmaxy)__P(( void ));
  void (*setmaxx)__P(( int maxx ));
  void (*setmaxy)__P(( int maxy ));
  void (*getsizexy)__P(( int *xsize, int *ysize ));
  void (*setsizexy)__P(( int xsize, int ysize ));
  void (*getgeometry)__P(( int *x, int *y, int *width, int *height ));
  void (*setgeometry)__P(( int x, int y, int width, int height ));
  void (*settitle)__P(( char *title ));
  void (*seticonname)__P(( char *filename ));
  int (*seticon)__P(( char *filename ));
  void (*setbackingstore)__P(( int flg ));
/* driver.c --------------------------------------- graphics driver and mode */
  /* common procedures
  char *getdriversname( int driver_number );
  int getdrivernumber( char *driver_name );
  int getmodenumber( char *mode_name );
  char *getdrivername( void );
  int getgraphmode( void );
  void setgraphmode( int gmode );
  char *getmodename( int mode_number );
  int getmaxmode( void );
  void getmoderange( int graphdriver, int *lomode, int *himode );
  unsigned setgraphbufsize( unsigned bufsize );
  void _graphfreemem( void *ptr, unsigned size );
  void *_graphgetmem( unsigned size );
  int installuserdriver( char *name, int (*detect)( void ) );
  int registerbgidriver( void (*driver)( void ) );
  int registerfarbgidriver( void *driver );*/
  /* inheritable procedures */
  void (*detectgraph)__P(( int *graphdriver, int *graphmode ));
  void (*_driver)__P(( void ));
  void (*driver)__P(( void ));
/* init.c ------------------------------ initialize and close graphic system */
  /* common procedures
  void _initgraph( int argc, char *argv[], char *pd );
  void initgraph( int *graphdriver, int *graphmode, char *pathtodriver );
  void graphdefaults( void );
  void closegraph( void );*/
/* id.c -------------------------------- multi-graphic system using graph id */
  /* common procedures
  int graphnumber( void );
  void selectgraph( int id );
  void termgraph( int id );*/
/* util.c ------------------------------------ utilities for X-Window system */
  /* inheritable procedures */
  int (*savemonographtofile)__P(( char *filename, char *option ));
  int (*savegraphtofile)__P(( char *filename, char *option ));
  int (*saveexposetofile)__P(( char *filename, char *option ));
/* error.c ------------------------------------------------- error messenger */
  /* inheritable procedures */
  int (*graphresult)__P(( void ));
  char *(*grapherrormsg)__P(( int errorcode ));
/* page.c ------------------------------------------- page as drawing device */
  /* inheritable procedures */
  void (*cleardevice)__P(( void ));
  void (*setactivepage)__P(( int page ));
  void (*setvisualpage)__P(( int page ));
  void (*restorecrtmode)__P(( void ));
/* viewport.c --------------------------- viewport as virtual drawing device */
  /* inheritable procedures */
  void (*clearviewport)__P(( void ));
  void (*setviewport)__P((int left,int top,int right,int bottom,int clip));
  void (*getviewsettings)__P(( struct viewporttype *viewport ));
/* lineinfo.c ------------------------------------------------ line settings */
  /* inheritable procedures */
  void (*getlinesettings)__P(( struct linesettingstype *lineinfo ));
  void (*setlinestyle)__P(( int linestyle, unsigned upattern, int thickness ));
/* writeops.c ------------------------------------------ set write operation */
  /* inheritable procedures */
  void (*setwritemode)__P(( int op ));
/* move.c ---------------------------------------------------- current point */
  /* inheritable procedures */
  int (*getx)__P(( void ));
  int (*gety)__P(( void ));
  void (*moverel)__P(( int dx, int dy ));
  void (*moveto)__P(( int x, int y ));
  double (*_getx)__P(( void ));
  double (*_gety)__P(( void ));
  void (*_moverel)__P(( double dx, double dy ));
  void (*_moveto)__P(( double x, double y ));
/* line.c ----------------------------------------------------- drawing line */
  /* inheritable procedures */
  void (*lines)__P(( int numpoints, int *points ));
  void (*line)__P(( int x1, int y1, int x2, int y2 ));
  void (*linerel)__P(( int dx, int dy ));
  void (*lineto)__P(( int x, int y ));
  void (*_lines)__P(( int numpoints, double *points ));
  void (*_line)__P(( double x1, double y1, double x2, double y2 ));
  void (*_linerel)__P(( double dx, double dy ));
  void (*_lineto)__P(( double x, double y ));
/* rect.c ------------------------------------------------ drawing rectangle */
  /* inheritable procedures */
  void (*rectangle)__P(( int left, int top, int right, int bottom ));
  void (*_rectangle)__P(( double left, double top, double right, double bottom ));
/* poly.c -------------------------------------------------- drawing polygon */
  /* inheritable procedures */
  void (*drawpoly)__P(( int numpoints, int *polypoints ));
  void (*_drawpoly)__P(( int numpoints, double *polypoints ));
/* arcinfo.c -------------------------------------------------- arc settings */
  /* inheritable procedures */
  void (*getarccoords)__P(( struct arccoordstype *arccoords ));
  void (*getaspectratio)__P(( int *xasp, int *yasp ));
  void (*setaspectratio)__P(( int xasp, int yasp ));
/* arc.c ------------------------------------------------------- drawing arc */
  /* inheritable procedures */
  void (*arc)__P(( int x, int y, int stangle, int endangle, int radius ));
  void (*circle)__P(( int x, int y, int radius ));
  void (*ellipse)__P(( int x, int y, int stangle, int endangle,
                      int xradius, int yradius ));
  void (*_arc)__P(( double x, double y, double stangle, double endangle,
                   double radius ));
  void (*_circle)__P(( double x, double y, double radius ));
  void (*_ellipse)__P(( double x, double y, double stangle, double endangle,
	        double xradius, double yradius ));
/* fillinfo.c ------------------------------------------------ fill settings */
  /* inheritable procedures */
  void (*getfillsettings)__P(( struct fillsettingstype *fillinfo ));
  void (*getfillpattern)__P(( char *pattern ));
  void (*setfillstyle)__P(( int pattern, int color ));
  void (*setfillpattern)__P(( char *upattern, int color ));
/* fillrect.c -------------------------------------------- filling rectangle */
  /* inheritable procedures */
  void (*bar)__P(( int left, int top, int right, int bottom ));
  void (*bar3d)__P(( int left, int top, int right, int bottom,
                    int depth, int topflag ));
  void (*_bar)__P(( double left, double top, double right, double bottom ));
  void (*_bar3d)__P(( double left, double top, double right, double bottom,
	             double depth, int topflag ));
/* fillpoly.c ---------------------------------------------- filling polygon */
  /* inheritable procedures */
  void (*fillpoly)__P(( int numpoints, int *polypoints ));
  void (*_fillpoly)__P(( int numpoints, double *polypoints ));
/* fillarc.c --------------------------------------------------- filling arc */
  /* inheritable procedures */
  void (*fillellipse)__P(( int x, int y, int xradius, int yradius ));
  void (*pieslice)__P(( int x, int y, int stangle, int endangle, int radius ));
  void (*sector)__P(( int x, int y, int stangle, int endangle,
                     int xradius, int yradius ));
  void (*_fillellipse)__P(( double x, double y, double xradius, double yradius ));
  void (*_pieslice)__P(( double x, double y, double stangle, double endangle,
                 double radius ));
  void (*_sector)__P(( double x, double y, double stangle, double endangle,
	       double xradius, double yradius ));
/* flood.c --------------------------------------------------- filling flood */
  /* inheritable procedures */
  void (*floodfill)__P(( int x, int y, int border ));
  void (*_floodfill)__P(( double x, double y, int border ));
/* pixel.c ----------------------------------------------------------- pixel */
  /* inheritable procedures */
  void (*putpixels)__P(( int numpoints, int *points, int color ));
  unsigned (*getpixel)__P(( int x, int y ));
  void (*putpixel)__P(( int x, int y, int color ));
  void (*_putpixels)__P(( int numpoints, double *points, int color ));
  unsigned (*_getpixel)__P(( double x, double y ));
  void (*_putpixel)__P(( double x, double y, int color ));
/* image.c ----------------------------------------------------------- image */
  /* inheritable procedures */
  unsigned (*imagesize)__P(( int left, int top, int right, int bottom ));
  void (*getimage)__P(( int left,int top,int right,int bottom,void *bitmap ));
  void (*putimage)__P(( int left, int top, void *bitmap, int op ));
  void (*_getimage)__P(( double left, double top, double right, double bottom,
                        void *bitmap ));
  void (*_putimage)__P(( double left, double top, void *bitmap, int op ));
/* point.c ----------------------------------------------------------- point */
  /* inheritable procedures */
  void (*putpoints)__P(( int numpoints, int *points ));
  void (*getpointsettings)__P(( struct pointsettingstype *pointinfo ));
  void (*setpointstyle)__P(( int type, int color, int fillcolor, int size ));
  void (*putpoint)__P(( int x, int y ));
  void (*_putpoints)__P(( int numpoints, double *points ));
  void (*_putpoint)__P(( double x, double y ));
/* textinfo.c ------------------------------------------------ text settings */
  /* inheritable procedures */
  int (*textheight)__P(( char *textstring ));
  int (*textwidth)__P(( char *textstring ));
  void (*gettextsettings)__P(( struct textsettingstype *texttypeinfo ));
  void (*settextstyle)__P(( int font, int direction, int charsize ));
  void (*settextjustify)__P(( int horiz, int vert ));
  void (*setusercharsize)__P(( int multx, int divx, int multy, int divy ));
  int (*installuserfont)__P(( char *name ));
  int (*registerbgifont)__P(( void (*font)(void) ));
  int (*registerfarbgifont)__P(( void *font ));
/* text.c --------------------------------------------- out text on graphics */
  /* inheritable procedures */
  void (*outtext)__P(( char *textstring ));
  void (*outtextxy)__P(( int x, int y, char *textstring ));
  void (*_outtextxy)__P(( double x, double y, char *textstring ));
/* color.c ----------------------------------------------- get and set color */
  /* inheritable procedures */
  int (*getcolor)__P(( void ));
  int (*getbkcolor)__P(( void ));
  int (*getmaxcolor)__P(( void ));
  void (*setcolor)__P(( int color ));
  void (*setbkcolor)__P(( int color ));
  void (*setmaxcolor)__P(( int c ));
/* palette.c -------------------------------- get and set palette and colors */
  /* inheritable procedures */
  struct palettetype *(*getdefaultpalette)__P(( void ));
  void (*getpalette)__P(( struct palettetype *palette ));
  int (*getpalettesize)__P(( void ));
  void (*setallpalette)__P(( struct palettetype *palette ));
  void (*setpalette)__P(( int colornum, int color ));
  void (*setrgbpalette)__P(( int colornum, int red, int green, int blue ));
  void (*_setrgbpalette)__P(( int colornum,
                      unsigned short red,
                      unsigned short green,
                      unsigned short blue ));
/* bgiutl.c ----------------------------------- meta-level procedures of bgi */
  /* inheritable procedures */
  void (*bgivprintf)__P((char *title,int textjust,char *fmt,va_list argptr));
  void (*bgiprintf)__P(( char *title, int textjust, char *fmt, ... ));
  void (*bgigets)__P(( char *title, int maxlen, char *str ));
  void (*bgimenu)__P(( char *title, int menuc, char *menuv[], int *menui ));
/* kbhit.c ------------------------------------------ get keyboard hit state */
  /* inheritable procedures */
  int (*kbhit)__P(( void ));
/* getch.c ---------------------------------------------- key pressed return */
  /* inheritable procedures */
  int (*getch)__P(( void ));
/* conio.c ---------------------------------------------- console procedures */
  /* all common procedures, reserved future */
/* ------------------------------------------------------------------------- */
} xbgi_procedures;

typedef struct _xbgi {
  int argc;
  char **argv;
  int id;
  int l10n;
  int colornames;
  int gdriver, gmode, gerror;
  int npage, apage, vpage;
  int ncolor, color, bkcolor;
  struct _pointtype cp;
  struct viewporttype viewport;
  struct linesettingstype lineset;
  struct textsettingstype textset;
  struct fillsettingstype fillset;
  struct palettetype palette;
  struct arcsettingstype arcset;
  struct pointsettingstype pointset;
  void *inherit_members;
  xbgi_procedures *inherit_procedures;
  struct _xbgi *next;
} xbgi;

extern xbgi *_creategraph(
#if NeedFunctionPrototypes
  int __argc, char *__argv[], char *__pd
#endif
);

extern xbgi *creategraph(
#if NeedFunctionPrototypes
  int *__graphdriver, int *__graphmode, char *__pathtodriver
#endif
);

extern xbgi *thisgraph(
#if NeedFunctionPrototypes
  void
#endif
);

extern void destroygraph(
#if NeedFunctionPrototypes
  xbgi *__this
#endif
);

extern void currentgraph(
#if NeedFunctionPrototypes
  xbgi *__this
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GRAPHIX_H_ */

