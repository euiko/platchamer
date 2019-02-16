/*
 * Source File < x11/driver.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"
#include "option.h"

void detectgraph( int *graphdriver, int *graphmode )
{
  /*
   * case of detecting before initgraph, always X11 and X11COLOR
   */
  if ( XBGIS == NULL || XBGI == NULL || XBGI->inherit_members == NULL ){
    *graphdriver = X11;
    *graphmode   = X11COLOR;
    return;
  }
  /*
   * case of detecting after initgraph, research visual class and depth
   */
  switch( *graphdriver ){
  case DETECT: default:
    *graphdriver = XBGI->gdriver = X11;
    XBGIVisual = DefaultVisual(XBGIDisplay,XBGIScreen);
    XBGIDepth = DefaultDepth(XBGIDisplay,XBGIScreen);
    switch ( XBGIVisualClass ){
    case StaticGray:
      *graphmode = XBGI->gmode = X11SGRAY;
      if ( XBGIDepth == 1 )
        *graphmode = XBGI->gmode = X11MONO;
      break;
    case GrayScale:
      *graphmode = XBGI->gmode = X11GRAY;
      if ( XBGIDepth == 1 )
        *graphmode = XBGI->gmode = X11MONO;
      break;
    case StaticColor:
      *graphmode = XBGI->gmode = X11SCOLOR;
      break;
    case PseudoColor:
      *graphmode = XBGI->gmode = X11COLOR;
      break;
    case TrueColor:
      *graphmode = XBGI->gmode = X11TCOLOR;
      break;
    case DirectColor:
      if ( scan_option(XBGI->argc,XBGI->argv,"-direct-color") )
	*graphmode = XBGI->gmode = X11DCOLOR; 
      else /* It's counter-plan for X down. */
	*graphmode = XBGI->gmode = X11SCOLOR;
      break;
    }
    break;
  case X11:
#if 1 /* It's test case since version 3.01. */
    if ( XBGIVisual == NULL ) {
      int best_colormap_size[6] = { 0, 0, 0, 0, 0, 0 };
      int best_depth[6] = { 0, 0, 0, 0, 0, 0 };
      XVisualInfo *best_vi[6];
      int n_vi, demand_vc = -1;
      XVisualInfo vi_template, *vi_list, *v;
      
      vi_list = XGetVisualInfo( XBGIDisplay,
                               VisualNoMask, &vi_template, &n_vi );
      for ( v=vi_list; v<vi_list+n_vi; v++ ) {
        if ( best_colormap_size[v->class] == 0
            || ( v->colormap_size > best_colormap_size[v->class]
                && v->depth > best_depth[v->class] ) ) {
          best_colormap_size[v->class] = v->colormap_size;
          best_depth[v->class] = v->depth;
          best_vi[v->class] = v;
        }
#if 0
        printf("v->class=%d,v->colormap_size=%d,v->depth=%d\n",
               v->class,v->colormap_size,v->depth);
#endif
      }
#if 0
      for ( i=0; i<6; i++ )
        printf("class=%d:best:visual->id=%lx,colormap_size=%d,depth=%d\n",
               i,best_vi[i]->visualid,best_colormap_size[i],best_depth[i]);
#endif
      /* visual class checking algorithm */
      switch ( *graphmode ) {
      case X11MONO:
      case X11SGRAY:
        if ( best_colormap_size[StaticGray] >= XBGI->ncolor )
          demand_vc = StaticGray;
        break;
      case X11GRAY:
        if ( best_colormap_size[GrayScale] >= XBGI->ncolor )
          demand_vc = GrayScale;
        else if ( best_colormap_size[PseudoColor] >= XBGI->ncolor )
          demand_vc = PseudoColor;
        else
          XBGI->gmode = X11SGRAY;
        break;
      case X11SCOLOR:
        if ( best_colormap_size[StaticColor] >= XBGI->ncolor )
          demand_vc = StaticColor;
        break;
      case X11COLOR:
      default:
        if ( best_colormap_size[PseudoColor] >= XBGI->ncolor )
          demand_vc = PseudoColor;
        else if ( best_colormap_size[DirectColor] >= XBGI->ncolor ) {
          demand_vc = DirectColor;
          XBGI->gmode = X11DCOLOR;
        } else
          XBGI->gmode = X11SCOLOR;
        break;
      case X11TCOLOR:
        if ( best_colormap_size[TrueColor] >= XBGI->ncolor )
          demand_vc = TrueColor;
        break;
      case X11DCOLOR:
        if ( best_colormap_size[DirectColor] >= XBGI->ncolor )
          demand_vc = DirectColor;
        else if ( best_colormap_size[PseudoColor] >= XBGI->ncolor ) {
          demand_vc = PseudoColor;
          XBGI->gmode = X11COLOR;
        } else
          XBGI->gmode = X11SCOLOR;
        break;
      }
      if ( best_vi[demand_vc]->visualid !=
          XVisualIDFromVisual(DefaultVisual(XBGIDisplay,XBGIScreen))
          && demand_vc >= 0 ) {
        XBGIVisual = best_vi[demand_vc]->visual;
        /*XBGIVisualClass
          = best_vi[demand_vc]->visual->class;*/ /* it's macro */
        XBGIDepth = best_vi[demand_vc]->depth;
#if 0
        printf("demand_vc=%d,visual->id=%lx,colormap_size=%d,depth=%d\n",
               demand_vc,best_vi[demand_vc]->visualid,
               best_colormap_size[demand_vc],best_depth[demand_vc]);
#endif
        /* Graphic driver must create and install new Colormap
           to new windows created by new visual class. */
      } else {
        XBGIVisual = DefaultVisual(XBGIDisplay,XBGIScreen);
        XBGIDepth = DefaultDepth(XBGIDisplay,XBGIScreen);
      }
    }
#else
    XBGIVisual = DefaultVisual(XBGIDisplay,XBGIScreen);
    XBGIDepth = DefaultDepth(XBGIDisplay,XBGIScreen);
#endif
    *graphmode = XBGI->gmode;
    break;
  }
}
/*
 * default special driver, destroyer and creater
 */
