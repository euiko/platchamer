/*
 * n-dimensional stereographic interface in graffit library < graphsn_.h >
 *
 * n-Dimensional Stereo Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHSN__H_
#define _GRAPHSN__H_
#include <math.h>
#include <graphs3_.h>
#include <graphpn_.h>

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
   n�������ƥ쥪����ե��å�(n-dimensional Stereo Graphics)�ѥå�����
  
   �����n������ɸ�Ϥ�3������ɸ�Ϥ��Ѵ����������3�����β�ž��ɸ�Ϥ�
   2�����Ʃ���Ѵ���ܤ���������Ω�λ��¸����뤿��Υѥå������Ǥ���

   �㤨�Хǥ����ץ쥤��˲��ۤ�Ķľ����(X:0..1,Y:0..2,Z:0..3,W:0..4)�������ˤ�
   �ʲ��Τ褦�ˤ��ޤ���

   double xf[4] = { 0, 0, 0, 0 };
   double xt[4] = { 1, 2, 3, 4 };
   setviewport_(0, 100, 0, 100, !0);   ���̤�100x100���ΰ��Ȥ�
   nhypermagnify_(1.5);                ��Ƥ���Ȥ��γ���Ψ
   nhyperrotationport_(4, xf, xt);     ��˾�β�ž�ΰ�����
   setrotation_(RAD(-15), RAD(20), 0); ��ž�Ѥ����(X,Y,Z��)
   nhyperrotate_(0, 3, RAD(-15));      ��ž�Ѥ����(XW��)
   nhyperrotate_(1, 3, RAD(-30));      ��ž�Ѥ����(YW��)
   nhyperrotate_(2, 3, RAD(+10));      ��ž�Ѥ����(ZW��)
   cubesn_(4, xf, xt, !0);             ��ž�ΰ��Ʊ��ľ���Τ�����

   �������褷��Ķľ���Τ��ž���������� nhyperrotation_ ����ٻ��ꤷ��
   cubesn_ ������褹�뤳�Ȥˤ�ä��̤β�ž�Ѥ�Ķľ���Τ��������Ȥ��Ǥ��ޤ���
   ���ʤߤ�RAD�ϥǥ��꡼��饸������Ѵ�����ޥ���Ǥ���
 */

/*
   [̾��]
   linesn_      --- n�������ƥ쥪������� line     ľ������
   linetosn_    --- n�������ƥ쥪������� lineto   ���а��֤ؤ�ľ������
   putpixelsn_  --- n�������ƥ쥪������� putpixel ������
   movetosn_    --- n�������ƥ쥪������� moveto   �����ȥݥ���Ȱ�ư
   outtextxysn_ --- n�������ƥ쥪������� outtext  �ƥ����Ƚ���
 
   [����]
   linesn_     (x1,x2)
   linetosn_   (x)
   putpixelsn_ (x,c)
   movetosn_   (x)
   outtextxysn_(x,str)
   double *x1; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *x2; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *x;  n������ɸ(�٥��ȥ�ǳ�Ǽ)
   int c;      �ѥ�å��ֹ�
   char *str;  ʸ����
 
   [����]
   �����������³����n�������ƥ쥪������Ѥδؿ��Ǥ���
   n������Ķ���֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3����Ʃ���Ѵ��ѥå����� graphr3_.h 
   ��3����Ʃ���Ѵ��ѥå����� graphp3_.h 
   ��3�������ƥ쥪����եѥå����� graphs3_.h
 */
extern void linesn_(double *x1, double *x2);
extern void linetosn_(double *x);
extern void putpixelsn_(double *x, int c);
extern void putpointsn_(double *x);
extern void movetosn_(double *x);
extern void outtextxysn_(double *x, char *str);

/*
   [̾��]
   cubesn_ --- n�������ƥ쥪������� cube ľ���Τ�����
 
   [����]
   cubesn_(xf, xt, flg)
   double xf; ��1(�٥��ȥ�ǳ�Ǽ)
   double xt; ��2(�٥��ȥ�ǳ�Ǽ)
   int flg;   !0�ξ�����ʬ�򥫥顼ɽ��

   [����]
   n������Ķ���֤���1����2��Ϥ�ĶΩ���Τ�n�������ƥ쥪����դ�
   ���褷�ޤ���
 */
extern void cubesn_(double *xf, double *xt, int flg);

/*
   [̾��]
   linessn_     --- n�������ƥ쥪������� lines     ʣ����ľ������ؿ�
   putpixelssn_ --- n�������ƥ쥪������� putpixels ʣ����������ؿ�

   [����]
   linessn_    (np, rnpoints)
   putpixelssn_(np, rnpoints, c)
   int np;            ���ꤹ���ɸ�ο�
   double **rnpoints; n������ɸ���Υ٥��ȥ���
   int c;             �ѥ�å��ֹ�

   [����]
   n�������֤�ľ����������ꤵ�줿�������ޤȤ�����褷�ޤ���
   double���ι��� rnpoints �ˤ�n������ɸ����
   rnpoints[0..np-1][0..n-1] �ǳ�Ǽ���Ʋ�������
 */
extern void linessn_(int np, double **rnpoints);
extern void putpixelssn_(int np, double **rnpoints, int c);
extern void putpointssn_(int np, double **rnpoints);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif 
