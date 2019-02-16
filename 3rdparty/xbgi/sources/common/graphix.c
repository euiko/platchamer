/*
 * Source File < common/graphix.c >
 *
 * Enhanced Functions: Borland Graphics Interface for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include "common_p.h"
#include "option.h"

#define XBGIENVIRON "XBGISET"
#define XBGISETFILE ".xbgisets"
#define SPACES " \t\n"
#define iscomment(c) ((c)=='#')
#define STRINGLEN 1024

extern char *getdriversname( int driver_number );
extern int getdrivernumber( char *driver_name );

xbgi *_creategraph( int argc, char *argv[], char *pd )
{
  static int id = 0;
  xbgi *this;
  int i;
  char buf[STRINGLEN], *ptr;
  
  this = (xbgi*)malloc(sizeof(xbgi));
  if ( !this ) FatalError( "memory allocation in _creategraph()" );
  this->inherit_procedures = (xbgi_procedures*)malloc(sizeof(xbgi_procedures));
  if ( !this->inherit_procedures )
    FatalError( "memory allocation in _creategraph()" );
  /*
   * insert to linked list
   */
  this->next = XBGIS;
  XBGIS = this;
  /*
   * set to current XBGI
   */
  XBGI = this;
  /*
   * set ID
   */
  XBGI->id = id++;
  /*
   * set to parameter options
   */
  XBGI->argc = argc;
  XBGI->argv = NULL;
  i = 0;
  if ( argc > 0 ){
    XBGI->argv = (char**)malloc( argc*sizeof(char*) );
    if ( !XBGI->argv ) FatalError( "memory allocation in _creategraph()" );
    for ( i=0; i<argc; i++ ){
      XBGI->argv[i] = (char*)malloc( (strlen(argv[i])+1)*sizeof(char) );
      strcpy( XBGI->argv[i], argv[i] );
    }
  }
  /*
   * set to parameter options of pd
   */
  i = argc;
  strcpy( buf, pd );
  ptr = strtok( buf, SPACES );
  while ( ptr != NULL ){
    argc++;
    ptr = strtok( NULL, SPACES );
  }
  if ( argc != XBGI->argc ){
    XBGI->argc = argc;
    if ( XBGI->argv )
      XBGI->argv = (char**)realloc( XBGI->argv, XBGI->argc*sizeof(char*) );
    else
      XBGI->argv = (char**)malloc( XBGI->argc*sizeof(char*) );
    if ( !XBGI->argv ) FatalError( "memory allocation in _creategraph()" );
    strcpy( buf, pd );
    ptr = strtok( buf, SPACES );
    while ( ptr != NULL ){
      XBGI->argv[i] = (char*)malloc( (strlen(ptr)+1)*sizeof(char) );
      strcpy( XBGI->argv[i], ptr );
      ptr = strtok( NULL, SPACES );
      i++;
    }
  }
  /*
   * xbgi system initializing by driver
   */
  XBGI->gerror  = grNoInitGraph;
  XBGI->gdriver = CURRENTDRIVER;
  XBGI->inherit_procedures->driver = XBGI_CURRENT_DRIVER;
  if ( (i=scan_option(XBGI->argc,XBGI->argv,"-gd")) )
    XBGI->gdriver = getdrivernumber( argv[i+1] );
#ifndef BUILD_STANDALONE
  switch (XBGI->gdriver){
  case DETECT:
    XBGI->inherit_procedures->driver = XBGI_CURRENT_DRIVER;
    break;
  case X11:
    XBGI->inherit_procedures->driver = x11_driver;
    break;
  case PS:
    Notice( "load driver for PostScript" );
    XBGI->inherit_procedures->driver = ps_driver;
    break;
  }
#endif
  XBGI->inherit_procedures->_driver = NULL;
  /*
   * call driver
   */
  XBGI->inherit_procedures->driver();
  return XBGI;
}

