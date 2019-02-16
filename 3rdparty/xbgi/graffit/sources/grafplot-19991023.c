/*
 * Graph plotting interface in graffit < grafplot.c >
 *
 * Graph-Plot Routines for Borland Graphics Interface
 *
 * Copyright (C) 1996-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <axisutil.h>
#include <coloring.h>
#include <graphr2_.h>
#include <graphl2_.h>
#include <outtext.h>
#include <outtext_.h>
#include <graphr3_.h>
#include <graphp3_.h>
#include <graphs3_.h>
#include <graphrn_.h>
#include <graphpn_.h>
#include <graphsn_.h>
#include <grafplot.h>

#ifndef MAXDOUBLE
#include <values.h>
#endif

#define DEFAULT_LIMIT_PLOT_NUMBER 500

static int plotcolor_table[N_COLOR_KINDS] = {
  LIGHTRED,
  LIGHTGREEN,
  LIGHTBLUE,
  LIGHTMAGENTA,
  YELLOW,
  LIGHTCYAN,
};
#define setplotcolor(colorkind) setcolor(\
        (getmaxcolor()!=1)?plotcolor_table[colorkind]:getcolor())
#define getplotcolor(colorkind) (\
        (getmaxcolor()!=1)?plotcolor_table[colorkind]:getcolor())

#define setplotline(linekind) \
        do {if (!gp.color_kind_flag)setlinestyle(linekind,0,0);} while (0)

#define setplotpoint(pointkind,c) setpointstyle(pointkind,c,getbkcolor(),6)

#define OFFSET_BASE 5

/*
 * 一本の軸の情報の初期化子
 */
static struct plotaxistype plotaxis0 = {
  NULL, /* char *title; */
  0, 0, /* int x, y; */
  SCALE_DEC, /* int scale_type; */
  0.0, /* Float from_range; */
  0.0, /* Float to_range; */
  !0, /* int axis_flag; */
  !0, /* int tick_flag; */
  !0, /* int zero_flag; */
  0.0, 0.0, /* Float from_tick, to_tick; */
  1, /* int div_tick; */
  OFFSET_BASE, /* int tick_height; */
  OFFSET_BASE, /* int tick_offset; */
};
/*
 * プロット対象のベクトルタイプの初期化子
 */
static struct plotvectortype plotvector0 = {
  NULL, /* char *title; */
  0, 0, /* int x, y */
  0,0, /* long nl, nh; */
  NULL, /* Float *data; */
  AXIS_C-1, /* int n_axes_are; */
  NULL, /* int *axes_are; */
  PLOT_LINE, /* unsigned long plotkind; */
  COLOR_BLUE, /* int colorkind; */
  LINE_SOLID, /* int linekind; */
  POINT_LOZENGE, /* int pointkind; */
  { 1, 1, 0, 0, }, /* int plotstep[4]; */
};
/*
 * プロット対象のマトリックスタイプの初期化子
 */
static struct plotmatrixtype plotmatrix0 = {
  NULL, /* char *title; */
  0, 0, /* int x, y; */
  0,0,0,0, /* long nrl, nrh, ncl, nch; */
  NULL, /* Float **data; */
  AXIS_C-1, /* int n_axes_are; */
  NULL, /* int *axes_are; */
  PLOT_LINE, /* unsigned long plotkind; */
  COLOR_BLUE, /* int colorkind; */
  LINE_SOLID, /* int linekind; */
  POINT_LOZENGE, /* int pointkind; */
  { 1, 1, 0, 0, }, /* int plotstep[4]; */
};
/*
 * プロット対象のマトリックスTタイプの初期化子
 */
static struct plotmatrixTtype plotmatrixT0 = {
  NULL, /* char *title; */
  0, 0, /* int x, y; */
  0,0,0,0, /* long nrl, nrh, ncl, nch; */
  NULL, /* Float **data; */
  AXIS_C-1, /* int n_axes_are; */
  NULL, /* int *axes_are; */
  PLOT_LINE, /* unsigned long plotkind; */
  COLOR_BLUE, /* int colorkind; */
  LINE_SOLID, /* int linekind; */
  POINT_LOZENGE, /* int pointkind; */
  { 1, 1, 0, 0, }, /* int plotstep[4]; */
};
/*
 * グラフ全体の情報の初期化子
 */
static struct plotgraphtype gp = {
  NULL, /* char *title; */
  0, -OFFSET_BASE, /* int x, y; */
  0, /* int color_kind_flag; */
  0, /* int color_axis_flag; */
  0, 0, /* int palette_from, palette_to; */
  R3_PERSPECTIVE, /* int r3kind; */
  SMALL_FONT, 2, /* int tick_font, tick_fontsize; */
  AXIS_C-1, /* int n_axes; */
  NULL, /* struct plotaxistype *axes; */
  0, /* int n_data; */
  0, /* int n_vectors; */
  NULL, /* struct plotvectortype *vectors; */
  0, /* int n_matrices; */
  NULL, /* struct plotmatrixtype *matrices; */
  0, /* int n_matricesT; */
  NULL, /* struct plotmatrixTtype *matricesT; */
};
/*
 * グラフ全体の設定関数
 */
/* グラフプロットのタイトル */
void set_plotgraph_title(char *title)
{
  if (title) {
    gp.title = gp.title?
      realloc(gp.title,sizeof(char)*(strlen(title)+1)):
        malloc(sizeof(char)*(strlen(title)+1));
    strcpy(gp.title, title);
  }
  else {
    if (gp.title) free(gp.title);
    gp.title = NULL;
  }
}
/* グラフプロットのタイトルと次元 */
void set_plotgraph(char *title, int dimension)
{
  void set_plotgraph_n_axes(int n_axes);

  set_plotgraph_title(title);
  set_plotgraph_n_axes(dimension);
}
/* グラフプロットでデータをカラーで区別するか */
void set_plotgraph_color_kind(int color_kind_flag)
{
  gp.color_kind_flag = color_kind_flag;
}
/* グラフプロットでもう一次元をカラーで表現するか */
void set_plotgraph_color_axis(int color_axis_flag)
{
  gp.color_axis_flag = color_axis_flag;
}
/* グラフプロットの2次元グラフの種類 */
void set_plotgraph_r2kind(int r2kind)
{
  switch (r2kind) {
  case R2_NORMAL:
    set_x_plotaxis_scale_type(SCALE_DEC);
    set_y_plotaxis_scale_type(SCALE_DEC);
    break;
  case R2_LOGX:
    set_x_plotaxis_scale_type(SCALE_LOG10);
    set_y_plotaxis_scale_type(SCALE_DEC);
    break;
  case R2_LOGY:
    set_x_plotaxis_scale_type(SCALE_DEC);
    set_y_plotaxis_scale_type(SCALE_LOG10);
    break;
  case R2_LOGLOG:
    set_x_plotaxis_scale_type(SCALE_LOG10);
    set_y_plotaxis_scale_type(SCALE_LOG10);
    break;
  }
}
/* グラフプロットの3次元グラフの種類 */
void set_plotgraph_r3kind(int r3kind)
{
  gp.r3kind = r3kind;
  if (r3kind == R3_STEREO)
    setstereotype(ColorGlass);
  else if (r3kind == R3_STEREO2)
    setstereotype(DoubleImage);
}
/* グラフプロットのリセット */
void reset_plotgraph(void)
{
  int i;
  void reset_ith_plotaxis(int ith);
  void reset_ith_plotvector(int ith);
  void reset_ith_plotmatrix(int ith);
  void reset_ith_plotmatrixT(int ith);
  
  for (i=AXIS_C; i<=gp.n_axes; i++)
    reset_ith_plotaxis(i);
  gp.axes = gp.axes?gp.axes+((AXIS_C-1)+1):NULL;
  if (gp.axes) free(gp.axes);
  gp.axes = NULL;
  gp.n_axes = AXIS_C-1;
  
  for (i=1; i<=gp.n_vectors; i++)
    reset_ith_plotvector(i);
  if (gp.vectors) free(++gp.vectors);
  gp.vectors = NULL;
  gp.n_vectors = 0;
  
  for (i=1; i<=gp.n_matrices; i++)
    reset_ith_plotmatrix(i);
  if (gp.matrices) free(++gp.matrices);
  gp.matrices = NULL;
  gp.n_matrices = 0;
  
  for (i=1; i<=gp.n_matricesT; i++)
    reset_ith_plotmatrixT(i);
  if (gp.matricesT) free(++gp.matricesT);
  gp.matricesT = NULL;
  gp.n_matricesT = 0;
  
  gp.n_data = gp.n_vectors + gp.n_matrices + gp.n_matricesT;
  
  if (gp.title != NULL)
    free(gp.title);
  gp.title = NULL;
  {
    static struct plotgraphtype gp0 = {
      NULL, /* char *title; */
      0, -OFFSET_BASE, /* int x, y; */
      0, /* int color_kind_flag; */
      0, /* int color_axis_flag; */
      0, 0, /* int palette_from, palette_to; */
      R3_PERSPECTIVE, /* int r3kind; */
      SMALL_FONT, 2, /* int tick_font, tick_fontsize; */
      AXIS_C-1, /* int n_axes; */
      NULL, /* struct plotaxistype *axes; */
      0, /* int n_data; */
      0, /* int n_vectors; */
      NULL, /* struct plotvectortype *vectors; */
      0, /* int n_matrices; */
      NULL, /* struct plotmatrixtype *matrices; */
      0, /* int n_matricesT; */
      NULL, /* struct plotmatrixTtype *matricesT; */
    };
    gp = gp0;
  }
}
/*
 * プロット軸に関する設定関数群
 */
/* グラフプロットの次元 */
void set_plotgraph_n_axes(int n_axes)
{
  int i;
  
  gp.axes = gp.axes?gp.axes-((AXIS_C-1)+1):NULL;
  gp.axes = gp.axes?
    realloc(gp.axes,sizeof(struct plotaxistype)*(n_axes-(AXIS_C-1))):
      malloc(sizeof(struct plotaxistype)*(n_axes-(AXIS_C-1)));
  gp.axes = gp.axes?gp.axes+((AXIS_C-1)+1):NULL;
  for (i=gp.n_axes+1; i<=n_axes; i++)
    gp.axes[i] = plotaxis0;
  gp.n_axes = n_axes;
}
/* プロット軸のタイトルとスケーリングタイプ */
void set_ith_plotaxis(int ith, char *title, int scale_type)
{
  void set_ith_plotaxis_title(int ith, char *title);
  void set_ith_plotaxis_scale_type(int ith, int scale_type);

  set_ith_plotaxis_title(ith, title);
  set_ith_plotaxis_scale_type(ith, scale_type);
}
/* プロット軸のタイトル */
void set_ith_plotaxis_title(int ith, char *title)
{
  if (gp.n_axes < ith)
    set_plotgraph_n_axes(ith);
  if (title) {
    gp.axes[ith].title = gp.axes[ith].title?
      realloc(gp.axes[ith].title,sizeof(char)*(strlen(title)+1)):
        malloc(sizeof(char)*(strlen(title)+1));
    strcpy(gp.axes[ith].title, title);
  }
  else {
    if (gp.axes[ith].title) free(gp.axes[ith].title);
    gp.axes[ith].title = NULL;
  }
  /* officious default settings */
  if (gp.n_axes == 2) {
    if (ith == AXIS_X) {
      gp.axes[ith].x = OFFSET_BASE*4;
      gp.axes[ith].y = OFFSET_BASE*4;
    }
    else if (ith == AXIS_Y) {
      gp.axes[ith].x = -OFFSET_BASE*4;
      gp.axes[ith].y = -OFFSET_BASE*2;
    }
  }
  if (ith == AXIS_C) {
    gp.axes[ith].x = OFFSET_BASE*2;
    gp.axes[ith].y = -OFFSET_BASE*2;
  }
}
/* プロット軸のスケーリングタイプ */
void set_ith_plotaxis_scale_type(int ith, int scale_type)
{
  if (gp.n_axes < ith)
    set_plotgraph_n_axes(ith);
  gp.axes[ith].scale_type = scale_type;
}
/* プロット軸のフラグ(主軸,チック,零軸を描くか否か) */
void set_ith_plotaxis_flags(int ith,
                            int axis_flag, int tick_flag, int zero_flag)
{
  if (gp.n_axes < ith)
    set_plotgraph_n_axes(ith);
  gp.axes[ith].axis_flag = axis_flag;
  gp.axes[ith].tick_flag = tick_flag;
  gp.axes[ith].zero_flag = zero_flag;
}
/* 軸のレンジ */
void set_ith_plotaxis_range(int ith, Float from_range, Float to_range)
{
  if (gp.n_axes < ith)
    set_plotgraph_n_axes(ith);
  gp.axes[ith].from_range = from_range;
  gp.axes[ith].to_range = to_range;
}
/* 軸のチックの描く場所 */
void set_ith_plotaxis_tick(int ith,
                           Float from_tick, Float to_tick, int div_tick)
{
  if (gp.n_axes < ith)
    set_plotgraph_n_axes(ith);
  gp.axes[ith].from_tick = from_tick;
  gp.axes[ith].to_tick = to_tick;
  gp.axes[ith].div_tick = div_tick;
}
/* プロット軸のリセット */
void reset_ith_plotaxis(int ith)
{
  if (gp.axes[ith].title != NULL)
    free(gp.axes[ith].title);
  gp.axes[ith].title = NULL;
}
void reset_x_plotaxis(void) { reset_ith_plotaxis(AXIS_X); }
void reset_y_plotaxis(void) { reset_ith_plotaxis(AXIS_Y); }
void reset_z_plotaxis(void) { reset_ith_plotaxis(AXIS_Z); }
void reset_w_plotaxis(void) { reset_ith_plotaxis(AXIS_W); }
void reset_c_plotaxis(void) { reset_ith_plotaxis(AXIS_C); }
/*
 * プロットベクトルに関する設定関数群
 */
/* プロットベクトルの数 */
void set_plotgraph_n_vectors(int n_vectors)
{
  int i;

  gp.vectors = gp.vectors?
    realloc(++gp.vectors,sizeof(struct plotvectortype)*n_vectors):
      malloc(sizeof(struct plotvectortype)*n_vectors);
  gp.vectors--;
  for (i=gp.n_vectors+1; i<=n_vectors; i++)
    gp.vectors[i] = plotvector0;
  gp.n_vectors = n_vectors;
  gp.n_data = gp.n_vectors + gp.n_matrices + gp.n_matricesT;
}
/* プロットベクトルのタイトル */
void set_ith_plotvector_title(int ith, char *title)
{
  if (gp.n_vectors < ith)
    set_plotgraph_n_vectors(ith);
  if (title) {
    gp.vectors[ith].title = gp.vectors[ith].title?
      realloc(gp.vectors[ith].title,sizeof(char)*(strlen(title)+1)):
      malloc(sizeof(char)*(strlen(title)+1));
    strcpy(gp.vectors[ith].title, title);
  }
  else {
    if (gp.vectors[ith].title) free(gp.vectors[ith].title);
    gp.vectors[ith].title = NULL;
  }
  /* officious default settings */
  gp.vectors[ith].x = -OFFSET_BASE*6;
  gp.vectors[ith].y = OFFSET_BASE*4 + OFFSET_BASE*4*(gp.n_data-1);
}
#define set_plotvector_title(title) \
        set_ith_plotvector_title(1,title)
