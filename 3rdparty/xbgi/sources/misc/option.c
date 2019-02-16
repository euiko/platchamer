/*
 * Routines to analyze command line options < option.h >
 *
 * コマンドラインオプション解析のためのルーチン
 *
 * Copyright (c) 1996 Taiji YAMADA
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scan_option( int argc, char *argv[], char *key, ... )
{
  int i, idx;
  char opt[1024], fmt[1024], buf[1024], *ptr;
  va_list argptr;
  int *flagptr, *enumptr, enumc;
  
#ifndef ENABLE_VSSCANF
#define VLIST10(V) V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7],V[8],V[9]
  int c;
  void **val;
#endif

  strcpy( opt, key );
  if ( (ptr=strchr(opt,'%')) != NULL ){
    /* scanf 形式 */
    strcpy( fmt, ptr );
    *ptr = '\0';
    while ( *(--ptr)==' ' ) *ptr = '\0';
#ifndef ENABLE_VSSCANF
    c = 0;
    ptr = strchr( fmt, '%' );
    while ( ptr != NULL ){
      c++;
      ptr = strchr( ptr+1, '%' );
    }
    val = (void**)malloc( (c+1)*sizeof(void*) );
    va_start( argptr, key );
    for ( i=0; i<c; i++ ){
      val[i] = va_arg( argptr, void* );
    }
    val[i] = NULL;
    va_end( argptr );
#endif
    idx = 0;
    for ( i=1; i<argc; i++ )
      if ( strcmp( argv[i], opt )==0 ){
	strcpy( buf, "" );
	idx = i;
	while ( ++i < argc ){
	  strcat( buf, argv[i] );
	  strcat( buf, " " );
	}
#ifdef ENABLE_VSSCANF
	va_start( argptr, key );
	vsscanf( buf, fmt, argptr );
	va_end( argptr );
#else
	sscanf( buf, fmt, VLIST10(val) );
#endif
	break;
      }
#ifndef ENABLE_VSSCANF
    free( val );
#undef VLIST10
#endif
    return idx;
  }else if ( (ptr=strstr(opt,"[-]")) != NULL ){
    /* フラグ */
    *ptr = '\0';
    va_start( argptr, key );
    flagptr = (int*)va_arg( argptr, int* );
    va_end( argptr );
    strcpy( buf, opt );
    for ( i=1; i<argc; i++ ){
      if ( strcmp( argv[i], buf )==0 ){
	*flagptr = !0;
        return i;
      }
    }
    strcat( buf, "-" );
    for ( i=1; i<argc; i++ ){
      if ( strcmp( argv[i], buf )==0 ){
	*flagptr = 0;
        return i;
      }
    }
    return 0;
  }else if ( (ptr=strstr(opt," ")) != NULL ){
    /* 列挙 */
    va_start( argptr, key );
    enumptr = (int*)va_arg( argptr, int* );
    va_end( argptr );
    enumc = 0;
    ptr = strtok( opt, " " );
    for ( i=1; i<argc; i++ ){
      if ( strcmp( argv[i], opt )==0 ){
	ptr = strtok( NULL, " " );
	while ( ptr && i+1<argc ){
	  if ( strcmp( argv[i+1], ptr )==0 ){
	    *enumptr = enumc;
	    return i;
	  }
	  enumc++;
	  ptr = strtok( NULL, " " );
	}
      }
    }
  }else{
    /* その他 */
    for ( i=1; i<argc; i++ )
      if ( strcmp( argv[i], key )==0 )
        return i;
    return( 0 );
  }
  return 0;
}
