/*
 * 2-dimensional turtle graphic interface in graffit library < gturtle_.h >
 *
 * Turtle Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _GTURTLE__H_
#define _GTURTLE__H_
#include <math.h>
#include <graphr2_.h>

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
   �����ȥ륰��ե��å��ѥå�����

   �����2�����Υ��ɺ�ɸ�ǥ����ȥ륰��ե��å���¸�����ѥå������Ǥ���
   move_�ǵ��ε��פ����衢setangle_�ǵ��θ����Ƥ������Ѥ����ꡢ
   turn_�Ǹ��߸����Ƥ������Ѥ��顢���θ����Ƥ������Ѥ��Ѥ��ޤ���
   ���٤ϥ�ǥ�����ǻ��ꤷ�ޤ���
   �ǥ��꡼�ǻ��ꤷ�������ϰʲ��Τ褦���Ѵ����Ʋ�������

   turn_(RAD(20));
 */

extern void move_(double d);
extern void setangle_(double angle);
extern void turn_(double dangle);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* _GTURTLE_H_ */