/* プロットベクトルのデータ */
void set_ith_plotvector_data(int ith, long nl, long nh, Float *data)
{
  void set_ith_plotvector_axis(int ith, int axis, int index);
  void set_ith_plotvector_kinds(int ith, unsigned long plotkind,
                                int colorkind, int linekind, int pointkind);

  if (gp.n_vectors < ith)
    set_plotgraph_n_vectors(ith);
  gp.vectors[ith].nl = nl;
  gp.vectors[ith].nh = nh;
  gp.vectors[ith].data = data;
  /* officious default settings */
  set_ith_plotvector_axis(ith, AXIS_X, 0);
  set_ith_plotvector_axis(ith, AXIS_Y, 1);
  set_ith_plotvector_kinds(ith, gp.vectors[ith].plotkind,
                           gp.n_data-1, gp.n_data-1, gp.n_data-1);
}
/* プロットベクトルのタイトルとデータ */
void set_ith_plotvector(int ith, char *title,
                        long nl, long nh, Float *data)
{
  set_ith_plotvector_title(ith, title);
  set_ith_plotvector_data(ith, nl, nh, data);
}
/* プロットベクトルの軸へ対応 */
void set_ith_plotvector_axis(int ith, int axis, int index)
{
  if (gp.n_vectors < ith)
    set_plotgraph_n_vectors(ith);
  if (gp.vectors[ith].n_axes_are < gp.n_axes) {
    int i;

    gp.vectors[ith].axes_are = gp.vectors[ith].axes_are?
      gp.vectors[ith].axes_are+((AXIS_C-1)+1):NULL;
    gp.vectors[ith].axes_are = gp.vectors[ith].axes_are?
      realloc(gp.vectors[ith].axes_are,sizeof(int)*(gp.n_axes-(AXIS_C-1))):
        malloc(sizeof(int)*(gp.n_axes-(AXIS_C-1)));
    gp.vectors[ith].axes_are = gp.vectors[ith].axes_are?
      gp.vectors[ith].axes_are-((AXIS_C-1)+1):NULL;
    for (i=gp.vectors[ith].n_axes_are+1; i<=gp.n_axes; i++)
      /* impossible -1, because 0 means index, 1 means data[](= data[1][]) */
      gp.vectors[ith].axes_are[i] = -1;
    gp.vectors[ith].n_axes_are = gp.n_axes;
  }
  if (AXIS_C<=axis && axis<=gp.n_axes && -1<=index && index<=1) {
    gp.vectors[ith].axes_are[axis] = index;
    /* officious default settings */
    if (index==0 && gp.axes[axis].scale_type==SCALE_DEC) {
      set_ith_plotaxis_range(axis, gp.vectors[ith].nl, gp.vectors[ith].nh);
    }
  }
}
/* プロットベクトルの値の取得 */
Float ith_plotvector_axis_value(int ith_vector,
                                int ith_axis, int ith)
{
  Float value = 0.0;

  if (ith_vector <= gp.n_vectors)
    if (gp.vectors[ith_vector].axes_are[ith_axis] == 1) {
      if (gp.vectors[ith_vector].nl <= ith
          && ith <= gp.vectors[ith_vector].nh)
        value = gp.vectors[ith_vector].data[ith];
    }
    else if (gp.vectors[ith_vector].axes_are[ith_axis] == 0)
      value = (Float)ith;
  return value;
}
/* プロットベクトルのプロット種類の設定 */
void set_ith_plotvector_kinds(int ith, unsigned long plotkind,
                              int colorkind, int linekind, int pointkind)
{
  if (gp.n_vectors < ith)
    set_plotgraph_n_vectors(ith);
  gp.vectors[ith].plotkind = plotkind;
  gp.vectors[ith].colorkind = colorkind%N_COLOR_KINDS;
  gp.vectors[ith].linekind = linekind%N_LINE_KINDS;
  gp.vectors[ith].pointkind = pointkind%N_POINT_KINDS;
}
/* プロットベクトルのプロット種におけるプロットステップ */
void set_ith_plotvector_step(int ith, unsigned long plotkind, int plotstep)
{
  if (gp.n_vectors < ith)
    set_plotgraph_n_vectors(ith);
  if (plotkind & PLOT_LINE)
    gp.vectors[ith].plotstep[0] = plotstep;
  if (plotkind & PLOT_DOT)
    gp.vectors[ith].plotstep[1] = plotstep;
  if (plotkind & PLOT_POINT)
    gp.vectors[ith].plotstep[2] = plotstep;
  if (plotkind & PLOT_ERROR)
    gp.vectors[ith].plotstep[3] = plotstep;
}
/* プロットベクトルのリセット */
void reset_ith_plotvector(int ith)
{
  gp.vectors[ith].axes_are = gp.vectors[ith].axes_are?
    gp.vectors[ith].axes_are+((AXIS_C-1)+1):NULL;
  if (gp.vectors[ith].axes_are) free(gp.vectors[ith].axes_are);
  gp.vectors[ith].axes_are = NULL;
  gp.vectors[ith].n_axes_are = AXIS_C-1;
  if (gp.vectors[ith].title) free(gp.vectors[ith].title);
  gp.vectors[ith].title = NULL;
}
void reset_plotvector(void) { reset_ith_plotvector(1); }
/*
 * プロットマトリックスに関する設定関数群
 */
/* プロットマトリックスの数 */
void set_plotgraph_n_matrices(int n_matrices)
{
  int i;

  gp.matrices = gp.matrices?
    realloc(++gp.matrices,sizeof(struct plotmatrixtype)*n_matrices):
      malloc(sizeof(struct plotmatrixtype)*n_matrices);
  gp.matrices--;
  for (i=gp.n_matrices+1; i<=n_matrices; i++)
    gp.matrices[i] = plotmatrix0;
  gp.n_matrices = n_matrices;
  gp.n_data = gp.n_vectors + gp.n_matrices + gp.n_matricesT;
}
/* プロットマトリックスのタイトル */
void set_ith_plotmatrix_title(int ith, char *title)
{
  if (gp.n_matrices < ith)
    set_plotgraph_n_matrices(ith);
  if (title) {
    gp.matrices[ith].title = gp.matrices[ith].title?
      realloc(gp.matrices[ith].title,sizeof(char)*(strlen(title)+1)):
      malloc(sizeof(char)*(strlen(title)+1));
    strcpy(gp.matrices[ith].title, title);
  }
  else {
    if (gp.matrices[ith].title) free(gp.matrices[ith].title);
    gp.matrices[ith].title = NULL;
  }
  /* officious default settings */
  gp.matrices[ith].x = -OFFSET_BASE*6;
  gp.matrices[ith].y = OFFSET_BASE*4 + OFFSET_BASE*4*(gp.n_data-1);
}
/* プロットマトリックスのデータ */
void set_ith_plotmatrix_data(int ith,
                             long nrl, long nrh, long ncl, long nch, Float **data)
{
  int i;
  void set_ith_plotmatrix_axis(int ith, int axis, int index);
  void set_ith_plotmatrix_kinds(int ith, unsigned long plotkind,
                                int colorkind, int linekind, int pointkind);

  if (gp.n_matrices < ith)
    set_plotgraph_n_matrices(ith);
  gp.matrices[ith].nrl = nrl;
  gp.matrices[ith].nrh = nrh;
  gp.matrices[ith].ncl = ncl;
  gp.matrices[ith].nch = nch;
  gp.matrices[ith].data = data;
  /* officious default settings */
  for (i=0; i<=min(gp.n_axes,nch-ncl+1); i++)
    set_ith_plotmatrix_axis(ith, AXIS_X+i, ncl+i);
  set_ith_plotmatrix_kinds(ith, PLOT_LINE,
                           gp.n_data-1, gp.n_data-1, gp.n_data-1);
  if (gp.color_axis_flag && gp.n_axes == 2 && nch-ncl+1 > 2)
    set_ith_plotmatrix_axis(ith, AXIS_C, ncl+2);
  if (gp.color_axis_flag && gp.n_axes == 3 && nch-ncl+1 > 3)
    set_ith_plotmatrix_axis(ith, AXIS_C, ncl+3);
}
/* プロットマトリックスのタイトルとデータ */
void set_ith_plotmatrix(int ith, char *title,
                        long nrl, long nrh, long ncl, long nch, Float **data)
{
  set_ith_plotmatrix_title(ith, title);
  set_ith_plotmatrix_data(ith, nrl, nrh, ncl, nch, data);
}
/* プロットマトリックスの軸へ対応 */
void set_ith_plotmatrix_axis(int ith, int axis, int index)
{
  if (gp.n_matrices < ith)
    set_plotgraph_n_matrices(ith);
  if (gp.matrices[ith].n_axes_are < gp.n_axes) {
    int i;

    gp.matrices[ith].axes_are = gp.matrices[ith].axes_are?
      gp.matrices[ith].axes_are+((AXIS_C-1)+1):NULL;
    gp.matrices[ith].axes_are = gp.matrices[ith].axes_are?
      realloc(gp.matrices[ith].axes_are,sizeof(int)*(gp.n_axes-(AXIS_C-1))):
        malloc(sizeof(int)*(gp.n_axes-(AXIS_C-1)));
    gp.matrices[ith].axes_are = gp.matrices[ith].axes_are?
      gp.matrices[ith].axes_are-((AXIS_C-1)+1):NULL;
    for (i=gp.matrices[ith].n_axes_are+1; i<=gp.n_axes; i++)
      /* ncl-2 means no-axis, for ncl-1 means index, ncl-nch means data[][] */
      gp.matrices[ith].axes_are[i] = gp.matrices[ith].ncl-2;
    gp.matrices[ith].n_axes_are = gp.n_axes;
  }
  if (AXIS_C<=axis && axis<=gp.n_axes
      && gp.matrices[ith].ncl-2<=index && index<=gp.matrices[ith].nch) {
    gp.matrices[ith].axes_are[axis] = index;
    /* officious default settings */
    if (index==gp.matrices[ith].ncl-1
        && gp.axes[axis].scale_type==SCALE_DEC) {
      set_ith_plotaxis_range(axis,
                             gp.matrices[ith].nrl, gp.matrices[ith].nrh);
    }
  }
}
/* プロットマトリックスの値の取得 */
Float ith_plotmatrix_axis_value(int ith_matrix,
                                int ith_axis, int ith)
{
  Float value = 0.0;

  if (ith_matrix <= gp.n_matrices)
    if (gp.matrices[ith_matrix].ncl
        <= gp.matrices[ith_matrix].axes_are[ith_axis]
        && gp.matrices[ith_matrix].axes_are[ith_axis]
        <= gp.matrices[ith_matrix].nch) {
      if (gp.matrices[ith_matrix].nrl <= ith
          && ith <= gp.matrices[ith_matrix].nrh)
        value = gp.matrices[ith_matrix].data
      [ith][gp.matrices[ith_matrix].axes_are[ith_axis]];
    }
    else if (gp.matrices[ith_matrix].axes_are[ith_axis] ==
	     gp.matrices[ith_matrix].ncl-1)
      value = (Float)ith;
  return value;
}
/* プロットマトリックスのプロット種類の設定 */
void set_ith_plotmatrix_kinds(int ith, unsigned long plotkind,
                              int colorkind, int linekind, int pointkind)
{
  if (gp.n_matrices < ith)
    set_plotgraph_n_matrices(ith);
  gp.matrices[ith].plotkind = plotkind;
  gp.matrices[ith].colorkind = colorkind%N_COLOR_KINDS;
  gp.matrices[ith].linekind = linekind%N_LINE_KINDS;
  gp.matrices[ith].pointkind = pointkind%N_POINT_KINDS;
}
/* プロットマトリックスのプロット種におけるプロットステップ */
void set_ith_plotmatrix_step(int ith, unsigned long plotkind, int plotstep)
{
  if (gp.n_matrices < ith)
    set_plotgraph_n_matrices(ith);
  if (plotkind & PLOT_LINE)
    gp.matrices[ith].plotstep[0] = plotstep;
  if (plotkind & PLOT_DOT)
    gp.matrices[ith].plotstep[1] = plotstep;
  if (plotkind & PLOT_POINT)
    gp.matrices[ith].plotstep[2] = plotstep;
  if (plotkind & PLOT_ERROR)
    gp.matrices[ith].plotstep[3] = plotstep;
}
/* プロットマトリックスのリセット */
void reset_ith_plotmatrix(int ith)
{
  gp.matrices[ith].axes_are = gp.matrices[ith].axes_are?
    gp.matrices[ith].axes_are+((AXIS_C-1)+1):NULL;
  if (gp.matrices[ith].axes_are) free(gp.matrices[ith].axes_are);
  gp.matrices[ith].axes_are = NULL;
  gp.matrices[ith].n_axes_are = AXIS_C-1;
  if (gp.matrices[ith].title) free(gp.matrices[ith].title);
  gp.matrices[ith].title = NULL;
}
void reset_plotmatrix(void) { reset_ith_plotmatrix(1); }
/*
 * プロットマトリックスTに関する設定関数群
 */
