/*
 * Key events service routines in graffit library < intext.h >
 *
 * Scan and Edit String for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _INTEXT_H_
#define _INTEXT_H_
#include <graphics.h>
#include <conio.h>

#define K_BREAK 0x03
#define K_BEL   0x07
#define K_BS    0x08
#define K_TAB   0x09
#define K_HOME  0x0a
#define K_ENTER 0x0d
#define K_ESC   0x1b
#define K_SPACE 0x20
#define K_CTRL(c) (((c)<'a')?((c)-'A'+1):((c)-'a'+1))

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void entry_ignored_keys_intext(char *keys);
extern int is_ignored_keys_intext(char key);
extern int echo_back_intext;
extern void set_echo_back_intext(int flag);
extern int maxlen_intext;
extern void set_maxlen_intext(int len);
extern int intext(char *str);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _INTEXT_H_ */
