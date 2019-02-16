/*
 * Private Include File < ps/ps_p.h >
 *
 * Macros and Definitions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _PS_P_H_
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include "dos.h"
#include "coniox.h"
#include "conio.h"
#include "graphix.h"
#include "graphics.h"
#include "ps.h"
#include "bgiutl.h"
#include "misc.h"
#ifdef ENABLE_BILINGUAL
#  include "japanese.h"
#endif

/*
 * macros to inherit
 */
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
  #define xbgi_button_press ps_xbgi_button_press
  #define xbgi_button_release ps_xbgi_button_release
  #define xbgi_mouse_motion ps_xbgi_mouse_motion
  #define xbgi_page_enter ps_xbgi_page_enter
  #define xbgi_page_leave ps_xbgi_page_leave
  #define xbgi_key_press ps_xbgi_key_press
  #define xbgi_configure ps_xbgi_configure
  #define xbgi_expose ps_xbgi_expose
  #define xbgi_noevent ps_xbgi_noevent
  #define xbgiloop ps_xbgiloop
  #define isevent ps_isevent
/* request.c ------------------------------------------------- request flush */
  /* inheritable procedures */
  #define xflush ps_xflush
  #define xsync ps_xsync
/* config.c -------------------------- configuration of graphics environment */
  /* inheritable procedures */
  #define getmaxx ps_getmaxx
  #define getmaxy ps_getmaxy
  #define setmaxx ps_setmaxx
  #define setmaxy ps_setmaxy
  #define getsizexy ps_getsizexy
  #define setsizexy ps_setsizexy
  #define getgeometry ps_getgeometry
  #define setgeometry ps_setgeometry
  #define settitle ps_settitle
  #define seticonname ps_seticonname
  #define seticon ps_seticon
  #define setbackingstore ps_setbackingstore
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
  #define detectgraph ps_detectgraph
  /* inheritable and programable procedures */
  #define _driver ps__driver
  #define driver ps_driver
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
  #define savemonographtofile ps_savemonographtofile
  #define savegraphtofile ps_savegraphtofile
  #define saveexposetofile ps_saveexposetofile
/* error.c ------------------------------------------------- error messenger */
  /* inheritable procedures */
  #define graphresult ps_graphresult
  #define grapherrormsg ps_grapherrormsg
/* page.c ------------------------------------------- page as drawing device */
  /* inheritable procedures */
  #define cleardevice ps_cleardevice
  #define setactivepage ps_setactivepage
  #define setvisualpage ps_setvisualpage
  #define restorecrtmode ps_restorecrtmode
/* viewport.c --------------------------- viewport as virtual drawing device */
  /* inheritable procedures */
  #define clearviewport ps_clearviewport
  #define setviewport ps_setviewport
  #define getviewsettings ps_getviewsettings
/* lineinfo.c ------------------------------------------------ line settings */
  /* inheritable procedures */
  #define getlinesettings ps_getlinesettings
  #define setlinestyle ps_setlinestyle
/* writeops.c ------------------------------------------ set write operation */
  /* inheritable procedures */
  #define setwritemode ps_setwritemode
/* move.c ---------------------------------------------------- current point */
  /* inheritable procedures */
  #define getx ps_getx
  #define gety ps_gety
  #define moverel ps_moverel
  #define moveto ps_moveto
  #define _getx ps__getx
  #define _gety ps__gety
  #define _moverel ps__moverel
  #define _moveto ps__moveto
/* line.c ----------------------------------------------------- drawing line */
  /* inheritable procedures */
  #define lines ps_lines
  #define line ps_line
  #define linerel ps_linerel
  #define lineto ps_lineto
  #define _lines ps__lines
  #define _line ps__line
  #define _linerel ps__linerel
  #define _lineto ps__lineto
/* rect.c ------------------------------------------------ drawing rectangle */
  /* inheritable procedures */
  #define rectangle ps_rectangle
  #define _rectangle ps__rectangle
/* poly.c -------------------------------------------------- drawing polygon */
  /* inheritable procedures */
  #define drawpoly ps_drawpoly
  #define _drawpoly ps__drawpoly
/* arcinfo.c -------------------------------------------------- arc settings */
  /* inheritable procedures */
  #define getarccoords ps_getarccoords
  #define getaspectratio ps_getaspectratio
  #define setaspectratio ps_setaspectratio
