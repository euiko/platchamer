/*
 * Source File < common/graphics.c >
 *
 * Standard Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include <stdio.h>
#include "graphix.h"

/* event.c ------------------------ event looper for simple event programing #/
  /# common procedures #/
  void set_button_press_handler( int (*handler)(int button,int x,int y) );
  void set_button_release_handler( int (*handler)(int button,int x,int y) );
  void set_mouse_motion_handler( int (*handler)(int button,int x,int y) );
  void set_page_enter_handler( int (*handler)(int page) );
  void set_page_leave_handler( int (*handler)(int page) );
  void set_key_press_handler( int (*handler)(int key) );
  void set_configure_handler( int (*handler)(void) );
  void set_expose_handler( int (*handler)(void) );
  void set_noevent_handler( int (*handler)(void) );
  /# inheritable procedures #/
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
/# request.c ------------------------------------------------- request flush #/
  /# inheritable procedures #/
  void xflush( void );
  void xsync( void );
/# config.c -------------------------- configuration of graphics environment #/
  /# inheritable procedures #/
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
/# driver.c --------------------------------------- graphics driver and mode #/
  /# common procedures #/
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
  /# inheritable procedures #/
  void detectgraph( int *graphdriver, int *graphmode );
  void _driver( void );
  void driver( void );
/# init.c ------------------------------ initialize and close graphic system #/
  /# common procedures #/
  void _initgraph( int argc, char *argv[], char *pd );
  void initgraph( int *graphdriver, int *graphmode, char *pathtodriver );
  void graphdefaults( void );
  void closegraph( void );
/# id.c -------------------------------- multi-graphic system using graph id #/
  /# common procedures #/
  int graphnumber( void );
  void selectgraph( int id );
  void termgraph( int id );
/# util.c ------------------------------------ utilities for X-Window system #/
  /# inheritable procedures #/
  int savemonographtofile( char *filename, char *option );
  int savegraphtofile( char *filename, char *option );
  int saveexposetofile( char *filename, char *option );
/# error.c ------------------------------------------------- error messenger #/
  /# inheritable procedures #/
  int graphresult( void );
  char *grapherrormsg( int errorcode );
/# page.c ------------------------------------------- page as drawing device #/
  /# inheritable procedures #/
  void cleardevice( void );
  void setactivepage( int page );
  void setvisualpage( int page );
  void restorecrtmode( void );
/# viewport.c --------------------------- viewport as virtual drawing device #/
  /# inheritable procedures #/
  void clearviewport( void );
  void setviewport( int left, int top, int right, int bottom, int clip );
  void getviewsettings( struct viewporttype *viewport );
/# lineinfo.c ------------------------------------------------ line settings #/
  /# inheritable procedures #/
  void getlinesettings( struct linesettingstype *lineinfo );
  void setlinestyle( int linestyle, unsigned upattern, int thickness );
/# writeops.c ------------------------------------------ set write operation #/
  /# inheritable procedures #/
  void setwritemode( int op );
/# move.c ---------------------------------------------------- current point #/
  /# inheritable procedures #/
  int getx( void );
  int gety( void );
  void moverel( int dx, int dy );
  void moveto( int x, int y );
  double _getx( void );
  double _gety( void );
  void _moverel( double dx, double dy );
  void _moveto( double x, double y );
/# line.c ----------------------------------------------------- drawing line #/
  /# inheritable procedures #/
  void lines( int numpoints, int *points );
  void line( int x1, int y1, int x2, int y2 );
  void linerel( int dx, int dy );
  void lineto( int x, int y );
  void _lines( int numpoints, double *points );
  void _line( double x1, double y1, double x2, double y2 );
  void _linerel( double dx, double dy );
  void _lineto( double x, double y );
/# rect.c ------------------------------------------------ drawing rectangle #/
  /# inheritable procedures #/
  void rectangle( int left, int top, int right, int bottom );
  void _rectangle( double left, double top, double right, double bottom );
/# poly.c -------------------------------------------------- drawing polygon #/
  /# inheritable procedures #/
  void drawpoly( int numpoints, int *polypoints );
  void _drawpoly( int numpoints, double *polypoints );
/# arcinfo.c -------------------------------------------------- arc settings #/
  /# inheritable procedures #/
  void getarccoords( struct arccoordstype *arccoords );
  void getaspectratio( int *xasp, int *yasp );
  void setaspectratio( int xasp, int yasp );
/# arc.c ------------------------------------------------------- drawing arc #/
  /# inheritable procedures #/
  void arc( int x, int y, int stangle, int endangle, int radius );
  void circle( int x, int y, int radius );
  void ellipse( int x, int y, int stangle, int endangle,
	       int xradius, int yradius );
  void _arc( double x, double y, double stangle, double endangle,
            double radius );
  void _circle( double x, double y, double radius );
  void _ellipse( double x, double y, double stangle, double endangle,
	        double xradius, double yradius );
/# fillinfo.c ------------------------------------------------ fill settings #/
  /# inheritable procedures #/
  void getfillsettings( struct fillsettingstype *fillinfo );
  void getfillpattern( char *pattern );
  void setfillstyle( int pattern, int color );
  void setfillpattern( char *upattern, int color );
/# fillrect.c -------------------------------------------- filling rectangle #/
  /# inheritable procedures #/
  void bar( int left, int top, int right, int bottom );
  void bar3d( int left, int top, int right, int bottom,
	     int depth, int topflag );
  void _bar( double left, double top, double right, double bottom );
  void _bar3d( double left, double top, double right, double bottom,
	      double depth, int topflag );
/# fillpoly.c ---------------------------------------------- filling polygon #/
  /# inheritable procedures #/
  void fillpoly( int numpoints, int *polypoints );
  void _fillpoly( int numpoints, double *polypoints );
/# fillarc.c --------------------------------------------------- filling arc #/
  /# inheritable procedures #/
  void fillellipse( int x, int y, int xradius, int yradius );
  void pieslice( int x, int y, int stangle, int endangle, int radius );
  void sector( int x, int y, int stangle, int endangle,
	      int xradius, int yradius );
  void _fillellipse( double x, double y, double xradius, double yradius );
  void _pieslice( double x, double y, double stangle, double endangle,
                 double radius );
  void _sector( double x, double y, double stangle, double endangle,
	       double xradius, double yradius );
/# flood.c --------------------------------------------------- filling flood #/
  /# inheritable procedures #/
  void floodfill( int x, int y, int border );
  void _floodfill( double x, double y, int border );
/# pixel.c ----------------------------------------------------------- pixel #/
  /# inheritable procedures #/
  void putpixels( int numpoints, int *points, int color );
  unsigned getpixel( int x, int y );
  void putpixel( int x, int y, int color );
  void _putpixels( int numpoints, double *points, int color );
  unsigned _getpixel( double x, double y );
  void _putpixel( double x, double y, int color );
/# image.c ----------------------------------------------------------- image #/
  /# inheritable procedures #/
  unsigned imagesize( int left, int top, int right, int bottom );
  void getimage( int left, int top, int right, int bottom, void *bitmap );
  void putimage( int left, int top, void *bitmap, int op );
  void _getimage( double left, double top, double right, double bottom,
                 void *bitmap );
  void _putimage( double left, double top, void *bitmap, int op );
/# point.c ----------------------------------------------------------- point #/
  /# inheritable procedures #/
  void putpoints( int numpoints, int *points );
  void getpointsettings( struct pointsettingstype *pointinfo );
  void setpointstyle( int type, int color, int fillcolor, int size );
  void putpoint( int x, int y );
  void _putpoints( int numpoints, double *points );
  void _putpoint( double x, double y );
/# textinfo.c ------------------------------------------------ text settings #/
  /# inheritable procedures #/
  int textheight( char *textstring );
  int textwidth( char *textstring );
  void gettextsettings( struct textsettingstype *texttypeinfo );
  void settextstyle( int font, int direction, int charsize );
  void settextjustify( int horiz, int vert );
  void setusercharsize( int multx, int divx, int multy, int divy );
  int installuserfont( char *name );
  int registerbgifont( void (*font)(void) );
  int registerfarbgifont( void *font );
/# text.c --------------------------------------------- out text on graphics #/
  /# inheritable procedures #/
  void outtext( char *textstring );
  void outtextxy( int x, int y, char *textstring );
  void _outtextxy( double x, double y, char *textstring );
/# color.c ----------------------------------------------- get and set color #/
  /# inheritable procedures #/
  int getcolor( void );
  int getbkcolor( void );
  int getmaxcolor( void );
  void setcolor( int color );
  void setbkcolor( int color );
  void setmaxcolor( int c );
/# palette.c -------------------------------- get and set palette and colors #/
  /# inheritable procedures #/
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
/# bgiutl.c ----------------------------------- meta-level procedures of bgi #/
  /# inheritable procedures #/
  void bgivprintf( char *title, int textjust, char *fmt, va_list argptr );
  void bgiprintf( char *title, int textjust, char *fmt, ... );
  void bgigets( char *title, int maxlen, char *str );
  void bgimenu( char *title, int menuc, char *menuv[], int *menui );
/# kbhit.c ------------------------------------------ get keyboard hit state #/
  /# inheritable procedures #/
  int kbhit( void );
/# getch.c ---------------------------------------------- key pressed return #/
  /# inheritable procedures #/
  int getch( void );
/# conio.c ---------------------------------------------- console procedures #/
  /# all common procedures, reserved future #/
/# ------------------------------------------------------------------------- */

/*
 * the header of XBGI to stack and it's initialized
 */
xbgi *XBGIS = NULL;

/*
 * the current XBGI and it's initialized
 */
xbgi *XBGI = NULL;

/*
 * the current XBGI driver and it's initialized
 */
#ifndef BUILD_STANDALONE
void (*XBGI_CURRENT_DRIVER)( void ) = XBGI_DEFAULT_DRIVER;
#endif