/* プロットマトリックスTの数 */
void set_plotgraph_n_matricesT(int n_matricesT)
{
  int i;

  gp.matricesT = gp.matricesT?
    realloc(++gp.matricesT,sizeof(struct plotmatrixTtype)*n_matricesT):
      malloc(sizeof(struct plotmatrixTtype)*n_matricesT);
  gp.matricesT--;
  for (i=gp.n_matricesT+1; i<=n_matricesT; i++)
    gp.matricesT[i] = plotmatrixT0;
  gp.n_matricesT = n_matricesT;
  gp.n_data = gp.n_vectors + gp.n_matrices + gp.n_matricesT;
}
/* プロットマトリックスのタイトル */
void set_ith_plotmatrixT_title(int ith, char *title)
{
  if (gp.n_matricesT < ith)
    set_plotgraph_n_matricesT(ith);
  if (title) {
    gp.matricesT[ith].title = gp.matricesT[ith].title?
      realloc(gp.matricesT[ith].title,sizeof(char)*(strlen(title)+1)):
        malloc(sizeof(char)*(strlen(title)+1));
    strcpy(gp.matricesT[ith].title, title);
  }
  else {
    if (gp.matricesT[ith].title) free(gp.matricesT[ith].title);
    gp.matricesT[ith].title = NULL;
  }
  /* officious default settings */
  gp.matricesT[ith].x = -OFFSET_BASE*6;
  gp.matricesT[ith].y = OFFSET_BASE*4 + OFFSET_BASE*4*(gp.n_data-1);
}
/* プロットマトリックスのデータ */
void set_ith_plotmatrixT_data(int ith,
                              long nrl, long nrh, long ncl, long nch,
                              Float **data)
{
  int i;
  void set_ith_plotmatrixT_axis(int ith, int axis, int index);
  void set_ith_plotmatrixT_kinds(int ith, unsigned long plotkind,
                                 int colorkind, int linekind, int pointkind);

  if (gp.n_matricesT < ith)
    set_plotgraph_n_matricesT(ith);
  gp.matricesT[ith].nrl = nrl;
  gp.matricesT[ith].nrh = nrh;
  gp.matricesT[ith].ncl = ncl;
  gp.matricesT[ith].nch = nch;
  gp.matricesT[ith].data = data;
  /* officious default settings */
  for (i=0; i<=min(gp.n_axes,nrh-nrl+1); i++)
    set_ith_plotmatrixT_axis(ith, AXIS_X+i, nrl+i);
  set_ith_plotmatrixT_kinds(ith, PLOT_LINE,
                            gp.n_data-1, gp.n_data-1, gp.n_data-1);
  if (gp.color_axis_flag && gp.n_axes == 2 && nch-ncl+1 > 2)
    set_ith_plotmatrixT_axis(ith, AXIS_C, nrl+2);
  if (gp.color_axis_flag && gp.n_axes == 3 && nch-ncl+1 > 3)
    set_ith_plotmatrixT_axis(ith, AXIS_C, nrl+3);
}
/* プロットマトリックスのタイトルとデータ */
void set_ith_plotmatrixT(int ith, char *title,
                        long nrl, long nrh, long ncl, long nch, Float **data)
{
  set_ith_plotmatrixT_title(ith, title);
  set_ith_plotmatrixT_data(ith, nrl, nrh, ncl, nch, data);
}
/* プロットマトリックスTの軸へ対応 */
void set_ith_plotmatrixT_axis(int ith, int axis, int index)
{
  if (gp.n_matricesT < ith)
    set_plotgraph_n_matricesT(ith);
  if (gp.matricesT[ith].n_axes_are < gp.n_axes) {
    int i;

    gp.matricesT[ith].axes_are = gp.matricesT[ith].axes_are?
      gp.matricesT[ith].axes_are+((AXIS_C-1)+1):NULL;
    gp.matricesT[ith].axes_are = gp.matricesT[ith].axes_are?
      realloc(gp.matricesT[ith].axes_are,sizeof(int)*(gp.n_axes+1)):
        malloc(sizeof(int)*(gp.n_axes+1));
    gp.matricesT[ith].axes_are = gp.matricesT[ith].axes_are?
      gp.matricesT[ith].axes_are-((AXIS_C-1)+1):NULL;
    for (i=gp.matricesT[ith].n_axes_are+1; i<=gp.n_axes; i++)
      /* nrl-2 means no-axis, for nrl-1 means index, nrl-nrh means data[][] */
      gp.matricesT[ith].axes_are[i] = gp.matricesT[ith].nrl-2;
    gp.matricesT[ith].n_axes_are = gp.n_axes;
  }
  if (AXIS_C<=axis && axis<=gp.n_axes
      && gp.matricesT[ith].nrl-2<=index && index<=gp.matricesT[ith].nrh) {
    gp.matricesT[ith].axes_are[axis] = index;
    /* officious default settings */
    if (index==gp.matricesT[ith].nrl-1
        && gp.axes[axis].scale_type==SCALE_DEC) {
      set_ith_plotaxis_range(axis,
                             gp.matricesT[ith].ncl, gp.matricesT[ith].nch);
    }
  }
}
/* プロットマトリックスTの値の取得 */
Float ith_plotmatrixT_axis_value(int ith_matrixT,
                                 int ith_axis, int ith)
{
  Float value = 0.0;

  if (ith_matrixT <= gp.n_matricesT)
    if (gp.matricesT[ith_matrixT].nrl
        <= gp.matricesT[ith_matrixT].axes_are[ith_axis]
        && gp.matricesT[ith_matrixT].axes_are[ith_axis]
        <= gp.matricesT[ith_matrixT].nrh) {
      if (gp.matricesT[ith_matrixT].ncl <= ith
          && ith <= gp.matricesT[ith_matrixT].nch)
        value = gp.matricesT[ith_matrixT].data
          [gp.matricesT[ith_matrixT].axes_are[ith_axis]][ith];
    }
    else if (gp.matricesT[ith_matrixT].axes_are[ith_axis] ==
	     gp.matricesT[ith_matrixT].nrl-1)
      value = (Float)ith;
  return value;
}
/* プロットマトリックスTのプロット種類の設定 */
void set_ith_plotmatrixT_kinds(int ith, unsigned long plotkind,
                               int colorkind, int linekind, int pointkind)
{
  if (gp.n_matricesT < ith)
    set_plotgraph_n_matricesT(ith);
  gp.matricesT[ith].plotkind = plotkind;
  gp.matricesT[ith].colorkind = colorkind%N_COLOR_KINDS;
  gp.matricesT[ith].linekind = linekind%N_LINE_KINDS;
  gp.matricesT[ith].pointkind = pointkind%N_POINT_KINDS;
}
/* プロットマトリックスTのプロット種におけるプロットステップ */
void set_ith_plotmatrixT_step(int ith, unsigned long plotkind, int plotstep)
{
  if (gp.n_matricesT < ith)
    set_plotgraph_n_matricesT(ith);
  if (plotkind & PLOT_LINE)
    gp.matricesT[ith].plotstep[0] = plotstep;
  if (plotkind & PLOT_DOT)
    gp.matricesT[ith].plotstep[1] = plotstep;
  if (plotkind & PLOT_POINT)
    gp.matricesT[ith].plotstep[2] = plotstep;
  if (plotkind & PLOT_ERROR)
    gp.matricesT[ith].plotstep[3] = plotstep;
}
/* プロットマトリックスTのリセット */
void reset_ith_plotmatrixT(int ith)
{
  gp.matricesT[ith].axes_are = gp.matricesT[ith].axes_are?
    gp.matricesT[ith].axes_are+((AXIS_C-1)+1):NULL;
  if (gp.matricesT[ith].axes_are) free(gp.matricesT[ith].axes_are);
  gp.matricesT[ith].axes_are = NULL;
  gp.matricesT[ith].n_axes_are = AXIS_C-1;
  if (gp.matricesT[ith].title) free(gp.matricesT[ith].title);
  gp.matricesT[ith].title = NULL;
}
void reset_plotmatrixT(void) { reset_ith_plotmatrixT(1); }
/*
 * 描画関係の内部マクロ
 */
/* ログ座標軸のためのマクロ */
#define l2(axis,value) \
        (log((value)/gp.axes[axis].from_range)\
	*(gp.axes[axis].to_range-gp.axes[axis].from_range)\
	/log(gp.axes[axis].to_range/gp.axes[axis].from_range)\
	+gp.axes[axis].from_range)
#define lga(axis,value) \
        ((gp.axes[axis].scale_type==SCALE_LOG10)?l2(axis,value):(value))
#define lgavectors(ith,i,v) do {\
        int ith_axis; for (ith_axis=1;ith_axis<=gp.n_axes;ith_axis++) {\
        v[ith_axis-1]=((gp.axes[ith].scale_type==SCALE_LOG10)\
        ?l2(ith_axis,ith_plotvector_axis_value(ith,ith_axis,i))\
        :(ith_plotvector_axis_value(ith,ith_axis,i)));}} while (0)
#define lgamatrices(ith,i,v) do {\
        int ith_axis; for (ith_axis=1;ith_axis<=gp.n_axes;ith_axis++) {\
        v[ith_axis-1]=((gp.axes[ith].scale_type==SCALE_LOG10)\
        ?l2(ith_axis,ith_plotmatrix_axis_value(ith,ith_axis,i))\
        :(ith_plotmatrix_axis_value(ith,ith_axis,i)));}} while (0)
#define lgamatricesT(ith,i,v) do {\
        int ith_axis; for (ith_axis=1;ith_axis<=gp.n_axes;ith_axis++) {\
        v[ith_axis-1]=((gp.axes[ith].scale_type==SCALE_LOG10)\
        ?l2(ith_axis,ith_plotmatrixT_axis_value(ith,ith_axis,i))\
        :(ith_plotmatrixT_axis_value(ith,ith_axis,i)));}} while (0)
/* カラーのためのマクロ */
#define wvcv(w) \
        (((w)-gp.axes[AXIS_C].from_range)*(vp.bottom-vp.top)\
        /(gp.axes[AXIS_C].to_range-gp.axes[AXIS_C].from_range))
#define wvch(w) \
        (((w)-gp.axes[AXIS_C].from_range)*(vp.right-vp.left)\
        /(gp.axes[AXIS_C].to_range-gp.axes[AXIS_C].from_range))
#define saxc(w) do {\
        if (gp.color_axis_flag)setcolor_(w);} while (0)
#define gaxc(w) \
        (gp.color_axis_flag?getcolor_(w):getcolor())
#define spc(ith) do {\
        if (gp.color_kind_flag)setplotcolor(ith);} while (0)
#define gpc(ith) \
        (gp.color_kind_flag?getplotcolor(ith):getcolor())
#define gaxpc(w,ith) \
        (gp.color_axis_flag?getcolor_(w):gp.color_kind_flag\
        ?getplotcolor(ith):getcolor())
#define swap(a,b) do {Float tmp;tmp=b;b=a;a=tmp;} while (0)
#if 0 /* old, before version 3.02 generic 19991101 */
/* 3次元描画のためのマクロ */
#define r3_lines(n,p) \
        (gp.r3kind==R3_ROTATION)?linesr3_(n,p):\
        linesp3_(n,p)
#define r3_line(x0,y0,z0,x1,y1,z1) \
        (gp.r3kind==R3_ROTATION)?liner3_(x0,y0,z0,x1,y1,z1):\
        linep3_(x0,y0,z0,x1,y1,z1)
#define r3_lineto(x,y,z) \
        (gp.r3kind==R3_ROTATION)?linetor3_(x,y,z):\
        linetop3_(x,y,z)
#define r3_putpixels(n,p,c) \
        (gp.r3kind==R3_ROTATION)?putpixelsr3_(n,p,c):\
        putpixelsp3_(n,p,c)
#define r3_putpixel(x,y,z,c) \
        (gp.r3kind==R3_ROTATION)?putpixelr3_(x,y,z,c):\
        putpixelp3_(x,y,z,c)
#define r3_putpoints(n,p) \
        (gp.r3kind==R3_ROTATION)?putpointsr3_(n,p):\
        putpointsp3_(n,p)
#define r3_putpoint(x,y,z) \
        (gp.r3kind==R3_ROTATION)?putpointr3_(x,y,z):\
        putpointp3_(x,y,z)
#define r3_moveto(x,y,z) \
        (gp.r3kind==R3_ROTATION)?movetor3_(x,y,z):\
        movetop3_(x,y,z)
#define r3_outtextxy(x,y,z,s) \
        (gp.r3kind==R3_ROTATION)?outtextxyr3_(x,y,z,s):\
        outtextxyp3_(x,y,z,s)
/* n次元描画のためのマクロ */
#define rn_lines(n,p) \
        (gp.r3kind==R3_ROTATION)?linesrn_(n,p):\
        linespn_(n,p)
#define rn_line(v0,v1) \
        (gp.r3kind==R3_ROTATION)?linern_(v0,v1):\
        linepn_(v0,v1)
#define rn_lineto(v) \
        (gp.r3kind==R3_ROTATION)?linetorn_(v):\
        linetopn_(v)
#define rn_putpixels(n,p,c) \
        (gp.r3kind==R3_ROTATION)?putpixelsrn_(n,p,c):\
        putpixelspn_(n,p,c)
#define rn_putpixel(v,c) \
        (gp.r3kind==R3_ROTATION)?putpixelrn_(v,c):\
        putpixelpn_(v,c)
#define rn_putpoints(n,p) \
        (gp.r3kind==R3_ROTATION)?putpointsrn_(n,p):\
        putpointspn_(n,p)
#define rn_putpoint(v) \
        (gp.r3kind==R3_ROTATION)?putpointrn_(v):\
        putpointpn_(v)
#define rn_moveto(v) \
        (gp.r3kind==R3_ROTATION)?movetorn_(v):\
        movetopn_(v)
#define rn_outtextxy(v,s) \
        (gp.r3kind==R3_ROTATION)?outtextxyrn_(v,s):\
        outtextxypn_(v,s)
#define rn_cube(v0,v,f) \
        (gp.r3kind==R3_ROTATION)?cubern_(v0,v,f):\
        cubepn_(v0,v,f)
#else /* since version 3.02 generic 19991101 */
#if 0 /* following macros are very slowly to compile, so it's off */
/* 3次元描画のためのマクロ */
#define r3_lines(n,p) do {\
        if (gp.r3kind==R3_ROTATION) linesr3_(n,p);\
        else if (gp.r3kind==R3_PERSPECTIVE) linesp3_(n,p);\
        else liness3_(n,p); } while (0)
#define r3_line(x0,y0,z0,x1,y1,z1) do {\
        if (gp.r3kind==R3_ROTATION) liner3_(x0,y0,z0,x1,y1,z1);\
        else if (gp.r3kind==R3_PERSPECTIVE) linep3_(x0,y0,z0,x1,y1,z1);\
        else lines3_(x0,y0,z0,x1,y1,z1); } while (0)
#define r3_lineto(x,y,z) do {\
        if (gp.r3kind==R3_ROTATION) linetor3_(x,y,z);\
        else if (gp.r3kind==R3_PERSPECTIVE) linetop3_(x,y,z);\
        else linetos3_(x,y,z); } while (0)
#define r3_putpixels(n,p,c) do {\
        if (gp.r3kind==R3_ROTATION) putpixelsr3_(n,p,c);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelsp3_(n,p,c);\
        else putpixelss3_(n,p,c); } while (0)
#define r3_putpixel(x,y,z,c) do {\
        if (gp.r3kind==R3_ROTATION) putpixelr3_(x,y,z,c);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelp3_(x,y,z,c);\
        else putpixels3_(x,y,z,c); } while (0)
#define r3_putpoints(n,p) do {\
        if (gp.r3kind==R3_ROTATION) putpointsr3_(n,p);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpointsp3_(n,p);\
        else putpointss3_(n,p); } while (0)
#define r3_putpoint(x,y,z) do {\
        if (gp.r3kind==R3_ROTATION) putpointr3_(x,y,z);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpointp3_(x,y,z);\
        else putpoints3_(x,y,z); } while (0)
#define r3_moveto(x,y,z) do {\
        if (gp.r3kind==R3_ROTATION) movetor3_(x,y,z);\
        else if (gp.r3kind==R3_PERSPECTIVE) movetop3_(x,y,z);\
        else movetos3_(x,y,z); } while (0)
#define r3_outtextxy(x,y,z,s) do {\
        if (gp.r3kind==R3_ROTATION) outtextxyr3_(x,y,z,s);\
        else if (gp.r3kind==R3_PERSPECTIVE) outtextxyp3_(x,y,z,s);\
        else outtextxys3_(x,y,z,s); } while (0)
/* n次元描画のためのマクロ */
#define rn_lines(n,p) do {\
        if (gp.r3kind==R3_ROTATION) linesrn_(n,p);\
        else if (gp.r3kind==R3_PERSPECTIVE) linespn_(n,p);\
        else linessn_(n,p); } while (0)
#define rn_line(v0,v1) do {\
        if (gp.r3kind==R3_ROTATION) linern_(v0,v1);\
        else if (gp.r3kind==R3_PERSPECTIVE) linepn_(v0,v1);\
        else linesn_(v0,v1); } while (0)
#define rn_lineto(v) do {\
        if (gp.r3kind==R3_ROTATION) linetorn_(v);\
        else if (gp.r3kind==R3_PERSPECTIVE) linetopn_(v);\
        else linetosn_(v); } while (0)
#define rn_putpixels(n,p,c) do {\
        if (gp.r3kind==R3_ROTATION) putpixelsrn_(n,p,c);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelspn_(n,p,c);\
        else putpixelssn_(n,p,c); } while (0)
#define rn_putpixel(v,c) do {\
        if (gp.r3kind==R3_ROTATION) putpixelrn_(v,c);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelpn_(v,c);\
        else putpixelsn_(v,c); } while (0)
#define rn_putpoints(n,p) do {\
        if (gp.r3kind==R3_ROTATION) putpointsrn_(n,p);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpointspn_(n,p);\
        else putpointssn_(n,p); } while (0)
#define rn_putpoint(v) do {\
        if (gp.r3kind==R3_ROTATION) putpointrn_(v);\
        else if (gp.r3kind==R3_PERSPECTIVE) putpointpn_(v);\
        else putpointsn_(v); } while (0)
#define rn_moveto(v) do {\
        if (gp.r3kind==R3_ROTATION) movetorn_(v);\
        else if (gp.r3kind==R3_PERSPECTIVE) movetopn_(v);\
        else movetosn_(v); } while (0)
#define rn_outtextxy(v,s) do {\
        if (gp.r3kind==R3_ROTATION) outtextxyrn_(v,s);\
        else if (gp.r3kind==R3_PERSPECTIVE) outtextxypn_(v,s);\
        else outtextxysn_(v,s); } while (0)
