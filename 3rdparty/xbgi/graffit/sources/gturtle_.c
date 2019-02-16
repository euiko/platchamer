/*
 * 2-dimensional turtle graphic interface in graffit library < gturtle_.c >
 *
 * Turtle Graphics for Borland Graphics Interface
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <gturtle_.h>

static double __GT = RAD(30);

void move_(double d)
{
  linerel_(d*cos(__GT), d*sin(__GT));
}

void setangle_(double angle)
{
  __GT = angle;
}

void turn_(double dangle)
{
  __GT += dangle;
}



