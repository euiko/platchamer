/*
 * Text drawing service in graffit library < outtext.h >
 *
 * Outtext Function with Format for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _OUTTEXT_H_
#define _OUTTEXT_H_
#include <stdio.h>
#include <graphics.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [名前]
   outtextxyf --- グラフィック画面へのフォーマット付テキスト出力

   [形式]
   outtextxyf(x, y, form, ...)
   int x, y;   グラフィック画面のビューポート座標
   char *form; printf形式の書式文字列
   ...;        可変引数

   [説明]
   setviewport で指定したビューポート座標へ、
   フォーマット付テキスト出力をします。
   form に指定する書式指定子は printf を参照して下さい。
   但し、このルーチンはタブや改行処理をしません。
 */
extern void outtextxyf(int x, int y, char *form, ...);

/*
   [名前]
   outtextxyf --- グラフィック画面へのフォーマット付テキスト出力

   [形式]
   outtextxyf(form, ...)
   char *form; printf形式の書式文字列
   ...;        可変引数

   [説明]
   グラフィック画面のカレント座標へ、
   フォーマット付テキスト出力をします。
   form に指定する書式指定子は printf を参照して下さい。
   但し、このルーチンはタブや改行処理をしません。
 */
extern void outtextf(char *form, ...);

/*
   [名前]
   outtextxyprintf --- グラフィック画面へのフォーマット付テキスト出力

   [形式]
   outtextxyprintf(x, y, form, ...)
   int x, y;   グラフィック画面のビューポート座標
   char *form; printf形式の書式文字列
   ...;        可変引数

   [説明]
   setviewport で指定したビューポート座標へ、
   フォーマット付テキスト出力をします。
   form に指定する書式指定子は printf を参照して下さい。
   このルーチンは outtextf と違い、タブや改行処理をします。
 */
extern void outtextxyprintf(int x, int y, char *form, ...);

/*
   [名前]
   outtextprintf --- グラフィック画面へのフォーマット付テキスト出力

   [形式]
   outtextprintf(form, ...)
   char *form; printf形式の書式文字列
   ...;        可変引数

   [説明]
   グラフィック画面のカレント座標へ、
   フォーマット付テキスト出力をします。
   form に指定する書式指定子は printf を参照して下さい。
   このルーチンは outtextf と違い、タブや改行処理をします。
 */
extern void outtextprintf(char *form, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _OUTTEXT_H_ */
