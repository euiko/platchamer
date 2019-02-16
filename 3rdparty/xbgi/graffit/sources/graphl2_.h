/*
 * 2-dimensional logarithmic graphic interface in graffit < graphl2_.h >
 *
 * Logarithmic Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GRAPHL2__H_
#define _GRAPHL2__H_
#include <graphr2_.h>
#include <outtext_.h>

/*
   [̾��]
   lxtox --- LOG-X��ɸ����X��ɸ�����ޥ���
   lytoy --- LOG-Y��ɸ����Y��ɸ�����ޥ���

   [����]
   lxtox(x)
   lytoy(y)
   double x, y; LOG��ɸ

   [����]
   �㤨�С�setwindow_(1E-10, 1E+5, 1E+10, 1E-5) �Ȥ��Ƥ���
   �������Ѵ��ޥ������Ѥ���ȥ��ɺ�ɸ�Ϥ�LOG��ɸ�Ȥߤʤ���
   �б�������ɺ�ɸ�Ϥκ�ɸ���֤��ޤ���
 */
#define lxtox(x) (log((x)/__W.left)*\
		  (__W.right-__W.left)/log(__W.right/__W.left)+__W.left)
#define lytoy(y) (log((y)/__W.bottom)*\
		  (__W.top-__W.bottom)/log(__W.top/__W.bottom)+__W.bottom)

/*
   [̾��]
   linel2_      --- LOG2��ɸ�Ѵ��� line     ľ������ޥ���
   linetol2_    --- LOG2��ɸ�Ѵ��� lineto   ���а��֤ؤ�ľ������ޥ���
   putpixell2_  --- LOG2��ɸ�Ѵ��� putpixel ������ޥ���
   movetol2_    --- LOG2��ɸ�Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ޥ���
   outtextxyl2_ --- LOG2��ɸ�Ѵ��� outtext  �ƥ����Ƚ��ϥޥ���
  
   [����]
   linel2_     (x1,y1, x2,y2)
   linetol2_   (x,y)
   putpixell2_ (x,y,c)
   movetol2_   (x,y)
   outtextxyl2_(x,y,str)
   double x1,y1; LOG2��ɸ
   double x2,y2; LOG2��ɸ
   double x,y;   LOG2��ɸ
   int c;        �ѥ�å��ֹ�
   char *str;    ʸ����
  
   [����]
   �����������³����LOG2��ɸ�Ѵ��ѤΥޥ���Ǥ���
   LOG2����դʤɤ��ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��2����������ɥ��Ѵ��ѥå����� graphr2_.h 
 */
#define linel2_(x0,y0,x1,y1) \
        line_(lxtox(x0),lytoy(y0),lxtox(x1),lytoy(y1))
#define linetol2_(x,y) \
        lineto_(lxtox(x),lytoy(y))
#define rectanglel2_(x0,y0,x1,y1) \
        rectangle_(lxtox(x0),lytoy(y0),lxtox(x1),lytoy(y1))
#define barl2_(x0,y0,x1,y1) \
        bar_(lxtox(x0),lytoy(y0),lxtox(x1),lytoy(y1))
#define putpixell2_(x,y,c) \
        putpixel_(lxtox(x),lytoy(y),c)
#define putpointl2_(x,y) \
        putpoint_(lxtox(x),lytoy(y))
#define movetol2_(x,y) \
        moveto_(lxtox(x),lytoy(y))
#define outtextxyl2_(x,y,s) \
        outtextxy_(lxtox(x),lytoy(y),s)

