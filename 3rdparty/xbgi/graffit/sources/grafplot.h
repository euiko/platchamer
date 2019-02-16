/*
 * Graph plotting interface in graffit < grafplot.h >
 *
 * Graph-Plot Routines for Borland Graphics Interface
 *
 * Copyright (C) 1996-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAFPLOT_H_
#define _GRAFPLOT_H_

#ifndef Float
#define Float double
#endif

/*
 * �ץ�åȤμ���
 */
#define PLOT_LINE   (1L<<0)
#define PLOT_DOT    (1L<<1)
#define PLOT_POINT  (1L<<2)
#define PLOT_ERROR  (1L<<3) /* reserved future */
/*
 * ���顼�μ���
 */
enum plotcolor_kinds {
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_YELLOW,
  COLOR_CYAN,
  N_COLOR_KINDS,
};
/*
 * �饤��μ���
 */
enum plotline_kinds {
  LINE_SOLID,
  LINE_DOTTED,
  LINE_CENTER,
  LINE_DASHED,
  N_LINE_KINDS,
};
/*
 * �ݥ���Ȥμ���
 */
enum plotpoint_kinds {
  POINT_LOZENGE,
  POINT_CROSS,
  POINT_SQUARE,
  POINT_XCROSS,
  POINT_TRIANGLE,
  POINT_ASTERISK,
  POINT_CIRCLE,
  POINT_CHECKMARK,
  N_POINT_KINDS,
};
/*
 * ��������󥰤μ���
 */
enum scale_kinds {
  SCALE_DEC,
  SCALE_LOG10,
};
/*
 * ��ź���Υ���ܥ�
 */
enum axis_index {
  ERROR_H = -2, /* these indicate error elements of error bar */
  ERROR_L = -1,
  AXIS_C = 0, /* indicates another axis with color gradations */
  AXIS_X,
  AXIS_Y,
  AXIS_Z,
  AXIS_W, /* over 4 dimension needs direct index */
};
/*
 * 2��������դμ���
 */
enum r2_kinds {
  R2_NORMAL,
  R2_LOGX,
  R2_LOGY,
  R2_LOGLOG,
};
/*
 * 3��������դμ���
 */
enum r3_kinds {
  R3_ROTATION,
  R3_PERSPECTIVE,
  R3_STEREO,
  R3_STEREO2,
};
/*
 * ���ܤμ��ξ���
 */
struct plotaxistype {
  char *title;
  int x, y;
  int scale_type;
  Float from_range;
  Float to_range;
  int axis_flag;
  int tick_flag;
  int zero_flag;
  Float from_tick, to_tick;
  int div_tick;
  int tick_height;
  int tick_offset;
};
/*
 * �ץ�å��оݤΥ٥��ȥ륿����
 */
struct plotvectortype {
  char *title;
  int x, y;
  long nl, nh;
  Float *data;
  int n_axes_are;
  int *axes_are;
  unsigned long plotkind;
  int colorkind;
  int linekind;
  int pointkind;
  int plotstep[4];
};
/*
 * �ץ�å��оݤΥޥȥ�å���������
 */
struct plotmatrixtype {
  char *title;
  int x, y;
  long nrl, nrh, ncl, nch;
  Float **data;
  int n_axes_are;
  int *axes_are;
  unsigned long plotkind;
  int colorkind;
  int linekind;
  int pointkind;
  int plotstep[4];
};
/*
 * �ץ�å��оݤΥޥȥ�å���T������
 */
struct plotmatrixTtype {
  char *title;
  int x, y;
  long nrl, nrh, ncl, nch;
  Float **data;
  int n_axes_are;
  int *axes_are;
  unsigned long plotkind;
  int colorkind;
  int linekind;
  int pointkind;
  int plotstep[4];
};
/*
 * ��������Τξ���
 */
struct plotgraphtype {
  char *title;
  int x, y;
  int color_kind_flag;
  int color_axis_flag;
  int palette_from, palette_to;
  int r3kind;
  int tick_font, tick_fontsize;
  int n_axes;
  struct plotaxistype *axes;
  int n_data;
  int n_vectors;
  struct plotvectortype *vectors;
  int n_matrices;
  struct plotmatrixtype *matrices;
  int n_matricesT;
  struct plotmatrixTtype *matricesT;
};

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
 * ��������Τ�����ؿ�
 */
