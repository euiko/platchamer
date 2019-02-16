/*
 * Header File < common/graphics.h >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#define _XBGI_

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

#ifndef RAND_MAX
#  define RAND_MAX 32767
#endif

#if 0 /*defined(__cplusplus) || defined(c_plusplus)*/

extern "C" int rand( void );
inline int random( int __num )
{
  return (int)(((long)rand()*__num)/(RAND_MAX+1));
}
extern "C" long time( long* );
inline void randomize(void)
{
  srand( (unsigned)time(NULL) );
}
template <class T>
inline T max( T __a, T __b )
{
  return (__a>__b)?__a:__b;
}
template <class T>
inline T min( T __a, T __b )
{
  return (__a>__b)?__b:__a;
}
#ifdef NO_ATOI
extern "C" long atol( const char* );
inline int atoi( const char *__s )
{
  return (int)atol(__s);
}
#endif

#else

#ifndef random
#  define random(num) (int)(((long)rand()*(num))/(RAND_MAX+1))
#endif
#ifndef randomize
#  define randomize() srand((unsigned)time(NULL))
#endif
#ifndef max
#  define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#  define min(a,b) (((a)>(b))?(b):(a))
#endif
#ifdef NO_ATOI
#ifndef atoi
#  define atoi(s) ((int)atol(s))
#endif
#endif

#endif

#define far

/* graphresult gerror return codes */
enum graphics_errors {
  grOk             =   0,
  grNoInitGraph    =  -1,
  grNotDetected    =  -2,
  grFileNotFound   =  -3,
  grInvalidDriver  =  -4,
  grNoLoadMem      =  -5,
  grNoScanMem      =  -6,
  grNoFloodMem     =  -7,
  grFontNotFound   =  -8,
  grNoFontMem      =  -9,
  grInvalidMode    = -10,
  grError          = -11,
  grIOerror        = -12,
  grInvalidFont    = -13,
  grInvalidFontNum = -14,
  grInvalidVersion = -18
};

/* define graphics drivers */
enum graphics_drivers {
  DETECT = 0, /* requests autodetection */
  X11    = 1,
  PS     = 2,
  PIX    = 3,
  VIX    = 4, MAXGRAPHICSDRIVER = VIX,
  CURRENTDRIVER = -1,
};

/* graphics color modes for each gdriver */
enum graphics_modes {
  /* X11 */
  X11MONO   = 0,
  X11SGRAY  = 1,
  X11GRAY   = 2,
  X11SCOLOR = 3,
  X11COLOR  = 4,
  X11TCOLOR = 5,
  X11DCOLOR = 6, MAXGRAPHICSMODE = X11DCOLOR,
  /* PS */
  PSMONO    = 0,
  PSGRAY    = 1,
  PSCOLOR   = 5,
  /* PIX */
  PIXMONO   = 0,
  PIXSGRAY  = 1,
  PIXGRAY   = 2,
  PIXSCOLOR = 3,
  PIXCOLOR  = 4,
  PIXTCOLOR = 5,
  PIXDCOLOR = 6,
  /* VIX */
  VIXMONO   = 0,
  VIXGRAY   = 1,
  VIXCOLOR  = 5,
};

/* Colors for setpalette and setallpalette */

#if !defined(__COLORS)
#define __COLORS

enum COLORS {
  BLACK,     /* dark colors */
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  LIGHTGRAY,
  DARKGRAY, /* light colors */
  LIGHTBLUE,
  LIGHTGREEN,
  LIGHTCYAN,
  LIGHTRED,
  LIGHTMAGENTA,
  YELLOW,
  WHITE
};

#endif

/* Line styles for get/setlinestyle */
enum line_styles {
  SOLID_LINE   = 0,
  DOTTED_LINE  = 1,
  CENTER_LINE  = 2,
  DASHED_LINE  = 3,
  USERBIT_LINE = 4, /* User defined line style */
};

/* Line widths for get/setlinestyle */
enum line_widths {
  NORM_WIDTH  = 1,
  THICK_WIDTH = 3,
};