#define rn_cube(v0,v,f) do {\
        if (gp.r3kind==R3_ROTATION) cubern_(v0,v,f);\
        else if (gp.r3kind==R3_PERSPECTIVE) cubepn_(v0,v,f);\
        else cubesn_(v0,v,f); } while (0)
#else
/* 3次元描画のための関数 */
void r3_lines(int n,double *p) {
        if (gp.r3kind==R3_ROTATION) linesr3_(n,p);
        else if (gp.r3kind==R3_PERSPECTIVE) linesp3_(n,p);
        else liness3_(n,p); }
void r3_line(double x0,double y0,double z0,double x1,double y1,double z1) {
        if (gp.r3kind==R3_ROTATION) liner3_(x0,y0,z0,x1,y1,z1);
        else if (gp.r3kind==R3_PERSPECTIVE) linep3_(x0,y0,z0,x1,y1,z1);
        else lines3_(x0,y0,z0,x1,y1,z1); }
void r3_lineto(double x,double y,double z) {
        if (gp.r3kind==R3_ROTATION) linetor3_(x,y,z);
        else if (gp.r3kind==R3_PERSPECTIVE) linetop3_(x,y,z);
        else linetos3_(x,y,z); }
void r3_putpixels(int n,double *p,int c) {
        if (gp.r3kind==R3_ROTATION) putpixelsr3_(n,p,c);
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelsp3_(n,p,c);
        else putpixelss3_(n,p,c); }
void r3_putpixel(double x,double y,double z,int c) {
        if (gp.r3kind==R3_ROTATION) putpixelr3_(x,y,z,c);
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelp3_(x,y,z,c);
        else putpixels3_(x,y,z,c); }
void r3_putpoints(int n,double *p) {
        if (gp.r3kind==R3_ROTATION) putpointsr3_(n,p);
        else if (gp.r3kind==R3_PERSPECTIVE) putpointsp3_(n,p);
        else putpointss3_(n,p); }
void r3_putpoint(double x,double y,double z) {
        if (gp.r3kind==R3_ROTATION) putpointr3_(x,y,z);
        else if (gp.r3kind==R3_PERSPECTIVE) putpointp3_(x,y,z);
        else putpoints3_(x,y,z); }
void r3_moveto(double x,double y,double z) {
        if (gp.r3kind==R3_ROTATION) movetor3_(x,y,z);
        else if (gp.r3kind==R3_PERSPECTIVE) movetop3_(x,y,z);
        else movetos3_(x,y,z); }
void r3_outtextxy(double x,double y,double z,char *s) {
        if (gp.r3kind==R3_ROTATION) outtextxyr3_(x,y,z,s);
        else if (gp.r3kind==R3_PERSPECTIVE) outtextxyp3_(x,y,z,s);
        else outtextxys3_(x,y,z,s); }
/* n次元描画のための関数 */
void rn_lines(int n,double **p) {
        if (gp.r3kind==R3_ROTATION) linesrn_(n,p);
        else if (gp.r3kind==R3_PERSPECTIVE) linespn_(n,p);
        else linessn_(n,p); }
void rn_line(double *v0,double *v1) {
        if (gp.r3kind==R3_ROTATION) linern_(v0,v1);
        else if (gp.r3kind==R3_PERSPECTIVE) linepn_(v0,v1);
        else linesn_(v0,v1); }
void rn_lineto(double *v) {
        if (gp.r3kind==R3_ROTATION) linetorn_(v);
        else if (gp.r3kind==R3_PERSPECTIVE) linetopn_(v);
        else linetosn_(v); }
void rn_putpixels(int n,double **p,int c) {
        if (gp.r3kind==R3_ROTATION) putpixelsrn_(n,p,c);
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelspn_(n,p,c);
        else putpixelssn_(n,p,c); }
void rn_putpixel(double *v,int c) {
        if (gp.r3kind==R3_ROTATION) putpixelrn_(v,c);
        else if (gp.r3kind==R3_PERSPECTIVE) putpixelpn_(v,c);
        else putpixelsn_(v,c); }
void rn_putpoints(int n,double **p) {
        if (gp.r3kind==R3_ROTATION) putpointsrn_(n,p);
        else if (gp.r3kind==R3_PERSPECTIVE) putpointspn_(n,p);
        else putpointssn_(n,p); }
void rn_putpoint(double *v) {
        if (gp.r3kind==R3_ROTATION) putpointrn_(v);
        else if (gp.r3kind==R3_PERSPECTIVE) putpointpn_(v);
        else putpointsn_(v); }
void rn_moveto(double *v) {
        if (gp.r3kind==R3_ROTATION) movetorn_(v);
        else if (gp.r3kind==R3_PERSPECTIVE) movetopn_(v);
        else movetosn_(v); }
void rn_outtextxy(double *v,char *s) {
        if (gp.r3kind==R3_ROTATION) outtextxyrn_(v,s);
        else if (gp.r3kind==R3_PERSPECTIVE) outtextxypn_(v,s);
        else outtextxysn_(v,s); }
void rn_cube(double *v0,double *v,int f) {
        if (gp.r3kind==R3_ROTATION) cubern_(v0,v,f);
        else if (gp.r3kind==R3_PERSPECTIVE) cubepn_(v0,v,f);
        else cubesn_(v0,v,f); }
#endif
#endif
/*
 * 内部関数
 */
static void cp_vec(long N, double a[], double b[])
{
  long i;

  for (i=0; i<N; i++)
    b[i] = a[i];
}
static double **mat(long M, long N)
{
  long i;
  double **m;

  m = (double **)malloc(sizeof(double*)*M);
  m[0] = (double *)malloc(sizeof(double)*(M*N));
  for (i=1; i<M; i++)
    m[i] = m[i-1] + N;
  return m;
}
static void free_mat(double **m)
{
  free(m[0]);
  free(m);
}
/*
 * 設定された全ての情報を描画する
 */