/* ����եץ�åȤΥ����ȥ� */
extern void set_plotgraph_title(char *title);

/* ����եץ�åȤΥ����ȥ�ȼ��� */
extern void set_plotgraph(char *title, int dimension);

/* ����եץ�åȤǥǡ����򥫥顼�Ƕ��̤��뤫 */
extern void set_plotgraph_color_kind(int color_kind_flag);

/* ����եץ�åȤǤ⤦�켡���򥫥顼��ɽ�����뤫 */
extern void set_plotgraph_color_axis(int color_axis_flag);

/* ����եץ�åȤ�2��������դμ��� */
extern void set_plotgraph_r2kind(int r2kind);

/* ����եץ�åȤ�3��������դμ��� */
extern void set_plotgraph_r3kind(int r3kind);

/* ����եץ�åȤΥꥻ�å� */
extern void reset_plotgraph(void);

/*
 * �ץ�åȼ��˴ؤ�������ؿ���
 */
/* ����եץ�åȤμ��� */
extern void set_plotgraph_n_axes(int n_axes);

/* �ץ�åȼ��Υ����ȥ�ȥ�������󥰥����� */
extern void set_ith_plotaxis(int ith, char *title, int scale_type);

#define set_x_plotaxis(title,scale_type) \
        set_ith_plotaxis(AXIS_X,title,scale_type)
#define set_y_plotaxis(title,scale_type) \
        set_ith_plotaxis(AXIS_Y,title,scale_type)
#define set_z_plotaxis(title,scale_type) \
        set_ith_plotaxis(AXIS_Z,title,scale_type)
#define set_w_plotaxis(title,scale_type) \
        set_ith_plotaxis(AXIS_W,title,scale_type)
#define set_c_plotaxis(title,scale_type) \
        set_ith_plotaxis(AXIS_C,title,scale_type)

/* �ץ�åȼ��Υ����ȥ� */
extern void set_ith_plotaxis_title(int ith, char *title);

#define set_x_plotaxis_title(title) \
        set_ith_plotaxis_title(AXIS_X,title)
#define set_y_plotaxis_title(title) \
        set_ith_plotaxis_title(AXIS_Y,title)
#define set_z_plotaxis_title(title) \
        set_ith_plotaxis_title(AXIS_Z,title)
#define set_w_plotaxis_title(title) \
        set_ith_plotaxis_title(AXIS_W,title)
#define set_c_plotaxis_title(title) \
        set_ith_plotaxis_title(AXIS_C,title)

/* �ץ�åȼ��Υ�������󥰥����� */
extern void set_ith_plotaxis_scale_type(int ith, int scale_type);

#define set_x_plotaxis_scale_type(scale_type) \
        set_ith_plotaxis_scale_type(AXIS_X,scale_type)
#define set_y_plotaxis_scale_type(scale_type) \
        set_ith_plotaxis_scale_type(AXIS_Y,scale_type)
#define set_z_plotaxis_scale_type(scale_type) \
        set_ith_plotaxis_scale_type(AXIS_Z,scale_type)
#define set_w_plotaxis_scale_type(scale_type) \
        set_ith_plotaxis_scale_type(AXIS_W,scale_type)
#define set_c_plotaxis_scale_type(scale_type) \
        set_ith_plotaxis_scale_type(AXIS_C,scale_type)

/* �ץ�åȼ��Υե饰(�缴,���å�,�����������ݤ�) */
extern
void set_ith_plotaxis_flags(int ith,
                            int axis_flag, int tick_flag, int zero_flag);

#define set_x_plotaxis_flags(axis_flag,tick_flag,zero_flag) \
        set_ith_plotaxis_flags(AXIS_X,axis_flag,tick_flag,zero_flag)
#define set_y_plotaxis_flags(axis_flag,tick_flag,zero_flag) \
        set_ith_plotaxis_flags(AXIS_Y,axis_flag,tick_flag,zero_flag)
#define set_z_plotaxis_flags(axis_flag,tick_flag,zero_flag) \
        set_ith_plotaxis_flags(AXIS_Z,axis_flag,tick_flag,zero_flag)
