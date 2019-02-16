/*
 * Image format services in graffit library < gsave.h >
 *
 * Utility to Save Screen for BGI and XBGI by TIFF format
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _GSAVE_H_
#define _GSAVE_H_
#include <graphics.h>

enum gsave_mode {
  GSAVE_MONO,
  GSAVE_MONO_REVERSE,
  GSAVE_COLOR
};

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern int savegraphtotiff(int mode, char *filename);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GSAVE_H_ */
