/*
 * n-dimensional graphic interface in graffit library < graphrn_.h >
 *
 * n-Dimensional Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHRN__H_
#define _GRAPHRN__H_
#include <math.h>
#include <graphr3_.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef RAD
#define RAD(d) (M_PI/180*(d))
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   n���������Ѵ�(n-dimensional Rotation Port Translation)�ѥå�����

   �����n������ɸ�Ϥ�3������ɸ�Ϥ��Ѵ�����3�����Ѵ��ѥå�����
   �������ǸƤӽФ����Ȥˤ�äƥǥ����ץ쥤��n�������֤�ʿ��Ʃ��ɽ�����뤿���
   �ѥå������Ǥ���ʪ�Τ˱�ᴶ���������Ʃ���Ѵ���Ԥ������Ȥ��ϡ�
   ���Υѥå������ǤϤʤ�Ʃ���Ѵ��ѥå�����graphpn_.h��Ȥ�ɬ�פ�����ޤ���

   ���Υѥå���������Ū��Ǥ�դ�n�������֤�ǥ����ץ쥤����Ƥ��뤳�ȤǤ���
   Ǥ�դ�n�������֤Ǥ���ΤǤ������Ω���ΤǤ���ɬ�פϤ���ޤ���
   �����Ǽ¿���n�������֤�nĶ��ž�ΰ�(n-Hyper Rotation Port)�ȸƤӤޤ���
   ���Υѥå������ǤϤ��β�ž�ΰ��Ƽ���ʬ�������������˲�ž�Ѵ���ܤ���
   3������ɸ�Ϥ�ĶΩ���ΤȤ�����Ƥ��ޤ���
   �㤨�Хǥ����ץ쥤��˲��ۤ�Ķľ����(X:0..1,Y:0..2,Z:0..3,W:0..4)�������ˤ�
   �ʲ��Τ褦�ˤ��ޤ���

   double xf[4] = { 0, 0, 0, 0 };
   double xt[4] = { 1, 2, 3, 4 };
   setviewport_(0, 100, 0, 100, !0);   ���̤�100x100���ΰ��Ȥ�
   hypermagnify_(1.5);                 ��Ƥ���Ȥ��γ���Ψ
   hyperrotationport_(4, xf, xt);      ��˾�β�ž�ΰ�����
   setrotation_(RAD(-15), RAD(20), 0); ��ž�Ѥ����(X,Y,Z��)
   hyperrotate_(0, 3, RAD(-15));       ��ž�Ѥ����(XW��)
   hyperrotate_(1, 3, RAD(-30));       ��ž�Ѥ����(YW��)
   hyperrotate_(2, 3, RAD(+10));       ��ž�Ѥ����(ZW��)
   cubern_(4, xf, xt, !0);             ��ž�ΰ��Ʊ��ľ���Τ�����

   �������褷��Ķľ���Τ��ž���������� hyperrotation_ ����ٻ��ꤷ��
   cubern_ ������褹�뤳�Ȥˤ�ä��̤β�ž�Ѥ�Ķľ���Τ��������Ȥ��Ǥ��ޤ���
   ���ʤߤ�RAD�ϥǥ��꡼��饸������Ѵ�����ޥ���Ǥ���
 */

struct hyperrotationporttype_ {
  double dim; /* n-dimensional rotation port */
  double *o;  /* region origin */
  double *m;  /* region magnify */
  double mag; /* rotation port magnify */
  double **r; /* rotation matrix */
  double **a; /* work matrix to rotate */
  double *x;  /* work to translate */
  double *y;  /* work to translate */
  double *z;  /* work to translate */
};

extern struct hyperrotationporttype_ __HR;

/*
   [̾��]
   rntov --- n������ɸ������Ƥ��줿��ɸ�����ؿ�

   [����]
   rntov(src, dst)
   double *src; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *dst; n������ɸ(�٥��ȥ�ǳ�Ǽ)

   [����]
   hypermagnify_ �� hyperrotate_ �ǻ��ꤵ�줿��ž�Ѥǡ�
   n������ɸ�����ž���줿n������ɸ�κ�ɸ��٥��ȥ�ǵ��ޤ���
 */
extern void rntov(double *xsrc, double *xdst);

/*
   [̾��]
   linern_      --- n���������Ѵ��� line     ľ������ؿ�
   linetorn_    --- n���������Ѵ��� lineto   ���а��֤ؤ�ľ������ؿ�
   putpixelrn_  --- n���������Ѵ��� putpixel ������ؿ�
   movetorn_    --- n���������Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ؿ�
   outtextxyrn_ --- n���������Ѵ��� outtext  �ƥ����Ƚ��ϴؿ�

   [����]
   linern_     (x1,x2)
   linetorn_   (x)
   putpixelrn_ (x,c)
   movetorn_   (x)
   outtextxyrn_(x,str)
   double *x1; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *x2; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *x;  n������ɸ(�٥��ȥ�ǳ�Ǽ)
   int c;      �ѥ�å��ֹ�
   char *str;  ʸ����
  
   [����]
   �����������³����n���������Ѵ��Ѥδؿ��Ǥ���
   n������Ķ���֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3����Ʃ���Ѵ��ѥå����� graphr3_.h 
 */