#define set_w_plotaxis_flags(axis_flag,tick_flag,zero_flag) \
        set_ith_plotaxis_flags(AXIS_W,axis_flag,tick_flag,zero_flag)
#define set_c_plotaxis_flags(axis_flag,tick_flag,zero_flag) \
        set_ith_plotaxis_flags(AXIS_C,axis_flag,tick_flag,zero_flag)

/* ���Υ�� */
extern
void set_ith_plotaxis_range(int ith, Float from_range, Float to_range);

#define set_x_plotaxis_range(from_range,to_range) \
        set_ith_plotaxis_range(AXIS_X,from_range,to_range)
#define set_y_plotaxis_range(from_range,to_range) \
        set_ith_plotaxis_range(AXIS_Y,from_range,to_range)
#define set_z_plotaxis_range(from_range,to_range) \
        set_ith_plotaxis_range(AXIS_Z,from_range,to_range)
#define set_w_plotaxis_range(from_range,to_range) \
        set_ith_plotaxis_range(AXIS_W,from_range,to_range)
#define set_c_plotaxis_range(from_range,to_range) \
        set_ith_plotaxis_range(AXIS_C,from_range,to_range)

/* ���Υ��å���������� */
extern
void set_ith_plotaxis_tick(int ith,
                           Float from_tick, Float to_tick, int div_tick);

#define set_x_plotaxis_tick(from_tick,to_tick,div_tick) \
        set_ith_plotaxis_tick(AXIS_X,from_tick,to_tick,div_tick)
#define set_y_plotaxis_tick(from_tick,to_tick,div_tick) \
        set_ith_plotaxis_tick(AXIS_Y,from_tick,to_tick,div_tick)
#define set_z_plotaxis_tick(from_tick,step_tick,div_tick) \
        set_ith_plotaxis_tick(AXIS_Z,from_tick,to_tick,div_tick)
#define set_w_plotaxis_tick(from_tick,to_tick,div_tick) \
        set_ith_plotaxis_tick(AXIS_W,from_tick,to_tick,div_tick)
#define set_c_plotaxis_tick(from_tick,to_tick,div_tick) \
        set_ith_plotaxis_tick(AXIS_C,from_tick,to_tick,div_tick)

/* �ץ�åȼ��Υꥻ�å� */
extern void reset_ith_plotaxis(int ith);

extern void reset_x_plotaxis(void);
extern void reset_y_plotaxis(void);
extern void reset_z_plotaxis(void);
extern void reset_w_plotaxis(void);
extern void reset_c_plotaxis(void);

/*
 * �ץ�åȥ٥��ȥ�˴ؤ�������ؿ���
 */
/* �ץ�åȥ٥��ȥ�ο� */
extern void set_plotgraph_n_vectors(int n_vectors);

/* �ץ�åȥ٥��ȥ�Υ����ȥ� */
extern void set_ith_plotvector_title(int ith, char *title);

#define set_plotvector_title(title) \
        set_ith_plotvector_title(1,title)

/* �ץ�åȥ٥��ȥ�Υǡ��� */
extern void set_ith_plotvector_data(int ith, long nl, long nh, Float *data);

#define set_plotvector_data(title,nl,nh,data) \
        set_ith_plotvector_data(1,title,nl,nh,data)

/* �ץ�åȥ٥��ȥ�Υ����ȥ�ȥǡ��� */
extern
void set_ith_plotvector(int ith, char *title,
                        long nl, long nh, Float *data);

#define set_plotvector(title,nl,nh,data) \
        set_ith_plotvector(1,title,nl,nh,data)

/* �ץ�åȥ٥��ȥ�μ����б� */
extern void set_ith_plotvector_axis(int ith, int axis, int index);

#define set_plotvector_axis(axis,index) \
        set_ith_plotvector_axis(1,axis,index)

/* �ץ�åȥ٥��ȥ���ͤμ��� */
extern
Float ith_plotvector_axis_value(int ith_vector,
                                int ith_axis, int ith);

#define plotvector_ith_axis_ith_value(ith_axis,ith) \
        ith_plotvector_axis_value(1,ith_axis,ith)

