/*
 * All include files of graffit library < graffit.h >
 *
 * GRAFFIT for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAFFIT_H_
#define _GRAFFIT_H_

#include <coloring.h>
#include <graphr2_.h>
#include <gturtle_.h>
#include <graphl2_.h>
#include <outtext.h>
#include <outtext_.h>
#include <intext.h>
#include <axes.h>
#include <axes_.h>
#include <graphr3_.h>
#include <graphp3_.h>
#include <graphs3_.h>
#include <graphrn_.h>
#include <graphpn_.h>
#include <graphsn_.h>
#include <grafplot.h>

struct graffittype_ {
  struct coloringtype_           co;
  struct windowtype_             w;
  struct viewporttype_           v;
  struct rotationporttype_       rp;
  struct perspectivetype_        pp;
  struct stereographtype_        sg;
  struct hyperrotationporttype_  hr;
  struct plotgraphtype           gp;
};

#endif
