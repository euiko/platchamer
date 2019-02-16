/*
 * Axes utilities in graffit library < axes.h >
 *
 * Draw Axes on View Port for Borland Graphics Interface
 *
 * Copyright (C) 1991-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _AXES_H_
#define _AXES_H_
#include <graphics.h>

/*
   [̾��]
   drawaxisl  --- ���ټ�������
   drawaxist  --- ��ؼ�������
   drawaxisr  --- ���ټ�������
   drawaxisb  --- ���ؼ�������
   
   [����]
   drawaxis?(sep, ssep, len, bos)
   int sep;  Ĺ����ʬ���
   int ssep; û����ʬ���
   int len;  ����Ĺ��
   int bos;  �ӥ塼�ݡ��Ȥ�Ϥ�����
          
   [����]
   �㤨�� setviewport(30, 30, 130, 130, 0) ��¹Ԥ����塢

   drawaxisl(2, 2, 6, 10);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��10�ӥåȳ�¦�ˡ�
   ���ټ������褵��ޤ������ξ�硢������Ĺ����2ʬ�䤵�줿���֤ˡ�
   û����2ʬ�䤵�줿���֤�������ޤ���
 */
#define drawaxisl(s,ss,l,b) drawaxisy(AXIS_LEFT,  s,ss,l,b)
#define drawaxist(s,ss,l,b) drawaxisx(AXIS_TOP,   s,ss,l,b)
#define drawaxisr(s,ss,l,b) drawaxisy(AXIS_RIGHT, s,ss,l,b)
#define drawaxisb(s,ss,l,b) drawaxisx(AXIS_BOTTOM,s,ss,l,b)

/*
   [̾��]
   drawaxeslb --- ���ټ��Ȳ��ؼ�������

   [����]
   drawaxeslb(sepx, ssepx, sepy, ssepy, len, bos)
   int sepx;  X����Ĺ����ʬ���
   int ssepx; X����û����ʬ���
   int sepy;  Y����Ĺ����ʬ���
   int ssepy; Y����û����ʬ���
   int len;   ����Ĺ��
   int bos;   �ӥ塼�ݡ��Ȥ�Ϥ�����

   [����]
   �㤨�� setviewport(30, 30, 130, 130, 0) ��¹Ԥ����塢

   drawaxeslb(5, 2, 2, 1, 6, 10);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��10�ӥåȳ�¦�ˡ�
   ���ټ��Ȳ��ؼ������褵��ޤ���
   ���ξ�硢X����������Ĺ����5ʬ�䤵�줿���֤ˡ�
   û����2ʬ�䤵�줿���֤�������ޤ���
   Y����������Ĺ����2ʬ�䤵�줿���֤�������ޤ���
   û����ʬ�䤷�ʤ��Τ�������ޤ���
 */
#define drawaxeslb(sx,ssx,sy,ssy,l,b) do {\
        drawaxisl(sy,ssy,l,b); drawaxisb(sx,ssx,l,b); } while(0)

/*
   [̾��]
   drawaxisix --- ��ؼ�������
   drawaxisiy --- ��ټ�������

   [����]
   drawaxisi?(sep, ssep, len, bos)
   int sep;  Ĺ����ʬ���
   int ssep; û����ʬ���
   int len;  ����Ĺ��
   int bos;  ���������ӥ塼�ݡ��Ⱥ�ɸ����
          
   [����]
   �㤨�� setviewport(30, 30, 130, 130, 0) ��¹Ԥ����塢

   drawaxisix(2, 0, 6, 50);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��100X100����Ρ�
   Y=50�ΰ��֤���ؼ������褵��ޤ���
   ���ξ�硢������Ĺ����2ʬ�䤵�줿���֤������졢
   û����������ޤ���
 */
#define drawaxisix(s,ss,l,b) drawaxisx(AXIS_INSIDE,s,ss,l,b)
#define drawaxisiy(s,ss,l,b) drawaxisy(AXIS_INSIDE,s,ss,l,b)

