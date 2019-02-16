/*
 * Source File < x11/textinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "x11_p.h"

static char *FONTNAME[MAX_CHAR_FONT+1][MAX_CHAR_SIZE+1] = {
#include "fonts/adef.chr"
#include "fonts/trip.chr"
#include "fonts/litt.chr"
#include "fonts/sans.chr"
#include "fonts/goth.chr"
#include "fonts/scri.chr"
#include "fonts/simp.chr"
#include "fonts/tscr.chr"
#include "fonts/lcom.chr"
#include "fonts/euro.chr"
#include "fonts/bold.chr"
};

#ifdef ENABLE_BILINGUAL
static char *BFONTNAME[MAX_CHAR_SIZE+1] = {
#include "fonts/jdef.chr"
};
#endif

#ifdef ENABLE_MULTILINGUAL
static char *FONTSETNAME[MAX_CHAR_SIZE+1] = {
#include "fonts/mdef.chr"
};
#endif

/*
 * standard functions to get and set text settings
 */
int textheight( char *textstring )
{
  int font = XBGI->textset.font;
  int size = XBGI->textset.charsize;
#ifdef ENABLE_MULTILINGUAL
  XRectangle ink, log;
#endif

  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    return TextHeight( XBGIStrokeFonts[font][size] );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    return TextHeight( XBGIStrokeFonts[font][size] );
#endif
#ifdef ENABLE_BILINGUAL
    return max( TextHeight( XBGIStrokeFonts[font][size] ),
	       TextHeight( XBGIBiFonts[size] ) );
#endif
#ifdef ENABLE_MULTILINGUAL
    if ( XBGIMultiFonts[size] ){
      XmbTextExtents( XBGIMultiFonts[size],
                     textstring, strlen(textstring), &ink, &log );
      /*return ink.height;*/ /* version 3.0 */
      return log.height; /* version 3.01 */
    }else{
      return TextHeight( XBGIStrokeFonts[font][size] );
    }
#endif
  }
}
int textwidth( char *textstring )
{
  int font = XBGI->textset.font;
  int size = XBGI->textset.charsize;

  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    return TextWidth( XBGIStrokeFonts[font][size],
                     textstring, strlen(textstring) );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    return TextWidth( XBGIStrokeFonts[font][size],
                     textstring, strlen(textstring) );
#endif
#ifdef ENABLE_BILINGUAL
    return XBiTextWidth( XBGIStrokeFonts[font][size], XBGIBiFonts[size],
                        textstring, strlen(textstring) );
#endif
#ifdef ENABLE_MULTILINGUAL
    if ( XBGIMultiFonts[size] ){
      XRectangle ink, log;
      
      XmbTextExtents( XBGIMultiFonts[size],
                     textstring, strlen(textstring), &ink, &log );
      /*return ink.width;*/ /* version 3.0 */
      return log.width; /* version 3.01 */
    }else{
      return TextWidth( XBGIStrokeFonts[font][size],
                       textstring, strlen(textstring) );
    }
#endif
  }
}
void gettextsettings( struct textsettingstype *texttypeinfo )
{
  *texttypeinfo = XBGI->textset;
}
void settextstyle( int font, int direction, int charsize )
{
#ifdef ENABLE_MULTILINGUAL
  char **miss, *def;
  int n_miss;
#endif    

  font      = minmax( DEFAULT_FONT, font, MAX_CHAR_FONT );
  direction = minmax( HORIZ_DIR, direction, VERT_DIR );
  charsize  = minmax( USER_CHAR_SIZE, charsize, MAX_CHAR_SIZE );
  XBGI->textset.font      = font;
  XBGI->textset.direction = direction;
  XBGI->textset.charsize  = charsize;
  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    if ( XBGIStrokeFonts[font][charsize] == NULL ){
      XBGIStrokeFonts[font][charsize]
        = XLoadQueryFont( XBGIDisplay, FONTNAME[font][charsize] );
    }
    if ( XBGIStrokeFonts[font][charsize] != NULL )
      XSetFont( XBGIDisplay, XBGIDrawGC,
	       XBGIStrokeFonts[font][charsize]->fid );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    if ( XBGIStrokeFonts[font][charsize] == NULL ){
      XBGIStrokeFonts[font][charsize]
        = XLoadQueryFont( XBGIDisplay, FONTNAME[font][charsize] );
    }
    if ( XBGIStrokeFonts[font][charsize] != NULL )
      XSetFont( XBGIDisplay, XBGIDrawGC,
	       XBGIStrokeFonts[font][charsize]->fid );
#endif
#ifdef ENABLE_BILINGUAL
    if ( XBGIBiFonts[charsize] == NULL ){
      XBGIBiFonts[charsize]
        = XLoadQueryFont( XBGIDisplay, BFONTNAME[charsize] );
    }
    if ( XBGIStrokeFonts[font][charsize] == NULL ){
      XBGIStrokeFonts[font][charsize]
        = XLoadQueryFont( XBGIDisplay, FONTNAME[font][charsize] );
    }
#endif
#ifdef ENABLE_MULTILINGUAL
    if ( XBGIMultiFonts[charsize] == NULL ){
      XBGIMultiFonts[charsize]
        = XCreateFontSet( XBGIDisplay, FONTSETNAME[charsize],
			 &miss, &n_miss, &def );
#if 0
      {
	int i;

	printf( "n_miss: %d\n", n_miss );
	for ( i=0; i<n_miss; i++ )
	  printf( "%s\n", miss[i] );
	printf( "def: %s\n", def );
      } 
#endif
      if ( n_miss != 0 )
        XBGIMultiFonts[charsize] = NULL;
    }
#endif
  }
}
void settextjustify( int horiz, int vert )
{
  XBGI->textset.horiz = minmax( LEFT_TEXT, horiz, RIGHT_TEXT );
  XBGI->textset.vert  = minmax( BOTTOM_TEXT, vert, TOP_TEXT );
}
void setusercharsize( int multx, int divx, int multy, int divy )
{
  ReservedFuture( "setusercharsize()" );
}
int installuserfont( char *name )
{
  ReservedFuture( "installuserfont()" );
  return -1;
}
int registerbgifont( void (*font)(void) )
{
  ReservedFuture( "registerbgifont()" );
  return grOk;
}
int registerfarbgifont( void *font )
{
  ReservedFuture( "registerfarbgifont()" );
  return grOk;
}





