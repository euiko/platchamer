/*
 * 3-dimensional graphic interface in graffit library < graphr3_.h >
 *
 * 3-dimensional Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHR3__H_
#define _GRAPHR3__H_
#include <math.h>
#include <graphr2_.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

#ifndef RAD
#define RAD(d) (M_PI/180*(d))
#endif
#ifndef DEG
#define DEG(r) (180.0/M_PI*(r))
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   3���������Ѵ�(3-dimensional Rotation Port Translation)�ѥå�����
  
   �����3������ɸ�Ϥ���ɺ�ɸ�Ϥ��Ѵ�����������ɥ��Ѵ��ѥå�����
   �������ǸƤӽФ����Ȥˤ�äƥǥ����ץ쥤��3�������֤�ʿ��Ʃ��ɽ�����뤿���
   �ѥå������Ǥ���ʪ�Τ˱�ᴶ���������Ʃ���Ѵ���Ԥ������Ȥ��ϡ�
   ���Υѥå������ǤϤʤ�Ʃ���Ѵ��ѥå�����graphp3_.h��Ȥ�ɬ�פ�����ޤ���
  
   ���Υѥå���������Ū��Ǥ�դ�3�������֤�ǥ����ץ쥤����Ƥ��뤳�ȤǤ���
   Ǥ�դ�3�������֤Ǥ���ΤǤ����Ω���ΤǤ���ɬ�פϤ���ޤ���
   �����Ǽ¿���3�������֤��ž�ΰ�(Rotation Port)�ȸƤӤޤ���
   ���Υѥå������ǤϤ��β�ž�ΰ��Ƽ���ʬ�������������˲�ž�Ѵ���ܤ���
   ���ɺ�ɸ�Ϥ�Ω���ΤȤ�����Ƥ��ޤ���
   �㤨�Хǥ����ץ쥤��˲��ۤ�ľ����(X:0..1,Y:0..2,Z:0..3)�������ˤ�
   �ʲ��Τ褦�ˤ��ޤ���

   setviewport_(0, 100, 0, 100, !0);   ���̤�100x100���ΰ��Ȥ�
   setmagnify_(1.5);                   ��Ƥ���Ȥ��γ���Ψ
   setrotationport_(0, 0, 0, 1, 2, 3); ��˾�β�ž�ΰ�����
   setrotation_(RAD(-15), RAD(20), 0); ��ž�Ѥ����
   cuber3_(0, 0, 0, 1, 2, 3, !0);      ��ž�ΰ��Ʊ��ľ���Τ�����

   setviewport_�ˤ���Ʋ������Ĥޤʤ��褦�������ΰ����ꤷ�ޤ���
   �������褷��ľ���Τ��ž����������setrotation����ٻ��ꤷ��
   cuber3_������褹�뤳�Ȥˤ�ä��̤β�ž�Ѥ�ľ���Τ��������Ȥ��Ǥ��ޤ���
   ���ʤߤ�RAD�ϥǥ��꡼��饸������Ѵ�����ޥ���Ǥ���
 */

struct rotationporttype_ {
  double ox, oy, oz;
  double mx, my, mz;
  double mag;
  double r[3][3];
};

extern struct rotationporttype_ __RP;

/*
   [̾��]
   r3tox --- 3������ɸ������Ƥ��줿X��ɸ�����ޥ���
   r3toy --- 3������ɸ������Ƥ��줿Y��ɸ�����ޥ���
   r3toz --- 3������ɸ������Ƥ��줿Z��ɸ�����ޥ���

   [����]
   r3tox(x,y,z)
   r3toy(x,y,z)
   r3toz(x,y,z)
   double x, y, z; 4������ɸ

   [����]
   setmagnify_ �� setrotation_ �ǻ��ꤵ�줿��ž�Ѥǡ�
   3������ɸ�����ž���줿3������ɸ�γơ��κ�ɸ����ޤ���
 */
#define r3tox(x,y,z) (__RP.mx*((x)-__RP.ox)*__RP.r[0][0]\
                     +__RP.my*((y)-__RP.oy)*__RP.r[1][0]\
                     +__RP.mz*((z)-__RP.oz)*__RP.r[2][0])
#define r3toy(x,y,z) (__RP.mx*((x)-__RP.ox)*__RP.r[0][1]\
                     +__RP.my*((y)-__RP.oy)*__RP.r[1][1]\
                     +__RP.mz*((z)-__RP.oz)*__RP.r[2][1])
#define r3toz(x,y,z) (__RP.mx*((x)-__RP.ox)*__RP.r[0][2]\
                     +__RP.my*((y)-__RP.oy)*__RP.r[1][2]\
                     +__RP.mz*((z)-__RP.oz)*__RP.r[2][2])

/*
   [̾��]
   liner3_      --- 3���������Ѵ��� line     ľ������ޥ���
   linetor3_    --- 3���������Ѵ��� lineto   ���а��֤ؤ�ľ������ޥ���
   putpixelr3_  --- 3���������Ѵ��� putpixel ������ޥ���
   movetor3_    --- 3���������Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ޥ���
   outtextxyr3_ --- 3���������Ѵ��� outtext  �ƥ����Ƚ��ϥޥ���

   [����]
   liner3_     (x1,y1,z1, x2,y2,z2)
   linetor3_   (x,y,z)
   putpixelr3_ (x,y,z,c)
   movetor3_   (x,y,z)
   outtextxyr3_(x,y,z,str)
   double x1,y1,z1; 3������ɸ
   double x2,y2,z2; 3������ɸ
   double x,y,z;    3������ɸ
   int c;           �ѥ�å��ֹ�
   char *str;       ʸ����

   [����]
   �����������³����3���������Ѵ��ѤΥޥ���Ǥ���
   3������Ķ���֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��2����������ɥ��Ѵ��ѥå����� graphr2_.h 
 */
