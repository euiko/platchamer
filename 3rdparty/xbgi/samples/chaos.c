/*
 * Sample program for enhanced functions about multi-graphics < chaos.c >
 *
 * XBGI 拡張機能、複数のグラフィック環境のサンプル
 *
 * Copyright (C) 1992-1994 Taiji Yamada, Tokyo Denki University
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

/*
   このプログラムは XBGI の拡張機能のうち、DOS 上ではサポートされない
   拡張機能である、「複数のグラフィック環境の構築」のサンプルである。
   もし DOS 上で拡張機能を無効化したいときには、
   インクルードファイル xbgi2bgi.h を使うとよい。
 */
#ifndef _XBGI_
#include <xbgi2bgi.h>
#endif

#define COEFB 1.5
double chaos(double x)
{
  if (0.0<=x && x<0.5)
    return(x+pow(2.0,COEFB-1)*pow(x,COEFB));
  else
    return(x-pow(2.0,COEFB-1)*pow(1.0-x,COEFB));
}
int main(void)
{
  int i = 0, gd = DETECT, gm;
  int graph1, graph2;
  double x0 = 0.2, x1;

  initgraph(&gd, &gm, "-geometry 800x200 -title Fig.1");
  graph1 = graphnumber();
  cleardevice();
  initgraph(&gd, &gm, "-geometry 400x400 -title Fig.2");
  graph2 = graphnumber();
  cleardevice();
  for (i=0; i<800; i++) {
    x1 = chaos(x0);
    selectgraph(graph1);
    line(i-1, 200-200.0*x0, i, 200-200.0*x1);
    selectgraph(graph2);
    line(400.0*x0, 400-400.0*x0, 400.0*x0, 400-400.0*x1);
    line(400.0*x0, 400-400.0*x1, 400.0*x1, 400-400.0*x1);
    x0 = x1;
  }
  xbgiloop();
  termgraph(graph1);
  termgraph(graph2);
  return 0;
}