void _driver( void )
{
  XUnmapSubwindows( XBGIDisplay, XBGIRoot );
  XUnmapWindow( XBGIDisplay, XBGIRoot );
  XFlush( XBGIDisplay );

  XFreeGC( XBGIDisplay, XBGIDrawGC  );
  XFreeGC( XBGIDisplay, XBGIFillGC  );
  XFreeGC( XBGIDisplay, XBGIPixelGC );
  XFreeGC( XBGIDisplay, XBGIImageGC );

  XFreeColormap( XBGIDisplay, XBGIColormap );
  if ( XBGIFontStruct ) XFreeFont( XBGIDisplay, XBGIFontStruct );

  XDestroySubwindows( XBGIDisplay, XBGIRoot );
  XDestroyWindow( XBGIDisplay, XBGIRoot );

#if 1 /* for segmentation fault, bug? fixed at version 3.01. */
  XSync( XBGIDisplay, False );
  XCloseDisplay( XBGIDisplay );
#endif
#if 1 /* for segmentation fault, bug? fixed at version 3.01. */
  free( XBGI->inherit_members );
  XBGI->inherit_members = NULL;
#endif
}
void driver( void )
{
  int i, j;
  int argc = XBGI->argc;
  char **argv = XBGI->argv;

  /*
   * inherit x11 of xbgi and it's memory initialization
   */
  {
    *XBGI->inherit_procedures = X11_XBGI_PROCEDURES;
    XBGI->inherit_members = malloc( sizeof(x11_xbgi) );
    if ( XBGI->inherit_members == NULL )
      FatalError( "XBGI cannot inherit X of XBGI" );
    XBGIDisplay = NULL;
    XBGIFontStruct = NULL;
    XBGIWins = NULL;
    for ( i=DEFAULT_FONT; i<=MAX_CHAR_FONT; i++ )
      for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
        XBGIStrokeFonts[i][j] = NULL;
    for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
      XBGIBiFonts[j] = NULL;
    for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
      XBGIMultiFonts[j] = NULL;
  }
  /*
   * connect display and initialize misc. after connecting
   */
  {
    char displayname[64] = "";
    extern char x11_xbgi_scolor_names[MAXCOLORS][64];

    XBGI->ncolor = 16;
    XBGI->color = XBGI->ncolor-1;
    XBGI->bkcolor = 0;
    XBGI->npage = 2;
    XBGI->apage = 0;
    XBGI->vpage = 0;
    XBGI->l10n = !0;
    XBGI->colornames = 0;
    scan_option( argc, argv, "-display %s", displayname );
    XBGIDisplay = XOpenDisplay( displayname );
    /*XSynchronize( XBGIDisplay, True );*/
    if ( XBGIDisplay == NULL )
      FatalError( "X cannot connect to display" );
    for ( i=0; i<=MAXCOLORS; i++ )
      XBGIPixels[i] = BlackPixel( XBGIDisplay, XBGIScreen );
    scan_option( argc, argv, "-ncolor %d", &(XBGI->ncolor) );
    scan_option( argc, argv, "-color %d", &(XBGI->color) );
    scan_option( argc, argv, "-bkcolor %d", &(XBGI->bkcolor) );
    scan_option( argc, argv, "-npage %d", &(XBGI->npage) );
    scan_option( argc, argv, "-apage %d", &(XBGI->apage) );
    scan_option( argc, argv, "-vpage %d", &(XBGI->vpage) );
    if ( (j=scan_option(argc,argv,"-colornames")) ){
      int c = 0;

      for ( i=j+1; i<argc; i++ ){
        if ( *argv[i] == '-' )
          break;
        strcpy( x11_xbgi_scolor_names[c++], argv[i] );
      }
      if ( 2<=c && c<=MAXCOLORS ){
        XBGI->colornames = !0;
        XBGI->ncolor = c;
      }
    }
    XBGI->palette.size = (unsigned char)XBGI->ncolor-1;
    if ( scan_option( argc, argv, "-l10n"  ) ) XBGI->l10n = !0;
    if ( scan_option( argc, argv, "-l10n-" ) ) XBGI->l10n =  0;
#ifdef ENABLE_MULTILINGUAL
    if ( setlocale( LC_ALL, "" ) == NULL )
      XBGI->l10n = 0;
    else if ( XSupportsLocale() == False )
      XBGI->l10n = 0;
    if ( !XBGI->l10n )
      XSetLocaleModifiers( "" );
#endif
  }
  /*
   * check mode of x11 driver
   */
  {
    if ( (i=scan_option(argc,argv,"-gd")) )
      XBGI->gdriver = getdrivernumber( argv[i+1] );
    if ( (i=scan_option(argc,argv,"-gm")) )
      XBGI->gmode = getmodenumber( argv[i+1] );
#if 0 /* USE_DEFAULT_VISUAL */
    XBGIVisual = DefaultVisual( XBGIDisplay, XBGIScreen );
    XBGIDepth = DefaultDepth( XBGIDisplay, XBGIScreen );
    detectgraph( &(XBGI->gdriver), &(XBGI->gmode) );
    XBGIColormap = DefaultColormap( XBGIDisplay, XBGIScreen );
#else
    if ( scan_option( argc, argv, "-force-visual-" )
	|| !scan_option( argc, argv, "-force-visual" ) ) {
      XBGIVisual = DefaultVisual( XBGIDisplay, XBGIScreen );
      XBGIDepth = DefaultDepth( XBGIDisplay, XBGIScreen );
      detectgraph( &(XBGI->gdriver), &(XBGI->gmode) );
      XBGIColormap = DefaultColormap( XBGIDisplay, XBGIScreen );
    } else {
      XBGIVisual = NULL;
      detectgraph( &(XBGI->gdriver), &(XBGI->gmode) );
      XBGIColormap = DefaultColormap( XBGIDisplay, XBGIScreen );
    }
#endif
  }
  /*
   * create windows
   */
  {
    int flag_mask;
    XSizeHints def;
    XSetWindowAttributes att;
    char defgeomstr[20] = "640x400";
    char usrgeomstr[20] = "640x400";
    char titlename[80] = "";
    char iconname[80] = "";
    
    scan_option( argc, argv, "-geometry %s", usrgeomstr );
    strcpy( titlename, argv[0] );
    strcpy( iconname,  argv[0] );
    if ( scan_option( argc, argv, "-title %s", titlename ) )
      strcpy( iconname, titlename );
    scan_option( argc, argv, "-name %s", iconname );

    flag_mask = XGeometry( XBGIDisplay, XBGIScreen, usrgeomstr, defgeomstr,
                          0, 1, 1, 0, 0,
                          &def.x, &def.y, &def.width, &def.height );
#if 0 /* USE_DEFAULT_VISUAL */
    XBGIRoot = XCreateSimpleWindow( XBGIDisplay,
                                   RootWindow(XBGIDisplay,XBGIScreen),
                                   def.x, def.y, def.width, def.height, 0,
                                   WhitePixel(XBGIDisplay,XBGIScreen),
                                   BlackPixel(XBGIDisplay,XBGIScreen) );
#else
    if ( XVisualIDFromVisual(XBGIVisual) !=
        XVisualIDFromVisual(DefaultVisual(XBGIDisplay,XBGIScreen)) ) {
      XBGIColormap = XCreateColormap( XBGIDisplay,
                                     RootWindow(XBGIDisplay,XBGIScreen),
                                     XBGIVisual, AllocNone );
      att.border_pixel = WhitePixel(XBGIDisplay,XBGIScreen);
      att.background_pixel = BlackPixel(XBGIDisplay,XBGIScreen);
      att.colormap = XBGIColormap;
      XBGIRoot = XCreateWindow( XBGIDisplay,
                               RootWindow(XBGIDisplay,XBGIScreen),
                               def.x, def.y, def.width, def.height, 0,
                               XBGIDepth, InputOutput, XBGIVisual,
                               CWBorderPixel|CWBackPixel|CWColormap, &att );
      /*XInstallColormap( XBGIDisplay, XBGIColormap );*/
      /*XSetWindowColormap( XBGIDisplay, XBGIRoot, XBGIColormap );*/
    } else {
      XBGIColormap = DefaultColormap( XBGIDisplay, XBGIScreen );
      XBGIRoot = XCreateSimpleWindow( XBGIDisplay,
                                     RootWindow(XBGIDisplay,XBGIScreen),
                                     def.x, def.y, def.width, def.height, 0,
                                     WhitePixel(XBGIDisplay,XBGIScreen),
                                     BlackPixel(XBGIDisplay,XBGIScreen) );
    }
#endif
    def.min_width = 1;
    def.min_height = 1;
    def.flags = PMinSize;
    if ( flag_mask&XValue ) def.flags |= PPosition;
    if ( flag_mask&YValue ) def.flags |= USPosition;
    if ( flag_mask&WidthValue ) def.flags |= PSize;
    if ( flag_mask&HeightValue ) def.flags |= USSize;
    XSelectInput( XBGIDisplay, XBGIRoot, ExposureMask|StructureNotifyMask );
    XSetStandardProperties( XBGIDisplay, XBGIRoot,
                           titlename, iconname, None, argv, argc, &def );
    XSetWMNormalHints( XBGIDisplay, XBGIRoot, &def );
    XBGIDrawGC  = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
    XBGIFillGC  = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
    XBGIPixelGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
    XBGIImageGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
    att.backing_store = Always;
    if ( scan_option( argc, argv, "-backing"  ) )
      att.backing_store = Always;
    if ( scan_option( argc, argv, "-backing-" ) )
      att.backing_store = NotUseful;
    XBGIWins = (Window*)malloc( XBGI->npage*sizeof(Window) );
    for ( i=0; i<XBGI->npage; i++ ){
      XBGIWins[i] = XCreateSimpleWindow( XBGIDisplay, XBGIRoot,
                                        0, 0, def.width, def.height, 0,
                                        WhitePixel(XBGIDisplay,XBGIScreen),
                                        BlackPixel(XBGIDisplay,XBGIScreen) );
      XSelectInput( XBGIDisplay, XBGIWins[i], ExposureMask|
                   OwnerGrabButtonMask|ButtonPressMask|ButtonReleaseMask|
                   PointerMotionMask|ButtonMotionMask|KeyPressMask|
                   EnterWindowMask|LeaveWindowMask );
      XChangeWindowAttributes( XBGIDisplay, XBGIWins[i],
			      CWBackingStore, &att );
      XSetStandardProperties( XBGIDisplay, XBGIWins[i],
                             titlename, iconname, None, argv, argc, &def );
    }
  }
  /*
   * gc, font and color settings for work
   */
  {
    XColor exact, fg, bg, ts, bs;
    char fn_name[80] = "lucidasanstypewriter-bold-12";
    char fg_name[20] = "white";
    char bg_name[20] = "gray50";
    
    scan_option( argc, argv, "-fn %s", fn_name );
    scan_option( argc, argv, "-fg %s", fg_name );
    scan_option( argc, argv, "-bg %s", bg_name );
    XBGIDefaultGC = XCreateGC( XBGIDisplay, RootWindow(XBGIDisplay,XBGIScreen),
                              0, NULL );
    XBGIFontStruct = XLoadQueryFont( XBGIDisplay, fn_name );
    if ( XBGIFontStruct == NULL ) Warning( "X cannot find font structure" );
    else
      XSetFont( XBGIDisplay, XBGIDefaultGC, XBGIFontStruct->fid );
    XBGIForeground = (XAllocNamedColor(XBGIDisplay,
				       DefaultColormap(XBGIDisplay,XBGIScreen),
				       fg_name,&exact,&fg)!=False)?fg.pixel
					 :WhitePixel(XBGIDisplay,XBGIScreen);
    XBGIBackground = (XAllocNamedColor(XBGIDisplay,
				       DefaultColormap(XBGIDisplay,XBGIScreen),
				       bg_name,&exact,&bg)!=False)?bg.pixel
					 :BlackPixel(XBGIDisplay,XBGIScreen);
    ts.red   = min( bg.red  *5/4, 65535 );
    ts.green = min( bg.green*5/4, 65535 );
    ts.blue  = min( bg.blue *5/4, 65535 );
    bs.red   = max( 0, bg.red  *3/4 );
    bs.green = max( 0, bg.green*3/4 );
    bs.blue  = max( 0, bg.blue *3/4 );
    XBGITopShadow = (XAllocColor(XBGIDisplay,
				 DefaultColormap(XBGIDisplay,XBGIScreen),
				 &ts)!=False)?ts.pixel
				   :BlackPixel(XBGIDisplay,XBGIScreen);
    XBGIBottomShadow = (XAllocColor(XBGIDisplay,
				    DefaultColormap(XBGIDisplay,XBGIScreen),
				    &bs)!=False)?bs.pixel
				      :BlackPixel(XBGIDisplay,XBGIScreen);
    XSetForeground( XBGIDisplay, XBGIDefaultGC, XBGIForeground );
  }
  /*
   * default setting
   */
  setgraphmode( XBGI->gmode );
  graphdefaults();
  /*
   * waiting expose
   */
  {
    XEvent ev;

    XMapWindow( XBGIDisplay, XBGIRoot );
    XMapSubwindows( XBGIDisplay, XBGIRoot ); 
    do { /* bug fixed at version 2.3 */
      XNextEvent( XBGIDisplay, &ev );
    } while ( Expose != ev.type );
    XFlush( XBGIDisplay );
  }
#if 0
  /*
   * set icon from default data or file
   */
  {
#define static
#include "bitmaps/icons/xbgi_a.xbm"
#include "bitmaps/icons/xbgi_b.xbm"
#include "bitmaps/icons/xbgi_c.xbm"
#define static static
    struct xbm {
      char *bits;
      int width, height;
    } xbms[] = {
      { xbgi_c_bits, xbgi_c_width, xbgi_c_height },
      { xbgi_b_bits, xbgi_b_width, xbgi_b_height },
      { xbgi_a_bits, xbgi_a_width, xbgi_a_height },
      { NULL, 0, 0 }
    };
    char icon_filename[256] = "";
    Pixmap bm;
    
    scan_option( argc, argv, "-icon %s", icon_filename );
    if ( strcmp(icon_filename,"")==0 ){
      for ( i=0; xbms[i].bits != NULL; i++ ){
        bm = XCreateBitmapFromData( XBGIDisplay,
                                   RootWindow(XBGIDisplay,XBGIScreen),
                                   xbms[i].bits,
                                   xbms[i].width, xbms[i].height );
        if ( XSetIconFromPixmap( XBGIDisplay, XBGIRoot, bm,
                                (unsigned int)xbms[i].width,
                                (unsigned int)xbms[i].height ) != False ) {
	  XFreePixmap( XBGIDisplay, bm );
          break;
	}
      }
    } else
      seticon( icon_filename );
  }
#endif
  XBGI->gerror = grOk;
}