#define liner3_(x1,y1,z1,x2,y2,z2) \
        line_(r3tox(x1,y1,z1),r3toy(x1,y1,z1),\
	      r3tox(x2,y2,z2),r3toy(x2,y2,z2))
#define linetor3_(x,y,z) \
	lineto_(r3tox(x,y,z),r3toy(x,y,z))
#define putpixelr3_(x,y,z,c) \
	putpixel_(r3tox(x,y,z),r3toy(x,y,z),c)
#define putpointr3_(x,y,z) \
	putpoint_(r3tox(x,y,z),r3toy(x,y,z))
#define movetor3_(x,y,z) \
	moveto_(r3tox(x,y,z),r3toy(x,y,z))
#define outtextxyr3_(x,y,z,str) \
	outtextxy_(r3tox(x,y,z),r3toy(x,y,z),str)

/*
   [̾��]
   setrotationport_ --- 3����Ʃ������Ѵ��ѡ���ɸ��������롼����

   [����]
   setrotationport_(xf,yf,zf, xt,yt,zt)
   double xf,yf,zf; ��1
   double xt,yt,zt; ��2

   [����]
   ��1����2��Ϥ�Ω���Τ�3����Ʃ������Ѵ������ΰ�Ȥ��ޤ���
 */
extern void setrotationport_(double xf, double yf, double zf,
                             double xt, double yt, double zt);

/*
   [̾��]
   setmagnify_ --- 3����Ʃ������Ѵ��ѡ�����Ψ����롼����

   [����]
   hypermagnify_(rm)
   double rm; ����Ψ

   [����]
   3������ʪ�Τ������2������Ʃ����Ƥ���Ȥ��γ���Ψ����ꤷ�ޤ���
   rm = 1.0 �ΤȤ���ʿ����ƤȤʤ�ޤ��������Ѵؿ���������
   �ºݤ˥ǥ����ץ쥤�����褵�줿�Ȥ��˾���������������ޤ��Τǡ�
   rm = 1.5 ���餤�����礦�ɤ����Ǥ��礦��
 */
extern void setmagnify_(double rm);

/*
   [̾��]
   setrotation_ --- 3����Ʃ������Ѵ��ѡ���Ƴѻ���롼����

   [����]
   setrotation_(a, b, c);
   double a; X����ž��(�饸����)
   double b; Y����ž��(�饸����)
   double c; Z����ž��(�饸����)

   [����]
   3������ʪ�Τ������2������Ʃ����Ƥ���Ȥ�����ƳѤ���ꤷ�ޤ���
 */
extern void setrotation_(double a, double b, double c);

/*
   [̾��]
   setrotatex_ --- 3����Ʃ������Ѵ��ѡ�X����ž�롼����
   setrotatey_ --- 3����Ʃ������Ѵ��ѡ�Y����ž�롼����
   setrotatez_ --- 3����Ʃ������Ѵ��ѡ�Z����ž�롼����

   [����]
   setrotatex_(d);
   setrotatey_(d);
   setrotatez_(d);
   double d; ��ž��(�饸����)

   [����]
   3������ʪ�Τ������2������Ʃ����Ƥ���Ȥ��β�ž�Ѥ���ꤷ�ޤ���
   �����Ȥ���ƳѤ�����ꤵ�줿���٤�����ž���ޤ���
 */
extern void setrotatex_(double d);
extern void setrotatey_(double d);
extern void setrotatez_(double d);

/*
   [̾��]
   cuber3_ --- 3���������Ѵ��� cube ľ���Τ�����

   [����]
   cuber3_(xf,yf,zf, xt,yt,zt, flg)
   double xf,yf,zf; ��1
   double xt,yt,zt; ��2
   int flg;         ̤����

   [����]
   3�����ζ��֤���1����2��Ϥ�Ω���Τ�3���������Ѵ������褷�ޤ���
 */
extern void cuber3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg);

extern void boxr3_(double xf, double yf, double zf,
                   double xt, double yt, double zt, int c6[]);

extern void lefthandr3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg);

/*
   [̾��]
   linesr3_     --- 3���������Ѵ��� lines     ʣ����ľ������ؿ�
   putpixelsr3_ --- 3���������Ѵ��� putpixels ʣ����������ؿ�

   [����]
   linesr3_    (n, r3points)
   putpixelsr3_(n, r3points, c)
   int n;            ���ꤹ���ɸ�ο�
   double *r3points; 3������ɸ�����¤�
   int c;            �ѥ�å��ֹ�

   [����]
   3�������֤�ľ����������ꤵ�줿�������ޤȤ�����褷�ޤ���
   double�������� r3points �ˤ�3������ɸ����٥��¤Ӥǳ�Ǽ���Ʋ�������
 */
extern void linesr3_(int n, double *r3points);
extern void putpixelsr3_(int n, double *r3points, int c);
extern void putpointsr3_(int n, double *r3points);

/*
   [̾��]
   getrotation_ --- 3����Ʃ������Ѵ��ѥ�������ƳѼ����ؿ�

   [����]
   getrotation_(a, b, c)
   double *a, *b, *c; ��������ƳѼ����Τ���Υݥ���

   [����]
   setrotation_ �� setrotatex_, setrotatey_, setrotatey_ �ʤɤ�
   ��ž�������������Ĥޤꥫ���Ȥβ�ž���󤫤顢
   Y-X-Z����ž�����гѲ�ž����a, b, c���ǥ�������֤��ޤ���
 */
extern void getrotation_(double *a, double *b, double *c);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
