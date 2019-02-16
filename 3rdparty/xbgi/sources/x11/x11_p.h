/*
 * Private Include File < x11/x11_p.h >
 *
 * Macros and Definitions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _X11_P_H_
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dos.h"
#include "coniox.h"
#include "conio.h"
#include "graphix.h"
#include "graphics.h"
#include "x11.h"
#include "bgiutl.h"
#include "misc.h"
#include <X11/keysym.h>
#include <X11/cursorfont.h>
#ifdef ENABLE_BILINGUAL
#  include "japanese.h"
#endif
#ifdef ENABLE_MULTILINGUAL
#  include <X11/Xlocale.h>
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
  #define xbgi_button_press x11_xbgi_button_press
  #define xbgi_button_release x11_xbgi_button_release
  #define xbgi_mouse_motion x11_xbgi_mouse_motion
  #define xbgi_page_enter x11_xbgi_page_enter
  #define xbgi_page_leave x11_xbgi_page_leave
  #define xbgi_key_press x11_xbgi_key_press
  #define xbgi_configure x11_xbgi_configure
  #define xbgi_expose x11_xbgi_expose
  #define xbgi_noevent x11_xbgi_noevent
  #define xbgiloop x11_xbgiloop
  #define isevent x11_isevent
/* request.c ------------------------------------------------- request flush */
  /* inheritable procedures */
  #define xflush x11_xflush
  #define xsync x11_xsync
/* config.c -------------------------- configuration of graphics environment */
  /* inheritable procedures */
  #define getmaxx x11_getmaxx
  #define getmaxy x11_getmaxy
  #define setmaxx x11_setmaxx
  #define setmaxy x11_setmaxy
  #define getsizexy x11_getsizexy
  #define setsizexy x11_setsizexy
  #define getgeometry x11_getgeometry
  #define setgeometry x11_setgeometry
  #define settitle x11_settitle
  #define seticonname x11_seticonname
  #define seticon x11_seticon
  #define setbackingstore x11_setbackingstore
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
  #define detectgraph x11_detectgraph
  /* inheritable and programable procedures */
  #define _driver x11__driver
  #define driver x11_driver
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
  #define savemonographtofile x11_savemonographtofile
  #define savegraphtofile x11_savegraphtofile
  #define saveexposetofile x11_saveexposetofile
/* error.c ------------------------------------------------- error messenger */
  /* inheritable procedures */
  #define graphresult x11_graphresult
  #define grapherrormsg x11_grapherrormsg
/* page.c ------------------------------------------- page as drawing device */
  /* inheritable procedures */
  #define cleardevice x11_cleardevice
  #define setactivepage x11_setactivepage
  #define setvisualpage x11_setvisualpage
  #define restorecrtmode x11_restorecrtmode
/* viewport.c --------------------------- viewport as virtual drawing device */
  /* inheritable procedures */
  #define clearviewport x11_clearviewport
  #define setviewport x11_setviewport
  #define getviewsettings x11_getviewsettings
/* lineinfo.c ------------------------------------------------ line settings */
  /* inheritable procedures */
  #define getlinesettings x11_getlinesettings
  #define setlinestyle x11_setlinestyle
/* writeops.c ------------------------------------------ set write operation */
  /* inheritable procedures */
  #define setwritemode x11_setwritemode
/* move.c ---------------------------------------------------- current point */
  /* inheritable procedures */
  #define getx x11_getx
  #define gety x11_gety
  #define moverel x11_moverel
  #define moveto x11_moveto
  #define _getx x11__getx
  #define _gety x11__gety
  #define _moverel x11__moverel
  #define _moveto x11__moveto
/* line.c ----------------------------------------------------- drawing line */
  /* inheritable procedures */
  #define lines x11_lines
  #define line x11_line
  #define linerel x11_linerel
  #define lineto x11_lineto
  #define _lines x11__lines
  #define _line x11__line
  #define _linerel x11__linerel
  #define _lineto x11__lineto
