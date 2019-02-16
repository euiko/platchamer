/*
 * 3-dimensional perspective graphic interface in graffit < graphp3_.h >
 *
 * 3-Dimensional Perspective Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHP3__H_
#define _GRAPHP3__H_
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
   3����Ʃ���Ѵ�(3-dimensional Perspective Translation)�ѥå�����

   �����3������ɸ�Ϥ���ɺ�ɸ�Ϥ��Ѵ����������Ʃ���Ѵ��ˤ�ä�
   ������Υ�ˤ��ʪ�Τα�ᴶ��ɽ������ѥå������Ǥ���
   ���Υѥå�������3���������Ѵ��ѥå�����(graphr3_.h)���ư��ޤ���
   ����ˤ����򺮺ߤ��ƻ��ѤǤ���Τǡ����󥿥饯�ƥ��֤˻����Ѵ���Ʃ���Ѵ�
   ���ڤ��ؤ��뤳�Ȥ��ǽ�Ǥ���

   �ѻ��Ԥλ�����Υ����ꤹ��ˤ�setdistance_(d)��Ȥ��ޤ���
   ��Υd���ͤ����μ¿��Ǥ�������ͤ���ꤹ��ȽĲ���ȿž����Ƥ��ޤ��ޤ���
   �ޤ���Υd����Ǥ��뤳�Ȥϻ�����ʪ�Τ�Ʊ���ɸ�ˤ��뤳�Ȥˤʤꡢ
   ���ͷ׻���Ǥϥ����С��ե��ˤʤäƤ��ޤ��Τ���դ��Ƥ���������

   �㤨�Хǥ����ץ쥤��˲��ۤ�ľ����(X:0..1,Y:0..2,Z:0..3)�������Υ0.5��
   Ʃ���Ѵ�����ɽ�����������ΤǤ���аʲ��Τ褦�ˤ��ޤ���

   setviewport_(0, 100, 0, 100, !0);   ���̤�100x100���ΰ��Ȥ�
   setmagnify_(1.5);                   ��Ƥ���Ȥ��γ���Ψ
   setrotationport_(0, 0, 0, 1, 2, 3); ��˾�β�ž�ΰ�����
   setrotation(RAD(-15), RAD(20), 0);  ��ž�Ѥ����
   setdistance_(0.5);                  ������Υ�����
   cubep3_(0, 0, 0, 1, 2, 3, !0);      ��ž�ΰ��Ʊ��ľ���Τ�����
 */

struct perspectivetype_ {
  double dist;
  double deform;
};

extern struct perspectivetype_ __PP;

/*
   [̾��]
   p3tox --- 3������ɸ����Ʃ����Ƥ��줿X��ɸ�����ޥ���
   p3toy --- 3������ɸ����Ʃ����Ƥ��줿Y��ɸ�����ޥ���
   p3toz --- 3������ɸ����Ʃ����Ƥ��줿Z��ɸ�����ޥ���

   [����]
   p3tox(x,y,z)
   p3toy(x,y,z)
   p3toz(x,y,z)
   double x, y, z; 3������ɸ

   [����]
   setmagnify_ �� setrotation_ �ǻ��ꤵ�줿��ž�Ѥǡ�
   3������ɸ����Ʃ������Ѵ����줿3������ɸ�γơ��κ�ɸ����ޤ���
 */
#define p3tox(x,y,z) (r3tox(x,y,z)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define p3toy(x,y,z) (r3toy(x,y,z)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define p3toz(x,y,z) (__PP.dist*(2.0-__PP.dist/(r3toz(x,y,z)+__PP.deform)))

