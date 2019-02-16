/*
 * Coloring interface in graffit library < coloring.h >
 *
 * Various Definitions of Color for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _COLORING_H_
#define _COLORING_H_
#include <graphics.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   ���顼���(Coloring)�ѥå�����

   �����BGI��Ϳ�����Ƥ���ѥ�åȤ��Ф��ơ�����ǡ�����󥫥顼�ʤɤ�
   ������뤿��Υ롼���󽸤Ǥ����㤨��4��������ե��å��������褹����ˡ�
   4�����ܤ򥰥�ǡ�����󥫥顼�˳�����Ƥ뤿��ʤɤ˻��ѤǤ���Ǥ��礦��

   ���Υѥå������Ǥϰʲ�����󷿤���ܿ��Ȥ��ƥ����������ޤ���

   enum COLORS {
     BLACK     = 0, DARKGRAY     =  8,
     BLUE      = 1, LIGHTBLUE    =  9,
     GREEN     = 2, LIGHTGREEN   = 10,
     CYAN      = 3, LIGHTCYAN    = 11,
     RED       = 4, LIGHTRED     = 12,
     MAGENTA   = 5, LIGHTMAGENTA = 13,
     BROWN     = 6, YELLOW       = 14,
     LIGHTGRAY = 7, WHITE        = 15,
   };

   ���顼����Υ롼����ˤϰʲ��δؿ����Ѱդ���Ƥ��ޤ���

   ��RGBľ������ǡ������
   coloring(�����ֹ�, ��λ�ֹ�)

   ��2��ľ������ǡ������
   coloring2(�����ֹ�, ��λ�ֹ�, ���ܿ�1, ���ܿ�2)

   ��3��ʿ�̥���ǡ������
   coloring3(�����ֹ�, ��λ�ֹ�, ���ܿ�1, ���ܿ�2, ���ܿ�3)

   ��N����������ǡ������
   coloringN(�����ֹ�, ��λ�ֹ�, ���ܿ���, *���ܿ�����)

   �����ֹ�Ƚ�λ�ֹ�ϥѥ�å��ֹ�Ǥ��ꡢ0 ���� getmaxcolor() ���֤����
   ���顼�����ϰ���ǻ���Ǥ��ޤ������ܿ��ˤ���� COLORS ����ꤷ�ޤ���
   �����ϡ�������⥫�顼��󥰤��Ԥ�줿�������֤��ޤ���
   �����������顼��󥰤˼��Ԥ������ˤ� 0 ���֤��ޤ���
   �ѥ�åȤγ����ֹ�Ƚ�λ�ֹ椬Ʊ��Ǥ��äƤϤʤ�ޤ���

   ���顼����Υ롼����ˤ�ä�������줿���顼����ꤹ��ˤϡ�
   ľ�ܡ��ѥ�å��ֹ����ꤹ��ʳ��ˡ�
   ��ư�������ˤ�벾��Ū�ʥ��顼������ꤷ��
   ��ư�������ˤ�äƥ����������뤿��δؿ����Ѱդ���Ƥ��ޤ���

   ��ľ������ǡ��������
   co_coloring(�����ֹ�, ��λ�ֹ�, double r1, double r2)
   int getcolor_(double r)
   setcolor_(double r)

   ��ľ������ǡ�������ѡ��줬 10 �Υ����������
   co_coloring(�����ֹ�, ��λ�ֹ�, double r1, double r2)
   int getlog10color_(double r)
   setlog10color_(double r)

   (��) BGI �Ǥ�Ϣ³����ѥ�å��ֹ�˴��꿧��������Ƥ��Ƥ��ꡢ
   BLACK, BLUE, GREEN,... �Ȥ����ۿ��� enum �� COLORS ���������Ƥ��롣
   ���Υإå��ե��������Ū�ϥѥ�åȤ� RGB �ͤ�ľ���������ߤο�ɽ
   ����Ԥ����ȤǤ���Τ� enum �� COLORS ���������Ƥ��� BLUE, RED ��
   �ɤ��ͤ�������̣��ʤ��ʤ��ʤ롣�����������ʿ����طʿ��˴ؤ��Ƥϥ�
   ��å�����Ԥ�ʤ��Τ�����Ǥ��������ꥸ�ʥ�� BGI �Ǥϼ�� 16 
   ����������߷פ���Ƥ��뤬������⡼�ɤˤ�äƤ� 2,4,8 ���ʤɤο���
   �򰷤����Ȥ⤢�롣�ޤ����ۺ� X11 �� BGI �Ǥ�Ǥ�տ��Υѥ�åȤ򰷤�
   ���Ȥ���ǽ�Ǥ��롣XBGI �Ǥ� BGI �Υѥ�å�����δ���Ȥ��ơ��ѥ��
   ���ֹ� 0 �˹����ѥ�å��ֹ� getmaxcolor() ���򤬳�����Ƥ��Ƥ��롣
   ���δ�������������Ȥ��θ����ȡ��嵭�δؿ��ο侩Ū�ʻȤ�����, 0 
   �� getmaxcolor() �����Ϣ³�����ѥ�å��ֹ���Ф���RGB�����Ԥ���
   �ȤǤ��롣

   (��) coloring(1, getmaxcolor()-1);

   �⤷ 16 ���⡼�ɤʤ� 1 ���� 15 �ޤǤ��桼���������Ѥ��륰��ǡ�����
   ��Ȥʤ� 0(=BLACK) �� getmaxcolor(=WHITE) ����¸����롣
 */

struct coloringtype_ {
  int p1, p2;
  double r1, r2;
};

