/*
 * Source File < ps/misc.c >
 *
 * Misc Functions for PS: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"
#include "script/abbrev.def"
#include "script/prolog.def"
#include "script/trailer.def"
#include "script/begin.def"
#include "script/end.def"

#ifndef DefaultInterpName
#  define DefaultInterpName "gs -"
#endif
#ifndef DefaultFileName
#  define DefaultFileName "scratch.ps"
#endif

void ps_xbgi_flush( void )
{
  if ( PSBGIInterpP ) fflush( PSBGIInterpP );
  if ( PSBGIFileP   ) if ( PSBGIFileP == stdout ) fflush( PSBGIFileP );
}
void ps_xbgi_vprintf( char *fmt, va_list argptr )
{
  if ( PSBGIInterpP ) vfprintf( PSBGIInterpP, fmt, argptr );
  if ( PSBGIFileP   ) vfprintf( PSBGIFileP,   fmt, argptr );
}
void ps_xbgi_printf( char *fmt, ... )
{
  va_list argptr;
  
  va_start( argptr, fmt );
  ps_xbgi_vprintf( fmt, argptr );
  va_end( argptr );
}
void ps_xbgi_open( void )
{
  char buf[256];
  time_t now;
  struct tm *now_tm;
  char tm_stamp[64];

  time( &now );
  now_tm = localtime( &now );
  strftime( tm_stamp, 64, "%a %h %d %T %Y", now_tm );

  if ( PSBGIUseInterp ){
    if ( strcmp(PSBGIInterpName,"")==0 )
      strcpy( PSBGIInterpName, DefaultInterpName );
    PSBGIInterpP = popen( PSBGIInterpName, "w" );
    if ( PSBGIInterpP == NULL ){
      sprintf( buf, "cannot open pipe (%s).", PSBGIInterpName );
      if ( !PSBGIUseFile )
        FatalError( buf );
      else{
        Warning( buf );
        PSBGIInterpP = NULL;
        PSBGIUseInterp = 0;
      }
    }
  }else{
    PSBGIInterpP = NULL;
  }
  if ( PSBGIUseFile ){
    if ( strcmp(PSBGIFileName,"")==0 )
      strcpy( PSBGIFileName, DefaultFileName );
    PSBGIFileP = fopen( PSBGIFileName, "w" );
    if ( PSBGIFileP == NULL ){
      sprintf( buf, "cannot open file (%s).", PSBGIFileName );
      if ( !PSBGIUseInterp )
        FatalError( buf );
      else{
        Warning( buf );
        PSBGIFileP = NULL;
        PSBGIUseFile = 0;
      }
    }
  }else{
    PSBGIFileP = stdout;
    PSBGIUseFile = !0;
    strcpy( PSBGIFileName, "(stdout)" );
  }
  if ( PSBGIEncapsule ) {
    ps_xbgi_printf( "%%!PS-Adobe-3.0 EPSF-3.0\n" );
    if ( PSBGICoordinate.orientation == 0 )
      ps_xbgi_printf( "%%%%BoundingBox: %d %d %d %d\n",
                     BBX, BBY, BBX+PSBGIRoot.width, BBY+PSBGIRoot.height );
    else
      ps_xbgi_printf( "%%%%BoundingBox: %d %d %d %d\n",
                     BBX, BBY, BBX+PSBGIRoot.height, BBY+PSBGIRoot.width );
  } else {
    ps_xbgi_printf( "%%!PS-Adobe-3.0\n" );
    if ( PSBGICoordinate.page_width==0 || PSBGICoordinate.page_height==0 )
      if ( PSBGICoordinate.orientation == 0 )
        ps_xbgi_printf( "%%%%BoundingBox: %d %d %d %d\n",
                       (int)(PSBGICoordinate.x),
                       (int)(PSBGICoordinate.y),
                       (int)(PSBGICoordinate.x
                             + PSBGIRoot.width*PSBGICoordinate.factor),
                       (int)(PSBGICoordinate.y
                             + PSBGIRoot.height*PSBGICoordinate.factor) );
      else
        ps_xbgi_printf( "%%%%BoundingBox: %d %d %d %d\n",
                       (int)(PSBGICoordinate.x),
                       (int)(PSBGICoordinate.y),
                       (int)(PSBGICoordinate.x
                             + PSBGIRoot.height*PSBGICoordinate.factor),
                       (int)(PSBGICoordinate.y
                             + PSBGIRoot.width*PSBGICoordinate.factor) );
    else {
      double factor_x = 1, factor_y = 1;

      if ( PSBGICoordinate.page_width!=0 &&
          PSBGICoordinate.page_width < PSBGIRoot.width )
        factor_x = (double)PSBGICoordinate.page_width/PSBGIRoot.width;
      if ( PSBGICoordinate.page_height!=0 &&
          PSBGICoordinate.page_height < PSBGIRoot.height )
        factor_y = (double)PSBGICoordinate.page_height/PSBGIRoot.height;
      PSBGICoordinate.factor = min(factor_x,factor_y);
      if ( PSBGICoordinate.orientation == 0 ) {
        if ( PSBGICoordinate.page_width != 0 )
          PSBGICoordinate.x
            = (PSBGICoordinate.page_width
               - (double)PSBGIRoot.width*PSBGICoordinate.factor)/2;
        else
          PSBGICoordinate.x = 0;
        if ( PSBGICoordinate.page_height != 0 )
          PSBGICoordinate.y
            = (PSBGICoordinate.page_height
               - (double)PSBGIRoot.height*PSBGICoordinate.factor)/2;
        else
          PSBGICoordinate.y = 0;
        ps_xbgi_printf( "%%%%BoundingBox: %d %d %d %d\n",
                       (int)(PSBGICoordinate.x),
                       (int)(PSBGICoordinate.y),
                       (int)(PSBGICoordinate.x
                             + PSBGIRoot.width*PSBGICoordinate.factor),
                       (int)(PSBGICoordinate.y
                             + PSBGIRoot.height*PSBGICoordinate.factor) );
      } else {
        if ( PSBGICoordinate.page_width != 0 )
          PSBGICoordinate.y
            = (PSBGICoordinate.page_width
               - (double)PSBGIRoot.width*PSBGICoordinate.factor)/2;
        else
          PSBGICoordinate.y = 0;
        if ( PSBGICoordinate.page_height != 0 )
          PSBGICoordinate.x
            = (PSBGICoordinate.page_height
               - (double)PSBGIRoot.height*PSBGICoordinate.factor)/2;
        else
          PSBGICoordinate.x = 0;
        ps_xbgi_printf( "%%%%BoundingBox: %d %d %d %d\n",
                       (int)(PSBGICoordinate.x),
                       (int)(PSBGICoordinate.y),
                       (int)(PSBGICoordinate.x
                             + PSBGIRoot.height*PSBGICoordinate.factor),
                       (int)(PSBGICoordinate.y
                             + PSBGIRoot.width*PSBGICoordinate.factor) );
      }
    }  
  }
  ps_xbgi_printf( "%%%%Title: %s\n", PSBGITitle );
  ps_xbgi_printf( "%%%%CreationDate: %s\n", tm_stamp );
  ps_xbgi_printf( "%%%%Creator: %s\n",
                 "XBGI(PS) by Taiji Yamada (taiji@aihara.co.jp)" );
  if ( PSBGIEncapsule )
    ps_xbgi_printf( "%%%%Pages: %d\n", 1 );
  else {
    ps_xbgi_printf( "%%%%Pages: (attend)\n" );
    if ( PSBGICoordinate.orientation == 0 )
      ps_xbgi_printf( "%%%%DocumentMedia: %s %d %d 0 white ()\n",
		     PSBGICoordinate.tag,
		     PSBGICoordinate.page_width, PSBGICoordinate.page_height );
    else
      ps_xbgi_printf( "%%%%DocumentMedia: %s %d %d 0 white ()\n",
		     PSBGICoordinate.tag,
		     PSBGICoordinate.page_height, PSBGICoordinate.page_width );
  }
  if ( PSBGICoordinate.orientation == 0 )
    ps_xbgi_printf( "%%%%Orientation: Portrait\n" );
  else
    ps_xbgi_printf( "%%%%Orientation: Landscape\n" );
  ps_xbgi_printf( "%%%%EndComments\n" );
  ps_xbgi_printf( PROLOG );
}
void ps_xbgi_close( void )
{
  cleardevice();
  ps_xbgi_printf( TRAILER );
  if ( PSBGIInterpP ) pclose( PSBGIInterpP );
  if ( PSBGIFileP   ) if ( PSBGIFileP != stdout ) fclose( PSBGIFileP );
}
void ps_xbgi_put_linewidth( double width )
{
  if ( PSBGIState.linewidth == width )
    ;
  else {
    PSBGIState.linewidth = width;
    ps_xbgi_printf( "%g "SETLINEWIDTH"\n", PSBGIState.linewidth );
  }
}
void ps_xbgi_put_linecap( int type )
{
  if ( PSBGIState.linecap == type )
    ;
  else {
    PSBGIState.linecap = type;
    ps_xbgi_printf( "%d "SETLINECAP"\n", PSBGIState.linecap );
  }
}
void ps_xbgi_put_linejoin( int type )
{
  if ( PSBGIState.linejoin == type )
    ;
  else {
    PSBGIState.linejoin = type;
    ps_xbgi_printf( "%d "SETLINEJOIN"\n", PSBGIState.linejoin );
  }
}
void ps_xbgi_put_miterlimit( double ratio )
{
  if ( PSBGIState.miterlimit == ratio )
    ;
  else {
    PSBGIState.miterlimit = ratio;
    ps_xbgi_printf( "%g "SETMITERLIMIT"\n", PSBGIState.miterlimit );
  }
}
void ps_xbgi_put_dash( char *pattern, int offset )
{
  if ( strcmp(PSBGIState.dash,pattern) == 0 )
    ;
  else {
    strcpy(PSBGIState.dash,pattern);
    PSBGIState.dash_offset = offset;
    ps_xbgi_printf( "%s %d "SETDASH"\n",
                   PSBGIState.dash, PSBGIState.dash_offset );
  }
}
void ps_xbgi_put_rgbcolor( double red, double green, double blue )
{
  if ( PSBGIState.color.red == red
      && PSBGIState.color.green == green
      && PSBGIState.color.blue == blue )
    ;
  else {
    PSBGIState.color.red = red;
    PSBGIState.color.green = green;
    PSBGIState.color.blue = blue;
    ps_xbgi_printf( "%g %g %g "SETRGBCOLOR"\n", PSBGIState.color.red,
                   PSBGIState.color.green, PSBGIState.color.blue );
  }
}
void ps_xbgi_put_gray( double brightness )
{
  if ( PSBGIState.color.red == brightness
      && PSBGIState.color.green == brightness
      && PSBGIState.color.blue == brightness )
    ;
  else {
    PSBGIState.color.red = PSBGIState.color.green = PSBGIState.color.blue
      = brightness;
    ps_xbgi_printf( "%g "SETGRAY"\n", PSBGIState.color.red );
  }
}
void ps_xbgi_put_color( int color )
{
  Color rgb = PSBGIRGB[XBGI->palette.colors[color]];
  
  switch ( XBGI->gmode ){
  case PSMONO:
    if ( color != XBGI->bkcolor )
      ps_xbgi_put_gray( 0 );
    else
      ps_xbgi_put_gray( 1 );
    break;
  case PSGRAY:
    ps_xbgi_put_gray( (rgb.red+rgb.green+rgb.blue)/3 );
    break;
  case PSCOLOR: default:
    ps_xbgi_put_rgbcolor( rgb.red, rgb.green, rgb.blue );
    break;
  }
}
void ps_xbgi_put_fillpat( char *pattern, int size )
{
  if ( strcmp(PSBGIState.fillpat,pattern)==0 && PSBGIState.fillpatsz==size )
    ;
  else {
    strcpy(PSBGIState.fillpat,pattern);
    PSBGIState.fillpatsz = size;
    ps_xbgi_printf( "/PAT %s def /PATSZ %d def\n",
                   PSBGIState.fillpat, PSBGIState.fillpatsz );
  }
}
void ps_xbgi_begin( char *name )
{
  if ( !PSBGIRoot.drawn ){
    ps_xbgi_printf( "%%%%Page: %d %d\n",
                   PSBGIRoot.showpage_count+1, PSBGIRoot.showpage_count+1 );
    if ( PSBGIEncapsule )
      if ( PSBGICoordinate.orientation == 0 )
        ps_xbgi_printf( "%%%%PageBoundingBox: %d %d %d %d\n",
                       BBX, BBY, BBX+PSBGIRoot.width, BBY+PSBGIRoot.height );
      else
        ps_xbgi_printf( "%%%%PageBoundingBox: %d %d %d %d\n",
                       BBX, BBY, BBX+PSBGIRoot.height, BBY+PSBGIRoot.width );
    else
      if ( PSBGICoordinate.page_width==0 || PSBGICoordinate.page_height==0 )
        if ( PSBGICoordinate.orientation == 0 )
          ps_xbgi_printf( "%%%%PageBoundingBox: %d %d %d %d\n",
                         (int)(PSBGICoordinate.x),
                         (int)(PSBGICoordinate.y),
                         (int)(PSBGICoordinate.x
                               + PSBGIRoot.width*PSBGICoordinate.factor),
                         (int)(PSBGICoordinate.y
                               + PSBGIRoot.height*PSBGICoordinate.factor) );
        else
          ps_xbgi_printf( "%%%%PageBoundingBox: %d %d %d %d\n",
                         (int)(PSBGICoordinate.x),
                         (int)(PSBGICoordinate.y),
                         (int)(PSBGICoordinate.x
                               + PSBGIRoot.height*PSBGICoordinate.factor),
                         (int)(PSBGICoordinate.y
                               + PSBGIRoot.width*PSBGICoordinate.factor) );
      else {
        double factor_x = 1, factor_y = 1;
        
        if ( PSBGICoordinate.page_width!=0 &&
            PSBGICoordinate.page_width < PSBGIRoot.width )
          factor_x = (double)PSBGICoordinate.page_width/PSBGIRoot.width;
        if ( PSBGICoordinate.page_height!=0 &&
            PSBGICoordinate.page_height < PSBGIRoot.height )
          factor_y = (double)PSBGICoordinate.page_height/PSBGIRoot.height;
        PSBGICoordinate.factor = min(factor_x,factor_y);
	if ( PSBGICoordinate.orientation == 0 ) {
	  if ( PSBGICoordinate.page_width != 0 )
	    PSBGICoordinate.x
	      = (PSBGICoordinate.page_width
		 - (double)PSBGIRoot.width*PSBGICoordinate.factor)/2;
	  else
	    PSBGICoordinate.x = 0;
	  if ( PSBGICoordinate.page_height != 0 )
	    PSBGICoordinate.y
	      = (PSBGICoordinate.page_height
		 - (double)PSBGIRoot.height*PSBGICoordinate.factor)/2;
	  else
	    PSBGICoordinate.y = 0;
	  ps_xbgi_printf( "%%%%PageBoundingBox: %d %d %d %d\n",
			 (int)(PSBGICoordinate.x),
			 (int)(PSBGICoordinate.y),
			 (int)(PSBGICoordinate.x
			       + PSBGIRoot.width*PSBGICoordinate.factor),
			 (int)(PSBGICoordinate.y
			       + PSBGIRoot.height*PSBGICoordinate.factor) );
	} else {
	  if ( PSBGICoordinate.page_width != 0 )
	    PSBGICoordinate.y
	      = (PSBGICoordinate.page_width
		 - (double)PSBGIRoot.width*PSBGICoordinate.factor)/2;
	  else
	    PSBGICoordinate.y = 0;
	  if ( PSBGICoordinate.page_height != 0 )
	    PSBGICoordinate.x
	      = (PSBGICoordinate.page_height
		 - (double)PSBGIRoot.height*PSBGICoordinate.factor)/2;
	  else
	    PSBGICoordinate.x = 0;
	  ps_xbgi_printf( "%%%%PageBoundingBox: %d %d %d %d\n",
			 (int)(PSBGICoordinate.x),
			 (int)(PSBGICoordinate.y),
			 (int)(PSBGICoordinate.x
			       + PSBGIRoot.height*PSBGICoordinate.factor),
			 (int)(PSBGICoordinate.y
			       + PSBGIRoot.width*PSBGICoordinate.factor) );
	}
      }
    ps_xbgi_printf( BEGIN );
    if ( PSBGIEncapsule )
      if ( PSBGICoordinate.orientation == 0 )
	ps_xbgi_printf( "%d %d translate\n", BBX, BBY );
      else {
	ps_xbgi_printf( "%d %d translate\n", BBX, BBY );
	ps_xbgi_printf( "90 rotate 0 %d neg translate\n", PSBGIRoot.height );
      }
    else {
      if ( PSBGICoordinate.orientation == 0 )
	ps_xbgi_printf( "%g %g translate %g %g scale\n",
		       PSBGICoordinate.x, PSBGICoordinate.y,
		       PSBGICoordinate.factor, PSBGICoordinate.factor );
      else {
	ps_xbgi_printf( "%g %g translate %g %g scale\n",
		       PSBGICoordinate.x, PSBGICoordinate.y,
		       PSBGICoordinate.factor, PSBGICoordinate.factor );
	ps_xbgi_printf( "90 rotate 0 %d neg translate\n", PSBGIRoot.height );
      }
    }
    ps_xbgi_printf( ""GSAVE"\n" );
    ps_xbgi_printf( "%g "SETLINEWIDTH"\n", PSBGIState.linewidth );
    ps_xbgi_printf( "%d "SETLINECAP"\n", PSBGIState.linecap );
    ps_xbgi_printf( "%d "SETLINEJOIN"\n", PSBGIState.linejoin );
    ps_xbgi_printf( "%g "SETMITERLIMIT"\n", PSBGIState.miterlimit );
    ps_xbgi_printf( "%s %d "SETDASH"\n",
                   PSBGIState.dash, PSBGIState.dash_offset );
    switch ( XBGI->gmode ){
    case PSMONO:
      if ( XBGI->color != XBGI->bkcolor )
        ps_xbgi_printf( "%g "SETGRAY"\n", 0 );
      else
        ps_xbgi_printf( "%g "SETGRAY"\n", 1 );
      break;
    case PSGRAY:
      ps_xbgi_printf( "%g "SETGRAY"\n", PSBGIState.color.red );
      break;
    case PSCOLOR: default:
      ps_xbgi_printf( "%g %g %g "SETRGBCOLOR"\n", PSBGIState.color.red,
                     PSBGIState.color.green, PSBGIState.color.blue );
      break;
    }
    ps_xbgi_printf( "/PAT %s def /PATSZ %d def\n",
                   PSBGIState.fillpat, PSBGIState.fillpatsz );
  }
  /*ps_xbgi_printf( "%% begin %s\n", name );*/ /* for readable script */
}
void ps_xbgi_end( char *name )
{
  /*ps_xbgi_printf( "%% end %s\n", name );*/ /* for readable script */
  ps_xbgi_flush();
  PSBGIRoot.drawn = !0;
}
void ps_xbgi_showpage( void )
{
  if ( PSBGIRoot.drawn ){
    ps_xbgi_printf( ""GRESTORE"\n" );
    ps_xbgi_printf( END );
    if ( !PSBGIEncapsule )
      ps_xbgi_printf( "showpage\n" );
    PSBGIRoot.drawn = 0;
    PSBGIRoot.showpage_count++;
  }
}
void ps_xbgi_put_string( char *string, int len )
{
  int i;

  for ( i=0; i<len; i++ ){
    switch( string[i] ){
    case '\\':
    case '(':
    case ')':
      ps_xbgi_printf( "\\%c", string[i] );
      break;
    default:
      if ( isprint(string[i]) ) /* ! */
        ps_xbgi_printf( "%c", string[i] );
      break;
    }
  }
}