/* arc.c ------------------------------------------------------- drawing arc */
  /* inheritable procedures */
  #define arc ps_arc
  #define circle ps_circle
  #define ellipse ps_ellipse

  #define _arc ps__arc

  #define _circle ps__circle
  #define _ellipse ps__ellipse

/* fillinfo.c ------------------------------------------------ fill settings */
  /* inheritable procedures */
  #define getfillsettings ps_getfillsettings
  #define getfillpattern ps_getfillpattern
  #define setfillstyle ps_setfillstyle
  #define setfillpattern ps_setfillpattern
/* fillrect.c -------------------------------------------- filling rectangle */
  /* inheritable procedures */
  #define bar ps_bar
  #define bar3d ps_bar3d

  #define _bar ps__bar
  #define _bar3d ps__bar3d

/* fillpoly.c ---------------------------------------------- filling polygon */
  /* inheritable procedures */
  #define fillpoly ps_fillpoly
  #define _fillpoly ps__fillpoly
/* fillarc.c --------------------------------------------------- filling arc */
  /* inheritable procedures */
  #define fillellipse ps_fillellipse
  #define pieslice ps_pieslice
  #define sector ps_sector

  #define _fillellipse ps__fillellipse
  #define _pieslice ps__pieslice

  #define _sector ps__sector

/* flood.c --------------------------------------------------- filling flood */
  /* inheritable procedures */
  #define floodfill ps_floodfill
  #define _floodfill ps__floodfill
/* pixel.c ----------------------------------------------------------- pixel */
  /* inheritable procedures */
  #define putpixels ps_putpixels
  #define getpixel ps_getpixel
  #define putpixel ps_putpixel
  #define _putpixels ps__putpixels
  #define _getpixel ps__getpixel
  #define _putpixel ps__putpixel
/* image.c ----------------------------------------------------------- image */
  /* inheritable procedures */
  #define imagesize ps_imagesize
  #define getimage ps_getimage
  #define putimage ps_putimage
  #define _getimage ps__getimage

  #define _putimage ps__putimage
/* point.c ----------------------------------------------------------- point */
  /* inheritable procedures */
  #define putpoints ps_putpoints
  #define getpointsettings ps_getpointsettings
  #define setpointstyle ps_setpointstyle
  #define putpoint ps_putpoint
  #define _putpoints ps__putpoints
  #define _putpoint ps__putpoint
/* textinfo.c ------------------------------------------------ text settings */
  /* inheritable procedures */
  #define textheight ps_textheight
  #define textwidth ps_textwidth
  #define gettextsettings ps_gettextsettings
  #define settextstyle ps_settextstyle
  #define settextjustify ps_settextjustify
  #define setusercharsize ps_setusercharsize
  #define installuserfont ps_installuserfont
  #define registerbgifont ps_registerbgifont
  #define registerfarbgifont ps_registerfarbgifont
/* text.c --------------------------------------------- out text on graphics */
  /* inheritable procedures */
  #define outtext ps_outtext
  #define outtextxy ps_outtextxy
  #define _outtextxy ps__outtextxy
/* color.c ----------------------------------------------- get and set color */
  /* inheritable procedures */
  #define getcolor ps_getcolor
  #define getbkcolor ps_getbkcolor
  #define getmaxcolor ps_getmaxcolor
  #define setcolor ps_setcolor
  #define setbkcolor ps_setbkcolor
  #define setmaxcolor ps_setmaxcolor
/* palette.c -------------------------------- get and set palette and colors */
  /* inheritable procedures */
  #define getdefaultpalette ps_getdefaultpalette
  #define getpalette ps_getpalette
  #define getpalettesize ps_getpalettesize
  #define setallpalette ps_setallpalette
  #define setpalette ps_setpalette
  #define setrgbpalette ps_setrgbpalette
  #define _setrgbpalette ps__setrgbpalette
/* bgiutl.c ----------------------------------- meta-level procedures of bgi */
  /* inheritable procedures */
  #define bgivprintf ps_bgivprintf
  #define bgiprintf ps_bgiprintf
  #define bgigets ps_bgigets
  #define bgimenu ps_bgimenu
/* kbhit.c ------------------------------------------ get keyboard hit state */
  /* inheritable procedures */
  #define kbhit ps_kbhit
/* getch.c ---------------------------------------------- key pressed return */
  /* inheritable procedures */
  #define getch ps_getch
/* conio.c ---------------------------------------------- console procedures */
  /* all common procedures, reserved future */
/* ------------------------------------------------------------------------- */

/*
 * prototypes of inheritor
 */
