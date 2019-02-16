/*
 * Axes utilities for R^2 graphics in graffit library < axes_.h >
 *
 * Draw Axes on Window Port for Borland Graphics Interface
 *
 * Copyright (C) 1991-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _AXES__H_
#define _AXES__H_
#include <graphr2_.h>
#include <axes.h>

/*
   [̾��]
   drawaxisl_  --- ���ټ�������
   drawaxist_  --- ��ؼ�������
   drawaxisr_  --- ���ټ�������
   drawaxisb_  --- ���ؼ�������

   [����]
   drawaxis?_(sep, ssep, len, bos)
   int sep;  Ĺ����ʬ���
   int ssep; û����ʬ���
   int len;  ����Ĺ��
   int bos;  �ӥ塼�ݡ��Ȥ�Ϥ�����
          
   [����]
   �㤨�� setviewport_(30, 30, 130, 130, 0) ��¹Ԥ����塢
   setwindow_(-1.0, 10.0, 1.0, -10.0) �ǲ���Ū�ʺ�ɸ�ͤ���ꤷ��

   drawaxisl_(2, 2, 6, 10);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��10�ӥåȳ�¦�ˡ�
   ���ټ������褵��ޤ���
   ���ξ�硢������Ĺ����2ʬ�䤵�줿���֤ˡ�
   û����2ʬ�䤵�줿���֤�������ޤ���
   �����������줿��ɸ�ˤϡ�����Ū�ʺ�ɸ�ͤˤ���������դ��ޤ���
 */
#define drawaxisl_(s,ss,l,b) drawaxisy_(AXIS_LEFT,  s,ss,l,b)
#define drawaxist_(s,ss,l,b) drawaxisx_(AXIS_TOP,   s,ss,l,b)
#define drawaxisr_(s,ss,l,b) drawaxisy_(AXIS_RIGHT, s,ss,l,b)
#define drawaxisb_(s,ss,l,b) drawaxisx_(AXIS_BOTTOM,s,ss,l,b)

/*
   [̾��]
   drawaxeslb_ --- ���ټ��Ȳ��ؼ�������

   [����]
   drawaxeslb_(sepx, ssepx, sepy, ssepy, len, bos)
   int sepx;  X����Ĺ����ʬ���
   int ssepx; X����û����ʬ���
   int sepy;  Y����Ĺ����ʬ���
   int ssepy; Y����û����ʬ���
   int len;   ����Ĺ��
   int bos;   �ӥ塼�ݡ��Ȥ�Ϥ�����
          
   [����]
   �㤨�� setviewport_(30, 30, 130, 130, 0) ��¹Ԥ����塢
   setwindow_(-1.0, 10.0, 1.0, -10.0) �ǲ���Ū�ʺ�ɸ�ͤ���ꤷ��

   drawaxeslb_(5, 2, 2, 1, 6, 10);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��10�ӥåȳ�¦�ˡ�
   ���ټ��Ȳ��ؼ������褵��ޤ���
   ���ξ�硢X����������Ĺ����5ʬ�䤵�줿���֤ˡ�
   û����2ʬ�䤵�줿���֤�������ޤ���
   Y����������Ĺ����2ʬ�䤵�줿���֤�������ޤ���
   û����ʬ�䤷�ʤ��Τ�������ޤ���
   �����������줿��ɸ�ˤϡ�����Ū�ʺ�ɸ�ͤˤ���������դ��ޤ���
 */
#define drawaxeslb_(sx,ssx,sy,ssy,l,b) do{\
        drawaxisb_(sx,ssx,l,b);drawaxisl_(sy,ssy,l,b);}while(0)

/*
   [̾��]
   drawaxisix_ --- ��ؼ�������
   drawaxisiy_ --- ��ټ�������

   [����]
   drawaxisi?_(sep, ssep, len, bos)
   int sep;  Ĺ����ʬ���
   int ssep; û����ʬ���
   int len;  ����Ĺ��
   int bos;  ���������ӥ塼�ݡ��Ⱥ�ɸ����

   [����]
   �㤨�� setviewport_(30, 30, 130, 130, 0) ��¹Ԥ����塢
   setwindow_(-1.0, 10.0, 1.0, -10.0) �ǲ���Ū�ʺ�ɸ�ͤ���ꤷ��

   drawaxisix_(2, 0, 6, 0.0);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��100X100����Ρ�
   ����Ū�ʺ�ɸY=0.0�ΰ��֤���ؼ������褵��ޤ���
   ���ξ�硢������Ĺ����2ʬ�䤵�줿���֤������졢
   û����������ޤ���
   �����������줿��ɸ�ˤϡ�����Ū�ʺ�ɸ�ͤˤ���������դ��ޤ���
 */
#define drawaxisix_(s,ss,l,b) drawaxisx_(AXIS_INSIDE,s,ss,l,b)
#define drawaxisiy_(s,ss,l,b) drawaxisy_(AXIS_INSIDE,s,ss,l,b)