/*
   [̾��]
   linelx_      --- LOGX��ɸ�Ѵ��� line     ľ������ޥ���
   linetolx_    --- LOGX��ɸ�Ѵ��� lineto   ���а��֤ؤ�ľ������ޥ���
   putpixellx_  --- LOGX��ɸ�Ѵ��� putpixel ������ޥ���
   movetolx_    --- LOGX��ɸ�Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ޥ���
   outtextxylx_ --- LOGX��ɸ�Ѵ��� outtext  �ƥ����Ƚ��ϥޥ���

   [����]
   linelx_     (x1,y1, x2,y2)
   linetolx_   (x,y)
   putpixellx_ (x,y,c)
   movetolx_   (x,y)
   outtextxylx_(x,y,str)
   double x1,y1; LOGX��ɸ
   double x2,y2; LOGX��ɸ
   double x,y;   LOGX��ɸ
   int c;        �ѥ�å��ֹ�
   char *str;    ʸ����
  
   [����]
   �����������³����LOGX��ɸ�Ѵ��ѤΥޥ���Ǥ���
   LOGX����դʤɤ��ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��2����������ɥ��Ѵ��ѥå����� graphr2_.h 
 */
#define linelx_(x0,y0,x1,y1) \
        line_(lxtox(x0),y0,lxtox(x1),y1)
#define linetolx_(x,y) \
        lineto_(lxtox(x),y)
#define rectanglelx_(x0,y0,x1,y1) \
        rectangle_(lxtox(x0),y0,lxtox(x1),y1)
#define barlx_(x0,y0,x1,y1) \
        bar_(lxtox(x0),y0,lxtox(x1),y1)
#define putpixellx_(x,y,c) \
        putpixel_(lxtox(x),y,c)
#define putpointlx_(x,y) \
        putpoint_(lxtox(x),y)
#define movetolx_(x,y) \
        moveto_(lxtox(x),y)
#define outtextxylx_(x,y,s) \
        outtextxy_(lxtox(x),y,s)

/*
   [̾��]
   linely_      --- LOGY��ɸ�Ѵ��� line     ľ������ޥ���
   linetoly_    --- LOGY��ɸ�Ѵ��� lineto   ���а��֤ؤ�ľ������ޥ���
   putpixelly_  --- LOGY��ɸ�Ѵ��� putpixel ������ޥ���
   movetoly_    --- LOGY��ɸ�Ѵ��� moveto   �����ȥݥ���Ȱ�ư�ޥ���
   outtextxyly_ --- LOGY��ɸ�Ѵ��� outtext  �ƥ����Ƚ��ϥޥ���
  
   [����]
   linely_     (x1,y1, x2,y2)
   linetoly_   (x,y)
   putpixelly_ (x,y,c)
   movetoly_   (x,y)
   outtextxyly_(x,y,str)
   double x1,y1; LOGY��ɸ
   double x2,y2; LOGY��ɸ
   double x,y;   LOGY��ɸ
   int c;        �ѥ�å��ֹ�
   char *str;    ʸ����
  
   [����]
   �����������³����LOGY��ɸ�Ѵ��ѤΥޥ���Ǥ���
   LOGY����դʤɤ��ñ�����褹�뤳�Ȥ��Ǥ��ޤ���
   �����������³���ϰʲ��Υѥå��������ư��Ƥ��ޤ���

   ��2����������ɥ��Ѵ��ѥå����� graphr2_.h 
 */
#define linely_(x0,y0,x1,y1) \
        line_(x0,lytoy(y0),x1,lytoy(y1))
#define linetoly_(x,y) \
        lineto_(x,lytoy(y))
#define rectanglely_(x0,y0,x1,y1) \
        rectangle_(x0,lytoy(y0),x1,lytoy(y1))
#define barly_(x0,y0,x1,y1) \
        bar_(x0,lytoy(y0),x1,lytoy(y1))
#define putpixelly_(x,y,c) \
        putpixel_(x,lytoy(y),c)
#define putpointly_(x,y) \
        putpoint_(x,lytoy(y))
#define movetoly_(x,y) \
        moveto_(x,lytoy(y))
#define outtextxyly_(x,y,s) \
        outtextxy_(x,lytoy(y),s)

#if 0
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif
#endif

#endif