/*
   [̾��]
   coloringCCCD --- 3��ľ������ǡ������

   [����]
   coloringCCCD(p1, p2, c1, c2, c3, d)
   int p1, p2;     �ѥ�å��ֹ�p1����p2�ޤ�
   int c1, c2, c3; 3���δ��ܿ�
   double d;       ����Ψ

   [����]
   ���ꤵ�줿3������ܤȤ��ơ�
   c1 -> c2 -> c3 �Ȥʤ�褦�ʥ���ǡ�����󥫥顼��������ޤ���
   d �Ϻ���Ψ���礭����Ф褯�����ޤ����侩�ͤ�0.7�Ǥ���
 */
extern int coloringCCCD(int p1, int p2, int c1, int c2, int c3, double d);

/*
   [̾��]
   coloring --- RGBľ������ǡ������

   [����]
   coloring(p1, p2)
   int p1, p2; �ѥ�å��ֹ�p1����p2�ޤ�

   [����]
   RGB(�֡��С���)����ܤȤ��ơ�
   �� -> �� -> �� �Ȥʤ�褦�ʥ���ǡ�����󥫥顼��������ޤ���
 */
extern int coloring(int p1, int p2);

/*
   [̾��]
   coloring2 --- 2��ľ������ǡ������

   [����]
   coloring2(p1, p2, c1, c2)
   int p1, p2; �ѥ�å��ֹ�p1����p2�ޤ�
   int c1, c2; 2���δ��ܿ�
 *
   [����]
   ���ꤵ�줿2������ܤȤ���ľ���Υ���ǡ�������������ޤ���
 */
extern int coloring2(int p1, int p2, int c1, int c2);

/*
   [̾��]
   co_coloring     --- �¿���ľ������ǡ������Υѥ�å��ֹ���б�
   getcolor_       --- ���ꤵ�줿�¿����б�����ѥ�åȤ��֤�
   setcolor_       --- ���ꤵ�줿�¿����б�����ѥ�åȤ����ʿ��򥻥å�
   getlog10color_  --- ���ꤵ�줿�¿����б�����ѥ�åȤ��֤�(�п�)
   setlog10color_  --- ���ꤵ�줿�¿����б�����ѥ�åȤ����ʿ��򥻥å�(�п�)

   [����]
   co_coloring(int p1, int p2, double r1, double r2)
   int getcolor_(double r)
   setcolor_(double r)
   int getlog10color_(double r)
   setlog10color_(double r)
   int p1, p2;    �ѥ�å��ֹ�p1����p2�ޤ�
   double r1, r2; �б������¿��ΰ�r1����r2�ޤ�
   double r;      �¿��ΰ���Τ������

   [����]
   �����ϡ��¿���ľ������ǡ������Υѥ�å��ֹ�˥����������뤿���
   ���Ѥ��ޤ����㤨�С��ʲ��Τ褦�˻��Ѥ��ޤ���

   coloring(0, getmaxcolor());              RGB����ǡ����������
   co_coloring(0, getmaxcolor(), 0.0, 1.0); ���顼��¿�[0,1]�˼���
   c = getcolor_(0.1);                      0.1���б�����ѥ�åȤ����
   putpixel(100, 100, c);                   ��ɸ(100,100)����������
   setcolor_(0.5);                          0.5���б�����ѥ�åȤ����ʿ���
   line(100, 100, 200, 200);                ���ο�����������

   �ޤ����п���������󥰤ξ��ϰʲ��Τ褦�ˤ��ޤ���

   coloring(0, getmaxcolor());              RGB����ǡ����������
   co_coloring(0, getmaxcolor(), 0.001, 10.0); ���顼��¿�[0.001,10.0]�˼���
   c = getlog10color_(1.0);                 1.0���б�����ѥ�åȤ����
   putpixel(100, 100, c);                   ��ɸ(100,100)����������
   setlog10color_(0.5);                     0.5���б�����ѥ�åȤ����ʿ���
   line(100, 100, 200, 200);                ���ο�����������

 */
extern void co_coloring(int p1, int p2, double r1, double r2);
extern int getcolor_(double r);
extern void setcolor_(double r);

extern int getlog10color_(double r);
extern void setlog10color_(double r);

/*
   [̾��]
   coloring3 --- 3��ʿ�̥���ǡ������

   [����]
   coloring3(p1, p2, c1, c2, c3)
   int p1, p2;     �ѥ�å��ֹ�p1����p2�ޤ�
   int c1, c2, c3; 3���δ��ܿ�

   [����]
   ���ꤵ�줿3������ܤȤ���ʿ�̤Υ���ǡ�������������ޤ���
 */
extern int coloring3(int p1, int p2, int c1, int c2, int c3);

/*
   [̾��]
   coloringN --- N����������ǡ������

   [����]
   coloringN(p1, p2, n, cs)
   int p1, p2; �ѥ�å��ֹ�p1����p2�ޤ�
   int n;      ���ܿ��ο�
   int *cs;    ���ܿ�������

   [����]
   ���ꤵ�줿N������ܤȤ��ƶ����Υ���ǡ�������������ޤ���
 */
extern int coloringN(int p1, int p2, int n, int *cs);

/*
   [̾��]
   swap_colors --- 2��p1��p2�������ؤ���롼����

   [����]
   swap_colors(p1, p2)
   int p1; �ѥ�å��ֹ�1
   int p2; �ѥ�å��ֹ�2

   [����]
   2��p1��p2�������ؤ��ޤ���
 */
extern void swap_colors(int p1, int p2);

/*
   [̾��]
   rotate_colors --- p2-p1�֤Υѥ�åȤ��ž����롼����

   [����]
   rotate_colors(p1, p2)
   int p1; �ѥ�å��ֹ�1
   int p2; �ѥ�å��ֹ�2

   [����]
   p2-p1�֤Υѥ�åȤ��ž���ޤ���
 */
extern void rotate_colors(int p1, int p2);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _COLORING_H_ */