/* event.c ------------------------ event looper for simple event programing */
  /* common procedures */
  void set_button_press_handler( int (*handler)(int button,int x,int y) );
  void set_button_release_handler( int (*handler)(int button,int x,int y) );
  void set_mouse_motion_handler( int (*handler)(int button,int x,int y) );
  void set_page_enter_handler( int (*handler)(int page) );
  void set_page_leave_handler( int (*handler)(int page) );
  void set_key_press_handler( int (*handler)(int key) );
  void set_configure_handler( int (*handler)(void) );
  void set_expose_handler( int (*handler)(void) );
  void set_noevent_handler( int (*handler)(void) );
  /* inheritable procedures */
  int xbgi_button_press( int button, int x, int y );
  int xbgi_button_release( int button, int x, int y );
  int xbgi_mouse_motion( int button, int x, int y );
  int xbgi_page_enter( int page );
  int xbgi_page_leave( int page );
  int xbgi_key_press( int key );
  int xbgi_configure( void );
  int xbgi_expose( void );
  int xbgi_noevent( void );
  void xbgiloop( void );
  int isevent( void );
/* request.c ------------------------------------------------- request flush */
  /* inheritable procedures */
  void xflush( void );
  void xsync( void );
/* config.c -------------------------- configuration of graphics environment */
  /* inheritable procedures */
  int getmaxx( void );
  int getmaxy( void );
  void setmaxx( int maxx );
  void setmaxy( int maxy );
  void getsizexy( int *xsize, int *ysize );
  void setsizexy( int xsize, int ysize );
  void getgeometry( int *x, int *y, int *width, int *height );
  void setgeometry( int x, int y, int width, int height );
  void settitle( char *title );
  void seticonname( char *filename );
  int seticon( char *filename );
  void setbackingstore( int flg );
/* driver.c --------------------------------------- graphics driver and mode */
  /* common procedures */
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
  int registerfarbgidriver( void *driver );
  /* inheritable procedures */
  void detectgraph( int *graphdriver, int *graphmode );
  void _driver( void );
  void driver( void );
/* init.c ------------------------------ initialize and close graphic system */
  /* common procedures */
  void _initgraph( int argc, char *argv[], char *pd );
  void initgraph( int *graphdriver, int *graphmode, char *pathtodriver );
  void graphdefaults( void );
  void closegraph( void );
/* id.c -------------------------------- multi-graphic system using graph id */
  /* common procedures */
  int graphnumber( void );
  void selectgraph( int id );
  void termgraph( int id );
/* util.c ------------------------------------ utilities for X-Window system */
  /* inheritable procedures */
  int savemonographtofile( char *filename, char *option );
  int savegraphtofile( char *filename, char *option );
  int saveexposetofile( char *filename, char *option );
/* error.c ------------------------------------------------- error messenger */
  /* inheritable procedures */
  int graphresult( void );
  char *grapherrormsg( int errorcode );
/* page.c ------------------------------------------- page as drawing device */
  /* inheritable procedures */
  void cleardevice( void );
  void setactivepage( int page );
  void setvisualpage( int page );
  void restorecrtmode( void );
/* viewport.c --------------------------- viewport as virtual drawing device */
  /* inheritable procedures */
  void clearviewport( void );
  void setviewport( int left, int top, int right, int bottom, int clip );
  void getviewsettings( struct viewporttype *viewport );
/* lineinfo.c ------------------------------------------------ line settings */
  /* inheritable procedures */
  void getlinesettings( struct linesettingstype *lineinfo );
  void setlinestyle( int linestyle, unsigned upattern, int thickness );
/* writeops.c ------------------------------------------ set write operation */
  /* inheritable procedures */
  void setwritemode( int op );
/* move.c ---------------------------------------------------- current point */
  /* inheritable procedures */
  int getx( void );
  int gety( void );
  void moverel( int dx, int dy );
  void moveto( int x, int y );
  double _getx( void );
  double _gety( void );
  void _moverel( double dx, double dy );
  void _moveto( double x, double y );
/* line.c ----------------------------------------------------- drawing line */
  /* inheritable procedures */
  void lines( int numpoints, int *points );
  void line( int x1, int y1, int x2, int y2 );
  void linerel( int dx, int dy );
  void lineto( int x, int y );
  void _lines( int numpoints, double *points );
  void _line( double x1, double y1, double x2, double y2 );
  void _linerel( double dx, double dy );
  void _lineto( double x, double y );
