/*
 * Text drawing service in graffit library < outtext.c >
 *
 * Outtext Function with Format for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <outtext.h>

#if !defined(__JSTRING_H) && !defined(__MSDOS__)
#define iskanji(c) 0
#define iskanji2(c) 0
#define jstrtok strtok
#endif
#ifdef __MSDOS__
#include <jctype.h>
#include <jstring.h>
#endif

void outtextxyf(int x, int y, char *form, ...)
{
  va_list argptr;
  char str[1024] = "";

  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtextxy(x, y, str);
  va_end(argptr);
}

void outtextf(char *form, ...)
{
  va_list argptr;
  char str[1024] = "";

  va_start(argptr, form);
  vsprintf(str, form, argptr);
  outtext(str);
  va_end(argptr);
}

void strcpy_tab_space(unsigned char *dst, unsigned char *src, int l)
{
  int i, c = 0;

  while (*src != '\0') {
    if (!iskanji(*src) || !iskanji2(*(src+1))) {
      if (isspace(*src)) {
        if (*src == '\t') { 
          for (i=0; i<l-c%l; i++) {
            c++;
            *dst++ = ' ';
          }
        }
	else if (*src == '\n') {
          c++;
          *dst++ = *src;
        }
	else {
          c++;
          *dst++ = ' ';
        }
      }
      else {
        c++;
        *dst++ = *src;
      }
      src++;
    }
    else {
      c+=2;
      *dst++ = *src++;
      *dst++ = *src++;
    }
  }
  *dst = '\0';
}

void outtextxyprintf(int x, int y, char *form, ...)
{
  va_list argptr;
  char buf[1024], str[1024] = "", *ptr = str;
  int height;

  height = textheight("H");
  
  va_start(argptr, form);
  vsprintf(buf, form, argptr);

  strcpy_tab_space((unsigned char*)str, (unsigned char*)buf, 8); /* ! */

  strcat(str, "\n");
  ptr = jstrtok(str, "\n");
  while (ptr != NULL) {
    outtextxy(x, y, ptr);
    y += height;
    moveto(x, y);
    ptr = jstrtok(NULL, "\n");
  }

  va_end(argptr);
}

void outtextprintf(char *form, ...)
{
  va_list argptr;
  char str[1024] = "";
  int x, y;
  
  x = getx(), y = gety();

  va_start(argptr, form);
  vsprintf(str, form, argptr);

  outtextxyprintf(x, y, str);

  va_end(argptr);
}
