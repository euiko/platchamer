/*
 * Text drawing service in graffit library < outtext.h >
 *
 * Outtext Function with Format for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 */
#ifndef _OUTTEXT_H_
#define _OUTTEXT_H_
#include <stdio.h>
#include <graphics.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/*
   [̾��]
   outtextxyf --- ����ե��å����̤ؤΥե����ޥå��եƥ����Ƚ���

   [����]
   outtextxyf(x, y, form, ...)
   int x, y;   ����ե��å����̤Υӥ塼�ݡ��Ⱥ�ɸ
   char *form; printf�����ν�ʸ����
   ...;        ���Ѱ���

   [����]
   setviewport �ǻ��ꤷ���ӥ塼�ݡ��Ⱥ�ɸ�ء�
   �ե����ޥå��եƥ����Ƚ��Ϥ򤷤ޤ���
   form �˻��ꤹ��񼰻���Ҥ� printf �򻲾Ȥ��Ʋ�������
   â�������Υ롼����ϥ��֤���Խ����򤷤ޤ���
 */
extern void outtextxyf(int x, int y, char *form, ...);

/*
   [̾��]
   outtextxyf --- ����ե��å����̤ؤΥե����ޥå��եƥ����Ƚ���

   [����]
   outtextxyf(form, ...)
   char *form; printf�����ν�ʸ����
   ...;        ���Ѱ���

   [����]
   ����ե��å����̤Υ����Ⱥ�ɸ�ء�
   �ե����ޥå��եƥ����Ƚ��Ϥ򤷤ޤ���
   form �˻��ꤹ��񼰻���Ҥ� printf �򻲾Ȥ��Ʋ�������
   â�������Υ롼����ϥ��֤���Խ����򤷤ޤ���
 */
extern void outtextf(char *form, ...);

/*
   [̾��]
   outtextxyprintf --- ����ե��å����̤ؤΥե����ޥå��եƥ����Ƚ���

   [����]
   outtextxyprintf(x, y, form, ...)
   int x, y;   ����ե��å����̤Υӥ塼�ݡ��Ⱥ�ɸ
   char *form; printf�����ν�ʸ����
   ...;        ���Ѱ���

   [����]
   setviewport �ǻ��ꤷ���ӥ塼�ݡ��Ⱥ�ɸ�ء�
   �ե����ޥå��եƥ����Ƚ��Ϥ򤷤ޤ���
   form �˻��ꤹ��񼰻���Ҥ� printf �򻲾Ȥ��Ʋ�������
   ���Υ롼����� outtextf �Ȱ㤤�����֤���Խ����򤷤ޤ���
 */
extern void outtextxyprintf(int x, int y, char *form, ...);

/*
   [̾��]
   outtextprintf --- ����ե��å����̤ؤΥե����ޥå��եƥ����Ƚ���

   [����]
   outtextprintf(form, ...)
   char *form; printf�����ν�ʸ����
   ...;        ���Ѱ���

   [����]
   ����ե��å����̤Υ����Ⱥ�ɸ�ء�
   �ե����ޥå��եƥ����Ƚ��Ϥ򤷤ޤ���
   form �˻��ꤹ��񼰻���Ҥ� printf �򻲾Ȥ��Ʋ�������
   ���Υ롼����� outtextf �Ȱ㤤�����֤���Խ����򤷤ޤ���
 */
extern void outtextprintf(char *form, ...);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _OUTTEXT_H_ */