/* カラー軸を描く */
void plotgraph_color_axis(void)
{
  int i;
  int ith_axis = AXIS_C;
  char buf[256];
  struct viewporttype vp;

  if (gp.color_axis_flag && gp.color_axis_flag == !0) { /* RIGHT_COLOR_AXIS */
    int c = getcolor();
    getviewsettings(&vp);
    /* カラーバーを描く */
    if ((gp.palette_from==gp.palette_to) && gp.palette_from == 0) {
      gp.palette_from = 1;
      gp.palette_to = getmaxcolor()-1;
    }
    co_coloring(gp.palette_from, gp.palette_to,
                gp.axes[ith_axis].from_range, gp.axes[ith_axis].to_range);
    for (i=0; i<abs(gp.palette_to-gp.palette_from)+1; i++) {
      setcolor(/*gp.palette_from+i*/gp.palette_to-i);
      setfillstyle(SOLID_FILL, /*gp.palette_from+i*/gp.palette_to-i);
      bar((vp.right-vp.left)+OFFSET_BASE*2,
          (vp.bottom-vp.top)*i/(abs(gp.palette_to-gp.palette_from)+1),
          (vp.right-vp.left)+OFFSET_BASE*4,
          (vp.bottom-vp.top)*(i+1)/(abs(gp.palette_to-gp.palette_from)+1));
    }
    setcolor(c);
    if (gp.axes[ith_axis].title) {
      /* 軸のタイトルを描く */
      struct textsettingstype ts;

      gettextsettings(&ts);
      settextjustify(LEFT_TEXT, BOTTOM_TEXT);
      outtextxy((vp.right-vp.left)+gp.axes[ith_axis].x,
                0+gp.axes[ith_axis].y,
                gp.axes[ith_axis].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.axes[ith_axis].axis_flag) {
      /* 主軸を描く */
      struct linesettingstype ls;
 
      getlinesettings(&ls);
      setlinestyle(SOLID_LINE, 0, 2);
      line((vp.right-vp.left)+OFFSET_BASE*4, 0,
           (vp.right-vp.left)+OFFSET_BASE*4, (vp.bottom-vp.top));
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].tick_flag
        && (gp.axes[ith_axis].from_tick!=gp.axes[ith_axis].to_tick)) {
      /* チックを描く */
      Float tick;
      int tick_height, tick_offset;
      struct textsettingstype ts;
      struct linesettingstype ls;
      
      gettextsettings(&ts);
      getlinesettings(&ls);
      settextstyle(gp.tick_font, HORIZ_DIR, gp.tick_fontsize);
      setlinestyle(SOLID_LINE, 0, 1);
      for (i=0; i<=gp.axes[ith_axis].div_tick; i++) {
        tick = (gp.axes[ith_axis].scale_type==SCALE_DEC)?
          get_tick_axis(i,gp.axes[ith_axis].div_tick,
                        gp.axes[ith_axis].from_tick,
                        gp.axes[ith_axis].to_tick)
            :get_tick_log10_axis(i,gp.axes[ith_axis].div_tick,
                                 gp.axes[ith_axis].from_tick,
                                 gp.axes[ith_axis].to_tick);
        if (tick
            <min(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            ||max(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            <tick)
          continue;
        tick_height = gp.axes[ith_axis].tick_height;
        tick_offset = gp.axes[ith_axis].tick_offset;
        line((vp.right-vp.left)+OFFSET_BASE*4,
             (vp.bottom-vp.top)-wvcv(lga(AXIS_C,tick)),
             (vp.right-vp.left)+OFFSET_BASE*4+tick_height,
             (vp.bottom-vp.top)-wvcv(lga(AXIS_C,tick)));
        settextjustify(LEFT_TEXT, CENTER_TEXT);
        sprintf(buf, (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g",
                tick);
        outtextxy((vp.right-vp.left)+OFFSET_BASE*4+tick_offset,
                  (vp.bottom-vp.top)-wvcv(lga(AXIS_C,tick)), buf);
      }
      settextstyle(ts.font, ts.direction, ts.charsize);
      settextjustify(ts.horiz, ts.vert);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].zero_flag) {
      /* 零軸を描く */
      /*struct linesettingstype ls;/# 描くと美しくないので描かない #/

      getlinesettings(&ls);
      setlinestyle(DASHED_LINE, 0, 0);
      if (gp.axes[ith_axis].from_range*gp.axes[ith_axis].to_range < 0)
      line((vp.right-vp.left)+OFFSET_BASE*2,
           (vp.bottom-vp.top)-wvcv(0.0),
           (vp.right-vp.left)+OFFSET_BASE*4,
           (vp.bottom-vp.top)-wvcv(0.0));
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);*/
    }
  }
  else if (gp.color_axis_flag && gp.color_axis_flag == 2) { /* TOP_COLOR_AXIS */
    int c = getcolor();
    getviewsettings(&vp);
    /* カラーバーを描く */
    if ((gp.palette_from==gp.palette_to) && gp.palette_from == 0) {
      gp.palette_from = 1;
      gp.palette_to = getmaxcolor()-1;
    }
    co_coloring(gp.palette_from, gp.palette_to,
                gp.axes[ith_axis].from_range, gp.axes[ith_axis].to_range);
    for (i=0; i<abs(gp.palette_to-gp.palette_from)+1; i++) {
      setcolor(gp.palette_from+i/*gp.palette_to-i*/);
      setfillstyle(SOLID_FILL, gp.palette_from+i/*gp.palette_to-i*/);
      bar((vp.right-vp.left)*i/(abs(gp.palette_to-gp.palette_from)+1),
          0-OFFSET_BASE*2,
          (vp.right-vp.left)*(i+1)/(abs(gp.palette_to-gp.palette_from)+1),
	  0-OFFSET_BASE*4);
    }
    setcolor(c);
    if (gp.axes[ith_axis].title) {
      /* 軸のタイトルを描く */
      struct textsettingstype ts;

      gettextsettings(&ts);
      settextjustify(LEFT_TEXT, BOTTOM_TEXT);
      outtextxy((vp.right-vp.left)+gp.axes[ith_axis].x,
                0+gp.axes[ith_axis].y,
                gp.axes[ith_axis].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.axes[ith_axis].axis_flag) {
      /* 主軸を描く */
      struct linesettingstype ls;
 
      getlinesettings(&ls);
      setlinestyle(SOLID_LINE, 0, 2);
      line(0, 0-OFFSET_BASE*4,
	   (vp.right-vp.left)+1/* ! */, 0-OFFSET_BASE*4);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].tick_flag
        && (gp.axes[ith_axis].from_tick!=gp.axes[ith_axis].to_tick)) {
      /* チックを描く */
      Float tick;
      int tick_height, tick_offset;
      struct textsettingstype ts;
      struct linesettingstype ls;
      
      gettextsettings(&ts);
      getlinesettings(&ls);
      settextstyle(gp.tick_font, HORIZ_DIR, gp.tick_fontsize);
      setlinestyle(SOLID_LINE, 0, 1);
      for (i=0; i<=gp.axes[ith_axis].div_tick; i++) {
        tick = (gp.axes[ith_axis].scale_type==SCALE_DEC)?
          get_tick_axis(i,gp.axes[ith_axis].div_tick,
                        gp.axes[ith_axis].from_tick,
                        gp.axes[ith_axis].to_tick)
            :get_tick_log10_axis(i,gp.axes[ith_axis].div_tick,
                                 gp.axes[ith_axis].from_tick,
                                 gp.axes[ith_axis].to_tick);
        if (tick
            <min(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            ||max(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            <tick)
          continue;
        tick_height = gp.axes[ith_axis].tick_height;
        tick_offset = gp.axes[ith_axis].tick_offset;
        line(/*(vp.right-vp.left)-*/wvch(lga(AXIS_C,tick)),
             0-OFFSET_BASE*4,
             /*(vp.right-vp.left)-*/wvch(lga(AXIS_C,tick)),
             0-OFFSET_BASE*4-tick_height);
        settextjustify(CENTER_TEXT, BOTTOM_TEXT);
        sprintf(buf, (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g",
                tick);
        outtextxy(/*(vp.right-vp.left)-*/wvch(lga(AXIS_C,tick)),
                  0-OFFSET_BASE*4-tick_offset, buf);
      }
      settextstyle(ts.font, ts.direction, ts.charsize);
      settextjustify(ts.horiz, ts.vert);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].zero_flag) {
      /* 零軸を描く */
      /*struct linesettingstype ls;/# 描くと美しくないので描かない #/

      getlinesettings(&ls);
      setlinestyle(DASHED_LINE, 0, 0);
      if (gp.axes[ith_axis].from_range*gp.axes[ith_axis].to_range < 0)
      line((vp.right-vp.left)-wvch(0.0),
           0-OFFSET_BASE*2,
           (vp.right-vp.left)-wvch(0.0),
           0-OFFSET_BASE*4);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);*/
    }
  }
  else if (gp.color_axis_flag && gp.color_axis_flag == 3) { /* BOTTOM_COLOR_AXIS */
    int c = getcolor();
    getviewsettings(&vp);
    /* カラーバーを描く */
    if ((gp.palette_from==gp.palette_to) && gp.palette_from == 0) {
      gp.palette_from = 1;
      gp.palette_to = getmaxcolor()-1;
    }
    co_coloring(gp.palette_from, gp.palette_to,
                gp.axes[ith_axis].from_range, gp.axes[ith_axis].to_range);
    for (i=0; i<abs(gp.palette_to-gp.palette_from)+1; i++) {
      setcolor(gp.palette_from+i/*gp.palette_to-i*/);
      setfillstyle(SOLID_FILL, gp.palette_from+i/*gp.palette_to-i*/);
      bar((vp.right-vp.left)*i/(abs(gp.palette_to-gp.palette_from)+1),
          (vp.bottom-vp.top)+OFFSET_BASE*5,
          (vp.right-vp.left)*(i+1)/(abs(gp.palette_to-gp.palette_from)+1),
	  (vp.bottom-vp.top)+OFFSET_BASE*7);
    }
    setcolor(c);
    if (gp.axes[ith_axis].title) {
      /* 軸のタイトルを描く */
      struct textsettingstype ts;

      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, TOP_TEXT);
      outtextxy(0-gp.axes[ith_axis].x,
                (vp.bottom-vp.top)-gp.axes[ith_axis].y,
                gp.axes[ith_axis].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.axes[ith_axis].axis_flag) {
      /* 主軸を描く */
      struct linesettingstype ls;
 
      getlinesettings(&ls);
      setlinestyle(SOLID_LINE, 0, 2);
      line(0, (vp.bottom-vp.top)+OFFSET_BASE*7,
	   (vp.right-vp.left)+1/* ! */, (vp.bottom-vp.top)+OFFSET_BASE*7);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].tick_flag
        && (gp.axes[ith_axis].from_tick!=gp.axes[ith_axis].to_tick)) {
      /* チックを描く */
      Float tick;
      int tick_height, tick_offset;
      struct textsettingstype ts;
      struct linesettingstype ls;
      
      gettextsettings(&ts);
      getlinesettings(&ls);
      settextstyle(gp.tick_font, HORIZ_DIR, gp.tick_fontsize);
      setlinestyle(SOLID_LINE, 0, 1);
      for (i=0; i<=gp.axes[ith_axis].div_tick; i++) {
        tick = (gp.axes[ith_axis].scale_type==SCALE_DEC)?
          get_tick_axis(i,gp.axes[ith_axis].div_tick,
                        gp.axes[ith_axis].from_tick,
                        gp.axes[ith_axis].to_tick)
            :get_tick_log10_axis(i,gp.axes[ith_axis].div_tick,
                                 gp.axes[ith_axis].from_tick,
                                 gp.axes[ith_axis].to_tick);
        if (tick
            <min(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            ||max(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            <tick)
          continue;
        tick_height = gp.axes[ith_axis].tick_height;
        tick_offset = gp.axes[ith_axis].tick_offset;
        line(/*(vp.right-vp.left)-*/wvch(lga(AXIS_C,tick)),
             (vp.bottom-vp.top)+OFFSET_BASE*7,
             /*(vp.right-vp.left)-*/wvch(lga(AXIS_C,tick)),
             (vp.bottom-vp.top)+OFFSET_BASE*7+tick_height);
        settextjustify(CENTER_TEXT, TOP_TEXT);
        sprintf(buf, (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g",
                tick);
        outtextxy(/*(vp.right-vp.left)-*/wvch(lga(AXIS_C,tick)),
                  (vp.bottom-vp.top)+OFFSET_BASE*7+tick_offset, buf);
      }
      settextstyle(ts.font, ts.direction, ts.charsize);
      settextjustify(ts.horiz, ts.vert);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].zero_flag) {
      /* 零軸を描く */
      /*struct linesettingstype ls;/# 描くと美しくないので描かない #/

      getlinesettings(&ls);
      setlinestyle(DASHED_LINE, 0, 0);
      if (gp.axes[ith_axis].from_range*gp.axes[ith_axis].to_range < 0)
      line((vp.right-vp.left)-wvch(0.0),
           (vp.bottom-vp.top)+OFFSET_BASE*5,
           (vp.right-vp.left)-wvch(0.0),
           (vp.bottom-vp.top)+OFFSET_BASE*7);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);*/
    }
  }
}
/* 2次元グラフの軸を描く */
void plotgraph_2d_axes(void)
{
  int i;
  int ith_axis;
  char buf[256];

  setwindow_(gp.axes[AXIS_X].from_range, gp.axes[AXIS_Y].to_range,
             gp.axes[AXIS_X].to_range, gp.axes[AXIS_Y].from_range);
  for (ith_axis=AXIS_X; ith_axis<=AXIS_Y; ith_axis++) {
    if (gp.axes[ith_axis].title) {
      /* 軸のタイトルを描く */
      struct viewporttype vp;
      struct textsettingstype ts;

      getviewsettings(&vp);
      gettextsettings(&ts);
      if (ith_axis == AXIS_X) {
        settextjustify(RIGHT_TEXT, TOP_TEXT);
        outtextxy((vp.right-vp.left)+gp.axes[ith_axis].x,
                  (vp.bottom-vp.top)+gp.axes[ith_axis].y,
                  gp.axes[ith_axis].title);
      }
      else {
        settextjustify(LEFT_TEXT, BOTTOM_TEXT);
        outtextxy(0+gp.axes[ith_axis].x, 0+gp.axes[ith_axis].y,
                  gp.axes[ith_axis].title);
      }
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.axes[ith_axis].axis_flag) {
      /* 主軸を描く */
      struct linesettingstype ls;

      getlinesettings(&ls);
      setlinestyle(SOLID_LINE, 0, 2);
      if (ith_axis == AXIS_X) {
        line_(gp.axes[AXIS_X].from_range, gp.axes[AXIS_Y].from_range,
              gp.axes[AXIS_X].to_range, gp.axes[AXIS_Y].from_range);
        line_(gp.axes[AXIS_X].to_range, gp.axes[AXIS_Y].to_range,
              gp.axes[AXIS_X].from_range, gp.axes[AXIS_Y].to_range);
      }
      else {
        line_(gp.axes[AXIS_X].from_range, gp.axes[AXIS_Y].from_range,
              gp.axes[AXIS_X].from_range, gp.axes[AXIS_Y].to_range);
        line_(gp.axes[AXIS_X].to_range, gp.axes[AXIS_Y].to_range,
              gp.axes[AXIS_X].to_range, gp.axes[AXIS_Y].from_range);
      }
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].tick_flag
        && (gp.axes[ith_axis].from_tick!=gp.axes[ith_axis].to_tick)) {
      /* チックを描く */
      Float tick;
      int tick_height, tick_offset;
      struct viewporttype vp;
      struct textsettingstype ts;
      struct linesettingstype ls;

      getviewsettings(&vp);
      gettextsettings(&ts);
      getlinesettings(&ls);
      settextstyle(gp.tick_font, HORIZ_DIR, gp.tick_fontsize);
      setlinestyle(SOLID_LINE, 0, 1);
      for (i=0; i<=gp.axes[ith_axis].div_tick; i++) {
        tick = (gp.axes[ith_axis].scale_type==SCALE_DEC)?
          get_tick_axis(i,gp.axes[ith_axis].div_tick,
                        gp.axes[ith_axis].from_tick,
                        gp.axes[ith_axis].to_tick)
            :get_tick_log10_axis(i,gp.axes[ith_axis].div_tick,
                                 gp.axes[ith_axis].from_tick,
                                 gp.axes[ith_axis].to_tick);
        if (tick
            <min(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            ||max(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            <tick)
          continue;
        tick_height = gp.axes[ith_axis].tick_height;
        tick_offset = gp.axes[ith_axis].tick_offset;
        if (ith_axis == AXIS_X) {
          line(wvx(lga(AXIS_X,tick)), (vp.bottom-vp.top),
               wvx(lga(AXIS_X,tick)), (vp.bottom-vp.top)-tick_height);
          settextjustify(CENTER_TEXT, TOP_TEXT);
          sprintf(buf,
                  (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g", tick);
          outtextxy(wvx(lga(AXIS_X,tick)), (vp.bottom-vp.top)+tick_offset,
                    buf);
        }
	else {
          line(0, wvy(lga(AXIS_Y,tick)),
               0+tick_height, wvy(lga(AXIS_Y,tick)));
          settextjustify(RIGHT_TEXT, CENTER_TEXT);
          sprintf(buf,
                  (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g", tick);
          outtextxy(-tick_offset, wvy(lga(AXIS_Y,tick)), buf);
        }
      }
      settextstyle(ts.font, ts.direction, ts.charsize);
      settextjustify(ts.horiz, ts.vert);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].zero_flag) {
      /* 零軸を描く */
      struct linesettingstype ls;

      getlinesettings(&ls);
      setlinestyle(DASHED_LINE, 0, 0);
      if (gp.axes[(ith_axis==AXIS_X)?AXIS_Y:AXIS_X].from_range
          *gp.axes[(ith_axis==AXIS_X)?AXIS_Y:AXIS_X].to_range < 0)
        if (ith_axis == AXIS_X)
          line_(gp.axes[AXIS_X].from_range, 0.0,
                gp.axes[AXIS_X].to_range, 0.0);
        else
          line_(0.0, gp.axes[AXIS_Y].from_range,
                0.0, gp.axes[AXIS_Y].to_range);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
  }
}
/* 2次元グラフのデータを描く */
void plotgraph_2d_data(void)
{
  long i;
  int ith;
  struct linesettingstype ls;
  
  getlinesettings(&ls);
  /* ベクトルタイプを描く */
  for (ith=1; ith<=gp.n_vectors; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;

    if (gp.vectors[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.vectors[ith].x,
                gp.vectors[ith].y, gp.vectors[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.vectors[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r2p;
	int step;

	step = gp.vectors[ith].plotstep[0]?
	  gp.vectors[ith].plotstep[0]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)/step;
	m = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)%step;
	if (m > 0) n++;
	r2p = (double*)malloc(sizeof(double)*n*2);
	spc(gp.vectors[ith].colorkind);
	setplotline(gp.vectors[ith].linekind);
	for (i0=i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  long j = (i-i0)/step;

	  r2p[2*j+0]=lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i));
	  r2p[2*j+1]=lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i));
	}
	lines_(n, r2p);
	free(r2p);
      } else
#endif
      {
	int step;

	step = gp.vectors[ith].plotstep[0]?
	  gp.vectors[ith].plotstep[0]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.vectors[ith].colorkind);
	setplotline(gp.vectors[ith].linekind);
	i = gp.vectors[ith].nl;
	moveto_(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)));
	for (i=gp.vectors[ith].nl+step;
	     i<=gp.vectors[ith].nh; i+=step) {
	  saxc(lga(AXIS_C,ith_plotvector_axis_value(ith,AXIS_C,i)));
	  lineto_(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		  lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)));
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.vectors[ith].title) {
        spc(gp.vectors[ith].colorkind);
        line((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE,
             gp.vectors[ith].y,
             (vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*4,
             gp.vectors[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.vectors[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r2p;
	int step;

	step = gp.vectors[ith].plotstep[1]?
	  gp.vectors[ith].plotstep[1]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)/step;
	m = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)%step;
	if (m > 0) n++;
	r2p = (double*)malloc(sizeof(double)*n*2);
	for (i0=i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  long j = (i-i0)/step;

	  r2p[2*j+0]=lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i));
	  r2p[2*j+1]=lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i));
	}
	putpixels_(n, r2p,
		   gaxpc(lga(AXIS_C,
			     ith_plotvector_axis_value(ith,AXIS_C,i)),
			 gp.vectors[ith].colorkind));
	free(r2p);
      } else
#endif
      {
	int step;

	step = gp.vectors[ith].plotstep[1]?
	  gp.vectors[ith].plotstep[1]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step)
	  putpixel_(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)),
		    gaxpc(lga(AXIS_C,
			      ith_plotvector_axis_value(ith,AXIS_C,i)),
			  gp.vectors[ith].colorkind));
      }
      /* データのドット種を描く */
      if (gp.vectors[ith].title)
        putpixel((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*5/2,
                 gp.vectors[ith].y,
                 gpc(gp.vectors[ith].colorkind));
    }
    if (gp.vectors[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.vectors[ith].plotstep[2]?
	gp.vectors[ith].plotstep[2]:
	  max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.vectors[ith].nl;
           i<=gp.vectors[ith].nh; i+=step) {
	setplotpoint(gp.vectors[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotvector_axis_value(ith,AXIS_C,i)),
			   gp.vectors[ith].colorkind));
        putpoint_(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
                  lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)));
      }
      /* データのポイント種を描く */
      if (gp.vectors[ith].title) {
	setplotpoint(gp.vectors[ith].pointkind,
		     gpc(gp.vectors[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*5/2,
                 gp.vectors[ith].y);
      }
    }
  }
  /* マトリックスタイプを描く */
  for (ith=1; ith<=gp.n_matrices; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.matrices[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.matrices[ith].x,
                gp.matrices[ith].y, gp.matrices[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.matrices[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r2p;
	int step;

	step = gp.matrices[ith].plotstep[0]?
	  gp.matrices[ith].plotstep[0]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/step;
	m = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)%step;
	if (m > 0) n++;
	r2p = (double*)malloc(sizeof(double)*n*2);
	spc(gp.matrices[ith].colorkind);
	setplotline(gp.matrices[ith].linekind);
	for (i0=i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  long j = (i-i0)/step;

	  r2p[2*j+0]=lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i));
	  r2p[2*j+1]=lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i));
	}
	lines_(n, r2p);
	free(r2p);
      } else
#endif
      {
	int step;

	step = gp.matrices[ith].plotstep[0]?
	  gp.matrices[ith].plotstep[0]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.matrices[ith].colorkind);
	setplotline(gp.matrices[ith].linekind);
	i = gp.matrices[ith].nrl;
	moveto_(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)));
	for (i=gp.matrices[ith].nrl+step;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  saxc(lga(AXIS_C,ith_plotmatrix_axis_value(ith,AXIS_C,i)));
	  lineto_(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		  lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)));
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.matrices[ith].title) {
        spc(gp.matrices[ith].colorkind);
        line((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE,
             gp.matrices[ith].y,
             (vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*4,
             gp.matrices[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.matrices[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r2p;
	int step;

	step = gp.matrices[ith].plotstep[1]?
	  gp.matrices[ith].plotstep[1]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/step;
	m = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)%step;
	if (m > 0) n++;
	r2p = (double*)malloc(sizeof(double)*n*2);
	for (i0=i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  long j = (i-i0)/step;

	  r2p[2*j+0]=lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i));
	  r2p[2*j+1]=lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i));
	}
	putpixels_(n, r2p,
		   gaxpc(lga(AXIS_C,
			     ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			 gp.matrices[ith].colorkind));
	free(r2p);
      } else
#endif
      {
	int step;

	step = gp.matrices[ith].plotstep[1]?
	  gp.matrices[ith].plotstep[1]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step)
	  putpixel_(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)),
		    gaxpc(lga(AXIS_C,
			      ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			  gp.matrices[ith].colorkind));
      }
      /* データのドット種を描く */
      if (gp.matrices[ith].title)
        putpixel((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*5/2,
                 gp.matrices[ith].y,
                 gpc(gp.matrices[ith].colorkind));
    }
    if (gp.matrices[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.matrices[ith].plotstep[2]?
	gp.matrices[ith].plotstep[2]:
	  max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.matrices[ith].nrl;
           i<=gp.matrices[ith].nrh; i+=step) {
	setplotpoint(gp.matrices[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			   gp.matrices[ith].colorkind));
	putpoint_(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
                  lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)));
      }
      /* データのポイント種を描く */
      if (gp.matrices[ith].title) {
	setplotpoint(gp.matrices[ith].pointkind,
		     gpc(gp.matrices[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*5/2,
                 gp.matrices[ith].y);
      }
    }
  }
  /* マトリックスTタイプを描く */
  for (ith=1; ith<=gp.n_matricesT; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.matricesT[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.matricesT[ith].x,
                gp.matricesT[ith].y, gp.matricesT[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.matricesT[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r2p;
	int step;

	step = gp.matricesT[ith].plotstep[0]?
	  gp.matricesT[ith].plotstep[0]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/step;
	m = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)%step;
	if (m > 0) n++;
	r2p = (double*)malloc(sizeof(double)*n*2);
	spc(gp.matricesT[ith].colorkind);
	setplotline(gp.matricesT[ith].linekind);
	for (i0=i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  long j = (i-i0)/step;

	  r2p[2*j+0]=lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i));
	  r2p[2*j+1]=lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i));
	}
	lines_(n, r2p);
	free(r2p);
      } else
