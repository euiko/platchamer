/*
 * Routines to analyze command line options < options.h >
 *
 * すすんだコマンドラインオプション解析のためのルーチン
 *
 * Copyright (c) 1996 Taiji YAMADA
 */
#ifndef _OPTIONS_H_
#define _OPTIONS_H_

typedef struct {
  char *opt;
  void *var;
} option_record;

typedef struct {
  char *key;
  char *fmt;
  int c;
  void **var;
  int idx;
} option_complex;

option_complex *set_option( char *key, ... );

option_complex *alias_option( char *key, char *alias );

void set_options( int n, option_record *options );

void scan_options( int argc, char *argv[] );

int is_option( char *key );

void reset_options( void );

#endif /* _OPTIONS_H_ */
