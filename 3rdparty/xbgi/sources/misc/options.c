/*
 * Routines to analyze command line options < options.c >
 *
 * すすんだコマンドラインオプション解析のためのルーチン
 *
 * Copyright (c) 1996 Taiji YAMADA
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <options.h>

#define n_options __n_options
#define options __options
static int n_options = 0;
static option_complex *options = NULL;

option_complex *set_option( char *key, ... )
{
  int i, n;
  char opt[1024], *ptr;
  option_complex *it;
  va_list argptr;

  n = n_options;
  n_options++;
  if ( options == NULL )
    options = (option_complex*)malloc( n_options*sizeof(option_complex) );
  else
    options = (option_complex*)realloc( options,
					n_options*sizeof(option_complex) );
  if ( options == NULL ) return NULL;
  it = &options[n];
  it->fmt = NULL;
  it->c = 0;
  it->var = NULL;
  it->idx = 0;

  strcpy( opt, key );
  if ( (ptr=strchr(opt,'%')) != NULL ){
    /* scanf 形式 */
    it->fmt = (char*)malloc( (strlen(ptr)+1)*sizeof(char) );
    strcpy( it->fmt, ptr );
    *ptr = '\0';
    while ( *(--ptr)==' ' ) *ptr = '\0';
    it->key = (char*)malloc( (strlen(opt)+1)*sizeof(char) );
    strcpy( it->key, opt );
    ptr = strchr( it->fmt, '%' );
    while ( ptr != NULL ){
      it->c++;
      ptr = strchr( ptr+1, '%' );
    }
    it->var = (void**)malloc( it->c*sizeof(void*) );
    va_start( argptr, key );
    for ( i=0; i<it->c; i++ )
      it->var[i] = va_arg( argptr, void* );
    va_end( argptr );
  }else if ( (ptr=strstr(opt,"[-]")) != NULL ){
    /* フラグ */
    it->key = (char*)malloc( (strlen(opt)+1)*sizeof(char) );
    strcpy( it->key, opt );
    va_start( argptr, key );
    it->c = 1;
    it->var = (void**)malloc( it->c*sizeof(void*) );
    it->var[0] = va_arg( argptr, int* );
    va_end( argptr );
  }else if ( (ptr=strstr(opt," ")) != NULL ){
    /* 列挙 */
    it->key = (char*)malloc( (strlen(opt)+1)*sizeof(char) );
    strcpy( it->key, opt );
    va_start( argptr, key );
    it->c = 1;
    it->var = (void**)malloc( it->c*sizeof(void*) );
    it->var[0] = va_arg( argptr, int* );
    va_end( argptr );
  }else{
    /* その他 */
    it->key = (char*)malloc( (strlen(opt)+1)*sizeof(char) );
    strcpy( it->key, opt );
  }
  return it;
}

option_complex *alias_option( char *key, char *alias )
{
#define VLIST10(V) V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7],V[8],V[9]
  int n;
  char buf[1024];
  option_complex *it;

  for ( n=0; n<n_options; n++ ){
    it = &options[n];
    if ( strcmp( key, it->key ) == 0 ){
      strcpy( buf, alias );
      if ( it->fmt ){
	strcat( buf, " " );
	strcat( buf, it->fmt );
      }
      return set_option( buf, VLIST10(it->var) );
    }
  }
  return NULL;
#undef VLIST10
}

void set_options( int n, option_record *options )
{
  int i;
  option_complex *it;

  for ( i=0; i<n; i++ )
    it = set_option( options[i].opt, options[i].var );
}

void scan_options( int argc, char *argv[] )
{
#define VLIST10(V) V[0],V[1],V[2],V[3],V[4],V[5],V[6],V[7],V[8],V[9]
  int i, n, enumc;
  char opt[1024], buf[1024], *ptr;
  option_complex *it;

  for ( n=0; n<n_options; n++ ){
    it = &options[n];
    strcpy( opt, it->key );
    if ( it->fmt ){
      /* scanf 形式 */
      for ( i=1; i<argc; i++ ){
	if ( strcmp( argv[i], it->key )==0 ){
	  it->idx = i;
	  break;
	}
      }
      if ( it->idx != 0 ){
	strcpy( buf, "" );
	i = it->idx;
	while ( ++i < argc ){
	  strcat( buf, argv[i] );
	  strcat( buf, " " );
	}
	sscanf( buf, it->fmt, VLIST10(it->var) );
      }
    }else if ( (ptr=strstr(opt,"[-]")) != NULL ){
      /* フラグ */
      *ptr = '\0';
      strcpy( buf, opt );
      for ( i=1; i<argc; i++ ){
	if ( strcmp( argv[i], buf )==0 ){
	  *(int*)it->var[0] = !0;
	  it->idx = i;
	}
      }
      strcat( buf, "-" );
      for ( i=1; i<argc; i++ ){
	if ( strcmp( argv[i], buf )==0 ){
	  *(int*)it->var[0] = 0;
	  it->idx = i;
	}
      }
    }else if ( (ptr=strstr(opt," ")) != NULL ){
      /* 列挙 */
      ptr = strtok( opt, " " );
      for ( i=1; i<argc; i++ ){
	if ( strcmp( argv[i], opt )==0 ){
	  ptr = strtok( NULL, " " );
	  enumc = 0;
	  while ( ptr && i+1<argc ){
	    if ( strcmp( argv[i+1], ptr )==0 ){
	      *(int*)(it->var[0]) = enumc;
	      it->idx = i;
	    }
	    enumc++;
	    ptr = strtok( NULL, " " );
	  }
	}
      }
    }else{
      for ( i=1; i<argc; i++ ){
	if ( strcmp( argv[i], it->key )==0 ){
	  it->idx = i;
	  break;
	}
      }
    }
  }
#undef VLIST10
}

int is_option( char *key )
{
  int n;
  option_complex *it;

  for ( n=0; n<n_options; n++ ){
    it = &options[n];
    if ( strcmp( key, it->key ) == 0 ){
      return it->idx;
    }
  }
  return 0;
}

void reset_options( void )
{
  int n;
  option_complex *it;

  for ( n=0; n<n_options; n++ ){
    it = &options[n];
    if ( it->c != 0 )
      free( it->var );
    if ( it->fmt != NULL ) free( it->fmt );
    if ( it->key != NULL ) free( it->key );
  }
  free( options );
  options = NULL;
  n_options = 0;
}