xbgi_procedures X11_XBGI_PROCEDURES = {
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
  xbgi_button_press,
  xbgi_button_release,
  xbgi_mouse_motion,
  xbgi_page_enter,
  xbgi_page_leave,
  xbgi_key_press,
  xbgi_configure,
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

#include <X11/Intrinsic.h>
int x11_widget_getmaxx( void )
{
  Window root;
  int x, y, width, height, border, depth;
  
  XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
               &x, &y, &width, &height, &border, &depth );
  return width-1;
}
int x11_widget_getmaxy( void )
{
  Window root;
  int x, y, width, height, border, depth;
  
  XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
               &x, &y, &width, &height, &border, &depth );
  return height-1;
}
void x11_widget_setmaxx( int maxx )
{
#if 0
  Window root;
  int x, y, width, height, border, depth;
  
  if ( maxx <= 0 ) return;
  XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
               &x, &y, &width, &height, &border, &depth );
  XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], maxx+1, height );
#endif
}
void x11_widget_setmaxy( int maxy )
{
#if 0
  Window root;
  int x, y, width, height, border, depth;

  if ( maxy <= 0 ) return;
  XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
               &x, &y, &width, &height, &border, &depth );
  XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], width, maxy+1 );
#endif
}
void x11_widget_getsizexy( int *xsize, int *ysize )
{
  Window root;
  int x, y, width, height, border, depth;
  
  XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
               &x, &y, &width, &height, &border, &depth );
  *xsize = width;
  *ysize = height;
}
void x11_widget_setsizexy( int xsize, int ysize )
{
#if 0
  int i;
  
  if ( xsize <= 0 || ysize <= 0 ) return;
  XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], xsize, ysize );