/*
   [̾��]
   linep3_      --- 3����Ʃ���Ѵ��� line     ľ������ޥ���
   linetop3_    --- 3����Ʃ���Ѵ��� lineto   ���а��֤ؤ�ľ������ޥ���
   putpixelp3_  --- 3����Ʃ���Ѵ��� putpixel ������ޥ���
   movetop3_    --- 3����Ʃ���Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ޥ���
   outtextxyp3_ --- 3����Ʃ���Ѵ��� outtext  �ƥ����Ƚ��ϥޥ���

   [����]
   linep3_     (x1,y1,z1, x2,y2,z2)
   linetop3_   (x,y,z)
   putpixelp3_ (x,y,z,c)
   movetop3_   (x,y,z)
   outtextxyp3_(x,y,z,str)
   double x1,y1,z1; 3������ɸ
   double x2,y2,z2; 3������ɸ
   double x,y,z;    3������ɸ
   int c;           �ѥ�å��ֹ�
   char *str;       ʸ����

   [����]
   �����������³����3����Ʃ���Ѵ��ѤΥޥ���Ǥ���
   3�����ζ��֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3���������Ѵ��ѥå����� graphr3_.h 
 */
#define linep3_(x1,y1,z1,x2,y2,z2) \
        line_(p3tox(x1,y1,z1),p3toy(x1,y1,z1), \
	      p3tox(x2,y2,z2),p3toy(x2,y2,z2))
#define linetop3_(x,y,z) \
	lineto_(p3tox(x,y,z),p3toy(x,y,z))
#define putpixelp3_(x,y,z,c) \
        putpixel_(p3tox(x,y,z),p3toy(x,y,z),c)
#define putpointp3_(x,y,z) \
        putpoint_(p3tox(x,y,z),p3toy(x,y,z))
#define movetop3_(x,y,z) \
        moveto_(p3tox(x,y,z),p3toy(x,y,z))
#define outtextxyp3_(x,y,z,str) \
        outtextxy_(p3tox(x,y,z),p3toy(x,y,z),str)

/*
   [̾��]
   setdistance_ --- 3����Ʃ���Ѵ��ѡ�������Υ����롼����

   [����]
   setdistance_(d)
   double d; ������Υ

   [����]
   ������Υ d �����μ¿��Ǥ����ۤ� d = 0.5 ���餤���侩�ͤǤ���
   ����򾮤��������3������ʪ�Τ��᤯������
   �դ��礭������ȱ󤯸�����褦�ˤʤ�ޤ���
 */
extern void setdistance_(double d);

/*
   [̾��]
   setdeformation_ --- 3����Ʃ���Ѵ��ѡ��ǥե�����������롼����

   [����]
   setdeformation_(d)
   double d; �ǥե�������

   [����]
   �ǥե������� d �����μ¿��Ǥ����ۤ� d = 2.5 ���餤���侩�ͤǤ���
   ����򾮤�������ȱ��ˡ�ζ�Ĵ�ٹ礬��ޤ�ޤ���
 */
extern void setdeformation_(double d);

/*
   [̾��]
   cubep3_ --- 3����Ʃ���Ѵ��� cube ľ���Τ�����

   [����]
   cubep3_(xf,yf,zf, xt,yt,zt, flg)
   double xf,yf,zf; ��1
   double xt,yt,zt; ��2
   int flg;         ̤����

   [����]
   3�����ζ��֤���1����2��Ϥ�Ω���Τ�3����Ʃ���Ѵ������褷�ޤ���
 */
extern void cubep3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg);

extern void boxp3_(double xf, double yf, double zf, double xt,
                   double yt, double zt, int c6[]);

extern void lefthandp3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg);

/*
   [̾��]
   linesp3_     --- 3����Ʃ���Ѵ��� lines     ʣ����ľ������ؿ�
   putpixelsp3_ --- 3����Ʃ���Ѵ��� putpixels ʣ����������ؿ�

   [����]
   linesp3_    (n, r3points)
   putpixelsp3_(n, r3points, c)
   int n;            ���ꤹ���ɸ�ο�
   double *r3points; 3������ɸ�����¤�
   int c;            �ѥ�å��ֹ�

   [����]
   3�������֤�ľ����������ꤵ�줿�������ޤȤ�����褷�ޤ���
   double�������� r3points �ˤ�3������ɸ����٥��¤Ӥǳ�Ǽ���Ʋ�������
 */
extern void linesp3_(int n, double *r3points);
extern void putpixelsp3_(int n, double *r3points, int c);
extern void putpointsp3_(int n, double *r3points);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
