/*
 * Source File < ps/textinfo.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

static FontStruct FONTNAME[MAX_CHAR_FONT+1][MAX_CHAR_SIZE+1] = {
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

#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
static FontStruct BFONTNAME[MAX_CHAR_SIZE+1] = {
#include "fonts/jdef.chr"
};
#endif

/*
 * standard functions to get and set text settings
 */
int textheight( char *textstring )
{
  int font = XBGI->textset.font;
  int size = XBGI->textset.charsize;

  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    return TextHeight( PSBGIStrokeFonts[font][size] );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    return TextHeight( PSBGIStrokeFonts[font][size] );
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
    return max( TextHeight( PSBGIStrokeFonts[font][size] ),
	       TextHeight( PSBGIBiFonts[size] ) );
#endif
  }
}
int textwidth( char *textstring )
{
  int font = XBGI->textset.font;
  int size = XBGI->textset.charsize;

  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    return TextWidth( PSBGIStrokeFonts[font][size],
                     textstring, strlen(textstring) );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    return TextWidth( PSBGIStrokeFonts[font][size],
                     textstring, strlen(textstring) );
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
    return ps_xbgi_bi_text_width( textstring, strlen(textstring) );
#endif
  }
}
void gettextsettings( struct textsettingstype *texttypeinfo )
{
  *texttypeinfo = XBGI->textset;
}
void settextstyle( int font, int direction, int charsize )
{
  font      = minmax( DEFAULT_FONT, font, MAX_CHAR_FONT );
  direction = minmax( HORIZ_DIR, direction, VERT_DIR );
  charsize  = minmax( USER_CHAR_SIZE, charsize, MAX_CHAR_SIZE );
  XBGI->textset.font      = font;
  XBGI->textset.direction = direction;
  XBGI->textset.charsize  = charsize;
  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    if ( PSBGIStrokeFonts[font][charsize] == NULL ){
      PSBGIStrokeFonts[font][charsize] = &FONTNAME[font][charsize];
    }
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    if ( PSBGIStrokeFonts[font][charsize] == NULL ){
      PSBGIStrokeFonts[font][charsize] = &FONTNAME[font][charsize];
    }
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
    if ( PSBGIStrokeFonts[font][charsize] == NULL
	&& PSBGIBiFonts[charsize] == NULL ) {
      if ( PSBGIStrokeFonts[font][charsize] == NULL ) {
	PSBGIStrokeFonts[font][charsize] = &FONTNAME[font][charsize];
      }
      if ( PSBGIBiFonts[charsize] == NULL ) {
	PSBGIBiFonts[charsize] = &BFONTNAME[charsize];
      }
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