/* �ץ�åȥ٥��ȥ�Υץ�åȼ�������� */
extern
void set_ith_plotvector_kinds(int ith, unsigned long plotkind,
                              int colorkind, int linekind, int pointkind);

#define set_plotvector_kinds(plotkind,colorkind,linekind,pointkind) \
        set_ith_plotvector_kinds(1,plotkind,colorkind,linekind,pointkind)

/* �ץ�åȥ٥��ȥ�Υץ�åȼ�ˤ�����ץ�åȥ��ƥå� */
extern
void set_ith_plotvector_step(int ith, unsigned long plotkind, int plotstep);

#define set_plotvector_step(plotkind,plotstep) \
        set_ith_plotvector_step(1,plotkind,plotstep)

/* �ץ�åȥ٥��ȥ�Υꥻ�å� */
extern void reset_ith_plotvector(int ith);

extern void reset_plotvector(void);

/*
 * �ץ�åȥޥȥ�å����˴ؤ�������ؿ���
 */
/* �ץ�åȥޥȥ�å����ο� */
extern void set_plotgraph_n_matrices(int n_matrices);

/* �ץ�åȥޥȥ�å����Υ����ȥ� */
extern void set_ith_plotmatrix_title(int ith, char *title);

#define set_plotmatrix_title(title) \
        set_ith_plotmatrix_title(1,title)

/* �ץ�åȥޥȥ�å����Υǡ��� */
extern
void set_ith_plotmatrix_data(int ith,
                             long nrl, long nrh, long ncl, long nch,
                             Float **data);

#define set_plotmatrix_data(nrl,nrh,ncl,nch,data) \
        set_ith_plotmatrix_data(1,nrl,nrh,ncl,nch,data)

/* �ץ�åȥޥȥ�å����Υ����ȥ�ȥǡ��� */
extern
void set_ith_plotmatrix(int ith, char *title,
                        long nrl, long nrh, long ncl, long nch, Float **data);

#define set_plotmatrix(title,nrl,nrh,ncl,nch,data) \
        set_ith_plotmatrix(1,title,nrl,nrh,ncl,nch,data)

/* �ץ�åȥޥȥ�å����μ����б� */
extern void set_ith_plotmatrix_axis(int ith, int axis, int index);

#define set_plotmatrix_axis(axis,index) \
        set_ith_plotmatrix_axis(1,axis,index)

/* �ץ�åȥޥȥ�å������ͤμ��� */
extern
Float ith_plotmatrix_axis_value(int ith_matrix,
                                int ith_axis, int ith);

#define plotmatrix_axis_value(ith_axis,ith) \
        ith_plotmatrix_axis_value(1,ith_axis,ith)

/* �ץ�åȥޥȥ�å����Υץ�åȼ�������� */
extern
void set_ith_plotmatrix_kinds(int ith, unsigned long plotkind,
                              int colorkind, int linekind, int pointkind);

#define set_plotmatrix_kinds(plotkind,colorkind,linekind,pointkind) \
        set_ith_plotmatrix_kinds(1,plotkind,colorkind,linekind,pointkind)

/* �ץ�åȥޥȥ�å����Υץ�åȼ�ˤ�����ץ�åȥ��ƥå� */
extern
void set_ith_plotmatrix_step(int ith, unsigned long plotkind, int plotstep);

#define set_plotmatrix_step(plotkind,plotstep) \
        set_ith_plotmatrix_step(1,plotkind,plotstep)

/* �ץ�åȥޥȥ�å����Υꥻ�å� */
extern void reset_ith_plotmatrix(int ith);

extern void reset_plotmatrix(void);

/*
 * �ץ�åȥޥȥ�å���T�˴ؤ�������ؿ���
 */
/* �ץ�åȥޥȥ�å���T�ο� */
extern void set_plotgraph_n_matricesT(int n_matricesT);

/* �ץ�åȥޥȥ�å����Υ����ȥ� */
extern void set_ith_plotmatrixT_title(int ith, char *title);

#define set_plotmatrixT_title(title) \
        set_ith_plotmatrixT_title(1,title)

/* �ץ�åȥޥȥ�å����Υǡ��� */
extern
void set_ith_plotmatrixT_data(int ith,
                              long nrl, long nrh, long ncl, long nch,
                              Float **data);

