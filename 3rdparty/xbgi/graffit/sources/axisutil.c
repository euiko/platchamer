/*
 * Axis utilities for grafplot.h < axisutil.c >
 *
 * グラフの軸の最大・最小を適当に計算
 *
 * Copyright (C) 1996 Jun Takahashi, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <axisutil.h>

#define	MIN_DIV_TICK	7
#define	MAX_DIV_TICK	15
#define	NUM_OF_UNIT	4

/*
 * グラフの軸の最大・最小を適当に計算
 * 入力は描くグラフの最大値と最小値。ただし、大小は任意。
 * 出力は分割数と、入力値が入る切りのいい最大値と最小値。
 * ただし、大小は入力に合わせる。
 * 分割数は define された MIN_DIV_TICK と MAX_DIV_TICK の間。
 */

typedef struct _ticks_inf {
  int	unit_tick;
  int	min_tick;
  int	max_tick;
  int	div_tick;
  int	div_tick2;
} ticks_inf;

/*
 * from_value と to_value が等しかったときの処理。特殊処理。
 */
static void
pretty_ticks_axis_eq(Float value,
		     int *div_tick, Float *from_tick, Float *to_tick)
{
  Float	value_order;

  if (value == 0) {
    *from_tick =  1;
    *to_tick   = -1;
    *div_tick  = 2;
  }
  else {
    value_order = pow(10, floor(log10(fabs(value)))-1);
    *from_tick = (floor(value/value_order)  )*value_order;
    *to_tick   = (floor(value/value_order)+1)*value_order;
    *div_tick  = 1;
    if (*from_tick == value) {
      *from_tick = (floor(value/value_order)-1)*value_order;
      *div_tick  = 2;
    }
  }
}

/*
 * from_value と to_value が等しくなかったときの処理
 */
static void
pretty_ticks_axis_ne(Float from_value, Float to_value,
		     int *div_tick, Float *from_tick, Float *to_tick)
{
  int	i;
  Float	min_value, max_value, def_value;
  int	min_val_i, max_val_i;
  Float	value_order;
  Float	min_tick = 0.0, max_tick = 0.0;
  Float	unit_tick_cnt, def_tick;
  ticks_inf ticks[NUM_OF_UNIT];

  ticks[0].unit_tick = 10;
  ticks[1].unit_tick = 5;
  ticks[2].unit_tick = 2;
  ticks[3].unit_tick = 1;

  if (from_value < to_value) {
    min_value = from_value;
    max_value = to_value;
  }
  else {
    min_value = to_value;
    max_value = from_value;
  }
  def_value = max_value-min_value;
  value_order = pow(10, floor(log10(fabs(def_value)))-1);
  min_val_i = (int) floor( min_value/value_order);
  max_val_i = (int)-floor(-max_value/value_order);

  for (i = 0; i < NUM_OF_UNIT; i++) {
    unit_tick_cnt = 10.0/(Float)ticks[i].unit_tick;
    ticks[i].min_tick =
      (int)( floor( ((Float)min_val_i/10.0)*unit_tick_cnt)*10/unit_tick_cnt);
    ticks[i].max_tick =
      (int)(-floor(-((Float)max_val_i/10.0)*unit_tick_cnt)*10/unit_tick_cnt);
    def_tick = ticks[i].max_tick-ticks[i].min_tick;
    ticks[i].div_tick  = def_tick/ticks[i].unit_tick;
    ticks[i].div_tick2 =
      ticks[i].div_tick*(ticks[i].div_tick < MIN_DIV_TICK ? 2 : 1);
  }

  for (i = 0; i < NUM_OF_UNIT; i++) {
    if ((MIN_DIV_TICK <= ticks[i].div_tick) &&
	(ticks[i].div_tick <= MAX_DIV_TICK)) {
      min_tick = (Float)ticks[i].min_tick*value_order;
      max_tick = (Float)ticks[i].max_tick*value_order;
      *div_tick = ticks[i].div_tick;
      break;
    }
  }
  if (i >= NUM_OF_UNIT) {
    min_tick = (Float)ticks[0].min_tick*value_order;
    max_tick = (Float)ticks[0].max_tick*value_order;
    *div_tick = ticks[0].div_tick2;
  }

  if (from_value < to_value) {
    *from_tick = min_tick;
    *to_tick   = max_tick;
  }
  else {
    *from_tick = max_tick;
    *to_tick   = min_tick;
  }
}

/*
 * from_value と to_value の値によって分岐
 */
void
pretty_ticks_axis(Float from_value, Float to_value,
		  int *div_tick, Float *from_tick, Float *to_tick)
{
  if (from_value == to_value) {
    pretty_ticks_axis_eq(from_value, div_tick, from_tick, to_tick);
  }
  else {
    pretty_ticks_axis_ne(from_value, to_value, div_tick, from_tick, to_tick);
  }
}

