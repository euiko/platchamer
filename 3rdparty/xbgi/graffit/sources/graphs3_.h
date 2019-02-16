/*
 * 3-dimensional stereographic interface in graffit library < graphs3_.h >
 *
 * 3-Dimensional Stereo Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHS3__H_
#define _GRAPHS3__H_
#include <graphics.h>
#include <graphr2_.h>
#include <graphs3_.h>
#include <graphp3_.h>

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
   3�������ƥ쥪����ե��å�(3-dimensional Stereo Graphics)�ѥå�����
  
   �����3������ɸ�Ϥ�2�����Ʃ���Ѵ���ܤ���
   ������Ω�λ��¸����뤿��Υѥå������Ǥ���
   ����̿���������'sl_'���ղä�����Τ������������Ѥ�����̿�ᡢ
   'sr_'���ղä�����Τ������������Ѥ�����̿��Ǥ���
   �ޤ���������������Ʊ������̿����Ѱդ���Ƥ��ꡢ����̿���������'s3_'��
   �ղä���̾�ΤˤʤäƤ��ޤ����ǥե�����ͤǺ������Ѵ����ֿ��򥻥åȡ�
   �������Ѵ����Ŀ��򥻥åȤ�Ԥ��ޤ���������ѹ���ǽ�Ǥ���

   �㤨�Хǥ����ץ쥤��˥��ƥ쥪����ե��å���ľ����(X:0..1,Y:0..2,Z:0..3)��
   �����ˤϰʲ��Τ褦�ˤ��ޤ���

   setviewport_(0, 100, 0, 100, !0);   ���̤�100x100���ΰ��Ȥ�
   setmagnify(1.5);                    ��Ƥ���Ȥ��γ���Ψ
   setrotationport_(0, 0, 0, 1, 2, 3); ��˾�β�ž��ɸ�Ϥ����
   setrotation_(RAD(-15), RAD(20), 0); ��ž�Ѥ����
   setdistance_(0.5);                  ������Υ�����
   stereodistance_(0.5);               ���ƥ쥪����ջ�����Υ�����
   cubes3_(0, 0, 0, 1, 2, 3, !0);      ��ž��ɸ�Ϥ�Ʊ��ľ���Τ�����

   �ʲ��Τ褦��Ω�λ�μ�ˡ���ѹ��Ǥ��ޤ���

   setstereotype(ColorGlass);  ���ᥬ��Ω�λ�
   setstereotype(DoubleImage); 2����Ω�λ�

   �ޤ����ʲ��Τ褦�˥桼���������Ω�λ��Ѽ�³�������Ǥ��ޤ���

   setstereoprocedures(start_proc, left_proc, right_proc, end_proc);

   2����Ω�λ�ΤȤ��ϡ��ʲ��Τ褦�������ѹ��Ǥ��ޤ���

   stereowidthimages(width);

   width����ʤ��ˡ�ˤʤ�ޤ���
 */

struct stereographtype_ {
  double dist;                /* stereo distance */
  void (*start)(void);        /* start procedure */
  void (*left) (void);        /* left procedure */
  void (*right)(void);        /* right procedure */
  void (*end)  (void);        /* end procedure */
  int c;                      /* keep current color */
  struct fillsettingstype fs; /* keep current fill settings */
#ifdef _XBGI_
  struct pointsettingstype ps; /* keep current point settings */
#endif
  struct viewporttype_ v;     /* keep current viewport settings */
  int wi;                     /* width between double images (bits) */
};

extern struct stereographtype_ __SG;

enum { ColorGlass, DoubleImage };

/*
   [̾��]
   sltox --- 3������ɸ���麸�ܤ�Ʃ����Ƥ��줿X��ɸ�����ޥ���
   sltoy --- 3������ɸ���麸�ܤ�Ʃ����Ƥ��줿Y��ɸ�����ޥ���
   sltoz --- 3������ɸ���麸�ܤ�Ʃ����Ƥ��줿Z��ɸ�����ޥ���

   [����]
   sltox(x,y,z)
   sltoy(x,y,z)
   sltoz(x,y,z)
   double x, y, z; 3������ɸ

   [����]
   setmagnify_ �� setrotation_ �ǻ��ꤵ�줿��ž�Ѥǡ�3������ɸ����
   ���ܤ�Ʃ������Ѵ����줿3������ɸ�γơ��κ�ɸ����ޤ���
 */
#define sltox(x,y,z) ((r3tox(x,y,z)+__SG.dist)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define sltoy(x,y,z) p3toy(x,y,z)
#define sltoz(x,y,z) p3toz(x,y,z)

