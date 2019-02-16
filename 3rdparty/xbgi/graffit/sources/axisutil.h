/*
 * Axis utilities for grafplot.h < axisutil.h >
 *
 * グラフの軸の最大・最小を適当に計算
 *
 * Copyright (C) 1996 Jun Takahashi, AIHARA Electrical Engineering Co.,Ltd.
 */
#ifndef _AXISUTIL_H_
#define _AXISUTIL_H_

#ifndef Float
#define Float double
#endif

/* function prototype definitions */

#ifndef __P
#if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define __P(p) p
#else
#define __P(p)
#endif
#endif

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* for decimal scaling */
void
pretty_ticks_axis __P((Float from_value, Float to_value,
		       int *div_tick, Float *from_tick, Float *to_tick));
Float
get_tick_axis __P((int num,
		   int div_tick, Float from_tick, Float to_tick));

Float
get_sub_tick_axis __P((int num,
		       int div_tick, Float from_tick, Float to_tick,
		       int sub_num, int sub_div_tick));

/* for log10 scaling */
void
pretty_ticks_log10_axis __P((Float from_value, Float to_value,
			     int *div_tick, Float *from_tick, Float *to_tick));

Float
get_tick_log10_axis __P((int num,
			 int div_tick, Float from_tick, Float to_tick));

Float
get_sub_tick_log10_axis __P((int num,
			     int div_tick, Float from_tick, Float to_tick,
			     int sub_num, int sub_div_tick));

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