/* rect.c ------------------------------------------------ drawing rectangle */
  /* inheritable procedures */
  #define rectangle x11_rectangle
  #define _rectangle x11__rectangle
/* poly.c -------------------------------------------------- drawing polygon */
  /* inheritable procedures */
  #define drawpoly x11_drawpoly
  #define _drawpoly x11__drawpoly
/* arcinfo.c -------------------------------------------------- arc settings */
  /* inheritable procedures */
  #define getarccoords x11_getarccoords
  #define getaspectratio x11_getaspectratio
  #define setaspectratio x11_setaspectratio
/* arc.c ------------------------------------------------------- drawing arc */
  /* inheritable procedures */
  #define arc x11_arc
  #define circle x11_circle
  #define ellipse x11_ellipse

  #define _arc x11__arc

  #define _circle x11__circle
  #define _ellipse x11__ellipse

/* fillinfo.c ------------------------------------------------ fill settings */
  /* inheritable procedures */
  #define getfillsettings x11_getfillsettings
  #define getfillpattern x11_getfillpattern
  #define setfillstyle x11_setfillstyle
  #define setfillpattern x11_setfillpattern
/* fillrect.c -------------------------------------------- filling rectangle */
  /* inheritable procedures */
  #define bar x11_bar
  #define bar3d x11_bar3d

  #define _bar x11__bar
  #define _bar3d x11__bar3d

/* fillpoly.c ---------------------------------------------- filling polygon */
  /* inheritable procedures */
  #define fillpoly x11_fillpoly
  #define _fillpoly x11__fillpoly
/* fillarc.c --------------------------------------------------- filling arc */
  /* inheritable procedures */
  #define fillellipse x11_fillellipse
  #define pieslice x11_pieslice
  #define sector x11_sector

  #define _fillellipse x11__fillellipse
  #define _pieslice x11__pieslice

  #define _sector x11__sector

/* flood.c --------------------------------------------------- filling flood */
  /* inheritable procedures */
  #define floodfill x11_floodfill
  #define _floodfill x11__floodfill
/* pixel.c ----------------------------------------------------------- pixel */
  /* inheritable procedures */
  #define putpixels x11_putpixels
  #define getpixel x11_getpixel
  #define putpixel x11_putpixel
  #define _putpixels x11__putpixels
  #define _getpixel x11__getpixel
  #define _putpixel x11__putpixel
/* image.c ----------------------------------------------------------- image */
  /* inheritable procedures */
  #define imagesize x11_imagesize
  #define getimage x11_getimage
  #define putimage x11_putimage
  #define _getimage x11__getimage

  #define _putimage x11__putimage
/* point.c ----------------------------------------------------------- point */
  /* inheritable procedures */
  #define putpoints x11_putpoints
  #define getpointsettings x11_getpointsettings
  #define setpointstyle x11_setpointstyle
  #define putpoint x11_putpoint
  #define _putpoints x11__putpoints
  #define _putpoint x11__putpoint
/* textinfo.c ------------------------------------------------ text settings */
  /* inheritable procedures */
  #define textheight x11_textheight
  #define textwidth x11_textwidth
  #define gettextsettings x11_gettextsettings
  #define settextstyle x11_settextstyle
  #define settextjustify x11_settextjustify
  #define setusercharsize x11_setusercharsize
  #define installuserfont x11_installuserfont
  #define registerbgifont x11_registerbgifont
  #define registerfarbgifont x11_registerfarbgifont
/* text.c --------------------------------------------- out text on graphics */
  /* inheritable procedures */
  #define outtext x11_outtext
  #define outtextxy x11_outtextxy
  #define _outtextxy x11__outtextxy
/* color.c ----------------------------------------------- get and set color */
  /* inheritable procedures */
  #define getcolor x11_getcolor
  #define getbkcolor x11_getbkcolor
  #define getmaxcolor x11_getmaxcolor
  #define setcolor x11_setcolor
  #define setbkcolor x11_setbkcolor
  #define setmaxcolor x11_setmaxcolor