/*
   [̾��]
   drawaxesi --- ��ؼ�����ټ�������

   [����]
   drawaxesi(sepx, ssepx, sepy, ssepy, len, bosx, bosy)
   int sepx;  X����Ĺ����ʬ���
   int ssepx; X����û����ʬ���
   int sepy;  Y����Ĺ����ʬ���
   int ssepy; Y����û����ʬ���
   int len;   ����Ĺ��
   int bosx;  X���������ӥ塼�ݡ��Ⱥ�ɸ����
   int bosy;  Y���������ӥ塼�ݡ��Ⱥ�ɸ����

   [����]
   �㤨�� setviewport(30, 30, 130, 130, 0) ��¹Ԥ����塢

   drawaxesi(0, 0, 0, 0, 6, 50, 10);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��100X100����Ρ�
   Y=50�ΰ��֤���ؼ������褵�졢X=10�ΰ��֤���ټ������褵��ޤ���
   ���ξ�硢������������ޤ���
 */
#define drawaxesi(sx,ssx,sy,ssy,l,bx,by) do {\
        drawaxisix(sx,ssx,l,bx); drawaxisiy(sy,ssy,l,by); }while(0)

enum axis_positions {
  AXIS_LEFT   = 0, /* ���ټ� */
  AXIS_RIGHT  = 1, /* ���ټ� */
  AXIS_TOP    = 0, /* ��ؼ� */
  AXIS_BOTTOM = 1, /* ���ؼ� */
  AXIS_INSIDE = 2, /* ��XY�� */
};

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [̾��]
   drawaxisx --- �ӥ塼�ݡ��Ȥأؼ�������

   [����]
   void drawaxisx(apos, sep, ssep, len, bos)
   int apos; ��ɸ�����֥�����
   int sep;  Ĺ����ʬ���
   int ssep; û����ʬ���
   int len;  ����Ĺ��
   int bos;  ���֥����פ� AXIS_INSIDE �ξ�硢�������褹������ֺ�ɸ
             ���֥����פ� AXIS_INSIDE �ʳ��ϡ��ӥ塼�ݡ��Ȥ�Ϥ�����

   [����]
   setviewport ��������줿�ӥ塼�ݡ��Ȥˣؼ������衣

   apos �ˤϰʲ��ΰ��֥����פΤ����줫����ꤷ�ޤ���

   enum axis_positions {
     AXIS_TOP    = 0, ��ؼ�
     AXIS_BOTTOM = 1, ���ؼ�
     AXIS_INSIDE = 2, ��ؼ�
   };

   bos �ˤϰ��֥����פ� AXIS_TOP��AXIS_BOTTOM �Τ����줫�ξ��ϡ�
   �ӥ塼�ݡ��Ȥ�Ϥ�;͵��(�ӥåȿ�)����ꤷ�ޤ���
   ���֥����פ� AXIS_INSIDE �ξ�� bos �ˤϡ�
   �������褹������ֺ�ɸ����ꤷ�ޤ���
 */
void drawaxisx(int apos, int sep, int ssep, int len, int bos);

/*
   [̾��]
   drawaxisy --- �ӥ塼�ݡ��Ȥأټ�������

   [����]
   void drawaxisy(apos, sep, ssep, len, bos)
   int apos; ��ɸ�����֥�����
   int sep;  Ĺ����ʬ���
   int ssep; û����ʬ���
   int len;  ����Ĺ��
   int bos;  ���֥����פ� AXIS_INSIDE �ξ�硢�������褹������ֺ�ɸ
             ���֥����פ� AXIS_INSIDE �ʳ��ϡ��ӥ塼�ݡ��Ȥ�Ϥ�����

   [����]
   setviewport ��������줿�ӥ塼�ݡ��Ȥˣټ������衣
   apos �ˤϰʲ��ΰ��֥����פΤ����줫����ꤷ�ޤ���

   enum axis_positions {
     AXIS_LEFT   = 0, ���ټ�
     AXIS_RIGHT  = 1, ���ټ�
     AXIS_INSIDE = 2, ��ټ�
   };
   
   bos �ˤϰ��֥����פ� AXIS_LEFT��AXIS_RIGHT �Τ����줫�ξ��ϡ�
   �ӥ塼�ݡ��Ȥ�Ϥ�;͵��(�ӥåȿ�)����ꤷ�ޤ���
   ���֥����פ� AXIS_INSIDE �ξ�� bos �ˤϡ�
   �������褹������ֺ�ɸ����ꤷ�ޤ���
 */
void drawaxisy(int apos, int sep, int ssep, int len, int bos);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