/* rect.c ------------------------------------------------ drawing rectangle */
  /* inheritable procedures */
  void rectangle( int left, int top, int right, int bottom );
  void _rectangle( double left, double top, double right, double bottom );
/* poly.c -------------------------------------------------- drawing polygon */
  /* inheritable procedures */
  void drawpoly( int numpoints, int *polypoints );
  void _drawpoly( int numpoints, double *polypoints );
/* arcinfo.c -------------------------------------------------- arc settings */
  /* inheritable procedures */
  void getarccoords( struct arccoordstype *arccoords );
  void getaspectratio( int *xasp, int *yasp );
  void setaspectratio( int xasp, int yasp );
/* arc.c ------------------------------------------------------- drawing arc */
  /* inheritable procedures */
  void arc( int x, int y, int stangle, int endangle, int radius );
  void circle( int x, int y, int radius );
  void ellipse( int x, int y, int stangle, int endangle,
	       int xradius, int yradius );
  void _arc( double x, double y, double stangle, double endangle,
            double radius );
  void _circle( double x, double y, double radius );
  void _ellipse( double x, double y, double stangle, double endangle,
	        double xradius, double yradius );
/* fillinfo.c ------------------------------------------------ fill settings */
  /* inheritable procedures */
  void getfillsettings( struct fillsettingstype *fillinfo );
  void getfillpattern( char *pattern );
  void setfillstyle( int pattern, int color );
  void setfillpattern( char *upattern, int color );
/* fillrect.c -------------------------------------------- filling rectangle */
  /* inheritable procedures */
  void bar( int left, int top, int right, int bottom );
  void bar3d( int left, int top, int right, int bottom,
	     int depth, int topflag );
  void _bar( double left, double top, double right, double bottom );
  void _bar3d( double left, double top, double right, double bottom,
	      double depth, int topflag );
/* fillpoly.c ---------------------------------------------- filling polygon */
  /* inheritable procedures */
  void fillpoly( int numpoints, int *polypoints );
  void _fillpoly( int numpoints, double *polypoints );
/* fillarc.c --------------------------------------------------- filling arc */
  /* inheritable procedures */
  void fillellipse( int x, int y, int xradius, int yradius );
  void pieslice( int x, int y, int stangle, int endangle, int radius );
  void sector( int x, int y, int stangle, int endangle,
	      int xradius, int yradius );
  void _fillellipse( double x, double y, double xradius, double yradius );
  void _pieslice( double x, double y, double stangle, double endangle,
                 double radius );
  void _sector( double x, double y, double stangle, double endangle,
	       double xradius, double yradius );
/* flood.c --------------------------------------------------- filling flood */
  /* inheritable procedures */
  void floodfill( int x, int y, int border );
  void _floodfill( double x, double y, int border );
/* pixel.c ----------------------------------------------------------- pixel */
  /* inheritable procedures */
  void putpixels( int numpoints, int *points, int color );
  unsigned getpixel( int x, int y );
  void putpixel( int x, int y, int color );
  void _putpixels( int numpoints, double *points, int color );
  unsigned _getpixel( double x, double y );
  void _putpixel( double x, double y, int color );
/* image.c ----------------------------------------------------------- image */
  /* inheritable procedures */
  unsigned imagesize( int left, int top, int right, int bottom );
  void getimage( int left, int top, int right, int bottom, void *bitmap );
  void putimage( int left, int top, void *bitmap, int op );
  void _getimage( double left, double top, double right, double bottom,
                 void *bitmap );
  void _putimage( double left, double top, void *bitmap, int op );
/* point.c ----------------------------------------------------------- point */
  /* inheritable procedures */
  void putpoints( int numpoints, int *points );
  void getpointsettings( struct pointsettingstype *pointinfo );
  void setpointstyle( int type, int color, int fillcolor, int size );
  void putpoint( int x, int y );
  void _putpoints( int numpoints, double *points );
  void _putpoint( double x, double y );
/* textinfo.c ------------------------------------------------ text settings */
  /* inheritable procedures */
  int textheight( char *textstring );
  int textwidth( char *textstring );
  void gettextsettings( struct textsettingstype *texttypeinfo );
  void settextstyle( int font, int direction, int charsize );
  void settextjustify( int horiz, int vert );
  void setusercharsize( int multx, int divx, int multy, int divy );
  int installuserfont( char *name );
  int registerbgifont( void (*font)(void) );
  int registerfarbgifont( void *font );
/* text.c --------------------------------------------- out text on graphics */
  /* inheritable procedures */
  void outtext( char *textstring );
  void outtextxy( int x, int y, char *textstring );
  void _outtextxy( double x, double y, char *textstring );