/* Font names for settextstyle */
enum font_names {
  DEFAULT_FONT     =  0,
  TRIPLEX_FONT     =  1,
  SMALL_FONT       =  2,
  SANS_SERIF_FONT  =  3,
  GOTHIC_FONT      =  4,
  SCRIPT_FONT      =  5,
  SIMPLEX_FONT     =  6,
  TRIPLEX_SCR_FONT =  7,
  COMPLEX_FONT     =  8,
  EUROPEAN_FONT    =  9,
  BOLD_FONT        = 10,
};
#define MAX_CHAR_FONT BOLD_FONT

#define HORIZ_DIR 0 /* left to right */
#define VERT_DIR  1 /* bottom to top */

#define USER_CHAR_SIZE  0 /* user-defined char size */
#define MAX_CHAR_SIZE  10 /* max-defined char size */

/* Fill patterns for get/setfillstyle */
enum fill_patterns {
  EMPTY_FILL,      /* fills area in background color */
  SOLID_FILL,      /* fills area in solid fill color */
  LINE_FILL,       /* --- fill */
  LTSLASH_FILL,    /* /// fill */
  SLASH_FILL,      /* /// fill with thick lines */
  BKSLASH_FILL,    /* \\\ fill with thick lines */
  LTBKSLASH_FILL,  /* \\\ fill */
  HATCH_FILL,      /* light hatch fill */
  XHATCH_FILL,     /* heavy cross hatch fill */
  INTERLEAVE_FILL, /* interleaving line fill */
  WIDE_DOT_FILL,   /* Widely spaced dot fill */
  CLOSE_DOT_FILL,  /* Closely spaced dot fill */
  USER_FILL        /* user defined fill */
};

/* write operators for ( draw, putpixel and ) putimage */
enum write_ops {
  COPY_PUT, /* MOV */
  XOR_PUT,  /* XOR */
  OR_PUT,   /* OR  */
  AND_PUT,  /* AND */
  NOT_PUT   /* NOT */
};

/* Horizontal and vertical justification for settextjustify */
enum text_just {
  LEFT_TEXT   = 0,
  CENTER_TEXT = 1,
  RIGHT_TEXT  = 2,
  BOTTOM_TEXT = 0,
  TOP_TEXT    = 2
};

/* Point styles (official enhanced definitions) */
enum point_types {
  LOZENGE_POINT,
  CROSS_POINT,
  SQUARE_POINT,
  XCROSS_POINT,
  TRIANGLE_POINT,
  ASTERISK_POINT,
  CIRCLE_POINT,
  CHECKMARK_POINT
};

#define MAXCOLORS 255

struct palettetype {
  unsigned char size;
  unsigned char colors[MAXCOLORS+1];
};

struct linesettingstype {
  int linestyle;
  unsigned upattern;
  int thickness;
};

struct textsettingstype {
  int font;
  int direction;
  int charsize;
  int horiz;
  int vert;
};

struct fillsettingstype {
  int pattern;
  int color;
};

struct pointtype {
  int x, y;
};

struct _pointtype {
  double x, y;
};

struct viewporttype {
  int left, top, right, bottom;
  int clip;
};

struct arcsettingstype { /* Original structure of xbgi, used internal */
  int x, y;
  int stangle, endangle;
  int xradius, yradius;
};

struct arccoordstype {
  int x, y;
  int xstart, ystart, xend, yend;
};

struct pointsettingstype { /* Original structure of xbgi, used for graph */
  int type;
  int color;
  int fillcolor;
  int size;
};

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
 * official enhanced functions to set event handler of xbgiloop
 */
extern void set_button_press_handler(
#if NeedFunctionPrototypes
  int (*proc)( int button, int x, int y )
#endif
);
extern void set_button_release_handler(
#if NeedFunctionPrototypes
  int (*proc)( int button, int x, int y )
#endif
);
extern void set_mouse_motion_handler(
#if NeedFunctionPrototypes
  int (*proc)( int button_state, int x, int y )
#endif
);
extern void set_key_press_handler(
#if NeedFunctionPrototypes
  int (*proc)( int key )
#endif
);
extern void set_configure_handler(
#if NeedFunctionPrototypes
  int (*proc)( void )
#endif
);
extern void set_expose_handler(
#if NeedFunctionPrototypes
  int (*proc)( void )
#endif
);
extern void set_noevent_handler(
#if NeedFunctionPrototypes
  int (*proc)( void )
#endif
);