xbgi *creategraph( int *graphdriver, int *graphmode, char *pathtodriver )
{
  int argc;
  char **argv;
  int i, j;
  char *ptr, options[STRINGLEN], buf[STRINGLEN], buf2[STRINGLEN];
  char file[STRINGLEN], key[STRINGLEN];
  FILE *fp;
  xbgi *this;

  /*
   * parameter settings to argc, argv from xbgienviron
   */
  sprintf( options, "%s ", "XBGI" );
  if ( getenv( XBGIENVIRON ) != NULL ){
    strcat( options, getenv( XBGIENVIRON ) );
    strcat( options, " " );
  }
  strcat( options, pathtodriver );
  strcat( options, " " );
  sprintf( buf, "-gd %s ", getdriversname(*graphdriver) );
  strcat( options, buf );
  if ( getmodename(*graphmode) != NULL ){ 
    sprintf( buf, "-gm %s ", getmodename(*graphmode) );
    strcat( options, buf );
  }
  strcpy( buf, options );
  ptr = strtok( buf, SPACES );
  argc = 0;
  while ( ptr != NULL ){
    argc++;
    ptr = strtok( NULL, SPACES );
  }
  argv = (char**)malloc( argc*sizeof(char*) );
  if ( !argv ) FatalError( "memory allocation in creategraph()" );
  i = 0; 
  strcpy( buf, options );
  ptr = strtok( buf, SPACES );
  while ( ptr != NULL ){
    argv[i] = (char*)malloc( (strlen(ptr)+1)*sizeof(char) );
    strcpy( argv[i++], ptr );
    ptr = strtok( NULL, SPACES );
  }
  /*
   * parameter settings to argc, argv from xbgisetfile
   */
  strcpy( file, "" );
  ptr = getenv( "HOME" );
  if ( ptr != NULL ){
    strcpy( file, ptr );
    strcat( file, "/" );
    strcat( file, XBGISETFILE );
  }
  if ( (fp=fopen(file,"r")) != NULL ){
    j = i = strspn( pathtodriver, SPACES );
    if ( strcmp(pathtodriver,"") == 0 || pathtodriver[i] == '-' ){
      strcpy( key, "" );
    }else{
      while( pathtodriver[j]!=' ' && pathtodriver[j]!='\0' ) j++;
      strncat( key, &pathtodriver[i], j-i+1 );
    }
    while ( fgets( buf, STRINGLEN, fp ) != NULL ){
      i = strspn( buf, SPACES );
      if ( i==strlen( buf ) || iscomment( buf[i] ) )
        continue;
      while ( buf[strlen(buf)-2] == '\\' ){
        buf[strlen(buf)-2] = '\0';
        if ( fgets( buf2, STRINGLEN, fp ) != NULL ){
          if ( strlen(buf)+strlen(buf2) < STRINGLEN )
            strcat( buf, buf2 );
        }else{
          break;
        }
      }
      i = strspn( buf, SPACES );
      if ( ( strcmp( key, "" )==0 && buf[i] == '-' )
          || ( strncmp(&buf[i],key,strlen(key)) == 0 ) ){
        i = argc;
        strcpy( options, buf );
        ptr = strtok( options, SPACES );
        while ( ptr != NULL ){
          argc++;
          ptr = strtok( NULL, SPACES );
        }
        argv = (char**)realloc( argv, argc*sizeof(char*) );
        if ( !argv ) FatalError( "memory allocation in creategraph()" );
        strcpy( options, buf );
        ptr = strtok( options, SPACES );
        while ( ptr != NULL ){
          argv[i] = (char*)malloc( (strlen(ptr)+1)*sizeof(char) );
          strcpy( argv[i++], ptr );
          ptr = strtok( NULL, SPACES );
        }
        break;
      }
    }
    fclose( fp );
  }
  /*
   * create xbgi
   */
  this = _creategraph( argc, argv, "" );
  for ( i=0; i<argc; i++ )
    free( argv[i] );
  free ( argv );
  *graphdriver = this->gdriver;
  *graphmode   = this->gmode;
  return this;
}

xbgi *thisgraph( void )
{
  return XBGI;
}

void currentgraph( xbgi *this )
{
  XBGI = this;
}

void destroygraph( xbgi *this )
{
  xbgi *ptr;

  /*
   * call destroyer of driver
   */
  if ( this->inherit_procedures->_driver ) {
    currentgraph( this );
    this->inherit_procedures->_driver();
  }
#if 1 /* for segmentation fault, bug? */
  {
    int i;

    for ( i=0; i<this->argc; i++ )
      free( this->argv[i] );
    free ( this->argv );
  }
#endif
  /*
   * delete from linked list
   */
  if ( XBGIS == this ){
    XBGI = XBGIS = this->next;
    free( this );
    this = NULL;
    return;
  }
  ptr = XBGIS;
  while ( ptr->next != NULL ){
    if ( ptr->next == this ){
      ptr->next = this->next;
      XBGI = ptr;
      free( this );
      this = NULL;
      return;
    }
    ptr = ptr->next;
  }
  return;
}