#endif
      {
	int step;

	step = gp.matricesT[ith].plotstep[0]?
	  gp.matricesT[ith].plotstep[0]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.matricesT[ith].colorkind);
	setplotline(gp.matricesT[ith].linekind);
	i = gp.matricesT[ith].ncl;
	moveto_(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)));
	for (i=gp.matricesT[ith].ncl+step;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  saxc(lga(AXIS_C,ith_plotmatrixT_axis_value(ith,AXIS_C,i)));
	  lineto_(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		  lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)));
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.matricesT[ith].title) {
        spc(gp.matricesT[ith].colorkind);
        line((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE,
             gp.matricesT[ith].y,
             (vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*4,
             gp.matricesT[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.matricesT[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r2p;
	int step;

	step = gp.matricesT[ith].plotstep[1]?
	  gp.matricesT[ith].plotstep[1]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/step;
	m = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)%step;
	if (m > 0) n++;
	r2p = (double*)malloc(sizeof(double)*n*2);
	for (i0=i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  long j = (i-i0)/step;

	  r2p[2*j+0]=lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i));
	  r2p[2*j+1]=lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i));
	}
	putpixels_(n, r2p,
		   gaxpc(lga(AXIS_C,
			     ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			 gp.matricesT[ith].colorkind));
	free(r2p);
      } else
#endif
      {
	int step;

	step = gp.matricesT[ith].plotstep[1]?
	  gp.matricesT[ith].plotstep[1]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step)
	  putpixel_(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)),
		    gaxpc(lga(AXIS_C,
			      ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			  gp.matricesT[ith].colorkind));
      }
      /* データのドット種を描く */
      if (gp.matricesT[ith].title)
        putpixel((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*5/2,
                 gp.matricesT[ith].y,
                 gpc(gp.matricesT[ith].colorkind));
    }
    if (gp.matricesT[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.matricesT[ith].plotstep[2]?
	gp.matricesT[ith].plotstep[2]:
	  max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.matricesT[ith].ncl;
           i<=gp.matricesT[ith].nch; i+=step) {
	setplotpoint(gp.matricesT[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			   gp.matricesT[ith].colorkind));
        putpoint_(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
                  lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)));
      }
      /* データのポイント種を描く */
      if (gp.matricesT[ith].title) {
	setplotpoint(gp.matricesT[ith].pointkind,
		     gpc(gp.matricesT[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*5/2,
                 gp.matricesT[ith].y);
      }
    }
  }
  setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
}
/* 2次元グラフを描く */
void plotgraph_2d(void)
{
  plotgraph_color_axis();
  plotgraph_2d_axes();
  plotgraph_2d_data();
}
/* 3次元グラフの軸を描く */
void plotgraph_3d_axes(void)
{
  int i;
  int ith_axis;
  char buf[256];

  setrotationport_(gp.axes[AXIS_X].from_range, gp.axes[AXIS_Z].from_range,
                   gp.axes[AXIS_Y].from_range, gp.axes[AXIS_X].to_range,
                   gp.axes[AXIS_Z].to_range, gp.axes[AXIS_Y].to_range);
  for (ith_axis=AXIS_X; ith_axis<=AXIS_Z; ith_axis++) {
    if (gp.axes[ith_axis].title) {
      /* 軸のタイトルを描く */
      Float x = 0.0, y = 0.0, z = 0.0;
      struct viewporttype vp;
      struct textsettingstype ts;
      
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(CENTER_TEXT, CENTER_TEXT);
      if (ith_axis == AXIS_X) {
        x=(gp.axes[AXIS_X].from_range+gp.axes[AXIS_X].to_range)/2;
        y=(gp.axes[AXIS_Y].from_range*12+gp.axes[AXIS_Y].to_range*(-2))/10;
        z=gp.axes[AXIS_Z].from_range;
        r3_outtextxy(x, z, y, gp.axes[ith_axis].title);
      }
      else if (ith_axis == AXIS_Y) {
        x=(gp.axes[AXIS_X].from_range*(-2)+gp.axes[AXIS_X].to_range*12)/10;
        y=(gp.axes[AXIS_Y].from_range+gp.axes[AXIS_Y].to_range)/2;
        z=gp.axes[AXIS_Z].from_range;
        r3_outtextxy(x, z, y, gp.axes[ith_axis].title);
      }
      else {
        x=(gp.axes[AXIS_X].from_range*11+gp.axes[AXIS_X].to_range*(-1))/10;
        y=(gp.axes[AXIS_Y].from_range*11+gp.axes[AXIS_Y].to_range*(-1))/10;
        z=(gp.axes[AXIS_Z].from_range+gp.axes[AXIS_Z].to_range)/2;
        r3_outtextxy(x, z, y, gp.axes[ith_axis].title);
      }
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.axes[ith_axis].axis_flag) {
      /* 主軸を描く */
      struct linesettingstype ls;

      getlinesettings(&ls);
      setlinestyle(SOLID_LINE, 0, 2);
      if (ith_axis == AXIS_X) {
        r3_line(gp.axes[AXIS_X].from_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].from_range,
		gp.axes[AXIS_X].to_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].from_range);
        r3_line(gp.axes[AXIS_X].from_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].to_range,
		gp.axes[AXIS_X].to_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].to_range);
      }
      else if (ith_axis == AXIS_Z)
        r3_line(gp.axes[AXIS_X].from_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].from_range,
		gp.axes[AXIS_X].from_range,
		gp.axes[AXIS_Z].to_range,
		gp.axes[AXIS_Y].from_range);
      else if (ith_axis == AXIS_Y) {
        r3_line(gp.axes[AXIS_X].from_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].from_range,
		gp.axes[AXIS_X].from_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].to_range);
        r3_line(gp.axes[AXIS_X].to_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].from_range,
		gp.axes[AXIS_X].to_range,
		gp.axes[AXIS_Z].from_range,
		gp.axes[AXIS_Y].to_range);
      }
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].tick_flag
        && (gp.axes[ith_axis].from_tick!=gp.axes[ith_axis].to_tick)) {
      /* チックを描く */
      Float tick;
      int tick_height, tick_offset;
      Float x = 0.0, y = 0.0, z = 0.0;
      struct viewporttype vp;
      struct textsettingstype ts;
      struct linesettingstype ls;

      getviewsettings(&vp);
      gettextsettings(&ts);
      getlinesettings(&ls);
      settextstyle(gp.tick_font, HORIZ_DIR, gp.tick_fontsize);
      setlinestyle(SOLID_LINE, 0, 1);
      settextjustify(CENTER_TEXT, CENTER_TEXT);
      for (i=0; i<=gp.axes[ith_axis].div_tick; i++) {
        tick = (gp.axes[ith_axis].scale_type==SCALE_DEC)?
          get_tick_axis(i,gp.axes[ith_axis].div_tick,
                        gp.axes[ith_axis].from_tick,
                        gp.axes[ith_axis].to_tick)
            :get_tick_log10_axis(i,gp.axes[ith_axis].div_tick,
                                 gp.axes[ith_axis].from_tick,
                                 gp.axes[ith_axis].to_tick);
        if (tick
            <min(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            ||max(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            <tick)
          continue;
        tick_height = gp.axes[ith_axis].tick_height;
        tick_offset = gp.axes[ith_axis].tick_offset;
        if (ith_axis == AXIS_X) {
          x=lga(ith_axis,tick);
          y=(gp.axes[AXIS_Y].from_range*48+gp.axes[AXIS_Y].to_range*2)/50;
          z=gp.axes[AXIS_Z].from_range;
          r3_line(lga(ith_axis,tick),
		  gp.axes[AXIS_Z].from_range,
		  gp.axes[AXIS_Y].from_range, x, z, y);
          x=lga(ith_axis,tick);
          y=(gp.axes[AXIS_Y].from_range*22+gp.axes[AXIS_Y].to_range*(-2))/20;
          z=gp.axes[AXIS_Z].from_range;
        }
	else if (ith_axis == AXIS_Y) {
          x=(gp.axes[AXIS_X].from_range*2+gp.axes[AXIS_X].to_range*48)/50;
          y=lga(ith_axis,tick);
          z=gp.axes[AXIS_Z].from_range;
          r3_line(gp.axes[AXIS_X].to_range,
		  gp.axes[AXIS_Z].from_range,
		  lga(ith_axis,tick), x, z, y);
          x=(gp.axes[AXIS_X].from_range*(-2)+gp.axes[AXIS_X].to_range*22)/20;
          y=lga(ith_axis,tick);
          z=gp.axes[AXIS_Z].from_range;
        }
	else if (ith_axis == AXIS_Z) {
          if (i==0) continue;
          x=(gp.axes[AXIS_X].from_range*49+gp.axes[AXIS_X].to_range*1)/50;
          y=(gp.axes[AXIS_Y].from_range*49+gp.axes[AXIS_Y].to_range*1)/50;
          z=lga(ith_axis,tick);
          r3_line(gp.axes[AXIS_X].from_range,
		  lga(ith_axis,tick),
		  gp.axes[AXIS_Y].from_range,
		  x, z, y);
          x=(gp.axes[AXIS_X].from_range*21+gp.axes[AXIS_X].to_range*(-1))/20;
          y=(gp.axes[AXIS_Y].from_range*21+gp.axes[AXIS_Y].to_range*(-1))/20;
          z=lga(ith_axis,tick);
        }
        sprintf(buf, (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g",
                tick);
        r3_outtextxy(x, z, y, buf);
      }
      settextstyle(ts.font, ts.direction, ts.charsize);
      settextjustify(ts.horiz, ts.vert);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].zero_flag) {
      /* 零軸を描く */
      struct linesettingstype ls;

      getlinesettings(&ls);
      setlinestyle(DASHED_LINE, 0, 0);
      if (gp.axes[(ith_axis==AXIS_X)?AXIS_Y:AXIS_X].from_range
          *gp.axes[(ith_axis==AXIS_X)?AXIS_Y:AXIS_X].to_range < 0)
        if (ith_axis == AXIS_X)
          r3_line(gp.axes[AXIS_X].from_range, gp.axes[AXIS_Z].from_range, 0.0,
		  gp.axes[AXIS_X].to_range, gp.axes[AXIS_Z].from_range, 0.0);
        else if (ith_axis == AXIS_Y)
          r3_line(0.0, gp.axes[AXIS_Z].from_range, gp.axes[AXIS_Y].from_range,
		  0.0, gp.axes[AXIS_Z].from_range, gp.axes[AXIS_Y].to_range);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
  }
}
/* 3次元グラフのデータを描く */
void plotgraph_3d_data(void)
{
  long i;
  int ith;
  struct linesettingstype ls;

  getlinesettings(&ls);
  /* ベクトルタイプを描く */
  for (ith=1; ith<=gp.n_vectors; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.vectors[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.vectors[ith].x,
                gp.vectors[ith].y, gp.vectors[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.vectors[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r3p;
	int step;

	step = gp.vectors[ith].plotstep[0]?
	  gp.vectors[ith].plotstep[0]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)/step;
	m = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)%step;
	if (m > 0) n++;
	r3p = (double*)malloc(sizeof(double)*n*3);
	spc(gp.vectors[ith].colorkind);
	setplotline(gp.vectors[ith].linekind);
	for (i0=i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  long j = (i-i0)/step;

	  r3p[3*j+0]=lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i));
	  r3p[3*j+1]=lga(AXIS_Z,ith_plotvector_axis_value(ith,AXIS_Z,i));
	  r3p[3*j+2]=lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i));
	}
	r3_lines(n, r3p);
	free(r3p);
      } else
#endif
      {
	int step;

	step = gp.vectors[ith].plotstep[0]?
	  gp.vectors[ith].plotstep[0]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.vectors[ith].colorkind);
	setplotline(gp.vectors[ith].linekind);
	i = gp.vectors[ith].nl;
	r3_moveto(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		  lga(AXIS_Z,ith_plotvector_axis_value(ith,AXIS_Z,i)),
		  lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)));
	for (i=gp.vectors[ith].nl+step;
	     i<=gp.vectors[ith].nh; i+=step) {
	  saxc(lga(AXIS_C,ith_plotvector_axis_value(ith,AXIS_C,i)));
	  r3_lineto(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Z,ith_plotvector_axis_value(ith,AXIS_Z,i)),
		    lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)));
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.vectors[ith].title) {
        spc(gp.vectors[ith].colorkind);
        line((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE,
             gp.vectors[ith].y,
             (vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*4,
             gp.vectors[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.vectors[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r3p;
	int step;

	step = gp.vectors[ith].plotstep[1]?
	  gp.vectors[ith].plotstep[1]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)/step;
	m = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)%step;
	if (m > 0) n++;
	r3p = (double*)malloc(sizeof(double)*n*3);
	for (i0=i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  long j = (i-i0)/step;

	  r3p[3*j+0]=lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i));
	  r3p[3*j+1]=lga(AXIS_Z,ith_plotvector_axis_value(ith,AXIS_Z,i));
	  r3p[3*j+2]=lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i));
	}
	r3_putpixels(n, r3p,
		     gaxpc(lga(AXIS_C,
			       ith_plotvector_axis_value(ith,AXIS_C,i)),
			   gp.vectors[ith].colorkind));
	free(r3p);
      } else
#endif
      {
	int step;

	step = gp.vectors[ith].plotstep[1]?
	  gp.vectors[ith].plotstep[1]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step)
	  r3_putpixel(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		      lga(AXIS_Z,ith_plotvector_axis_value(ith,AXIS_Z,i)),
		      lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)),
		      gaxpc(lga(AXIS_C,
				ith_plotvector_axis_value(ith,AXIS_C,i)),
			    gp.vectors[ith].colorkind));
      }
      /* データのドット種を描く */
      if (gp.vectors[ith].title)
        putpixel((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*5/2,
                 gp.vectors[ith].y,
                 gpc(gp.vectors[ith].colorkind));
    }
    if (gp.vectors[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.vectors[ith].plotstep[2]?
	gp.vectors[ith].plotstep[2]:
	  max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.vectors[ith].nl;
           i<=gp.vectors[ith].nh; i+=step) {
	setplotpoint(gp.vectors[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotvector_axis_value(ith,AXIS_C,i)),
			   gp.vectors[ith].colorkind));
	r3_putpoint(lga(AXIS_X,ith_plotvector_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Z,ith_plotvector_axis_value(ith,AXIS_Z,i)),
		    lga(AXIS_Y,ith_plotvector_axis_value(ith,AXIS_Y,i)));
      }
      /* データのポイント種を描く */
      if (gp.vectors[ith].title) {
	setplotpoint(gp.vectors[ith].pointkind,
		     gpc(gp.vectors[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*5/2,
                 gp.vectors[ith].y);
      }
    }
  }
  /* マトリックスタイプを描く */
  for (ith=1; ith<=gp.n_matrices; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.matrices[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.matrices[ith].x,
                gp.matrices[ith].y, gp.matrices[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.matrices[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r3p;
	int step;

	step = gp.matrices[ith].plotstep[0]?
	  gp.matrices[ith].plotstep[0]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/step;
	m = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)%step;
	if (m > 0) n++;
	r3p = (double*)malloc(sizeof(double)*n*3);
	spc(gp.matrices[ith].colorkind);
	setplotline(gp.matrices[ith].linekind);
	for (i0=i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  long j = (i-i0)/step;

	  r3p[3*j+0]=lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i));
	  r3p[3*j+1]=lga(AXIS_Z,ith_plotmatrix_axis_value(ith,AXIS_Z,i));
	  r3p[3*j+2]=lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i));
	}
	r3_lines(n, r3p);
	free(r3p);
      } else