/*
 * official enhanced functions
 */

extern void xbgiloop(
#if NeedFunctionPrototypes
  void
#endif
);

extern int isevent(
#if NeedFunctionPrototypes
  void
#endif
);

extern void xflush(
#if NeedFunctionPrototypes
  void
#endif
);

extern void xsync(
#if NeedFunctionPrototypes
  void
#endif
);

extern void settitle(
#if NeedFunctionPrototypes
  char *__title
#endif
);

extern void seticonname(
#if NeedFunctionPrototypes
  char *__name
#endif
);

extern int seticon(
#if NeedFunctionPrototypes
  char *__filename
#endif
);

extern void setmaxx(
#if NeedFunctionPrototypes
  int __x
#endif
);

extern void setmaxy(
#if NeedFunctionPrototypes
  int __y
#endif
);

extern void getsizexy(
#if NeedFunctionPrototypes
  int *__xsize, int *__ysize
#endif
);

extern void setsizexy(
#if NeedFunctionPrototypes
  int __xsize, int __ysize
#endif
);

void getgeometry(
#if NeedFunctionPrototypes
  int *__x, int *__y, int *__width, int *__height
#endif
);

void setgeometry(
#if NeedFunctionPrototypes
  int __x, int __y, int __width, int __height
#endif
);

extern void setmaxcolor(
#if NeedFunctionPrototypes
  int __c
#endif
);

extern void setbackingstore(
#if NeedFunctionPrototypes
  int __flg
#endif
);

extern void _setrgbpalette(
#if NeedFunctionPrototypes
  int __colornum,
  unsigned short __red,
  unsigned short __green,
  unsigned short __blue
#endif
);

extern void _initgraph(
#if NeedFunctionPrototypes
  int __argc, char *__argv[], char *__pd
#endif
);

extern int graphnumber(
#if NeedFunctionPrototypes
  void
#endif
);

extern void selectgraph(
#if NeedFunctionPrototypes
  int __id
#endif
);

extern void termgraph(
#if NeedFunctionPrototypes
  int __id
#endif
);

extern int savemonographtofile(
#if NeedFunctionPrototypes
  char *__filename, char *option
#endif
);
#define savegraphtoxbm(f) savemonographtofile(f,NULL) /* for compatibility */

extern int savegraphtofile(
#if NeedFunctionPrototypes
  char *__filename, char *option
#endif
);
#define savegraphtoxpm(f) savegraphtofile(f,NULL) /* for compatibility */

extern int saveexposetofile(
#if NeedFunctionPrototypes
  char *__filename, char *option
#endif
);
#define saveexposetops(f,o) saveexposetofile(f,o) /* for compatibility */

void lines(
#if NeedFunctionPrototypes
  int __numpoints, int *__points
#endif
);

void putpixels(
#if NeedFunctionPrototypes
  int __numpoints, int *__points, int __color
#endif
);

extern void putpoints(
#if NeedFunctionPrototypes
  int numpoints, int *points
#endif
);

extern void getpointsettings(
#if NeedFunctionPrototypes
  struct pointsettingstype *pointinfo
#endif
);

extern void setpointstyle(
#if NeedFunctionPrototypes
  int type, int color, int fillcolor, int size
#endif
);

extern void putpoint(
#if NeedFunctionPrototypes
  int x, int y
#endif
);

/*
 * standard functions
 */

extern void arc(
#if NeedFunctionPrototypes
  int __x, int __y, int __stangle, int __endangle, int __radius
#endif
);

extern void bar(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom
#endif
);

extern void bar3d(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom, int __depth, int __topflag
#endif
);

extern void circle(
#if NeedFunctionPrototypes
  int __x, int __y, int __radius
#endif
);

extern void cleardevice(
#if NeedFunctionPrototypes
  void
#endif
);

extern void clearviewport(
#if NeedFunctionPrototypes
  void
#endif
);

extern void closegraph(
#if NeedFunctionPrototypes
  void
#endif
);

extern void detectgraph(
#if NeedFunctionPrototypes
 int *__graphdriver,int *__graphmode
#endif
);

extern void drawpoly(
#if NeedFunctionPrototypes
 int __numpoints, int *__polypoints
#endif
);