#endif
}
void x11_widget_getgeometry( int *x, int *y, int *width, int *height )
{
  Window root;
  int border, depth;
  
  XGetGeometry( XBGIDisplay, XBGIWins[XBGI->apage], &root,
               x, y, width, height, &border, &depth );
}
void x11_widget_setgeometry( int x, int y, int width, int height )
{
#if 0
  XMoveWindow( XBGIDisplay, XBGIWins[XBGI->apage], x, y );
  XResizeWindow( XBGIDisplay, XBGIWins[XBGI->apage], width, height );
#endif
}
void x11_widget__driver( void )
{
  XFreeGC( XBGIDisplay, XBGIDrawGC  );
  XFreeGC( XBGIDisplay, XBGIFillGC  );
  XFreeGC( XBGIDisplay, XBGIPixelGC );
  XFreeGC( XBGIDisplay, XBGIImageGC );

  XFreeColormap( XBGIDisplay, XBGIColormap );
  if ( XBGIFontStruct ) XFreeFont( XBGIDisplay, XBGIFontStruct );

#if 1 /* for segmentation fault, bug? fixed at version 3.01. */
  free( XBGI->inherit_members );
  XBGI->inherit_members = NULL;
#endif
}
xbgi *XbgiSimpleCreateFromWidget( Widget w )
{
  int i, j;
  extern xbgi *XBGI;
  XSetWindowAttributes att;
  
  att.backing_store = Always;
  XBGI = (xbgi*)malloc(sizeof(xbgi));
  XBGI->gdriver = X11;
  XBGI->gmode = X11SCOLOR;
  XBGI->gerror = grNoInitGraph;
  XBGI->ncolor = 16;
  XBGI->color = XBGI->ncolor-1;
  XBGI->bkcolor = 0;
  XBGI->npage = 1;
  XBGI->apage = 0;
  XBGI->vpage = 0;
  XBGI->l10n = !0;
  XBGI->colornames = 0;
  XBGI->palette.size = (unsigned char)XBGI->ncolor-1;

  XBGI->inherit_procedures
    = (xbgi_procedures*)malloc(sizeof(xbgi_procedures));
  *XBGI->inherit_procedures = X11_XBGI_PROCEDURES;
#undef getmaxx
#undef getmaxy
#undef setmaxx
#undef setmaxy
#undef setsizexy
#undef getsizexy
#undef setgeometry
#undef getgeometry
#undef _driver
  XBGI->inherit_procedures->getmaxx = x11_widget_getmaxx;
  XBGI->inherit_procedures->getmaxy = x11_widget_getmaxy;
  XBGI->inherit_procedures->setmaxx = x11_widget_setmaxx;
  XBGI->inherit_procedures->setmaxy = x11_widget_setmaxy;
  XBGI->inherit_procedures->setsizexy = x11_widget_setsizexy;
  XBGI->inherit_procedures->getsizexy = x11_widget_getsizexy;
  XBGI->inherit_procedures->setgeometry = x11_widget_setgeometry;
  XBGI->inherit_procedures->getgeometry = x11_widget_getgeometry;
  XBGI->inherit_procedures->_driver = x11_widget__driver;
  XBGI->inherit_members = malloc( sizeof(x11_xbgi) );

  XBGIDisplay = XtDisplay( w );
  XBGIVisual = DefaultVisual( XBGIDisplay, XBGIScreen );
  XBGIDepth = DefaultDepth( XBGIDisplay, XBGIScreen );
  XBGIColormap = DefaultColormap( XBGIDisplay, XBGIScreen );
  XBGIDefaultGC =
    XCreateGC( XBGIDisplay, RootWindow(XBGIDisplay,XBGIScreen), 0, NULL );
  XBGIRoot = RootWindow(XBGIDisplay,XBGIScreen);
  XBGIDrawGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIFillGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIPixelGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIImageGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIWins = (Window*)malloc( XBGI->npage*sizeof(Window) );
  XBGIWins[0] = XtWindow( w );
  XSelectInput( XBGIDisplay, XBGIWins[0], ExposureMask|
               OwnerGrabButtonMask|ButtonPressMask|ButtonReleaseMask|
               PointerMotionMask|ButtonMotionMask|KeyPressMask|
               EnterWindowMask|LeaveWindowMask );
  XChangeWindowAttributes( XBGIDisplay, XBGIWins[0], CWBackingStore, &att );
  for ( i=DEFAULT_FONT; i<=MAX_CHAR_FONT; i++ )
    for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
      XBGIStrokeFonts[i][j] = NULL;
  for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
    XBGIBiFonts[j] = NULL;
  for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
    XBGIMultiFonts[j] = NULL;
  setgraphmode( XBGI->gmode );
  graphdefaults();
  XBGI->gerror = grOk;
  return XBGI;
}
xbgi *XbgiMonoCreateFromWidget( Widget w )
{
  int i, j;
  extern xbgi *XBGI;
  XSetWindowAttributes att;
  
  att.backing_store = Always;
  XBGI = (xbgi*)malloc(sizeof(xbgi));
  XBGI->gdriver = X11;
  XBGI->gmode = X11MONO;
  XBGI->gerror = grNoInitGraph;
  XBGI->ncolor = 2;
  XBGI->color = XBGI->ncolor-1;
  XBGI->bkcolor = 0;
  XBGI->npage = 1;
  XBGI->apage = 0;
  XBGI->vpage = 0;
  XBGI->l10n = !0;
  XBGI->colornames = 0;
  XBGI->palette.size = (unsigned char)XBGI->ncolor-1;

  XBGI->inherit_procedures
    = (xbgi_procedures*)malloc(sizeof(xbgi_procedures));
  *XBGI->inherit_procedures = X11_XBGI_PROCEDURES;
#undef getmaxx
#undef getmaxy
#undef setmaxx
#undef setmaxy
#undef setsizexy
#undef getsizexy
#undef setgeometry
#undef getgeometry
#undef _driver
  XBGI->inherit_procedures->getmaxx = x11_widget_getmaxx;
  XBGI->inherit_procedures->getmaxy = x11_widget_getmaxy;
  XBGI->inherit_procedures->setmaxx = x11_widget_setmaxx;
  XBGI->inherit_procedures->setmaxy = x11_widget_setmaxy;
  XBGI->inherit_procedures->setsizexy = x11_widget_setsizexy;
  XBGI->inherit_procedures->getsizexy = x11_widget_getsizexy;
  XBGI->inherit_procedures->setgeometry = x11_widget_setgeometry;
  XBGI->inherit_procedures->getgeometry = x11_widget_getgeometry;
  XBGI->inherit_procedures->_driver = x11_widget__driver;
  XBGI->inherit_members = malloc( sizeof(x11_xbgi) );

  XBGIDisplay = XtDisplay( w );
  XBGIVisual = DefaultVisual( XBGIDisplay, XBGIScreen );
  XBGIDepth = DefaultDepth( XBGIDisplay, XBGIScreen );
  XBGIColormap = DefaultColormap( XBGIDisplay, XBGIScreen );
  XBGIDefaultGC =
    XCreateGC( XBGIDisplay, RootWindow(XBGIDisplay,XBGIScreen), 0, NULL );
  XBGIRoot = RootWindow(XBGIDisplay,XBGIScreen);
  XBGIDrawGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIFillGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIPixelGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIImageGC = XCreateGC( XBGIDisplay, XBGIRoot, 0, NULL );
  XBGIWins = (Window*)malloc( XBGI->npage*sizeof(Window) );
  XBGIWins[0] = XtWindow( w );
  XSelectInput( XBGIDisplay, XBGIWins[0], ExposureMask|
               OwnerGrabButtonMask|ButtonPressMask|ButtonReleaseMask|
               PointerMotionMask|ButtonMotionMask|KeyPressMask|
               EnterWindowMask|LeaveWindowMask );
  XChangeWindowAttributes( XBGIDisplay, XBGIWins[0], CWBackingStore, &att );
  for ( i=DEFAULT_FONT; i<=MAX_CHAR_FONT; i++ )
    for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
      XBGIStrokeFonts[i][j] = NULL;
  for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
    XBGIBiFonts[j] = NULL;
  for ( j=USER_CHAR_SIZE; j<=MAX_CHAR_SIZE; j++ )
    XBGIMultiFonts[j] = NULL;
  setgraphmode( XBGI->gmode );
  graphdefaults();
  XBGI->gerror = grOk;
  return XBGI;
}



