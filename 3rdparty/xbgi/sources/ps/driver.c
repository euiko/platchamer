/*
 * Source File < ps/driver.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"
#include "option.h"

void detectgraph( int *graphdriver, int *graphmode )
{
  /*
   * case of detecting before initgraph, always PS and PSCOLOR
   */
  if ( XBGIS == NULL || XBGI == NULL || XBGI->inherit_members == NULL ){
    *graphdriver = PS;
    *graphmode   = PSCOLOR;
    return;
  }
  /*
   * case of detecting after initgraph, research visual class and depth
   */
  switch( *graphdriver ){
  case DETECT: default:
    *graphdriver = XBGI->gdriver = PS;
    break;
  case PS:
    *graphmode = XBGI->gmode; /* user's hope visual class */
    break;
  }
}
/*
 * default special driver, destroyer and creater
 */
void _driver( void )
{
  ps_xbgi_close();
  free( XBGI->inherit_members );
  XBGI->inherit_members = NULL;
}
void driver( void )
{
  int i, j;
#if 0
  extern char ps_xbgi_scolor_names[MAXCOLORS+1][64];
#endif
  int argc = XBGI->argc;
  char **argv = XBGI->argv;
  /*CurrentState cs = { 0.1,0,0,1,"[]",0,{0,0,0},"<ffffffffffffffff>",8 };*/
  CurrentState cs = { 0.0,0,0,1,"[]",0,{0,0,0},"<ffffffffffffffff>",8 }; /* fine stroke since 19991225 */
  char defgeomstr[20] = "640x400";
  char usrgeomstr[20] = "640x400";

  XBGI->ncolor = 16;
  XBGI->color = XBGI->ncolor-1;
  XBGI->bkcolor = 0;
  XBGI->npage = 2;
  XBGI->apage = 0;
  XBGI->vpage = 0;
  XBGI->l10n = !0;
  XBGI->colornames = 0;

  /* inherit ps of xbgi */
  *XBGI->inherit_procedures = PS_XBGI_PROCEDURES;
  XBGI->inherit_members = (ps_xbgi*)malloc( sizeof(ps_xbgi) );
  if ( XBGI->inherit_members == NULL )
    FatalError( "XBGI cannot inherit PS of XBGI" );

  /* memory initialization of ps */
  strcpy( PSBGITitle, "" );
  PSBGIUseInterp = 0;
  strcpy( PSBGIInterpName, "" );
  PSBGIInterpP = NULL;
  PSBGIUseFile = 0;
  strcpy( PSBGIFileName, "" );
  PSBGIFileP = NULL;
  PSBGIEncapsule = 0;
  PSBGIWins = NULL;
  /* initializing fonts */
  for ( i=DEFAULT_FONT; i<=MAX_CHAR_FONT; i++ )
    for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
      PSBGIStrokeFonts[i][j] = NULL;
  for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
    PSBGIBiFonts[j] = NULL;

  /* position, size, gc, font and color settings for work */
  scan_option( argc, argv, "-geometry %s", usrgeomstr );
  sscanf( usrgeomstr, "%dx%d", &PSBGIRoot.width, &PSBGIRoot.height );
  if ( PSBGIRoot.width <= 0 || PSBGIRoot.height <= 0 )
    sscanf( defgeomstr, "%dx%d", &PSBGIRoot.width, &PSBGIRoot.height );
  PSBGIRoot.x = 0;
  PSBGIRoot.y = 0;
  PSBGIRoot.drawn = 0;
  PSBGIRoot.showpage_count = 0;
  strcpy(PSBGIDash,cs.dash);
  strcpy(PSBGIFillpat,cs.fillpat);
  PSBGIState = cs;

  /* media and orientation settings */
  {
    static struct DocumentMedia {
      char *name;
      int width, height;
    } papersizes[] = {
      { "Letter",     612,  792 },
      { "Tabloid",    792, 1224 },
      { "Ledger",    1224,  792 },
      { "Legal",      612, 1008 },
      { "Statement",  396,  612 },
      { "Executive",  540,  720 },
      { "A3",         842, 1190 },
      { "A4",         595,  842 },
      { "A5",         420,  595 },
      { "B4",         729, 1032 },
      { "B5",         516,  729 },
      { "Folio",      612,  936 },
      { "Quarto",     610,  780 },
      { "10x14",      720, 1008 },
      { NULL,           0,    0 },
    };
#if 0
    static MediaCoordinate mc = {
      "Unknown", 0,0/* zero means unknown */,0, BBX,BBY, 0.5
    };
#else
    static MediaCoordinate mc = {
      "A4", 595,842,0, 0,0, 0/* zero means media depending */
    };
#endif
    char buf[256], tmp[64];
    int type;

    PSBGICoordinate = mc;
    strcpy( buf, "-paper " );
    for ( i=0; papersizes[i].name!=NULL; i++ ) {
      if ( isupper(papersizes[i].name[0]) ) {
	strcpy( tmp, papersizes[i].name );
	tmp[0] = tolower(papersizes[i].name[0]);
	strcat( buf, tmp );
      } else
	strcat( buf, papersizes[i].name );
      strcat( buf, " " );
    }
    if ( scan_option(argc,argv,buf,&type) ) {
      strcpy( PSBGICoordinate.tag, papersizes[type].name );
      PSBGICoordinate.page_width = papersizes[type].width;
      PSBGICoordinate.page_height = papersizes[type].height;
    }
    if ( scan_option( argc, argv, "-portrait" ) )
      PSBGICoordinate.orientation = 0;
    if ( scan_option( argc, argv, "-landscape" ) )
      PSBGICoordinate.orientation = 1;
    if ( PSBGICoordinate.orientation == 1 ) {
      int tmp = PSBGICoordinate.page_width;
      PSBGICoordinate.page_width = PSBGICoordinate.page_height;
      PSBGICoordinate.page_height = tmp;
    }
  }

  /* titlename and iconname settings */
  scan_option( argc, argv, "-title %s", PSBGITitle );

  /* get user bgi settings */
  if ( (i=scan_option(argc,argv,"-gd")) )
    XBGI->gdriver = getdrivernumber( argv[i+1] );
  if ( (i=scan_option(argc,argv,"-gm")) )
    XBGI->gmode = getmodenumber( argv[i+1] );
  scan_option( argc, argv, "-ncolor %d",  &(XBGI->ncolor)  );
  scan_option( argc, argv, "-color %d",   &(XBGI->color)   );
  scan_option( argc, argv, "-bkcolor %d", &(XBGI->bkcolor) );
  scan_option( argc, argv, "-npage %d",   &(XBGI->npage)   );
  scan_option( argc, argv, "-apage %d",   &(XBGI->apage)   );
  scan_option( argc, argv, "-vpage %d",   &(XBGI->vpage)   );

#if 0
  /* scanning named color list */
  if ( (j=scan_option(argc,argv,"-colornames")) ){
    c = 0;
    for ( i=j+1; i<argc; i++ ){
      if ( *argv[i] == '-' )
        break;
      strcpy( ps_xbgi_scolor_names[c++], argv[i] );
    }
    if ( 2 <= c && c<=MAXCOLORS ){
      XBGI->colornames = !0;
      XBGI->ncolor = c;
    }
  }
#endif
  XBGI->palette.size = (unsigned char)XBGI->ncolor-1;

  /* set font valuable */
  if ( scan_option( argc, argv, "-l10n"  ) ) XBGI->l10n = !0;
  if ( scan_option( argc, argv, "-l10n-" ) ) XBGI->l10n =  0;

  /* set interp connect */
  if ( scan_option( argc, argv, "-interp" ) ) PSBGIUseInterp = !0;

  /* set output to file */
  if ( scan_option( argc, argv, "-psfile %s", PSBGIFileName ) )
    PSBGIUseFile = !0;
  
  /* set eps/ps */
  if ( scan_option( argc, argv, "-eps"  ) ) PSBGIEncapsule = !0;
  if ( scan_option( argc, argv, "-eps-" ) ) PSBGIEncapsule =  0;

  /* create windows */
  PSBGIWins = (Geometry*)malloc( XBGI->npage*sizeof(Geometry) );
  for ( i=0; i<XBGI->npage; i++ )
    PSBGIWins[i] = PSBGIRoot;

  /* open pipe or/and file */
  ps_xbgi_open();
  
  /* default setting */
  detectgraph( &(XBGI->gdriver), &(XBGI->gmode) );
  setgraphmode( XBGI->gmode );
  graphdefaults();

  XBGI->gerror = grOk;
}