extern void ellipse(
#if NeedFunctionPrototypes
  int __x, int __y, int __stangle, int __endangle, int __xradius, int __yradius
#endif
);

extern void fillellipse(
#if NeedFunctionPrototypes
  int __x, int __y, int __xradius, int __yradius
#endif
);

extern void fillpoly(
#if NeedFunctionPrototypes
  int __numpoints, int *__polypoints
#endif
);

extern void floodfill(
#if NeedFunctionPrototypes
  int __x, int __y, int __border
#endif
);

extern void getarccoords(
#if NeedFunctionPrototypes
  struct arccoordstype *__arccoords
#endif
);

extern void getaspectratio(
#if NeedFunctionPrototypes
  int *__xasp, int *__yasp
#endif
);

extern int getbkcolor(
#if NeedFunctionPrototypes
  void
#endif
);

extern int getcolor(
#if NeedFunctionPrototypes
  void
#endif
);

extern struct palettetype* getdefaultpalette(
#if NeedFunctionPrototypes
  void
#endif
);

extern char* getdrivername(
#if NeedFunctionPrototypes
  void
#endif
);

extern void getfillpattern(
#if NeedFunctionPrototypes
  char *__pattern
#endif
);

extern void getfillsettings(
#if NeedFunctionPrototypes
  struct fillsettingstype *__fillinfo
#endif
);

extern int getgraphmode(
#if NeedFunctionPrototypes
  void 
#endif
);

extern void getimage(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom, void *__bitmap
#endif
);

extern void getlinesettings(
#if NeedFunctionPrototypes
  struct linesettingstype *__lineinfo
#endif
);

extern int getmaxcolor(
#if NeedFunctionPrototypes
  void
#endif
);

extern int getmaxmode(
#if NeedFunctionPrototypes
  void
#endif
);

extern int getmaxx(
#if NeedFunctionPrototypes
  void
#endif
);

extern int getmaxy(
#if NeedFunctionPrototypes
  void
#endif
);

extern char* getmodename(
#if NeedFunctionPrototypes
  int __mode_number
#endif
);

extern void getmoderange(
#if NeedFunctionPrototypes
  int __graphdriver, int *__lomode, int *__himode
#endif
);

extern unsigned getpixel(
#if NeedFunctionPrototypes
  int __x, int __y
#endif
);

extern void getpalette(
#if NeedFunctionPrototypes
  struct palettetype *__palette
#endif
);

extern int getpalettesize(
#if NeedFunctionPrototypes
  void
#endif
);

extern void gettextsettings(
#if NeedFunctionPrototypes
  struct textsettingstype *__texttypeinfo
#endif
);

extern void getviewsettings(
#if NeedFunctionPrototypes
  struct viewporttype *__viewport
#endif
);

extern int getx(
#if NeedFunctionPrototypes
  void
#endif
);

extern int gety(
#if NeedFunctionPrototypes
  void
#endif
);

extern void graphdefaults(
#if NeedFunctionPrototypes
  void
#endif
);

extern char* grapherrormsg(
#if NeedFunctionPrototypes
  int __errorcode
#endif
);

extern void _graphfreemem(
#if NeedFunctionPrototypes
  void *__ptr, unsigned __size
#endif
);

extern void* _graphgetmem(
#if NeedFunctionPrototypes
  unsigned __size
#endif
);

extern int graphresult(
#if NeedFunctionPrototypes
  void
#endif
);

extern unsigned imagesize(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom
#endif
);

extern void initgraph(
#if NeedFunctionPrototypes
  int *__graphdriver, int *__graphmode, char *__pathtodriver
#endif
);

extern int installuserdriver(
#if NeedFunctionPrototypes
  char *__name, int (*__detect)(void)
#endif
);

extern int installuserfont(
#if NeedFunctionPrototypes
  char *__name
#endif
);

extern void line(
#if NeedFunctionPrototypes
  int __x1, int __y1, int __x2, int __y2
#endif
);

extern void linerel(
#if NeedFunctionPrototypes
  int __dx, int __dy
#endif
);

extern void lineto(
#if NeedFunctionPrototypes
  int __x, int __y
#endif
);

extern void moverel(
#if NeedFunctionPrototypes
  int __dx, int __dy
#endif
);

extern void moveto(
#if NeedFunctionPrototypes
  int __x, int __y
#endif
);

