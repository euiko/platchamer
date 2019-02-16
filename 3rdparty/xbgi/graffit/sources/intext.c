/*
 * Key events service routines in graffit library < intext.c >
 *
 * Scan and Edit String for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <intext.h>

#if 0 /*defined(__cplusplus) || defined(c_plusplus)*/
template <class T>
inline T max(T __a, T __b)
{
  return (__a>__b)?__a:__b;
}
template <class T>
inline T min(T __a, T __b)
{
  return (__a>__b)?__b:__a;
}
#else
#ifdef __BORLANDC__
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)>(b))?(b):(a))
#endif
#endif
#endif

char ignored_keys_intext[64] = {
  K_SPACE, K_BREAK, K_BEL, K_TAB, K_HOME, 0
};
void entry_ignored_keys_intext(char *keys)
{
  strcpy(ignored_keys_intext, keys);
}
int is_ignored_keys_intext(char key)
{
  int i, len;

  len = strlen(ignored_keys_intext);
  for (i=0; i<len; i++) {
    if (ignored_keys_intext[i]==key)
      return 1;
  }
  return 0;
}
int echo_back_intext = !0;
void set_echo_back_intext(int flag)
{
  echo_back_intext = flag;
}
int maxlen_intext = 64;
void set_maxlen_intext(int len)
{
  maxlen_intext = len;
}
int intext(char *str)
{
  int key, len = 0;
  int x, y;
#ifndef _XBGI_
  int color, bkcolor;
#endif

  x = getx(), y = gety();
#ifndef _XBGI_
  color = getcolor(), bkcolor = getpixel(x, y);
#else
  setwritemode(XOR_PUT);
#endif
  while ((key=getch())!=K_ENTER) {
    if (is_ignored_keys_intext((char)key))
      continue;
    switch (key) {
    case K_ESC:
      if (echo_back_intext) {
        moveto(x, y);
#ifndef _XBGI_
        setcolor(bkcolor);
#endif
        outtext(str);
#ifndef _XBGI_
        setcolor(color);
#endif
      }
      len = 0;
      return len;
    case K_CTRL('W'):
      if (echo_back_intext) {
        moveto(x, y);
#ifndef _XBGI_
        setcolor(bkcolor);
#endif
        outtext(str);
      }
      len = 0;
      str[len] = '\0';
      break;
    case K_BS:
      if (echo_back_intext) {
        if (len != 0) {
          moverel(-textwidth(&str[len-1]), 0);
#ifndef _XBGI_
          setcolor(bkcolor);
#endif
          outtext(&str[len-1]);
          moverel(-textwidth(&str[len-1]), 0);
#ifndef _XBGI_
          setcolor(color);
#endif
        }
      }
      len = max(0,len-1);
      str[len] = '\0';
      break;
    default:
      if (isascii(key) && !iscntrl(key) && (len<maxlen_intext)) {
        str[len] = (char)key;
        len = len+1;
        str[len] = '\0';
        if (echo_back_intext) {
#ifndef _XBGI_
          setcolor(color);
#endif
          outtext(&str[len-1]);
        }
      }
      break;
    }
  }
#ifndef _XBGI_
#else
  setwritemode(COPY_PUT);
#endif
  return len;
}