/* color.c ----------------------------------------------- get and set color */
  /* inheritable procedures */
  int getcolor( void );
  int getbkcolor( void );
  int getmaxcolor( void );
  void setcolor( int color );
  void setbkcolor( int color );
  void setmaxcolor( int c );
/* palette.c -------------------------------- get and set palette and colors */
  /* inheritable procedures */
  struct palettetype *getdefaultpalette( void );
  void getpalette( struct palettetype *palette );
  int getpalettesize( void );
  void setallpalette( struct palettetype *palette );
  void setpalette( int colornum, int color );
  void setrgbpalette( int colornum, int red, int green, int blue );
  void _setrgbpalette( int colornum,
		      unsigned short red,
		      unsigned short green,
		      unsigned short blue );
/* bgiutl.c ----------------------------------- meta-level procedures of bgi */
  /* inheritable procedures */
  void bgivprintf( char *title, int textjust, char *fmt, va_list argptr );
  void bgiprintf( char *title, int textjust, char *fmt, ... );
  void bgigets( char *title, int maxlen, char *str );
  void bgimenu( char *title, int menuc, char *menuv[], int *menui );
/* kbhit.c ------------------------------------------ get keyboard hit state */
  /* inheritable procedures */
  int kbhit( void );
/* getch.c ---------------------------------------------- key pressed return */
  /* inheritable procedures */
  int getch( void );
/* conio.c ---------------------------------------------- console procedures */
  /* all common procedures, reserved future */
/* ------------------------------------------------------------------------- */

/*
 * the header of XBGI to stack
 */
extern xbgi *XBGIS;

/*
 * the current XBGI
 */
extern xbgi *XBGI;

/*
 * the current XBGI driver
 */
extern void (*XBGI_CURRENT_DRIVER)( void );

/*
 * the procedure set for Postscript
 */
extern xbgi_procedures PS_XBGI_PROCEDURES;

/*
 * the various macros and definitions
 */
#define BBX 10  /* these are for PS original point to view EPS */
#define BBY 100

#define minmax(a,x,b) ((((a)<=(x))&&((x)<=(b)))?(x):(((x)<(a))?(a):(b)))
/* repaired, since version 3.02 generic 19991024 */
#define Xx(x)         (XBGI->viewport.left+(x))
#define Xy(y)         (getmaxy()-(XBGI->viewport.top+(y)))
#define xX(x)         ((x)-XBGI->viewport.left)
#define yX(y)         ((y)-(getmaxy()-XBGI->viewport.top))
#define CTRL(c)       (((c)<'a')?((c)-'A'+1):((c)-'a'+1))

#define eprintf(fp,fmt,err) do{ fprintf(fp,fmt,err); exit( 1 ); }while(0)

#define FatalError(err)     eprintf(stderr,"XBGI(PS): fatal error: %s.\n",err)
#define Warning(err)        fprintf(stderr,"XBGI(PS): warning: %s.\n",err)
#define ReservedFuture(err) fprintf(stderr,"XBGI(PS): reserved future: %s.\n",err)
#define NotSupported(err)   fprintf(stderr,"XBGI(PS): not supported: %s.\n",err)
#define Notice(msg)         fprintf(stderr,"XBGI(PS): notice: %s.\n",msg)

#define  ASCENT_CANNOT_FIND 14
#define DESCENT_CANNOT_FIND  2
#define   WIDTH_CANNOT_FIND  8
#define  HEIGHT_CANNOT_FIND (ASCENT_CANNOT_FIND+DESCENT_CANNOT_FIND)

#define TextHeight(fs)      ((fs!=NULL)?(fs->tm[1][0]):\
			     (HEIGHT_CANNOT_FIND))
#define TextAscent(fs)      ((fs!=NULL)?(fs->tm[1][0]*14/16):\
                             (ASCENT_CANNOT_FIND))
#define TextDescent(fs)     ((fs!=NULL)?(fs->tm[1][0]*2/16):\
                             (DESCENT_CANNOT_FIND))
#define TextWidth(fs,p,l)   ((fs!=NULL)?(fs->tm[0][0]*l):\
                             (WIDTH_CANNOT_FIND*l))
#define TextWidth16(fs,p,l) ((fs!=NULL)?(fs->tm[0][0]*2*l):\
                             (WIDTH_CANNOT_FIND*2*l))

#endif /* _PS_P_H_ */
