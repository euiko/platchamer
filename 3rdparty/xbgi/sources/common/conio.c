/*
 * Source File < common/conio.c >
 *
 * Standard Functions of Console I/O: on BGI for common procedures
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#include <stdarg.h>
#include <string.h>
#include "common_p.h"

/*
 * following functions are dummy
 */

/*
 * input of conio
 */
#if 0
int gettext( int left, int top, int right, int bottom, void *destin )
{
  if (!XBGI){ return 0; }
  return 0;
}
#endif
char *cgets( char *str )
{
  int n = str[0];
  char *ret = str+2;

  str[1] = 0;
  if (!XBGI){ if(fgets(ret,n,stdin))str[1]=strlen(ret); return ret; }
  return NULL;
}
#if 0
char *getpass( char *prompt )
{
  if (!XBGI){ return gets(prompt); }
  return NULL;
}
#endif
int ungetch( int ch )
{
  if (!XBGI){ ungetc(ch,stdin); return ch; }
  return ch;
}
/*
 * output of conio
 */
void clreol( void )
{
  if (!XBGI){ puts( "\x1b[K" ); return; }
}
void clrscr( void )
{
  if (!XBGI){ puts( "\x1b[2J" ); return; }
}
int putch( int c )
{
  if (!XBGI){ return putc( c, stdout ); }
  return 0;
}
void delline( void )
{
  if (!XBGI){ puts( "\x1b[2K" ); return; }
}
void insline( void )
{
  if (!XBGI){ puts( "\x1b[1L" ); return; }
}
int movetext( int left, int top, int right, int bottom,
             int destleft, int desttop )
{
  if (!XBGI){ return 0; }
  return 0;
}
int puttext( int left, int top, int right, int bottom, void *source )
{
  if (!XBGI){ return 0; }
  return 0;
}
int cprintf( char *format, ... )
{
  va_list argptr;
  int ret;

  va_start( argptr, format );
  if (!XBGI){ ret=vprintf( format, argptr ); va_end( argptr ); return ret; }

  va_end( argptr );
  return 0;
}
int cputs( char *str )
{
  if (!XBGI){ return puts(str); }
  return 0;
}
/*
 * input and output of conio
 */
int getche( void )
{
  if (!XBGI){ return getchar(); }
  return 0;
}
int cscanf( char *format, ... )
{
  return 0;
}
/*
 * others of conio
 */
void gotoxy( int x, int y )
{
  if (!XBGI){ printf( "\x1b[%d;%dH", y, x ); return; }
}
int wherex( void )
{
  if (!XBGI){ return 0; }
  return 0;
}
int wherey( void )
{
  if (!XBGI){ return 0; }
  return 0;
}
void highvideo( void )
{
}
void normvideo( void )
{
}
void lowvideo( void )
{
}
void textmode( int newmode )
{
  if (!XBGI){ return; }
}
void gettextinfo( struct text_info *r )
{
  static struct text_info ti = {
    1, 1, 80, 25, 0x0000, 0x0000, _NORMALCURSOR, 25, 80, 0, 0,
  };
  if (!XBGI){ *r = ti; return; }
}
void window( int left, int top, int right, int bottom )
{
  if (!XBGI){ return; }
}
void textattr( int attr )
{
  if (!XBGI){ return; }
}
void textcolor( int col )
{
  if (!XBGI){ printf( "\x1b[%dm", 30+col  ); return; }
}
void textbackground( int bcol )
{
  if (!XBGI){ printf( "\x1b[%dm", 40+bcol ); return; }
}
void textkanji( int flag )
{
}
void _setcursortype( int cur_t )
{
  if (!XBGI){ printf("\x1b[>%s",cur_t?"51":"5h"); return; }
}