/*
   [̾��]
   drawaxesi_ --- ��ؼ�����ټ�������

   [����]
   drawaxesi_(sepx, ssepx, sepy, ssepy, len, bosx, bosy)
   int sepx;  X����Ĺ����ʬ���
   int ssepx; X����û����ʬ���
   int sepy;  Y����Ĺ����ʬ���
   int ssepy; Y����û����ʬ���
   int len;   ����Ĺ��
   int bosx;  X���������ӥ塼�ݡ��Ⱥ�ɸ����
   int bosy;  Y���������ӥ塼�ݡ��Ⱥ�ɸ����
          
   [����]
   �㤨�� setviewport_(30, 30, 130, 130, 0) ��¹Ԥ����塢
   setwindow_(-1.0, 10.0, 1.0, -10.0) �ǲ���Ū�ʺ�ɸ�ͤ���ꤷ��

   drawaxesi_(0, 0, 0, 0, 6, 0.0, -0.8);

   �Ȥ���ȡ��ӥ塼�ݡ���(30,30)-(130,130)��100X100����Ρ�
   ����Ū�ʺ�ɸY=0.0�ΰ��֤���ؼ������褵�졢
   ����Ū�ʺ�ɸX=-0.8�ΰ��֤���ټ������褵��ޤ���
   ���ξ�硢������������ޤ���
   �����������줿��ɸ�ˤϡ�����Ū�ʺ�ɸ�ͤˤ���������դ��ޤ���
 */
#define drawaxesi_(sx,ssx,sy,ssy,l,bx,by) do{\
        drawaxisix_(sx,ssx,l,bx);drawaxisiy_(sy,ssy,l,by);}while(0)

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [̾��]
   drawaxisx_ --- ������ɥ��ݡ��Ȥأؼ�������

   [����]
   void drawaxisx_(apos, sep, ssep, len, bos)
   int apos;     ��ɸ�����֥�����
   int sep;      Ĺ����ʬ���
   int ssep;     û����ʬ���
   int len;      ����Ĺ��
   double bos;   ���֥����פ� AXIS_INSIDE �ξ�硢�������褹������ֺ�ɸ
                 ���֥����פ� AXIS_INSIDE �ʳ��ϡ��ӥ塼�ݡ��Ȥ�Ϥ�����

   [����]
   setviewport_ �� setwindow_ ��������줿������ɥ��ݡ��Ȥˣؼ������衣
   Ĺ�������������褵�줿��ɸ�ˤϥ���ե��å�ʸ���Ǻ�ɸ�ͤ�������ޤ���

   apos �ˤϰʲ��ΰ��֥����פΤ����줫����ꤷ�ޤ���

   enum axis_positions {
     AXIS_TOP    = 0, ��ؼ�
     AXIS_BOTTOM = 1, ���ؼ�
     AXIS_INSIDE = 2, ��ؼ�
   };

   bos �ˤϰ��֥����פ� AXIS_TOP��AXIS_BOTTOM �Τ����줫�ξ��ϡ�
   ������ɥ��ݡ��Ȥ�Ϥ�;͵��(�ӥåȿ�)����ꤷ�ޤ���
   ���֥����פ� AXIS_INSIDE �ξ�� bos �ˤϡ�
   �������褹������ֺ�ɸ����ꤷ�ޤ���
   ����� setwindow_ �ǻ��ꤷ������Ū�ʺ�ɸ����ꤷ�ޤ���
   �����������줿��ɸ�ˤϡ�����Ū�ʺ�ɸ�ͤˤ���������դ��ޤ���
 */
extern void drawaxisx_(int apos, int sep, int ssep, int len, double bos);

/*
   [̾��]
   drawaxisy_ --- ������ɥ��ݡ��Ȥأټ�������

   [����]
   void drawaxisy_(apos, sep, ssep, len, bos)
   int apos;     ��ɸ�����֥�����
   int sep;      Ĺ����ʬ���
   int ssep;     û����ʬ���
   int len;      ����Ĺ��
   double bos;   ���֥����פ� AXIS_INSIDE �ξ�硢�������褹������ֺ�ɸ
                 ���֥����פ� AXIS_INSIDE �ʳ��ϡ��ӥ塼�ݡ��Ȥ�Ϥ�����

   [����]
   setviewport_ �� setwindow_ ��������줿������ɥ��ݡ��Ȥˣټ������衣
   Ĺ�������������褵�줿��ɸ�ˤϥ���ե��å�ʸ���Ǻ�ɸ�ͤ�������ޤ���

   apos �ˤϰʲ��ΰ��֥����פΤ����줫����ꤷ�ޤ���

   enum axis_positions {
     AXIS_LEFT   = 0, ���ټ�
     AXIS_RIGHT  = 1, ���ټ�
     AXIS_INSIDE = 2, ��ټ�
   };

   bos �ˤϰ��֥����פ� AXIS_LEFT��AXIS_RIGHT �Τ����줫�ξ��ϡ�
   ������ɥ��ݡ��Ȥ�Ϥ�;͵��(�ӥåȿ�)����ꤷ�ޤ���
   ���֥����פ� AXIS_INSIDE �ξ�� bos �ˤϡ�
   �������褹������ֺ�ɸ����ꤷ�ޤ���
   ����� setwindow_ �ǻ��ꤷ������Ū�ʺ�ɸ����ꤷ�ޤ���
   �����������줿��ɸ�ˤϡ�����Ū�ʺ�ɸ�ͤˤ���������դ��ޤ���
 */
extern void drawaxisy_(int apos, int sep, int ssep, int len, double bos);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
