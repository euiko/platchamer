/*
 * Source File < ps/text.c >
 *
 * Standard Functions: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "ps_p.h"

/*
 * standard function to out text on graphics
 */
void _outtextxy( double x, double y, char *textstring );
void outtext( char *textstring )
{
  _outtextxy( XBGI->cp.x, XBGI->cp.y, textstring );
  moverel( (XBGI->textset.direction==HORIZ_DIR)?textwidth(textstring):0,
          (XBGI->textset.direction==VERT_DIR)?textwidth(textstring):0 );
}
void outtextxy( int x, int y, char *textstring )
{
  _outtextxy( x, y, textstring );
}
/*
 * extented functions for high-quality graphics
 */
void _outtextxy( double x, double y, char *textstring )
{
  int font = XBGI->textset.font;
  int dir  = XBGI->textset.direction;
  int size = XBGI->textset.charsize;
  int /*width = textwidth(textstring),*/ height = textheight(textstring);

  switch ( dir ){
  case VERT_DIR:
    /*
     * vertical direction
     */
    if ( !XBGI->l10n || font != DEFAULT_FONT ){
      switch( XBGI->textset.horiz ){
      case LEFT_TEXT:
        x += TextAscent( PSBGIStrokeFonts[font][size] );
        break;
      case CENTER_TEXT:
        x += height/2;
        break;
      case RIGHT_TEXT:
        x -= TextDescent( PSBGIStrokeFonts[font][size] );
        break;
      }
    }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
      switch( XBGI->textset.horiz ){
      case LEFT_TEXT:
        x += TextAscent( PSBGIStrokeFonts[font][size] );
        break;
      case CENTER_TEXT:
        x += height/2;
        break;
      case RIGHT_TEXT:
        x -= TextDescent( PSBGIStrokeFonts[font][size] );
        break;
      }
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
      switch( XBGI->textset.horiz ){
      case LEFT_TEXT:
        x += max( TextAscent( PSBGIStrokeFonts[font][size] ),
                 TextAscent( PSBGIBiFonts[size] ) );
        break;
      case CENTER_TEXT:
        x += height/2;
        break;
      case RIGHT_TEXT:
        x += max( TextDescent( PSBGIStrokeFonts[font][size] ),
                 TextDescent( PSBGIBiFonts[size] ) );
        break;
      }
#endif
    }
  case HORIZ_DIR:
    /*
     * horizontal direction
     */
    if ( !XBGI->l10n || font != DEFAULT_FONT ){
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += TextAscent( PSBGIStrokeFonts[font][size] );
        break;
      case CENTER_TEXT:
        y += height/2;
        break;
      case BOTTOM_TEXT:
        y -= TextDescent( PSBGIStrokeFonts[font][size] );
        break;
      }
    }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += TextAscent( PSBGIStrokeFonts[font][size] );
        break;
      case CENTER_TEXT:
        y += height/2;
        break;
      case BOTTOM_TEXT:
        y -= TextDescent( PSBGIStrokeFonts[font][size] );
        break;
      }
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
      switch( XBGI->textset.vert ){
      case TOP_TEXT:
        y += max( TextAscent( PSBGIStrokeFonts[font][size] ),
                 TextAscent( PSBGIBiFonts[size] ) );
        break;
      case CENTER_TEXT:
        y += height/2;
        break;
      case BOTTOM_TEXT:
        y -= max( TextDescent( PSBGIStrokeFonts[font][size] ),
                 TextDescent( PSBGIBiFonts[size] ) );
        break;
      }
