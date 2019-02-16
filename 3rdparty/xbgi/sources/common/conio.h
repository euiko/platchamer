/*
 * Header File < common/conio.h >
 *
 * Standard Functions: Borland Console I/O for Xlib
 *
 * Copyright (c) 1992-94,95 Tokyo Denki University, Taiji Yamada
 */
#ifndef _CONIO_H_
#define _CONIO_H_

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* Not Supported Almost Functions on XBGI. This header is for registration. */
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#define _NOCURSOR     0
#define _SOLIDCURSOR  1
#define _LINECURSOR   2
#define _NORMALCURSOR _SOLIDCURSOR

struct text_info {
  unsigned char winleft;
  unsigned char wintop;
  unsigned char winright;
  unsigned char winbottom;
  unsigned short attribute;
  unsigned short normattr;
  unsigned char currmode;
  unsigned char screenheight;
  unsigned char screenwidth;
  unsigned char curx;
  unsigned char cury;
};

enum text_modes {
  LASTMODE = -1,
  N8025 =  0,
  N8020 =  1,
  N8031 =  9,
  E8025 = 16,
  E8020 = 17,
  E8031 = 25,
};

#define BLINK         0x0100
#define REVERSE       0x0200
#define UNDERLINE     0x0400
#define VERTICALLINE  0x0800
#define OVERLINE      0x1000

#define _KANJI   0x01
#define _NOKANJI 0x00

extern int directvideo;
extern int _wclrnorm;
extern int _wgarbage;
extern int _wkanji;
extern int _wnewline;
extern int _wscroll;

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

extern void  clreol(
#if NeedFunctionPrototypes
  void
#endif
);

extern void  clrscr(
#if NeedFunctionPrototypes
  void
#endif
);

extern void  delline(
#if NeedFunctionPrototypes
  void
#endif
);

#if 0
extern int   gettext(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom, void *__destin
#endif
);
#endif

extern void  gettextinfo(
#if NeedFunctionPrototypes
  struct text_info *__r
#endif
);

extern void  gotoxy(
#if NeedFunctionPrototypes
  int __x, int __y
#endif
);

extern void  highvideo(
#if NeedFunctionPrototypes
  void
#endif
);

extern void  insline(
#if NeedFunctionPrototypes
  void
#endif
);

extern void  lowvideo(
#if NeedFunctionPrototypes
  void
#endif
);

extern int   movetext(
#if NeedFunctionPrototypes
   int __left, int __top, int __right, int __bottom,
   int __destleft, int __desttop
#endif
);

extern void  normvideo(
#if NeedFunctionPrototypes
  void
#endif
);

extern int   puttext(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom, void *__source
#endif
);

extern void  textattr(
#if NeedFunctionPrototypes
  int __newattr
#endif
);

extern void  textbackground(
#if NeedFunctionPrototypes
  int __newcolor
#endif
);

extern void  textcolor(
#if NeedFunctionPrototypes
  int __newcolor
#endif
);

extern void  textkanji(
#if NeedFunctionPrototypes
  int __kanjiflag
#endif
);

extern void  textmode(
#if NeedFunctionPrototypes
  int __newmode
#endif
);

extern int   wherex(
#if NeedFunctionPrototypes
  void
#endif
);

extern int   wherey(
#if NeedFunctionPrototypes
  void
#endif
);

extern void  window(
#if NeedFunctionPrototypes
  int __left, int __top, int __right, int __bottom
#endif
);

extern void  _setcursortype(
#if NeedFunctionPrototypes
  int __cur_t
#endif
);

extern char *cgets(
#if NeedFunctionPrototypes
  char *__str
#endif
);

extern int   cprintf(
#if NeedFunctionPrototypes
  char *__format, ...
#endif
);

extern int   cputs(
#if NeedFunctionPrototypes
  char *__str
#endif
);

extern int   cscanf(
#if NeedFunctionPrototypes
  char *__format, ...
#endif
);

extern int   getch(
#if NeedFunctionPrototypes
  void
#endif
);

extern int   getche(
#if NeedFunctionPrototypes
  void
#endif
);

#if 0
extern char *getpass(
#if NeedFunctionPrototypes
  char *__prompt
#endif
);
#endif

extern int   kbhit(
#if NeedFunctionPrototypes
  void
#endif
);

extern int   putch(
#if NeedFunctionPrototypes
  int __c
#endif
);

extern int   ungetch(
#if NeedFunctionPrototypes
  int __ch
#endif
);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _CONIO_H_ */