#endif
      {
	int step;

	step = gp.matrices[ith].plotstep[0]?
	  gp.matrices[ith].plotstep[0]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.matrices[ith].colorkind);
	setplotline(gp.matrices[ith].linekind);
	i = gp.matrices[ith].nrl;
	r3_moveto(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		  lga(AXIS_Z,ith_plotmatrix_axis_value(ith,AXIS_Z,i)),
		  lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)));
	for (i=gp.matrices[ith].nrl+step;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  saxc(lga(AXIS_C,ith_plotmatrix_axis_value(ith,AXIS_C,i)));
	  r3_lineto(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Z,ith_plotmatrix_axis_value(ith,AXIS_Z,i)),
		    lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)));
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.matrices[ith].title) {
        spc(gp.matrices[ith].colorkind);
        line((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE,
             gp.matrices[ith].y,
             (vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*4,
             gp.matrices[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.matrices[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r3p;
	int step;

	step = gp.matrices[ith].plotstep[1]?
	  gp.matrices[ith].plotstep[1]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/step;
	m = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)%step;
	if (m > 0) n++;
	r3p = (double*)malloc(sizeof(double)*n*3);
	for (i0=i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  long j = (i-i0)/step;

	  r3p[3*j+0]=lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i));
	  r3p[3*j+1]=lga(AXIS_Z,ith_plotmatrix_axis_value(ith,AXIS_Z,i));
	  r3p[3*j+2]=lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i));
	}
	r3_putpixels(n, r3p,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			   gp.matrices[ith].colorkind));
	free(r3p);
      } else
#endif
      {
	int step;

	step = gp.matrices[ith].plotstep[1]?
	  gp.matrices[ith].plotstep[1]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step)
	  r3_putpixel(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		      lga(AXIS_Z,ith_plotmatrix_axis_value(ith,AXIS_Z,i)),
		      lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)),
		      gaxpc(lga(AXIS_C,
				ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			    gp.matrices[ith].colorkind));
      }
      /* データのドット種を描く */
      if (gp.matrices[ith].title)
        putpixel((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*5/2,
                 gp.matrices[ith].y,
                 gpc(gp.matrices[ith].colorkind));
    }
    if (gp.matrices[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.matrices[ith].plotstep[2]?
	gp.matrices[ith].plotstep[2]:
	  max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.matrices[ith].nrl;
           i<=gp.matrices[ith].nrh; i+=step) {
	setplotpoint(gp.matrices[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			   gp.matrices[ith].colorkind));
        r3_putpoint(lga(AXIS_X,ith_plotmatrix_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Z,ith_plotmatrix_axis_value(ith,AXIS_Z,i)),
		    lga(AXIS_Y,ith_plotmatrix_axis_value(ith,AXIS_Y,i)));
      }
      /* データのポイント種を描く */
      if (gp.matrices[ith].title) {
	setplotpoint(gp.matrices[ith].pointkind,
		     gpc(gp.matrices[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*5/2,
                 gp.matrices[ith].y);
      }
    }
  }
  /* マトリックスTタイプを描く */
  for (ith=1; ith<=gp.n_matricesT; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.matricesT[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.matricesT[ith].x,
                gp.matricesT[ith].y, gp.matricesT[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.matricesT[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r3p;
	int step;

	step = gp.matricesT[ith].plotstep[0]?
	  gp.matricesT[ith].plotstep[0]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/step;
	m = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)%step;
	if (m > 0) n++;
	r3p = (double*)malloc(sizeof(double)*n*3);
	spc(gp.matricesT[ith].colorkind);
	setplotline(gp.matricesT[ith].linekind);
	for (i0=i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  long j = (i-i0)/step;

	  r3p[3*j+0]=lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i));
	  r3p[3*j+1]=lga(AXIS_Z,ith_plotmatrixT_axis_value(ith,AXIS_Z,i));
	  r3p[3*j+2]=lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i));
	}
	r3_lines(n, r3p);
	free(r3p);
      } else
#endif
      {
	int step;

	step = gp.matricesT[ith].plotstep[0]?
	  gp.matricesT[ith].plotstep[0]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.matricesT[ith].colorkind);
	setplotline(gp.matricesT[ith].linekind);
	i = gp.matricesT[ith].ncl;
	r3_moveto(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		  lga(AXIS_Z,ith_plotmatrixT_axis_value(ith,AXIS_Z,i)),
		  lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)));
	for (i=gp.matricesT[ith].ncl+step;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  saxc(lga(AXIS_C,ith_plotmatrixT_axis_value(ith,AXIS_C,i)));
	  r3_lineto(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Z,ith_plotmatrixT_axis_value(ith,AXIS_Z,i)),
		    lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)));
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.matricesT[ith].title) {
        spc(gp.matricesT[ith].colorkind);
        line((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE,
             gp.matricesT[ith].y,
             (vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*4,
             gp.matricesT[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.matricesT[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double *r3p;
	int step;

	step = gp.matricesT[ith].plotstep[1]?
	  gp.matricesT[ith].plotstep[1]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/step;
	m = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)%step;
	if (m > 0) n++;
	r3p = (double*)malloc(sizeof(double)*n*3);
	for (i0=i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  long j = (i-i0)/step;

	  r3p[3*j+0]=lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i));
	  r3p[3*j+1]=lga(AXIS_Z,ith_plotmatrixT_axis_value(ith,AXIS_Z,i));
	  r3p[3*j+2]=lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i));
	}
	r3_putpixels(n, r3p,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			   gp.matricesT[ith].colorkind));
	free(r3p);
      } else