extern void linern_(double *x1, double *x2);
extern void linetorn_(double *x);
extern void putpixelrn_(double *x, int c);
extern void putpointrn_(double *x);
extern void movetorn_(double *x);
extern void outtextxyrn_(double *x, char *str);

/*
   [̾��]
   hyperrotationport_ --- n����Ʃ������Ѵ��ѡ���ɸ��������롼����

   [����]
   hyperrotationport_(xf, xt)
   double *xf; ��1(�٥��ȥ�ǳ�Ǽ)
   double *xt; ��2(�٥��ȥ�ǳ�Ǽ)

   [����]
   ��1����2��Ϥ�ĶΩ���Τ�n����Ʃ������Ѵ������ΰ�Ȥ��ޤ���
 */
extern void hyperrotationport_(int dim, double *xf, double *xt);

/*
   [̾��]
   hypermagnify_ --- n����Ʃ������Ѵ��ѡ�����Ψ����롼����
  
   [����]
   hypermagnify_(nhm)
   double nhm; ����Ψ
  
   [����]
   n������ʪ�Τ������3������Ʃ����Ƥ���Ȥ��γ���Ψ����ꤷ�ޤ���
   nhm = 1.0 �ΤȤ���ʿ����ƤȤʤ�ޤ��������Ѵؿ���������
   �ºݤ˥ǥ����ץ쥤�����褵�줿�Ȥ��˾���������������ޤ��Τǡ�
   nhm = 1.5 ���餤�����礦�ɤ����Ǥ��礦��
 */
extern void hypermagnify_(double nhm);

/*
   [̾��]
   hyperrotation_ --- n����Ʃ������Ѵ��ѡ���Ƴѻ���롼����

   [����]
   hyperrotation_(n, fa, ta, angle);
   int n;         ��ž�ο�
   int *fa, *ta;  ��ž���μ���ź��(fa����ta�ؤβ�ž)�Υꥹ��
   double *angle; ��ž�ѤΥꥹ��

   [����]
   n������ʪ�Τ������3������Ʃ����Ƥ���Ȥ�����ƳѤ���ꤷ�ޤ���
 */
extern void hyperrotation_(int n, int *fx, int *tx, double *angle);

/*
   [̾��]
   hyperrotate_ --- n����Ʃ������Ѵ��ѡ�Ǥ�ռ���ž�롼����

   [����]
   hyperrotation_(fa, ta, angle);
   int fa, ta;   ��ž���μ���ź��(fa����ta�ؤβ�ž)
   double angle; ��ž��

   [����]
   n������ʪ�Τ������3������Ʃ����Ƥ���Ȥ��β�ž�Ѥ���ꤷ�ޤ���
   �����Ȥ���ƳѤ�����ꤵ�줿���٤�����ž���ޤ���
 */
extern void hyperrotate_(int fa, int ta, double angle);

/*
   [̾��]
   cubern_ --- n���������Ѵ��� cube ľ���Τ�����

   [����]
   cubern_(xf, xt, flg)
   double xf; ��1(�٥��ȥ�ǳ�Ǽ)
   double xt; ��2(�٥��ȥ�ǳ�Ǽ)
   int flg;   !0�ξ�����ʬ�򥫥顼ɽ��

   [����]
   n������Ķ���֤���1����2��Ϥ�ĶΩ���Τ�n���������Ѵ������褷�ޤ���
 */
extern void cubern_(double *xf, double *xt, int flg);

/*
   [̾��]
   linesrn_     --- n���������Ѵ��� lines     ʣ����ľ������ؿ�
   putpixelsrn_ --- n���������Ѵ��� putpixels ʣ����������ؿ�

   [����]
   linesrn_    (np, rnpoints)
   putpixelsrn_(np, rnpoints, c)
   int np;            ���ꤹ���ɸ�ο�
   double **rnpoints; n������ɸ���Υ٥��ȥ���
   int c;             �ѥ�å��ֹ�

   [����]
   n�������֤�ľ����������ꤵ�줿�������ޤȤ�����褷�ޤ���
   double���ι��� rnpoints �ˤ�n������ɸ����
   rnpoints[0..np-1][0..n-1] �ǳ�Ǽ���Ʋ�������
 */
extern void linesrn_(int np, double **rnpoints);
extern void putpixelsrn_(int np, double **rnpoints, int c);
extern void putpointsrn_(int np, double **rnpoints);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif 
