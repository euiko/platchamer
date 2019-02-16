/*
 * Text drawing service in graffit library < outtext_.h >
 *
 * Outtext Function with Format for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _OUTTEXT__H_
#define _OUTTEXT__H_
#include <outtext.h>
#include <graphr2_.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [̾��]
   outtextxyf_ --- ����ե��å����̤ؤΥե����ޥå��եƥ����Ƚ���

   [����]
   outtextxyf_(x, y, form, ...)
   double x, y; ����ե��å����̤Υ�����ɥ���ɸ(��ư������)
   char *form;  printf�����ν�ʸ����
   ...;         ���Ѱ���

   [����]
   setviewport_ �� setwindow_ �ǻ��ꤷ������Ū�ʺ�ɸ�ء�
   �ե����ޥå��եƥ����Ƚ��Ϥ򤷤ޤ���
   form �˻��ꤹ��񼰻���Ҥ� printf �򻲾Ȥ��Ʋ�������
   â�������Υ롼����ϥ��֤���Խ����򤷤ޤ���
 */
extern void outtextxyf_(double x, double y, char *form, ...);
extern void outtextxyfl2_(double x, double y, char *form, ...);
extern void outtextxyflx_(double x, double y, char *form, ...);
extern void outtextxyfly_(double x, double y, char *form, ...);
extern void outtextxyfr3_(double x, double y, double z, char *form, ...);
extern void outtextxyfp3_(double x, double y, double z, char *form, ...);
extern void outtextxyfsl_(double x, double y, double z, char *form, ...);
extern void outtextxyfsr_(double x, double y, double z, char *form, ...);
extern void outtextxyfs3_(double x, double y, double z, char *form, ...);
extern void outtextxyfrn_(double *x, char *form, ...);
extern void outtextxyfpn_(double *x, char *form, ...);
extern void outtextxyfsn_(double *x, char *form, ...);

/*
   [̾��]
   outtextxyprintf_ --- ����ե��å����̤ؤΥե����ޥå��եƥ����Ƚ���

   [����]
   outtextxyprintf_(x, y, form, ...)
   double x, y; ����ե��å����̤Υ�����ɥ���ɸ(��ư������)
   char *form;  printf�����ν�ʸ����
   ...;         ���Ѱ���

   [����]
   setviewport_ �� setwindow_ �ǻ��ꤷ������Ū�ʺ�ɸ�ء�
   �ե����ޥå��եƥ����Ƚ��Ϥ򤷤ޤ���
   form �˻��ꤹ��񼰻���Ҥ� printf �򻲾Ȥ��Ʋ�������
   ���Υ롼����� outtextf �Ȱ㤤�����֤���Խ����򤷤ޤ���
 */
extern void outtextxyprintf_(double x, double y, char *form, ...);
extern void outtextxyprintfl2_(double x, double y, char *form, ...);
extern void outtextxyprintflx_(double x, double y, char *form, ...);
extern void outtextxyprintfly_(double x, double y, char *form, ...);
extern void outtextxyprintfr3_(double x, double y, double z,
			       char *form, ...);
extern void outtextxyprintfp3_(double x, double y, double z,
			       char *form, ...);
extern void outtextxyprintfsl_(double x, double y, double z,
			       char *form, ...);
extern void outtextxyprintfsr_(double x, double y, double z,
			       char *form, ...);
extern void outtextxyprintfs3_(double x, double y, double z,
			       char *form, ...);
extern void outtextxyprintfrn_(double *x, char *form, ...);
extern void outtextxyprintfpn_(double *x, char *form, ...);
extern void outtextxyprintfsn_(double *x, char *form, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _OUTTEXT__H_ */