#define set_plotmatrixT_data(nrl,nrh,ncl,nch,data) \
        set_ith_plotmatrixT_data(1,nrl,nrh,ncl,nch,data)

/* �ץ�åȥޥȥ�å����Υ����ȥ�ȥǡ��� */
extern
void set_ith_plotmatrixT(int ith, char *title,
			 long nrl, long nrh, long ncl, long nch, Float **data);

#define set_plotmatrixT(title,nrl,nrh,ncl,nch,data) \
        set_ith_plotmatrixT(1,title,nrl,nrh,ncl,nch,data)

/* �ץ�åȥޥȥ�å���T�μ����б� */
extern void set_ith_plotmatrixT_axis(int ith, int axis, int index);

#define set_plotmatrixT_axis(axis,index) \
        set_ith_plotmatrixT_axis(1,axis,index)

/* �ץ�åȥޥȥ�å���T���ͤμ��� */
extern
Float ith_plotmatrixT_axis_value(int ith_matrixT,
                                 int ith_axis, int ith);

#define plotmatrixT_axis_value(ith_axis,ith) \
        ith_plotmatrixT_axis_value(1,ith_axis,ith)

/* �ץ�åȥޥȥ�å���T�Υץ�åȼ�������� */
extern
void set_ith_plotmatrixT_kinds(int ith, unsigned long plotkind,
                               int colorkind, int linekind, int pointkind);

#define set_plotmatrixT_kinds(plotkind,colorkind,linekind,pointkind) \
        set_ith_plotmatrixT_kinds(1,plotkind,colorkind,linekind,pointkind)

/* �ץ�åȥޥȥ�å���T�Υץ�åȼ�ˤ�����ץ�åȥ��ƥå� */
extern
void set_ith_plotmatrixT_step(int ith, unsigned long plotkind, int plotstep);

#define set_plotmatrixT_step(plotkind,plotstep) \
        set_ith_plotmatrixT_step(1,plotkind,plotstep)

/* �ץ�åȥޥȥ�å���T�Υꥻ�å� */
extern void reset_ith_plotmatrixT(int ith);

extern void reset_plotmatrixT(void);

/*
 * ���ꤵ�줿���Ƥξ�������褹��
 */
/* ���顼�������� */
extern void plotgraph_color_axis(void);

/* 2��������դμ������� */
extern void plotgraph_2d_axes(void);

/* 2��������դΥǡ��������� */
extern void plotgraph_2d_data(void);

/* 2��������դ����� */
extern void plotgraph_2d(void);

/* 3��������դμ������� */
extern void plotgraph_3d_axes(void);

/* 3��������դΥǡ��������� */
extern void plotgraph_3d_data(void);

/* 3��������դ����� */
extern void plotgraph_3d(void);

/* n��������դμ������� */
extern void plotgraph_nd_axes(void);

/* n��������դΥǡ��������� */
extern void plotgraph_nd_data(void);

/* n��������դ����� */
extern void plotgraph_nd(void);

/* ���ꤵ�줿���������� */
extern void plotgraph(void);

/* ���襤�󥿡��ե����� */ /* since version 3.02 generic 19991101 */

/* 3��������Τ���δؿ� */
extern void r3_lines(int n,double *p);
extern void r3_line(double x0,double y0,double z0,double x1,double y1,double z1);
extern void r3_lineto(double x,double y,double z);
extern void r3_putpixels(int n,double *p,int c);
extern void r3_putpixel(double x,double y,double z,int c);
extern void r3_putpoints(int n,double *p);
extern void r3_putpoint(double x,double y,double z);
extern void r3_moveto(double x,double y,double z);
extern void r3_outtextxy(double x,double y,double z,char *s);
/* n��������Τ���δؿ� */
extern void rn_lines(int n,double **p);
extern void rn_line(double *v0,double *v1);
extern void rn_lineto(double *v);
extern void rn_putpixels(int n,double **p,int c);
extern void rn_putpixel(double *v,int c);
extern void rn_putpoints(int n,double **p);
extern void rn_putpoint(double *v);
extern void rn_moveto(double *v);
extern void rn_outtextxy(double *v,char *s);
extern void rn_cube(double *v0,double *v,int f);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