extern void outtext(
#if NeedFunctionPrototypes
  char *__textstring
#endif
);

extern void outtextxy(
#if NeedFunctionPrototypes
  int __x, int __y, char *__textstring
#endif
);

extern void pieslice(
#if NeedFunctionPrototypes
  int __x, int __y, int __stangle, int __endangle, int __radius
#endif
);

extern void putimage(
#if NeedFunctionPrototypes
  int __left, int __top, void *__bitmap, int __operator
#endif
);

extern void putpixel(
#if NeedFunctionPrototypes
  int __x, int __y, int __color
#endif
);

extern void rectangle(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom
#endif
);

extern void restorecrtmode(
#if NeedFunctionPrototypes
  void 
#endif
);

extern void sector(
#if NeedFunctionPrototypes
  int __x, int __y, int __stangle, int __endangle, int __xradius, int __yradius
#endif
);

extern void setactivepage(
#if NeedFunctionPrototypes
  int __page
#endif
);

extern void setallpalette(
#if NeedFunctionPrototypes
  struct palettetype *__palette
#endif
);

extern void setaspectratio(
#if NeedFunctionPrototypes
  int __xasp, int __yasp
#endif
);

extern void setbkcolor(
#if NeedFunctionPrototypes
  int __color
#endif
);

extern void setcolor(
#if NeedFunctionPrototypes
  int __color
#endif
);

extern void setfillpattern(
#if NeedFunctionPrototypes
  char  *__upattern, int __color
#endif
);

extern void setfillstyle(
#if NeedFunctionPrototypes
  int __pattern, int __color
#endif
);

extern unsigned setgraphbufsize(
#if NeedFunctionPrototypes
  unsigned __bufsize 
#endif
);

extern void setgraphmode(
#if NeedFunctionPrototypes
  int __mode 
#endif
);

extern void setlinestyle(
#if NeedFunctionPrototypes
  int __linestyle, unsigned __upattern, int __thickness
#endif
);

extern void setpalette(
#if NeedFunctionPrototypes
  int __colornum, int __color
#endif
);

extern void setrgbpalette(
#if NeedFunctionPrototypes
  int __colornum, int __red, int __green, int __blue
#endif
);

extern void settextjustify(
#if NeedFunctionPrototypes
  int __horiz, int __vert 
#endif
);

extern void settextstyle(
#if NeedFunctionPrototypes
  int __font, int __direction, int __charsize
#endif
);

extern void setusercharsize(
#if NeedFunctionPrototypes
  int __multx, int __divx, int __multy, int __divy
#endif
);

extern void setviewport(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom, int __clip
#endif
);

extern void setvisualpage(
#if NeedFunctionPrototypes
  int __page
#endif
);

extern void setwritemode(
#if NeedFunctionPrototypes
  int __mode
#endif
);

extern int textheight(
#if NeedFunctionPrototypes
  char *__textstring
#endif
);

extern int textwidth(
#if NeedFunctionPrototypes
  char *__textstring
#endif
);

extern int registerbgidriver(
#if NeedFunctionPrototypes
  void (*__driver)( void )
#endif
);

extern int registerfarbgidriver(
#if NeedFunctionPrototypes
  void *__driver
#endif
);

extern int registerbgidriver(
#if NeedFunctionPrototypes
  void (*__driver)( void )
#endif
);

extern int registerfarbgidriver(
#if NeedFunctionPrototypes
  void *__driver
#endif
);

extern void x11_driver(
#if NeedFunctionPrototypes
  void
#endif
);

extern void ps_driver(
#if NeedFunctionPrototypes
  void
#endif
);

extern int x11_driver_far[];

/*
 * default event handlers of xbgiloop
 */
extern int xbgi_button_press(
#if NeedFunctionPrototypes
  int __button, int __x, int __y
#endif
);
extern int xbgi_button_release(
#if NeedFunctionPrototypes
  int __button, int __x, int __y
#endif
);
extern int xbgi_mouse_motion(
#if NeedFunctionPrototypes
  int __button_state, int __x, int __y
#endif
);
extern int xbgi_page_enter(
#if NeedFunctionPrototypes
  int __page
#endif
);
extern int xbgi_page_leave(
#if NeedFunctionPrototypes
  int __page
#endif
);
extern int xbgi_key_press(
#if NeedFunctionPrototypes
  int __key
#endif
);
extern int xbgi_configure(
#if NeedFunctionPrototypes
  void
#endif
);
extern int xbgi_expose(
#if NeedFunctionPrototypes
  void
#endif
);
extern int xbgi_noevent(
#if NeedFunctionPrototypes
  void
#endif
);