xbgi_procedures PS_XBGI_PROCEDURES = {
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
  /* inheritable procedures */
  NULL/*xbgi_button_press*/,
  NULL/*xbgi_button_release*/,
  NULL/*xbgi_mouse_motion*/,
  NULL/*xbgi_page_enter*/,
  NULL/*xbgi_page_leave*/,
  NULL/*xbgi_key_press*/,
  NULL/*xbgi_configure*/,
  NULL/*xbgi_expose*/,
  NULL/*xbgi_noevent*/,
  xbgiloop,
  isevent,
/* request.c ------------------------------------------------- request flush */
  /* inheritable procedures */
  xflush,
  xsync,
/* config.c -------------------------- configuration of graphics environment */
  /* inheritable procedures */
  getmaxx,
  getmaxy,
  setmaxx,
  setmaxy,
  getsizexy,
  setsizexy,
  getgeometry,
  setgeometry,
  settitle,
  seticonname,
  seticon,
  setbackingstore,
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
  detectgraph,
  _driver,
  driver,
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
  savemonographtofile,
  savegraphtofile,
  saveexposetofile,
/* error.c ------------------------------------------------- error messenger */
  /* inheritable procedures */
  graphresult,
  *grapherrormsg,
/* page.c ------------------------------------------- page as drawing device */
  /* inheritable procedures */
  cleardevice,
  setactivepage,
  setvisualpage,
  restorecrtmode,
/* viewport.c --------------------------- viewport as virtual drawing device */
  /* inheritable procedures */
  clearviewport,
  setviewport,
  getviewsettings,
/* lineinfo.c ------------------------------------------------ line settings */
  /* inheritable procedures */
  getlinesettings,
  setlinestyle,
/* writeops.c ------------------------------------------ set write operation */
  /* inheritable procedures */
  setwritemode,
/* move.c ---------------------------------------------------- current point */
  /* inheritable procedures */
  getx,
  gety,
  moverel,
  moveto,
  _getx,
  _gety,
  _moverel,
  _moveto,
/* line.c ----------------------------------------------------- drawing line */
  /* inheritable procedures */
  lines,
  line,
  linerel,
  lineto,
  _lines,
  _line,
  _linerel,
  _lineto,
/* rect.c ------------------------------------------------ drawing rectangle */
  /* inheritable procedures */
  rectangle,
  _rectangle,
/* poly.c -------------------------------------------------- drawing polygon */
  /* inheritable procedures */
  drawpoly,
  _drawpoly,
/* arcinfo.c -------------------------------------------------- arc settings */
  /* inheritable procedures */
  getarccoords,
  getaspectratio,
  setaspectratio,
/* arc.c ------------------------------------------------------- drawing arc */
  /* inheritable procedures */
  arc,
  circle,
  ellipse,

  _arc,

  _circle,
  _ellipse,

/* fillinfo.c ------------------------------------------------ fill settings */
  /* inheritable procedures */
  getfillsettings,
  getfillpattern,
  setfillstyle,
  setfillpattern,
/* fillrect.c -------------------------------------------- filling rectangle */
  /* inheritable procedures */
  bar,
  bar3d,

  _bar,
  _bar3d,

/* fillpoly.c ---------------------------------------------- filling polygon */
  /* inheritable procedures */
  fillpoly,
  _fillpoly,
/* fillarc.c --------------------------------------------------- filling arc */
  /* inheritable procedures */
  fillellipse,
  pieslice,
  sector,

  _fillellipse,
  _pieslice,

  _sector,

/* flood.c --------------------------------------------------- filling flood */
  /* inheritable procedures */
  floodfill,
  _floodfill,
/* pixel.c ----------------------------------------------------------- pixel */
  /* inheritable procedures */
  putpixels,
  getpixel,
  putpixel,
  _putpixels,
  _getpixel,
  _putpixel,
/* image.c ----------------------------------------------------------- image */
  /* inheritable procedures */
  imagesize,
  getimage,
  putimage,
  _getimage,

  _putimage,
/* point.c ----------------------------------------------------------- point */
  /* inheritable procedures */
  putpoints,
  getpointsettings,
  setpointstyle,
  putpoint,
  _putpoints,
  _putpoint,
/* textinfo.c ------------------------------------------------ text settings */
  /* inheritable procedures */
  textheight,
  textwidth,
  gettextsettings,
  settextstyle,
  settextjustify,
  setusercharsize,
  installuserfont,
  registerbgifont,
  registerfarbgifont,
/* text.c --------------------------------------------- out text on graphics */
  /* inheritable procedures */
  outtext,
  outtextxy,
  _outtextxy,
/* color.c ----------------------------------------------- get and set color */
  /* inheritable procedures */
  getcolor,
  getbkcolor,
  getmaxcolor,
  setcolor,
  setbkcolor,
  setmaxcolor,
/* palette.c -------------------------------- get and set palette and colors */
  /* inheritable procedures */
  *getdefaultpalette,
  getpalette,
  getpalettesize,
  setallpalette,
  setpalette,
  setrgbpalette,
  _setrgbpalette,
/* bgiutl.c ----------------------------------- meta-level procedures of bgi */
  /* inheritable procedures */
  bgivprintf,
  bgiprintf,
  bgigets,
  bgimenu,
/* kbhit.c ------------------------------------------ get keyboard hit state */
  /* inheritable procedures */
  kbhit,
/* getch.c ---------------------------------------------- key pressed return */
  /* inheritable procedures */
  getch,
/* conio.c ---------------------------------------------- console procedures */
  /* all common procedures, reserved future */
/* ------------------------------------------------------------------------- */
};
