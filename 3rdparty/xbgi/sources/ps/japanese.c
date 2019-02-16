/*
 * routines to analyse japanese code and draw PS 16 bit text < ps/japanese.c >
 *
 * 日本語コードを解析し、PSで16ビット文字列を出力するためのルーチン
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "jutil.h"
#include "japanese.h"

/*
 * ps_put_bi_string for japanese
 */
void ps_xbgi_put_bi_string( char *string, int len )
{
  unsigned char buf[2048], *ptr;
  int ocode, code, c;
  unsigned jisc, eucc;

  ocode = jcode( string );
  str2jis( string, buf );
  c = 0;
  ptr = buf;
  code = JCT_ANK;
  while ( *ptr != '\0' && c <= len ){
    if ( isjise(ptr) ){
      code = JCT_ANK;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else if ( isjiss(ptr) ){
      code = JCT_JIS;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else{
      if ( code==JCT_ANK ){
	switch( *ptr ){
	case '\\':
	case '(': 
	case ')':
	  ps_xbgi_printf( "\\%c", *ptr );
	  break;
	default:
	  if ( isprint(*ptr) ) /* ! */
	    ps_xbgi_printf( "%c", *ptr );
	  break;
	}
        ptr++;
        c++;
      }else{
        jisc = s2code(ptr);
        eucc = jistoeuc(jisc);
        ps_xbgi_printf( "\\%o\\%o",
		       (unsigned char)((eucc)>>8),
		       (unsigned char)((eucc)&0x00ff) );
        ptr += 2;
        c += 2;
      }
    }
  }
}
/*
 * ps_xbgi_bi_text_width for japanese
 */
int ps_xbgi_bi_text_width( char *string, int len )
{
  unsigned char buf[2048], *ptr;
  int ocode, code, c;
  unsigned jisc, eucc;
  int x = 0;

  ocode = jcode( string );
  str2jis( string, buf );
  c = 0;
  ptr = buf;
  code = JCT_ANK;
  while ( *ptr != '\0' && c <= len ){
    if ( isjise(ptr) ){
      code = JCT_ANK;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else if ( isjiss(ptr) ){
      code = JCT_JIS;
      ptr += 3;
      if ( ocode == JCT_JIS ) c += 3;
    }else{
      if ( code==JCT_ANK ){
        if ( isprint(*ptr) ) /* ! */
	  x += 8;
        ptr++;
        c++;
      }else{
        jisc = s2code(ptr);
        eucc = jistoeuc(jisc);
        x += 16;;
        ptr += 2;
        c += 2;
      }
    }
  }
  return x;
}