/* palette.c -------------------------------- get and set palette and colors */
  /* inheritable procedures */
  #define getdefaultpalette x11_getdefaultpalette
  #define getpalette x11_getpalette
  #define getpalettesize x11_getpalettesize
  #define setallpalette x11_setallpalette
  #define setpalette x11_setpalette
  #define setrgbpalette x11_setrgbpalette
  #define _setrgbpalette x11__setrgbpalette
/* bgiutl.c ----------------------------------- meta-level procedures of bgi */
  /* inheritable procedures */
  #define bgivprintf x11_bgivprintf
  #define bgiprintf x11_bgiprintf
  #define bgigets x11_bgigets
  #define bgimenu x11_bgimenu
/* kbhit.c ------------------------------------------ get keyboard hit state */
  /* inheritable procedures */
  #define kbhit x11_kbhit
/* getch.c ---------------------------------------------- key pressed return */
  /* inheritable procedures */
  #define getch x11_getch
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
 * the procedure set for Xlib
 */
extern xbgi_procedures X11_XBGI_PROCEDURES;

/*
 * the various macros and definitions
 */
#define minmax(a,x,b) ((((a)<=(x))&&((x)<=(b)))?(x):(((x)<(a))?(a):(b)))
#define Xx(x)         (XBGI->viewport.left+(x))
#define Xy(y)         (XBGI->viewport.top +(y))
#define xX(x)         ((x)-XBGI->viewport.left)
#define yX(y)         ((y)-XBGI->viewport.top )
#define CTRL(c)       (((c)<'a')?((c)-'A'+1):((c)-'a'+1))

#define eprintf(fp,fmt,err) do{ fprintf(fp,fmt,err); exit( 1 ); }while(0)

#define FatalError(err)     eprintf(stderr,"XBGI(X11): fatal error: %s.\n",err)
#define Warning(err)        fprintf(stderr,"XBGI(X11): warning: %s.\n",err)
#define ReservedFuture(err) fprintf(stderr,"XBGI(X11): reserved future: %s.\n",err)
#define NotSupported(err)   fprintf(stderr,"XBGI(X11): not supported: %s.\n",err)
#define Notice(msg)         fprintf(stderr,"XBGI(X11): notice: %s.\n",msg)

#define DecoHemBits   1
#define DecoBrimBits  2

#define HemBrim    (DecoHemBits+DecoBrimBits)
#define Hem(size)  (DecoHemBits+(size)+DecoHemBits)
#define Brim(size) (DecoBrimBits+(size)+DecoBrimBits)

#define  ASCENT_CANNOT_FIND 14
#define DESCENT_CANNOT_FIND  2
#define   WIDTH_CANNOT_FIND  8
#define  HEIGHT_CANNOT_FIND (ASCENT_CANNOT_FIND+DESCENT_CANNOT_FIND)

#define TextHeight(fs)      ((fs!=NULL)?\
                             (fs->max_bounds.ascent+fs->max_bounds.descent):\
                             (HEIGHT_CANNOT_FIND))
#define TextAscent(fs)      ((fs!=NULL)?\
                             (fs->max_bounds.ascent):\
                             (ASCENT_CANNOT_FIND))
#define TextDescent(fs)     ((fs!=NULL)?\
                             (fs->max_bounds.descent):\
                             (DESCENT_CANNOT_FIND))
#define TextWidth(fs,p,l)   ((fs!=NULL)?\
                             (XTextWidth(fs,p,l)):\
                             (WIDTH_CANNOT_FIND*l))
#define TextWidth16(fs,p,l) ((fs!=NULL)?\
                             (XTextWidth16(fs,p,l)):\
                             (WIDTH_CANNOT_FIND*2*l))

#endif /* _X11_P_H_ */