#endif
    }
    break;
  }
  ps_xbgi_begin( "_outtextxy" );
  ps_xbgi_put_color( XBGI->color );
  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    ps_xbgi_printf( "/%s "FINDFONT" [%g %g %g %g %g %g] "MAKEFONT" "SETFONT"\n",
		   PSBGIStrokeFonts[font][size]->name,
		   PSBGIStrokeFonts[font][size]->tm[0][0],
		   PSBGIStrokeFonts[font][size]->tm[0][1],
		   PSBGIStrokeFonts[font][size]->tm[0][2],
		   PSBGIStrokeFonts[font][size]->tm[1][0],
		   PSBGIStrokeFonts[font][size]->tm[1][1],
		   PSBGIStrokeFonts[font][size]->tm[1][2] );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    ps_xbgi_printf( "/%s "FINDFONT" [%g %g %g %g %g %g] "MAKEFONT" "SETFONT"\n",
		   PSBGIStrokeFonts[font][size]->name,
		   PSBGIStrokeFonts[font][size]->tm[0][0],
		   PSBGIStrokeFonts[font][size]->tm[0][1],
		   PSBGIStrokeFonts[font][size]->tm[0][2],
		   PSBGIStrokeFonts[font][size]->tm[1][0],
		   PSBGIStrokeFonts[font][size]->tm[1][1],
		   PSBGIStrokeFonts[font][size]->tm[1][2] );
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
    ps_xbgi_printf( "/%s-%s /%s /%s "JAEUCFONT"\n",
		   PSBGIStrokeFonts[font][size]->name,
		   PSBGIBiFonts[size]->name,
		   PSBGIStrokeFonts[font][size]->name,
		   PSBGIBiFonts[size]->name );
    ps_xbgi_printf( "/%s-%s "FINDFONT" [%g %g %g %g %g %g] "MAKEFONT" "SETFONT"\n",
		   PSBGIStrokeFonts[font][size]->name,
		   PSBGIBiFonts[size]->name,
		   PSBGIBiFonts[size]->tm[0][0],
		   PSBGIBiFonts[size]->tm[0][1],
		   PSBGIBiFonts[size]->tm[0][2],
		   PSBGIBiFonts[size]->tm[1][0],
		   PSBGIBiFonts[size]->tm[1][1],
		   PSBGIBiFonts[size]->tm[1][2] );
#endif
  }
  ps_xbgi_flush();
  ps_xbgi_printf( ""GSAVE"\n" );
  ps_xbgi_printf( "%g %g "MOVETO"\n", Xx(x), Xy(y) );
  if ( dir == VERT_DIR )
    ps_xbgi_printf( "90 rotate\n" );
  ps_xbgi_printf( "(" );
  if ( !XBGI->l10n || font != DEFAULT_FONT ){
    ps_xbgi_put_string( textstring, strlen(textstring) );
  }else{
#if !defined( ENABLE_BILINGUAL ) && !defined( ENABLE_MULTILINGUAL )
    ps_xbgi_put_string( textstring, strlen(textstring) );
#endif
#if defined(ENABLE_BILINGUAL) || defined(ENABLE_MULTILINGUAL) /* ! */
    ps_xbgi_put_bi_string( textstring, strlen(textstring) );
#endif
  }
  ps_xbgi_printf( ") " );
  switch ( dir ) {
  case VERT_DIR:
    switch( XBGI->textset.vert ) {
    case BOTTOM_TEXT:
      ps_xbgi_printf( ""SHOW"\n" );
      break;
    case CENTER_TEXT:
      ps_xbgi_printf( ""CTEXT" "SHOW"\n" );
      break;
    case TOP_TEXT:
      ps_xbgi_printf( ""RTEXT" "SHOW"\n" );
      break;
    }
    ps_xbgi_printf( "-90 rotate\n" );
    break;
  case HORIZ_DIR:
    switch( XBGI->textset.horiz ) {
    case LEFT_TEXT:
      ps_xbgi_printf( ""SHOW"\n" );
      break;
    case CENTER_TEXT:
      ps_xbgi_printf( ""CTEXT" "SHOW"\n" );
      break;
    case RIGHT_TEXT:
      ps_xbgi_printf( ""RTEXT" "SHOW"\n" );
      break;
    }
  }
  ps_xbgi_printf( ""GRESTORE"\n" );
  ps_xbgi_end( "_outtextxy" );
}
