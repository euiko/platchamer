/*
 * n-dimensional perspective graphic interface in graffit < graphpn_.h >
 *
 * n-Dimensional Perspective Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHPN__H_
#define _GRAPHPN__H_
#include <math.h>
#include <graphp3_.h>
#include <graphrn_.h>

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
   n����Ʃ���Ѵ�(n-dimentinal Perspective Translation)�ѥå�����
  
   �����n������ɸ�Ϥ�3������ɸ�Ϥ��Ѵ�����3����Ʃ���Ѵ��ѥå�����
   �������ǸƤӽФ����Ȥˤ�äƥǥ����ץ쥤��n�������֤��ᴶɽ�����뤿���
   �ѥå������Ǥ���
   ���Υѥå�������n���������Ѵ��ѥå�����(graphrn_.h)���ư��ޤ���
   ����ˤ����򺮺ߤ��ƻ��ѤǤ���Τǡ����󥿥饯�ƥ��֤˻����Ѵ���Ʃ���Ѵ�
   ���ڤ��ؤ��뤳�Ȥ��ǽ�Ǥ���

   �ѻ��Ԥλ�����Υ����ꤹ��ˤ�setdistance_(d)��Ȥ��ޤ���
   ��Υd���ͤ����μ¿��Ǥ�������ͤ���ꤹ��ȽĲ���ȿž����Ƥ��ޤ��ޤ���
   �ޤ���Υd����Ǥ��뤳�Ȥϻ�����ʪ�Τ�Ʊ���ɸ�ˤ��뤳�Ȥˤʤꡢ
   ���ͷ׻���Ǥϥ����С��ե��ˤʤäƤ��ޤ��Τ���դ��Ƥ���������

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
   cubepn_(4, xf, xt, !0);             ��ž�ΰ��Ʊ��ľ���Τ�����

   �������褷��Ķľ���Τ��ž���������� nhyperrotation_ ����ٻ��ꤷ��
   cubepn_ ������褹�뤳�Ȥˤ�ä��̤β�ž�Ѥ�Ķľ���Τ��������Ȥ��Ǥ��ޤ���
   ���ʤߤ�RAD�ϥǥ��꡼��饸������Ѵ�����ޥ���Ǥ���
 */

/*
   [̾��]
   linepn_      --- n����Ʃ���Ѵ��� line     ľ������ؿ�
   linetopn_    --- n����Ʃ���Ѵ��� lineto   ���а��֤ؤ�ľ������ؿ�
   putpixelpn_  --- n����Ʃ���Ѵ��� putpixel ������ؿ�
   movetopn_    --- n����Ʃ���Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ؿ�
   outtextxypn_ --- n����Ʃ���Ѵ��� outtext  �ƥ����Ƚ��ϴؿ�

   [����]
   linepn_     (x1,x2)
   linetopn_   (x)
   putpixelpn_ (x,c)
   movetopn_   (x)
   outtextxypn_(x,str)
   double *x1; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *x2; n������ɸ(�٥��ȥ�ǳ�Ǽ)
   double *x;  n������ɸ(�٥��ȥ�ǳ�Ǽ)
   int c;      �ѥ�å��ֹ�
   char *str;  ʸ����

   [����]
   �����������³����n����Ʃ���Ѵ��Ѥδؿ��Ǥ���
   n������Ķ���֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3����Ʃ���Ѵ��ѥå����� graphr3_.h 
 */
extern void linepn_(double *x1, double *x2);
extern void linetopn_(double *x);
extern void putpixelpn_(double *x, int c);
extern void putpointpn_(double *x);
extern void movetopn_(double *x);
extern void outtextxypn_(double *x, char *str);

/*
   [̾��]
   cubepn_ --- n����Ʃ���Ѵ��� cube ľ���Τ�����

   [����]
   cubepn_(xf, xt, flg)
   double xf; ��1(�٥��ȥ�ǳ�Ǽ)
   double xt; ��2(�٥��ȥ�ǳ�Ǽ)
   int flg;   !0�ξ�����ʬ�򥫥顼ɽ��

   [����]
   n������Ķ���֤���1����2��Ϥ�ĶΩ���Τ�n����Ʃ���Ѵ������褷�ޤ���
 */
extern void cubepn_(double *xf, double *xt, int flg);

/*
   [̾��]
   linespn_     --- n����Ʃ���Ѵ��� lines     ʣ����ľ������ؿ�
   putpixelspn_ --- n����Ʃ���Ѵ��� putpixels ʣ����������ؿ�

   [����]
   linespn_    (np, rnpoints)
   putpixelspn_(np, rnpoints, c)
   int np;            ���ꤹ���ɸ�ο�
   double **rnpoints; n������ɸ���Υ٥��ȥ���
   int c;             �ѥ�å��ֹ�

   [����]
   n�������֤�ľ����������ꤵ�줿�������ޤȤ�����褷�ޤ���
   double���ι��� rnpoints �ˤ�n������ɸ����
   rnpoints[0..np-1][0..n-1] �ǳ�Ǽ���Ʋ�������
 */
extern void linespn_(int np, double **rnpoints);
extern void putpixelspn_(int np, double **rnpoints, int c);
extern void putpointspn_(int np, double **rnpoints);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif 