/*
   [̾��]
   linesl_      --- 3��������Ʃ���Ѵ��� line     ľ������
   linetosl_    --- 3��������Ʃ���Ѵ��� lineto   ���а��֤ؤ�ľ������
   putpixelsl_  --- 3��������Ʃ���Ѵ��� putpixel ������
   movetosl_    --- 3��������Ʃ���Ѵ��� moveto   �����ȥݥ���Ȱ�ư
   outtextxysl_ --- 3��������Ʃ���Ѵ��� outtext  �ƥ����Ƚ���

   [����]
   linesl_     (x1,y1,z1, x2,y2,z2)
   linetosl_   (x,y,z)
   putpixelsl_ (x,y,z,c)
   movetosl_   (x,y,z)
   outtextxysl_(x,y,z,str)
   double x1,y1,z1; 3������ɸ
   double x2,y2,z2; 3������ɸ
   double x,y,z;    3������ɸ
   int c;           �ѥ�å��ֹ�
   char *str;       ʸ����

   [����]
   �����������³����3��������Ʃ���Ѵ��ѤΥޥ���Ǥ���
   3�����ζ��֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3����Ʃ���Ѵ��ѥå����� graphp3_.h
 */
#define linesl_(x1,y1,z1,x2,y2,z2) \
        line_(sltox(x1,y1,z1),sltoy(x1,y1,z1), \
              sltox(x2,y2,z2),sltoy(x2,y2,z2))
#define linetosl_(x,y,z) \
        lineto_(sltox(x,y,z),sltoy(x,y,z))
#define putpixelsl_(x,y,z,c) \
        putpixel_(sltox(x,y,z),sltoy(x,y,z),c)
#define putpointsl_(x,y,z) \
        putpoint_(sltox(x,y,z),sltoy(x,y,z))
#define movetosl_(x,y,z) \
        moveto_(sltox(x,y,z),sltoy(x,y,z))
#define outtextxysl_(x,y,z,str) \
        outtextxy_(sltox(x,y,z),sltoy(x,y,z),str)

/*
   [̾��]
   srtox --- 3������ɸ���鱦�ܤ�Ʃ����Ƥ��줿X��ɸ�����ޥ���
   srtoy --- 3������ɸ���鱦�ܤ�Ʃ����Ƥ��줿Y��ɸ�����ޥ���
   srtoz --- 3������ɸ���鱦�ܤ�Ʃ����Ƥ��줿Z��ɸ�����ޥ���

   [����]
   srtox(x,y,z)
   srtoy(x,y,z)
   srtoz(x,y,z)
   double x, y, z; 3������ɸ

   [����]
   setmagnify_ �� setrotation_ �ǻ��ꤵ�줿��ž�Ѥǡ�3������ɸ����
   ���ܤ�Ʃ������Ѵ����줿3������ɸ�γơ��κ�ɸ����ޤ���
 */
#define srtox(x,y,z) ((r3tox(x,y,z)-__SG.dist)*__PP.dist/(r3toz(x,y,z)+__PP.deform))
#define srtoy(x,y,z) p3toy(x,y,z)
#define srtoz(x,y,z) p3toz(x,y,z)

/*
   [̾��]
   linesr_      --- 3��������Ʃ���Ѵ��� line     ľ������
   linetosr_    --- 3��������Ʃ���Ѵ��� lineto   ���а��֤ؤ�ľ������
   putpixelsr_  --- 3��������Ʃ���Ѵ��� putpixel ������
   movetosr_    --- 3��������Ʃ���Ѵ��� moveto   �����ȥݥ���Ȱ�ư
   outtextxysr_ --- 3��������Ʃ���Ѵ��� outtext  �ƥ����Ƚ���

   [����]
   linesr_     (x1,y1,z1, x2,y2,z2)
   linetosr_   (x,y,z)
   putpixelsr_ (x,y,z,c)
   movetosr_   (x,y,z)
   outtextxysr_(x,y,z,str)
   double x1,y1,z1; 3������ɸ
   double x2,y2,z2; 3������ɸ
   double x,y,z;    3������ɸ
   int c;           �ѥ�å��ֹ�
   char *str;       ʸ����

   [����]
   �����������³����3��������Ʃ���Ѵ��ѤΥޥ���Ǥ���
   3�����ζ��֤ο޷����ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3����Ʃ���Ѵ��ѥå����� graphp3_.h
 */
#define linesr_(x1,y1,z1,x2,y2,z2) \
        line_(srtox(x1,y1,z1),srtoy(x1,y1,z1), \
              srtox(x2,y2,z2),srtoy(x2,y2,z2))
#define linetosr_(x,y,z) \
        lineto_(srtox(x,y,z),srtoy(x,y,z))
#define putpixelsr_(x,y,z,c) \
        putpixel_(srtox(x,y,z),srtoy(x,y,z),c)
#define putpointsr_(x,y,z) \
        putpoint_(srtox(x,y,z),srtoy(x,y,z))
#define movetosr_(x,y,z) \
        moveto_(srtox(x,y,z),srtoy(x,y,z))
#define outtextxysr_(x,y,z,str) \
        outtextxy_(srtox(x,y,z),srtoy(x,y,z),str)