extern int registerbgifont(
#if NeedFunctionPrototypes
  void (*__font)( void )
#endif
);

extern int registerfarbgifont(
#if NeedFunctionPrototypes
  void *__font
#endif
);

extern void triplex_font();
extern void small_font();
extern void sansserif_font();
extern void gothic_font();
extern int triplex_font_far[];
extern int small_font_far[];
extern int sansserif_font_far[];
extern int gothic_font_far[];
extern int script_font_far[];
extern int simplex_font_far[];
extern int triplexscript_font_far[];
extern int complex_font_far[];
extern int european_font_far[];
extern int bold_font_far[];

/*
 * extented functions for high-quality graphics
 */

extern double _getx(
#if NeedFunctionPrototypes
  void
#endif
);

extern double _gety(
#if NeedFunctionPrototypes
  void
#endif
);

extern void _moverel(
#if NeedFunctionPrototypes
  double dx, double dy
#endif
);

extern void _moveto(
#if NeedFunctionPrototypes
  double x, double y
#endif
);

extern void _lines(
#if NeedFunctionPrototypes
  int numpoints, double *points
#endif
);

extern void _line(
#if NeedFunctionPrototypes
  double x1, double y1, double x2, double y2
#endif
);

extern void _linerel(
#if NeedFunctionPrototypes
  double dx, double dy
#endif
);

extern void _lineto(
#if NeedFunctionPrototypes
  double x, double y
#endif
);

extern void _rectangle(
#if NeedFunctionPrototypes
  double left, double top, double right, double bottom
#endif
);

extern void _drawpoly(
#if NeedFunctionPrototypes
  int numpoints, double *polypoints
#endif
);

extern void _arc(
#if NeedFunctionPrototypes
 double x, double y, double stangle, double endangle, double radius
#endif
);

extern void _circle(
#if NeedFunctionPrototypes
  double x, double y, double radius
#endif
);

extern void _ellipse(
#if NeedFunctionPrototypes
 double x, double y, double stangle, double endangle,
 double xradius, double yradius
#endif
);

extern void _bar(
#if NeedFunctionPrototypes
  double left, double top, double right, double bottom
#endif
);

extern void _bar3d(
#if NeedFunctionPrototypes
 double left, double top, double right, double bottom,
 double depth, int topflag
#endif
);

extern void _fillpoly(
#if NeedFunctionPrototypes
  int numpoints, double *polypoints
#endif
);

extern void _fillellipse(
#if NeedFunctionPrototypes
  double x, double y, double xradius, double yradius
#endif
);

extern void _pieslice(
#if NeedFunctionPrototypes
 double x, double y, double stangle, double endangle, double radius
#endif
);

extern void _sector(
#if NeedFunctionPrototypes
 double x, double y, double stangle, double endangle,
 double xradius, double yradius
#endif
);

extern void _floodfill(
#if NeedFunctionPrototypes
  double x, double y, int border
#endif
);

extern void _putpixels(
#if NeedFunctionPrototypes
  int numpoints, double *points, int color
#endif
);

extern unsigned _getpixel(
#if NeedFunctionPrototypes
  double x, double y
#endif
);

extern void _putpixel(
#if NeedFunctionPrototypes
  double x, double y, int color
#endif
);

extern void _getimage(
#if NeedFunctionPrototypes
 double left, double top, double right, double bottom, void *bitmap
#endif
);

extern void _putimage(
#if NeedFunctionPrototypes
  double left, double top, void *bitmap, int op
#endif
);

extern void _putpoints(
#if NeedFunctionPrototypes
  int numpoints, double *points
#endif
);

extern void _putpoint(
#if NeedFunctionPrototypes
  double x, double y
#endif
);

extern void _outtextxy(
#if NeedFunctionPrototypes
  double x, double y, char *textstring
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GRAPHICS_H_ */