/*
 * num 番目の目盛を計算
 */
Float
get_tick_axis(int num, int div_tick, Float from_tick, Float to_tick)
{
  Float	tick, tick_step;

  tick_step = (to_tick-from_tick)/(Float)div_tick;
  tick = from_tick+(to_tick-from_tick)*(Float)num/(Float)div_tick;
  if (fabs(tick) < fabs(tick_step*1e-6)) {
    tick = 0;
  }
  return tick;
}

/*
 * num 番目の目盛の中の sub_num 番目の補助目盛を計算
 */
Float
get_sub_tick_axis(int num,
		  int div_tick, Float from_tick, Float to_tick,
		  int sub_num, int sub_div_tick)
{
  Float	tick, tick_step;

  tick_step = (to_tick-from_tick)/(Float)div_tick;
  tick = from_tick + (to_tick-from_tick)*(Float)(num*sub_div_tick+sub_num)
    /(Float)(div_tick*sub_div_tick);
  if (fabs(tick) < fabs(tick_step*1e-6)) {
    tick = 0;
  }
  return tick;
}

/*
 * グラフの対数(底=10)軸の最大・最小を適当に計算
 * 入力は描くグラフの最大値と最小値。ただし、大小は任意。
 * 出力は分割数と、入力値が入る切りのいい最大値と最小値。
 * ただし、大小は入力に合わせる。
 */
void
pretty_ticks_log10_axis(Float from_value, Float to_value,
			int *div_tick, Float *from_tick, Float *to_tick)
{
  Float	min_value, max_value;
  int	min_tick_e, max_tick_e;
  Float	min_tick_e_f, max_tick_e_f;

  if ((from_value <= 0) || (to_value <= 0)) {
    fprintf(stderr, "error: log(0) in pretty_ticks_log10_axis()\n");
    exit(1); /* ! */
  }
  if (from_value < to_value) {
    min_value = from_value;
    max_value = to_value;
  }
  else {
    min_value = to_value;
    max_value = from_value;
  }

  min_tick_e =  floor( log10(min_value));
  max_tick_e = -floor(-log10(max_value));
  if (min_tick_e == max_tick_e) {
    min_tick_e--;
    max_tick_e++;
  }

  *div_tick = max_tick_e-min_tick_e;
  if (*div_tick < MIN_DIV_TICK) {
    min_tick_e_f = (Float)min_tick_e;
    max_tick_e_f = (Float)max_tick_e;
  }
  else {
    pretty_ticks_axis((Float)min_tick_e, (Float)max_tick_e,
		      div_tick, &min_tick_e_f, &max_tick_e_f);
  }

  if (from_value < to_value) {
    *from_tick = pow(10, min_tick_e_f);
    *to_tick   = pow(10, max_tick_e_f);
  }
  else {
    *from_tick = pow(10, max_tick_e_f);
    *to_tick   = pow(10, min_tick_e_f);
  }
}

/*
 * num 番目の目盛を計算
 */
Float
get_tick_log10_axis(int num, int div_tick, Float from_tick, Float to_tick)
{
  Float	tick;

  tick = from_tick*
    pow(10,(Float)(((int)log10(to_tick)-(int)log10(from_tick))*num/div_tick));
  return tick;
}

/*
 * num 番目の目盛の中の sub_num 番目の補助目盛を計算
 */
Float
get_sub_tick_log10_axis(int num,
			int div_tick, Float from_tick, Float to_tick,
			int sub_num, int sub_div_tick)
{
  int	tick_step_e, tick_sign, base_e;
  Float	tick;

  tick = 0;
  if (sub_num != 0) {
    tick_sign = (from_tick < to_tick ? +1 : -1);
    tick_step_e = abs((int)log10(to_tick)-(int)log10(from_tick))/div_tick;
    base_e = tick_sign*tick_step_e*num;
    if (tick_step_e == 1) {
      if (tick_sign == +1) {
	tick = from_tick*
	  pow(10,(Float)(base_e))*10*(Float)sub_num/(Float)sub_div_tick;
      }
      else {
	tick = from_tick*
	  pow(10,(Float)(base_e))*(Float)(sub_div_tick-sub_num)/
	    (Float)sub_div_tick;
      }
    }
    else {
      if ((tick_step_e <= sub_div_tick) && (sub_num < tick_step_e)) {
	tick = from_tick*pow(10,(Float)(base_e+tick_sign*sub_num));
      }
      else if ((tick_step_e % sub_div_tick) == 0) {
	tick = from_tick*
	  pow(10,(Float)(base_e+tick_sign*sub_num*(tick_step_e/sub_div_tick)));
      }
    }
  }
  return tick;
}
