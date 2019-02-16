/*
 * Header File < ps/misc.h >
 *
 * Misc Functions for PS: Borland Graphics Interface for PostScript
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _MISC_H_
#define _MISC_H_
#include <stdio.h>
#include "script/abbrev.h"

#ifndef NeedFunctionPrototypes
#  if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#    define NeedFunctionPrototypes 1
#  else
#    define NeedFunctionPrototypes 0
#  endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

void ps_xbgi_flush( void );
void ps_xbgi_vprintf( char *fmt, va_list argptr );
void ps_xbgi_printf( char *fmt, ... );
void ps_xbgi_open( void );
void ps_xbgi_close( void );
void ps_xbgi_put_linewidth( double width );
void ps_xbgi_put_linecap( int type );
void ps_xbgi_put_linejoin( int type );
void ps_xbgi_put_miterlimit( double ratio );
void ps_xbgi_put_dash( char *pattern, int offset );
void ps_xbgi_put_rgbcolor( double red, double green, double blue );
void ps_xbgi_put_gray( double brightness );
void ps_xbgi_put_color( int color );
void ps_xbgi_put_fillpat( char *pattern, int size );
void ps_xbgi_begin( char *name );
void ps_xbgi_end( char *name );
void ps_xbgi_showpage( void );
void ps_xbgi_put_string( char *string, int len );

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _MISC_H_ */