#endif
      {
	int step;

	step = gp.matricesT[ith].plotstep[1]?
	  gp.matricesT[ith].plotstep[1]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step)
	  r3_putpixel(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		      lga(AXIS_Z,ith_plotmatrixT_axis_value(ith,AXIS_Z,i)),
		      lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)),
		      gaxpc(lga(AXIS_C,
				ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			    gp.matricesT[ith].colorkind));
      }
      /* データのドット種を描く */
      if (gp.matricesT[ith].title)
        putpixel((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*5/2,
                 gp.matricesT[ith].y,
                 gpc(gp.matricesT[ith].colorkind));
    }
    if (gp.matricesT[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.matricesT[ith].plotstep[2]?
	gp.matricesT[ith].plotstep[2]:
	  max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.matricesT[ith].ncl;
           i<=gp.matricesT[ith].nch; i+=step) {
	setplotpoint(gp.matricesT[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			   gp.matricesT[ith].colorkind));
        r3_putpoint(lga(AXIS_X,ith_plotmatrixT_axis_value(ith,AXIS_X,i)),
		    lga(AXIS_Z,ith_plotmatrixT_axis_value(ith,AXIS_Z,i)),
		    lga(AXIS_Y,ith_plotmatrixT_axis_value(ith,AXIS_Y,i)));
      }
      /* データのポイント種を描く */
      if (gp.matricesT[ith].title) {
	setplotpoint(gp.matricesT[ith].pointkind,
		     gpc(gp.matricesT[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*5/2,
                 gp.matricesT[ith].y);
      }
    }
  }
  setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
}
/* 3次元グラフを描く */
void plotgraph_3d(void)
{
  plotgraph_color_axis();
  plotgraph_3d_axes();
  plotgraph_3d_data();
}
/* n次元グラフの軸を描く */
void plotgraph_nd_axes(void)
{
  int i;
  int ith_axis;
  char buf[256];
  double *v0, *v;

  v0 = malloc(sizeof(double)*gp.n_axes);
  v = malloc(sizeof(double)*gp.n_axes);
  for (i=0; i<gp.n_axes; i++) {
    v0[i] = gp.axes[i+1].from_range;
    v[i] = gp.axes[i+1].to_range;
  }
  swap(v0[1],v0[2]);
  swap(v[1],v[2]);
  hyperrotationport_(gp.n_axes, v0, v);
  for (ith_axis=AXIS_X; ith_axis<=gp.n_axes; ith_axis++) {
    if (gp.axes[ith_axis].title) {
      /* 軸のタイトルを描く */
      struct viewporttype vp;
      struct textsettingstype ts;
      
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(CENTER_TEXT, CENTER_TEXT);
      for (i=0; i<gp.n_axes; i++) {
        if (i+1 == ith_axis)
          v[i]=(gp.axes[i+1].from_range*(-1)+gp.axes[i+1].to_range*11)/10;
        else
          v[i]=(gp.axes[i+1].from_range*11+gp.axes[i+1].to_range*(-1))/10;
      }
      swap(v[1],v[2]);
      rn_outtextxy(v, gp.axes[ith_axis].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.axes[ith_axis].axis_flag) {
      /* 主軸を描く */
      struct linesettingstype ls;
      
      getlinesettings(&ls);
#if 1
      setlinestyle(SOLID_LINE, 0, 2);
      for (i=0; i<gp.n_axes; i++) {
        if (i+1 == ith_axis) {
          v0[i]=gp.axes[i+1].from_range;
          v[i]=gp.axes[i+1].to_range;
        }
	else {
          v0[i]=gp.axes[i+1].from_range;
          v[i]=gp.axes[i+1].from_range;
        }
      }
      swap(v0[1],v0[2]);
      swap(v[1],v[2]);
      rn_line(v0, v);
#endif      
      setlinestyle(SOLID_LINE, 0, 0);
      if (ith_axis == AXIS_X) {
        for (i=0; i<gp.n_axes; i++) {
          v0[i]=gp.axes[i+1].from_range;
          v[i]=gp.axes[i+1].to_range;
        }
        swap(v0[1],v0[2]);
        swap(v[1],v[2]);
        rn_cube(v0, v, 0); /* ! */
      }
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].tick_flag
        && (gp.axes[ith_axis].from_tick!=gp.axes[ith_axis].to_tick)) {
      /* チックを描く */
      Float tick;
      int tick_height, tick_offset;
      struct viewporttype vp;
      struct textsettingstype ts;
      struct linesettingstype ls;
      int j;
      
      getviewsettings(&vp);
      gettextsettings(&ts);
      getlinesettings(&ls);
      settextstyle(gp.tick_font, HORIZ_DIR, gp.tick_fontsize);
      setlinestyle(SOLID_LINE, 0, 1);
      settextjustify(CENTER_TEXT, CENTER_TEXT);
      /* チックは描かない */
      for (i=0; i<=gp.axes[ith_axis].div_tick; i++) {
        tick = (gp.axes[ith_axis].scale_type==SCALE_DEC)?
          get_tick_axis(i,gp.axes[ith_axis].div_tick,
                        gp.axes[ith_axis].from_tick,
                        gp.axes[ith_axis].to_tick)
            :get_tick_log10_axis(i,gp.axes[ith_axis].div_tick,
                                 gp.axes[ith_axis].from_tick,
                                 gp.axes[ith_axis].to_tick);
        if (tick
            <min(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            ||max(gp.axes[ith_axis].from_range,gp.axes[ith_axis].to_range)
            <tick)
          continue;
        tick_height = gp.axes[ith_axis].tick_height;
        tick_offset = gp.axes[ith_axis].tick_offset;
        for (j=0; j<gp.n_axes; j++) {
          if (j+1 == ith_axis) {
            v0[j]=lga(ith_axis,tick); /* after version 3.02 generic 19990208 */
            v[j]=lga(ith_axis,tick); /* after version 3.02 generic 19990208 */
          }
	  else if (j+1 == (ith_axis+1+gp.n_axes)%gp.n_axes) {
            v0[j]=gp.axes[j+1].from_range;
            v[j]=(gp.axes[j+1].from_range*48+gp.axes[j+1].to_range*2)/50;
          }
	  else {
            v0[j]=gp.axes[j+1].from_range;
            v[j]=gp.axes[j+1].from_range;
          }
        }
        swap(v0[1],v0[2]);
        swap(v[1],v[2]);
        rn_line(v0, v);
        for (j=0; j<gp.n_axes; j++) {
          if (j+1 == ith_axis) {
            v[j]=lga(ith_axis,tick); /* after version 3.02 generic 19990208 */
          }
	  else if (j+1 == (ith_axis+1+gp.n_axes)%gp.n_axes) {
            v[j]=(gp.axes[j+1].from_range*21+gp.axes[j+1].to_range*(-1))/20;
          }
	  else {
            v[j]=gp.axes[j+1].from_range;
          }
        }
        swap(v[1],v[2]);
        sprintf(buf, (gp.axes[ith_axis].scale_type==SCALE_DEC)?"%g":"%g",
                tick);
        rn_outtextxy(v, buf);
      }
      settextstyle(ts.font, ts.direction, ts.charsize);
      settextjustify(ts.horiz, ts.vert);
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
    if (gp.axes[ith_axis].zero_flag) {
      /* 零軸を描く */
      struct linesettingstype ls;
      int j;

      getlinesettings(&ls);
      setlinestyle(DASHED_LINE, 0, 0);
      if (gp.axes[(ith_axis-1+gp.n_axes)%gp.n_axes].from_range
          *gp.axes[(ith_axis-1+gp.n_axes)%gp.n_axes].to_range < 0) {
        for (j=0; j<gp.n_axes; j++) {
          if (j+1 == ith_axis) {
            v0[j]=gp.axes[j+1].from_range;
            v[j]=gp.axes[j+1].to_range;
          }
	  else if (j+1 == (ith_axis-1+gp.n_axes)%gp.n_axes) {
            v0[j]=0.0;
            v[j]=0.0;
          }
	  else {
            v0[j]=gp.axes[j+1].from_range;
            v[j]=gp.axes[j+1].from_range;
          }
        }
        swap(v0[1],v0[2]);
        swap(v[1],v[2]);
        rn_line(v0, v);
      }
      setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
    }
  }
  free(v0);
  free(v);
}
/* n次元グラフのデータを描く */
void plotgraph_nd_data(void)
{
  long i;
  int ith;
  struct linesettingstype ls;
  double *v0, *v;

  v0 = malloc(sizeof(double)*gp.n_axes);
  v = malloc(sizeof(double)*gp.n_axes);
  getlinesettings(&ls);
  /* ベクトルタイプを描く */
  for (ith=1; ith<=gp.n_vectors; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.vectors[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.vectors[ith].x,
                gp.vectors[ith].y, gp.vectors[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.vectors[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double **rnp;
	int step;

	step = gp.vectors[ith].plotstep[0]?
	  gp.vectors[ith].plotstep[0]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)/step;
	m = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)%step;
	if (m > 0) n++;
	rnp = mat(n,gp.n_axes);
	spc(gp.vectors[ith].colorkind);
	setplotline(gp.vectors[ith].linekind);
	for (i0=i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  long j = (i-i0)/step;

	  lgavectors(ith,i,v);
	  swap(v[1],v[2]);
	  cp_vec(gp.n_axes,v,rnp[j]);
	}
	rn_lines(n, rnp);
	free_mat(rnp);
      } else
#endif
      {
	int step;

	step = gp.vectors[ith].plotstep[0]?
	  gp.vectors[ith].plotstep[0]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.vectors[ith].colorkind);
	setplotline(gp.vectors[ith].linekind);
	i = gp.vectors[ith].nl;
	lgavectors(ith,i,v);
	swap(v[1],v[2]);
	rn_moveto(v);
	for (i=gp.vectors[ith].nl+step;
	     i<=gp.vectors[ith].nh; i+=step) {
	  saxc(lga(AXIS_C,ith_plotvector_axis_value(ith,AXIS_C,i)));
	  lgavectors(ith,i,v);
	  swap(v[1],v[2]);
	  rn_lineto(v);
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.vectors[ith].title) {
        spc(gp.vectors[ith].colorkind);
        line((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE,
             gp.vectors[ith].y,
             (vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*4,
             gp.vectors[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.vectors[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double **rnp;
	int step;

	step = gp.vectors[ith].plotstep[1]?
	  gp.vectors[ith].plotstep[1]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)/step;
	m = (gp.vectors[ith].nh-gp.vectors[ith].nl+1)%step;
	if (m > 0) n++;
	rnp = mat(n,gp.n_axes);
	for (i0=i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  long j = (i-i0)/step;

	  lgavectors(ith,i,v);
	  swap(v[1],v[2]);
	  cp_vec(gp.n_axes,v,rnp[j]);
	}
	rn_putpixels(n, rnp,
		     gaxpc(lga(AXIS_C,
			       ith_plotvector_axis_value(ith,AXIS_C,i)),
			   gp.vectors[ith].colorkind));
	free_mat(rnp);
      } else
#endif
      {
	int step;

	step = gp.vectors[ith].plotstep[1]?
	  gp.vectors[ith].plotstep[1]:
	    max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.vectors[ith].nl;
	     i<=gp.vectors[ith].nh; i+=step) {
	  lgavectors(ith,i,v);
	  swap(v[1],v[2]);
	  rn_putpixel(v,
		      gaxpc(lga(AXIS_C,
				ith_plotvector_axis_value(ith,AXIS_C,i)),
			    gp.vectors[ith].colorkind));
	}
      }
      /* データのドット種を描く */
      if (gp.vectors[ith].title)
        putpixel((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*5/2,
                 gp.vectors[ith].y,
                 gpc(gp.vectors[ith].colorkind));
    }
    if (gp.vectors[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.vectors[ith].plotstep[2]?
	gp.vectors[ith].plotstep[2]:
	  max(1,(gp.vectors[ith].nh-gp.vectors[ith].nl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.vectors[ith].nl;
           i<=gp.vectors[ith].nh; i+=step) {
        lgavectors(ith,i,v);
        swap(v[1],v[2]);
	setplotpoint(gp.vectors[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotvector_axis_value(ith,AXIS_C,i)),
			   gp.vectors[ith].colorkind));
        rn_putpoint(v);
      }
      /* データのポイント種を描く */
      if (gp.vectors[ith].title) {
	setplotpoint(gp.vectors[ith].pointkind,
		     gpc(gp.vectors[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.vectors[ith].x+OFFSET_BASE*5/2,
                 gp.vectors[ith].y);
      }
    }
  }
  /* マトリックスタイプを描く */
  for (ith=1; ith<=gp.n_matrices; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.matrices[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.matrices[ith].x,
                gp.matrices[ith].y, gp.matrices[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.matrices[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double **rnp;
	int step;

	step = gp.matrices[ith].plotstep[0]?
	  gp.matrices[ith].plotstep[0]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/step;
	m = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)%step;
	if (m > 0) n++;
	rnp = mat(n,gp.n_axes);
	spc(gp.matrices[ith].colorkind);
	setplotline(gp.matrices[ith].linekind);
	for (i0=i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  long j = (i-i0)/step;

	  lgamatrices(ith,i,v);
	  swap(v[1],v[2]);
	  cp_vec(gp.n_axes,v,rnp[j]);
	}
	rn_lines(n, rnp);
	free_mat(rnp);
      } else
#endif
      {
	int step;

	step = gp.matrices[ith].plotstep[0]?
	  gp.matrices[ith].plotstep[0]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.matrices[ith].colorkind);
	setplotline(gp.matrices[ith].linekind);
	i = gp.matrices[ith].nrl;
	lgamatrices(ith,i,v);
	swap(v[1],v[2]);
	rn_moveto(v);
	for (i=gp.matrices[ith].nrl+step;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  saxc(lga(AXIS_C,ith_plotmatrix_axis_value(ith,AXIS_C,i)));
	  lgamatrices(ith,i,v);
	  swap(v[1],v[2]);
	  rn_lineto(v);
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.matrices[ith].title) {
        spc(gp.matrices[ith].colorkind);
        line((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE,
             gp.matrices[ith].y,
             (vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*4,
             gp.matrices[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.matrices[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double **rnp;
	int step;

	step = gp.matrices[ith].plotstep[1]?
	  gp.matrices[ith].plotstep[1]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/step;
	m = (gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)%step;
	if (m > 0) n++;
	rnp = mat(n,gp.n_axes);
	for (i0=i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  long j = (i-i0)/step;

	  lgamatrices(ith,i,v);
	  swap(v[1],v[2]);
	  cp_vec(gp.n_axes,v,rnp[j]);
	}
	rn_putpixels(n, rnp,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			   gp.matrices[ith].colorkind));
	free_mat(rnp);
      } else
#endif
      {
	int step;

	step = gp.matrices[ith].plotstep[1]?
	  gp.matrices[ith].plotstep[1]:
	    max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.matrices[ith].nrl;
	     i<=gp.matrices[ith].nrh; i+=step) {
	  lgamatrices(ith,i,v);
	  swap(v[1],v[2]);
	  rn_putpixel(v,
		      gaxpc(lga(AXIS_C,
				ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			    gp.matrices[ith].colorkind));
	}
      }
      /* データのドット種を描く */
      if (gp.matrices[ith].title)
        putpixel((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*5/2,
                 gp.matrices[ith].y,
                 gpc(gp.matrices[ith].colorkind));
    }
    if (gp.matrices[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.matrices[ith].plotstep[2]?
	gp.matrices[ith].plotstep[2]:
	  max(1,(gp.matrices[ith].nrh-gp.matrices[ith].nrl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.matrices[ith].nrl;
           i<=gp.matrices[ith].nrh; i+=step) {
        lgamatrices(ith,i,v);
        swap(v[1],v[2]);
	setplotpoint(gp.matrices[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrix_axis_value(ith,AXIS_C,i)),
			   gp.matrices[ith].colorkind));
        rn_putpoint(v);
      }
      /* データのポイント種を描く */
      if (gp.matrices[ith].title) {
	setplotpoint(gp.matrices[ith].pointkind,
		     gpc(gp.matrices[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.matrices[ith].x+OFFSET_BASE*5/2,
                 gp.matrices[ith].y);
      }
    }
  }
  /* マトリックスTタイプを描く */
  for (ith=1; ith<=gp.n_matricesT; ith++) {
    /* データのタイトルを描く */
    struct viewporttype vp;
    struct textsettingstype ts;
    
    if (gp.matricesT[ith].title) {
      getviewsettings(&vp);
      gettextsettings(&ts);
      settextjustify(RIGHT_TEXT, CENTER_TEXT);
      outtextxy((vp.right-vp.left)+gp.matricesT[ith].x,
                gp.matricesT[ith].y, gp.matricesT[ith].title);
      settextjustify(ts.horiz, ts.vert);
    }
    if (gp.matricesT[ith].plotkind & PLOT_LINE) {
      int c = 0;
      
      if (gp.color_kind_flag||gp.color_axis_flag) c = getcolor();
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double **rnp;
	int step;

	step = gp.matricesT[ith].plotstep[0]?
	  gp.matricesT[ith].plotstep[0]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/step;
	m = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)%step;
	if (m > 0) n++;
	rnp = mat(n,gp.n_axes);
	spc(gp.matricesT[ith].colorkind);
	setplotline(gp.matricesT[ith].linekind);
	for (i0=i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  long j = (i-i0)/step;

	  lgamatricesT(ith,i,v);
	  swap(v[1],v[2]);
	  cp_vec(gp.n_axes,v,rnp[j]);
	}
	rn_lines(n, rnp);
	free_mat(rnp);
      } else
#endif
      {
	int step;

	step = gp.matricesT[ith].plotstep[0]?
	  gp.matricesT[ith].plotstep[0]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	spc(gp.matricesT[ith].colorkind);
	setplotline(gp.matricesT[ith].linekind);
	i = gp.matricesT[ith].ncl;
	lgamatricesT(ith,i,v);
	swap(v[1],v[2]);
	rn_moveto(v);
	for (i=gp.matricesT[ith].ncl+step;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  saxc(lga(AXIS_C,ith_plotmatrixT_axis_value(ith,AXIS_C,i)));
	  lgamatricesT(ith,i,v);
	  swap(v[1],v[2]);
	  rn_lineto(v);
	}
      }
      if (gp.color_axis_flag) setcolor(c);
      /* データの線種を描く */
      if (gp.matricesT[ith].title) {
        spc(gp.matricesT[ith].colorkind);
        line((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE,
             gp.matricesT[ith].y,
             (vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*4,
             gp.matricesT[ith].y);
      }
      if (gp.color_kind_flag||gp.color_axis_flag) setcolor(c);
    }
    if (gp.matricesT[ith].plotkind & PLOT_DOT) {
#if 1 /* safe since version 3.02 generic 19991101 */
      if (!gp.color_axis_flag) {
	long n, m, i0;
	double **rnp;
	int step;

	step = gp.matricesT[ith].plotstep[1]?
	  gp.matricesT[ith].plotstep[1]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	n = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/step;
	m = (gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)%step;
	if (m > 0) n++;
	rnp = mat(n,gp.n_axes);
	for (i0=i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  long j = (i-i0)/step;

	  lgamatricesT(ith,i,v);
	  swap(v[1],v[2]);
	  cp_vec(gp.n_axes,v,rnp[j]);
	}
	rn_putpixels(n, rnp,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			   gp.matricesT[ith].colorkind));
	free_mat(rnp);
      } else
#endif
      {
	int step;

	step = gp.matricesT[ith].plotstep[1]?
	  gp.matricesT[ith].plotstep[1]:
	    max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
		DEFAULT_LIMIT_PLOT_NUMBER);
	for (i=gp.matricesT[ith].ncl;
	     i<=gp.matricesT[ith].nch; i+=step) {
	  lgamatricesT(ith,i,v);
	  swap(v[1],v[2]);
	  rn_putpixel(v,
		      gaxpc(lga(AXIS_C,
			       ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			   gp.matricesT[ith].colorkind));
	}
      }
      /* データのドット種を描く */
      if (gp.matricesT[ith].title)
        putpixel((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*5/2,
                 gp.matricesT[ith].y,
                 gpc(gp.matricesT[ith].colorkind));
    }
    if (gp.matricesT[ith].plotkind & PLOT_POINT) {
      int step;

      step = gp.matricesT[ith].plotstep[2]?
	gp.matricesT[ith].plotstep[2]:
	  max(1,(gp.matricesT[ith].nch-gp.matricesT[ith].ncl+1)/
	      DEFAULT_LIMIT_PLOT_NUMBER);
      for (i=gp.matricesT[ith].ncl;
           i<=gp.matricesT[ith].nch; i+=step) {
        lgamatricesT(ith,i,v);
        swap(v[1],v[2]);
	setplotpoint(gp.matricesT[ith].pointkind,
		     gaxpc(lga(AXIS_C,
			       ith_plotmatrixT_axis_value(ith,AXIS_C,i)),
			   gp.matricesT[ith].colorkind));
        rn_putpoint(v);
      }
      /* データのポイント種を描く */
      if (gp.matricesT[ith].title) {
	setplotpoint(gp.matricesT[ith].pointkind,
		     gpc(gp.matricesT[ith].colorkind));
        putpoint((vp.right-vp.left)+gp.matricesT[ith].x+OFFSET_BASE*5/2,
                 gp.matricesT[ith].y);
      }
    }
  }
  setlinestyle(ls.linestyle, ls.upattern, ls.thickness);
  free(v0);
  free(v);
}
/* n次元グラフを描く */
void plotgraph_nd(void)
{
  plotgraph_color_axis();
  plotgraph_nd_axes();
  plotgraph_nd_data();
}
/* 設定された形式で描く */
void plotgraph(void)
{
  long i;
  int ith_axis, ith;

  /*
   * タイトルを描く
   */
  if (gp.title) {
    struct viewporttype vp;

    getviewsettings(&vp);
    settextjustify(CENTER_TEXT, BOTTOM_TEXT);
    outtextxy((vp.right-vp.left)/2+gp.x, gp.y, gp.title);
  }
  for (ith_axis=gp.color_axis_flag?AXIS_C:AXIS_X;
       ith_axis<=gp.n_axes; ith_axis++) {
    if (gp.axes[ith_axis].from_range == gp.axes[ith_axis].to_range) {
      /*
       * レンジの自動スケール
       */
      gp.axes[ith_axis].from_range = MAXDOUBLE;
      gp.axes[ith_axis].to_range = -MAXDOUBLE;
      /* ベクトルタイプを調べる */
      for (ith=1; ith<=gp.n_vectors; ith++) {
        for (i=gp.vectors[ith].nl;
             i<=gp.vectors[ith].nh; i++) {
          gp.axes[ith_axis].from_range
            = min(gp.axes[ith_axis].from_range,
                  ith_plotvector_axis_value(ith,ith_axis,i));
          gp.axes[ith_axis].to_range
            = max(gp.axes[ith_axis].to_range,
                  ith_plotvector_axis_value(ith,ith_axis,i));
        }
      }
      /* マトリックスタイプを調べる */
      for (ith=1; ith<=gp.n_matrices; ith++) {
        for (i=gp.matrices[ith].nrl;
             i<=gp.matrices[ith].nrh; i++) {
          gp.axes[ith_axis].from_range
            = min(gp.axes[ith_axis].from_range,
                  ith_plotmatrix_axis_value(ith,ith_axis,i));
          gp.axes[ith_axis].to_range
            = max(gp.axes[ith_axis].to_range,
                  ith_plotmatrix_axis_value(ith,ith_axis,i));
        }
      }
      /* マトリックスTタイプを調べる */
      for (ith=1; ith<=gp.n_matricesT; ith++) {
        for (i=gp.matricesT[ith].ncl;
             i<=gp.matricesT[ith].nch; i++) {
          gp.axes[ith_axis].from_range
            = min(gp.axes[ith_axis].from_range,
                  ith_plotmatrixT_axis_value(ith,ith_axis,i));
          gp.axes[ith_axis].to_range
            = max(gp.axes[ith_axis].to_range,
                  ith_plotmatrixT_axis_value(ith,ith_axis,i));
        }
      }
      /*
       * チックを設定する(レンジが自動設定の場合)
       */
      if (gp.axes[ith_axis].from_tick == gp.axes[ith_axis].to_tick) {
        if (gp.axes[ith_axis].scale_type == SCALE_DEC)
          pretty_ticks_axis(gp.axes[ith_axis].from_range,
                            gp.axes[ith_axis].to_range,
                            &gp.axes[ith_axis].div_tick,
                            &gp.axes[ith_axis].from_tick,
                            &gp.axes[ith_axis].to_tick);
        else
          pretty_ticks_log10_axis(gp.axes[ith_axis].from_range,
                                  gp.axes[ith_axis].to_range,
                                  &gp.axes[ith_axis].div_tick,
                                  &gp.axes[ith_axis].from_tick,
                                  &gp.axes[ith_axis].to_tick);
        gp.axes[ith_axis].from_range = gp.axes[ith_axis].from_tick;
        gp.axes[ith_axis].to_range = gp.axes[ith_axis].to_tick;
      }
    }
    else {
      /*
       * チックを設定する(レンジがユーザー定義の場合)
       */
      if (gp.axes[ith_axis].from_tick == gp.axes[ith_axis].to_tick) {
        if (gp.axes[ith_axis].scale_type == SCALE_DEC)
          pretty_ticks_axis(gp.axes[ith_axis].from_range,
                            gp.axes[ith_axis].to_range,
                            &gp.axes[ith_axis].div_tick,
                            &gp.axes[ith_axis].from_tick,
                            &gp.axes[ith_axis].to_tick);
        else
          pretty_ticks_log10_axis(gp.axes[ith_axis].from_range,
                                  gp.axes[ith_axis].to_range,
                                  &gp.axes[ith_axis].div_tick,
                                  &gp.axes[ith_axis].from_tick,
                                  &gp.axes[ith_axis].to_tick);
      }
    }
  }
  
  if (gp.n_axes == 2)
    plotgraph_2d();
  else if (gp.n_axes == 3)
    plotgraph_3d();
  else if (gp.n_axes > 3)
    plotgraph_nd();

  reset_plotgraph();
}