/*
   [̾��]
   lines3_      --- 3����ξ��Ʃ���Ѵ��� line     ľ������
   linetos3_    --- 3����ξ��Ʃ���Ѵ��� lineto   ���а��֤ؤ�ľ������
   putpixels3_  --- 3����ξ��Ʃ���Ѵ��� putpixel ������
   movetos3_    --- 3����ξ��Ʃ���Ѵ��� moveto   �����ȥݥ���Ȱ�ư
   outtextxys3_ --- 3����ξ��Ʃ���Ѵ��� outtext  �ƥ����Ƚ���

   [����]
   lines3_     (x1,y1,z1, x2,y2,z2)
   linetos3_   (x,y,z)
   putpixels3_ (x,y,z,c)
   movetos3_   (x,y,z)
   outtextxys3_(x,y,z,str)
   double x1,y1,z1; 3������ɸ
   double x2,y2,z2; 3������ɸ
   double x,y,z;    3������ɸ
   int c;           �ѥ�å��ֹ�
   char *str;       ʸ����

   [����]
   �����������³����3����ξ��Ʃ���Ѵ��ѤΥޥ���Ǥ���
   3�����ζ��֤ο޷���Ω�λ�Ǵ�ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��3����Ʃ���Ѵ��ѥå����� graphp3_.h
 */
#define lines3_(x1,y1,z1,x2,y2,z2) \
                               do{__SG.start(); \
                                  __SG.left(); linesl_(x1,y1,z1,x2,y2,z2); \
                                  __SG.right();linesr_(x1,y1,z1,x2,y2,z2); \
                                  __SG.end();} while(0)
#define linetos3_(x,y,z)       do{__SG.start(); \
                                  __SG.left(); linetosl_(x,y,z); \
                                  __SG.right();linetosr_(x,y,z); \
                                  __SG.end();} while(0)
#define putpixels3_(x,y,z,c)   do{__SG.start(); \
                                  __SG.left(); putpixelsl_(x,y,z,getcolor()); \
                                  __SG.right();putpixelsr_(x,y,z,getcolor()); \
                                  __SG.end();} while(0)
#define putpoints3_(x,y,z)     do{__SG.start(); \
                                  __SG.left(); putpointsl_(x,y,z); \
                                  __SG.right();putpointsr_(x,y,z); \
                                  __SG.end();} while(0)
#define movetos3_(x,y,z)       do{__SG.start(); \
                                  __SG.left(); movetosl_(x,y,z); \
                                  __SG.right();movetosr_(x,y,z); \
                                  __SG.end();} while(0)
#define outtextxys3_(x,y,z,str) \
                               do{__SG.start(); \
                                  __SG.left(); outtextxysl_(x,y,z,str); \
                                  __SG.right();outtextxysr_(x,y,z,str); \
                                  __SG.end();} while(0)

extern void stereowidthimages(int width);

extern void setstereoprocedures(void (*start)(void),
                                void (*left)(void),
                                void (*right)(void),
                                void (*end)(void));

extern void setstereotype(int type);

/*
   [̾��]
   stereodistance_ --- 3�������ƥ쥪������ѡ�ξ���Υ����롼����

   [����]
   stereodistance_(d)
   double d; ξ���Υ

   [����]
   ξ���Υ d �����μ¿��Ǥ����ۤ� d = 0.02 ���餤���侩�ͤǤ���
 */
extern void stereodistance_(double d);

/*
   [̾��]
   cubes3_ --- 3�������ƥ쥪������� cube ľ���Τ�����

   [����]
   cubes3_(xf,yf,zf, xt,yt,zt, flg)
   double xf,yf,zf; ��1
   double xt,yt,zt; ��2
   int flg;         ̤����

   [����]
   3�����ζ��֤���1����2��Ϥ�Ω���Τ�3�������ƥ쥪����դ����褷�ޤ���
 */
extern void cubes3_(double xf, double yf, double zf,
                    double xt, double yt, double zt, int flg);

extern void boxs3_(double xf, double yf, double zf, double xt,
                   double yt, double zt, int c6[]);

extern void lefthands3_(double xf, double yf, double zf,
                        double xt, double yt, double zt, int flg);

/*
   [̾��]
   liness3_     --- 3�������ƥ쥪������� lines     ʣ����ľ������ؿ�
   putpixelss3_ --- 3�������ƥ쥪������� putpixels ʣ����������ؿ�

   [����]
   liness3_    (n, r3points)
   putpixelss3_(n, r3points, c)
   int n;            ���ꤹ���ɸ�ο�
   double *r3points; 3������ɸ�����¤�
   int c;            �ѥ�å��ֹ�

   [����]
   3�������֤�ľ����������ꤵ�줿�������ޤȤ�����褷�ޤ���
   double�������� r3points �ˤ�3������ɸ����٥��¤Ӥǳ�Ǽ���Ʋ�������
 */
extern void liness3_(int n, double *r3points);
extern void putpixelss3_(int n, double *r3points, int c);
extern void putpointss3_(int n, double *r3points);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GRAPHS3__H_ */
