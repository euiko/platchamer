/*
 * Sample program for grafplot in graffit library < graph.c >
 *
 * XBGI の graffit ライブラリの grafplot.h の サンプル
 *
 * Copyright (C) 1995-1999 Taiji Yamada, AIHARA Electrical Engineering Co.,Ltd.
 */
#include <stdio.h>
#include <stdlib.h>
#include <graffit.h>
#include "mat.h"
#include "rk.h"

#ifndef _XBGI_
#define xbgiloop (void)getchar
#endif

/*
 * 0: vector  in R^2
 * 1: matrix  in R^2
 * 2: matrixT in R^2
 * 3: matrix  in R^3
 * 4: matrixT in R^3
 * 5: matrix  in R^N
 * 6: matrixT in R^N
 */
int test_kind = 3;

int width = 640, height = 480;
int reverse = 0;
int zero_axis_flag = !0;
unsigned long plotkind = PLOT_LINE;
int figure_dimension = 1;
int r3kind = R3_ROTATION;
double center_x = 0.0, center_y = 0.2;
double magnify = 1.2;
double distance_eyes = 0.1;
double deformation = 10.0;
double rotation_x = -45.0, rotation_y = 25.0, rotation_z = 0.0;
int color_kind_flag = 0;
int color_axis_flag = 0;

/*
 * Lorenz方程式
 */
#define dxdt dXdt[0]
#define dydt dXdt[1]
#define dzdt dXdt[2]
#define x    X[0]
#define y    X[1]
#define z    X[2]
void Lorenz(double t, double X[], double dXdt[])
{
  double sigma = 10, b = 8.0/3, r = 28.0;
  dxdt = -sigma*x + sigma*y;
  dydt = -x*z + r*x - y;
  dzdt = x*y - b*z;
}
#undef dxdt
#undef dydt
#undef dzdt
#undef x
#undef y
#undef z

/*
 * HyperRessler方程式
 */
#define dxdt dXdt[0]
#define dydt dXdt[1]
#define dzdt dXdt[2]
#define dwdt dXdt[3]
#define x    X[0]
#define y    X[1]
#define z    X[2]
#define w    X[3]
void HyperRessler(double t, double X[], double dXdt[])
{
  double a = 0.25, b = 2.2, c = 0.05, d = 0.5;
  dxdt = -y - z;
  dydt = x + a*y + w;
  dzdt = b + x*z;
  dwdt = c*w - d*z;
}
#undef dxdt
#undef dydt
#undef dzdt
#undef dwdt
#undef x
#undef y
#undef z
#undef w

#define N_DATA 10000
/*#define N_DATA 70000*/
#define N_KIND 2

int expose(void)
{
  if (!reverse) {
    setcolor(0); setbkcolor(getmaxcolor());
  }
  else {
    setcolor(getmaxcolor()); setbkcolor(0);
  }
  switch (test_kind) {
  case 0: default:
    {
      static int first = !0;
      long i;
      int k;
      static double data[N_KIND][N_DATA+1];
      char title[N_KIND][64];
      
      if (first) {
	first = 0;
	for (k=0; k<N_KIND; k++)
	  for (i=0; i<N_DATA+1; i++)
	    data[k][i] = sin(2*M_PI*(i+k*N_DATA/100)/N_DATA);
      }
      set_plotgraph("2次元グラフのサンプル(vectorデータ)", 2);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      for (k=0; k<N_KIND; k++) {
	sprintf(title[k], "sin(2π(t+%d)/%d)", k*N_DATA/100, N_DATA);
	set_ith_plotvector(k+1, title[k], 0,N_DATA, data[k]);
	set_ith_plotvector_kinds(k+1, plotkind, k, k, k);
	set_ith_plotvector_step(k+1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
	set_ith_plotvector_step(k+1, PLOT_POINT, 0); /* since 3.02 */
      }
      setviewport_(40, 40, width-40, height-40, 0);
      plotgraph();
      return !0;
    }
    break;
  case 1:
    {
      static int first = !0;
      long i;
      int k;
      static double **data[N_KIND];
      char title[N_KIND][64];
      
      if (first) {
	first = 0;
	for (k=0; k<N_KIND; k++) {
	  data[k] = mat(N_DATA+1,2);
	  for (i=0; i<N_DATA+1; i++) {
	    data[k][i][0] = 2*M_PI*i/N_DATA;
	    data[k][i][1] = sin(data[k][i][0] + 2*M_PI*(k*N_DATA/100)/N_DATA);
	  }
	}
      }
      set_plotgraph("2次元グラフのサンプル(matrixデータ)", 2);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_x_plotaxis_range(0, 2*M_PI);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      for (k=0; k<N_KIND; k++) {
	sprintf(title[k], "y=sin(x+2π%d/%d)", k*N_DATA/100, N_DATA);
	set_ith_plotmatrix(k+1, title[k], 0,N_DATA, 0,1, data[k]);
	set_ith_plotmatrix_axis(k+1, AXIS_X, 0);
	set_ith_plotmatrix_axis(k+1, AXIS_Y, 1);
	set_ith_plotmatrix_kinds(k+1, plotkind, k, k, k);
	set_ith_plotmatrix_step(k+1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
	set_ith_plotmatrix_step(k+1, PLOT_POINT, 0); /* since 3.02 */
      }
      setviewport_(40, 40, width-40, height-40, 0);
      plotgraph();

      /*for (k=0; k<N_KIND; k++)
	free_mat(data[k]);*/
      return !0;
    }
    break;
  case 2:
    {
      static int first = !0;
      int i, k;
      static double **data[N_KIND];
      char title[N_KIND][64];
      
      if (first) {
	first = 0;
	for (k=0; k<N_KIND; k++) {
	  data[k] = mat(2,N_DATA+1);
	  for (i=0; i<N_DATA+1; i++) {
	    data[k][0][i] = 2*M_PI*i/N_DATA;
	    data[k][1][i] = sin(data[k][0][i] + 2*M_PI*(k*N_DATA/100)/N_DATA);
	  }
	}
      }
      set_plotgraph("2次元グラフのサンプル(matrixTデータ)", 2);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_x_plotaxis_range(0, 2*M_PI);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      for (k=0; k<N_KIND; k++) {
	sprintf(title[k], "y=sin(x+2π%d/%d)", k*N_DATA/100, N_DATA);
	set_ith_plotmatrixT(k+1, title[k], 0,1, 0,N_DATA, data[k]);
	set_ith_plotmatrixT_axis(k+1, AXIS_X, 0);
	set_ith_plotmatrixT_axis(k+1, AXIS_Y, 1);
	set_ith_plotmatrixT_kinds(k+1, plotkind, k, k, k);
	set_ith_plotmatrixT_step(k+1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
	set_ith_plotmatrixT_step(k+1, PLOT_POINT, 0); /* since 3.02 */
      }
      setviewport_(40, 40, width-40, height-40, 0);
      plotgraph();

      /*for (k=0; k<N_KIND; k++)
	free_mat(data[k]);*/
      return !0;
    }
    break;
  case 3:
    {
      static int first = !0;
      long i;
      static double **data[2];
      char title[2][64];
      
      if (first) {
	first = 0;
	data[0] = mat(N_DATA+1,3);
	data[1] = mat(N_DATA+1,3);
	data[0][0][0] = 10, data[0][0][1] = 20, data[0][0][2] = 30;
	data[1][0][0] = 10, data[1][0][1] = 20, data[1][0][2] = 30.01;
	for (i=0; i<N_DATA; i++) {
	  rk(0.01, 3, Lorenz, 0.01*i, data[0][i], data[0][i+1]);
	  rk(0.01, 3, Lorenz, 0.01*i, data[1][i], data[1][i+1]);
	}
      }
      set_plotgraph("3次元グラフのサンプル(matrixデータ)", 3);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_plotgraph_r3kind(r3kind);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      set_z_plotaxis("Z", SCALE_DEC), set_z_plotaxis_flags(!0, !0, zero_axis_flag);

      sprintf(title[0], "ロレンツ(Z(0)=%g))", data[0][0][2]);
      set_ith_plotmatrix(1, title[0], 0,N_DATA, 0,2, data[0]);
      set_ith_plotmatrix_kinds(1, plotkind, 0, 0, 0);
      set_ith_plotmatrix_step(1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrix_step(1, PLOT_POINT, 0); /* since 3.02 */

      sprintf(title[1], "ロレンツ(Z(0)=%g))", data[1][0][2]);
      set_ith_plotmatrix(2, title[1], 0,N_DATA, 0,2, data[1]);
      set_ith_plotmatrix_kinds(2, plotkind, 1, 1, 1);
      set_ith_plotmatrix_step(2, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrix_step(2, PLOT_POINT, 0); /* since 3.02 */

      setviewport_(40, 40, width-40, height-40, 0);
      setwindow_(-1.0/magnify-center_x, 1.0/magnify-center_y, 1.0/magnify-center_x, -1.0/magnify-center_y);
      setdistance_(distance_eyes);
      setdeformation_(deformation);
      stereowidthimages(width/3);
      plotgraph();

      /*free_mat(data[0]);
      free_mat(data[1]);*/
      return !0;
    }
    break;
  case 4:
    {
      static int first = !0;
      long i;
      static double **data[2], *v0, *v1;
      char title[2][64];
      
      if (first) {
	first = 0;
	v0 = vec(3), v1 = vec(3);
	data[0] = mat(3,N_DATA+1);
	data[1] = mat(3,N_DATA+1);
	data[0][0][0] = 10, data[0][1][0] = 20, data[0][2][0] = 30;
	data[1][0][0] = 10, data[1][1][0] = 20, data[1][2][0] = 30.01;
	for (i=0; i<N_DATA; i++) {
	  v0[0] = data[0][0][i];
	  v0[1] = data[0][1][i];
	  v0[2] = data[0][2][i];
	  rk(0.01, 3, Lorenz, 0.01*i, v0, v1);
	  data[0][0][i+1] = v1[0];
	  data[0][1][i+1] = v1[1];
	  data[0][2][i+1] = v1[2];
	  v0[0] = data[1][0][i];
	  v0[1] = data[1][1][i];
	  v0[2] = data[1][2][i];
	  rk(0.01, 3, Lorenz, 0.01*i, v0, v1);
	  data[1][0][i+1] = v1[0];
	  data[1][1][i+1] = v1[1];
	  data[1][2][i+1] = v1[2];
	}
      }      
      set_plotgraph("3次元グラフのサンプル(matrixTデータ)", 3);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_plotgraph_r3kind(r3kind);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      set_z_plotaxis("Z", SCALE_DEC), set_z_plotaxis_flags(!0, !0, zero_axis_flag);

      sprintf(title[0], "ロレンツ(Z(0)=%g))", data[0][2][0]);
      set_ith_plotmatrixT(1, title[0], 0,2, 0,N_DATA, data[0]);
      set_ith_plotmatrixT_kinds(1, plotkind, 0, 0, 0);
      set_ith_plotmatrixT_step(1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrixT_step(1, PLOT_POINT, 0); /* since 3.02 */

      sprintf(title[1], "ロレンツ(Z(0)=%g))", data[1][2][0]);
      set_ith_plotmatrixT(2, title[1], 0,2, 0,N_DATA, data[1]);
      set_ith_plotmatrixT_kinds(2, plotkind, 1, 1, 1);
      set_ith_plotmatrixT_step(2, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrixT_step(2, PLOT_POINT, 0); /* since 3.02 */

      setviewport_(40, 40, width-40, height-40, 0);
      setwindow_(-1.0/magnify-center_x, 1.0/magnify-center_y, 1.0/magnify-center_x, -1.0/magnify-center_y);
      setdistance_(distance_eyes);
      setdeformation_(deformation);
      stereowidthimages(width/3);
      plotgraph();

      /*free_vec(v0);
      free_vec(v1);
      free_mat(data[0]);
      free_mat(data[1]);*/
      return !0;
    }
    break;
  case 5:
    {
      static int first = !0;
      long i;
      static double **data[2], *v0, *v1;
      char title[2][64];
      
      if (first) {
	first = 0;
	v0 = vec(4), v1 = vec(4);
	data[0] = mat(N_DATA+1,4);
	data[1] = mat(N_DATA+1,4);
	data[0][0][0]=-19, data[0][0][1]=0, data[0][0][2]=0, data[0][0][3]=15;
	data[1][0][0]=-19, data[1][0][1]=0, data[1][0][2]=0, data[1][0][3]=14.9;
	for (i=0; i<N_DATA; i++) {
	  rk(0.01, 4, HyperRessler, 0.01*i, data[0][i], data[0][i+1]);
	  rk(0.01, 4, HyperRessler, 0.01*i, data[1][i], data[1][i+1]);
	}
      }
      set_plotgraph("4次元グラフのサンプル(matrixデータ)", 4);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_plotgraph_r3kind(r3kind);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      set_z_plotaxis("Z", SCALE_DEC), set_z_plotaxis_flags(!0, !0, zero_axis_flag);
      set_w_plotaxis("W", SCALE_DEC), set_w_plotaxis_flags(!0, !0, zero_axis_flag);

      sprintf(title[0], "レスラー(W(0)=%g))", data[0][0][3]);
      set_ith_plotmatrix(1, title[0], 0,N_DATA, 0,3, data[0]);
      set_ith_plotmatrix_kinds(1, plotkind, 0, 0, 0);
      set_ith_plotmatrix_step(1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrix_step(1, PLOT_POINT, 0); /* since 3.02 */

      sprintf(title[1], "レスラー(W(0)=%g))", data[1][0][3]);
      set_ith_plotmatrix(2, title[1], 0,N_DATA, 0,3, data[1]);
      set_ith_plotmatrix_kinds(2, plotkind, 1, 1, 1);
      set_ith_plotmatrix_step(2, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrix_step(2, PLOT_POINT, 0); /* since 3.02 */

      setviewport_(40, 40, width-40, height-40, 0);
      setwindow_(-1.0/magnify-center_x, 1.0/magnify-center_y, 1.0/magnify-center_x, -1.0/magnify-center_y);
      setrotationport_(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      setdistance_(distance_eyes);
      setdeformation_(deformation);
      stereowidthimages(width/3);
      plotgraph();

      /*free_vec(v0);
      free_vec(v1);
      free_mat(data[0]);
      free_mat(data[1]);*/
      return !0;
    }
    break;
  case 6:
    {
      static int first = !0;
      long i;
      static double **data[2], *v0, *v1;
      char title[2][64];
      
      if (first) {
	first = 0;
	v0 = vec(4), v1 = vec(4);
	data[0] = mat(4,N_DATA+1);
	data[1] = mat(4,N_DATA+1);
	data[0][0][0]=-19, data[0][1][0]=0, data[0][2][0]=0, data[0][3][0]=15;
	data[1][0][0]=-19, data[1][1][0]=0, data[1][2][0]=0, data[1][3][0]=14.9;
	for (i=0; i<N_DATA; i++) {
	  v0[0] = data[0][0][i];
	  v0[1] = data[0][1][i];
	  v0[2] = data[0][2][i];
	  v0[3] = data[0][3][i];
	  rk(0.01, 4, HyperRessler, 0.01*i, v0, v1);
	  data[0][0][i+1] = v1[0];
	  data[0][1][i+1] = v1[1];
	  data[0][2][i+1] = v1[2];
	  data[0][3][i+1] = v1[3];
	  v0[0] = data[1][0][i];
	  v0[1] = data[1][1][i];
	  v0[2] = data[1][2][i];
	  v0[3] = data[1][3][i];
	  rk(0.01, 4, HyperRessler, 0.01*i, v0, v1);
	  data[1][0][i+1] = v1[0];
	  data[1][1][i+1] = v1[1];
	  data[1][2][i+1] = v1[2];
	  data[1][3][i+1] = v1[3];
	}
      }      
      set_plotgraph("4次元グラフのサンプル(matrixTデータ)", 4);
      set_plotgraph_color_kind(color_kind_flag);
      set_plotgraph_color_axis(color_axis_flag);
      set_plotgraph_r3kind(r3kind);
      set_x_plotaxis("X", SCALE_DEC), set_x_plotaxis_flags(!0, !0, zero_axis_flag);
      set_y_plotaxis("Y", SCALE_DEC), set_y_plotaxis_flags(!0, !0, zero_axis_flag);
      set_z_plotaxis("Z", SCALE_DEC), set_z_plotaxis_flags(!0, !0, zero_axis_flag);
      set_w_plotaxis("W", SCALE_DEC), set_w_plotaxis_flags(!0, !0, zero_axis_flag);

      sprintf(title[0], "レスラー(W(0)=%g))", data[0][3][0]);
      set_ith_plotmatrixT(1, title[0], 0,3, 0,N_DATA, data[0]);
      set_ith_plotmatrixT_kinds(1, plotkind, 0, 0, 0);
      set_ith_plotmatrixT_step(1, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrixT_step(1, PLOT_POINT, 0); /* since 3.02 */

      sprintf(title[1], "レスラー(W(0)=%g))", data[1][3][0]);
      set_ith_plotmatrixT(2, title[1], 0,3, 0,N_DATA, data[1]);
      set_ith_plotmatrixT_kinds(2, plotkind, 1, 1, 1);
      set_ith_plotmatrixT_step(2, PLOT_LINE|PLOT_DOT, 1); /* since 3.02 */
      set_ith_plotmatrixT_step(2, PLOT_POINT, 0); /* since 3.02 */

      setviewport_(40, 40, width-40, height-40, 0);
      setwindow_(-1.0/magnify-center_x, 1.0/magnify-center_y, 1.0/magnify-center_x, -1.0/magnify-center_y);
      setrotationport_(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      setdistance_(distance_eyes);
      setdeformation_(deformation);
      stereowidthimages(width/3);
      plotgraph();

      /*free_vec(v0);
      free_vec(v1);
      free_mat(data[0]);
      free_mat(data[1]);*/
      return !0;
    }
    break;
  }
}
int key_press(int key)
{
  int i, j;
  double d = 5.0, hd = 10.0;

  switch (test_kind) {
  case 0: figure_dimension = 1; break;
  case 1: figure_dimension = 2; break;
  case 2: figure_dimension = 2; break;
  case 3: figure_dimension = 3; break;
  case 4: figure_dimension = 3; break;
  case 5: figure_dimension = 4; break;
  case 6: figure_dimension = 4; break;
  }
  switch (key) {
  case 'r':
    break;
  case 'R': reverse = !reverse;
    if (!reverse) {
      setcolor(0); setbkcolor(getmaxcolor());
    }
    else {
      setcolor(getmaxcolor()); setbkcolor(0);
    }
    break;
  case 'Z': zero_axis_flag = !zero_axis_flag; break;
  case 'x': center_y -= 0.05; break;
  case 'e': center_y += 0.05; break;
  case 's': center_x -= 0.05; break;
  case 'd': center_x += 0.05; break;
  case 'c': center_x = center_y = 0.0; break;
  case 'f': magnify *= 1.1; break;
  case 'b': magnify *= 0.9; break;
  case 'g': magnify = 1.2; break;
  case 'F': distance_eyes *= 0.9; break;
  case 'B': distance_eyes *= 1.1; break;
  case 'G': distance_eyes = 0.1; break;
  case K_CTRL('f'): deformation *= 0.9; break;
  case K_CTRL('b'): deformation *= 1.1; break;
  case K_CTRL('g'): deformation = 10.0; break;
  case '2': rotation_x -= d; break;
  case '8': rotation_x += d; break;
  case '4': rotation_y += d; break;
  case '6': rotation_y -= d; break;
  case '-': rotation_z -= d; break;
  case '+': rotation_z += d; break;
  case '5': rotation_x = rotation_y = rotation_z = 0; break;
  case '/':
    /*for (i=0; i<figure_dimension; i++)
      for (j=0; j<figure_dimension; j++)*/
    for (i=figure_dimension-1; i>=0; --i)
      for (j=figure_dimension-1; j>=0; --j) /* Thanks! Mr. Jun Takahashi */
        if (i != j) hyperrotate_(i, j, RAD(-hd));
    break;
  case '*':
    for (i=0; i<figure_dimension; i++)
      for (j=0; j<figure_dimension; j++)
        if (i != j) hyperrotate_(i, j, RAD(hd));
    break;
  case 'D':
    plotkind = (plotkind==PLOT_LINE)?PLOT_DOT
      :(plotkind==PLOT_DOT)?PLOT_POINT
        :(plotkind==PLOT_POINT)?(PLOT_LINE|PLOT_POINT):PLOT_LINE;
    break;
  case 'T': r3kind = (r3kind+1)%(R3_STEREO2+1); break;
  case 'C': color_kind_flag = !color_kind_flag; break;
  /*case 'C': color_axis_flag = !color_axis_flag; break;*/
  case 'p': test_kind = max(0,test_kind-1); break;
  case 'n': test_kind = min(test_kind+1,6); break;
  }
  switch (key) {
  case 'r':
  case 'R':
  case 'Z':
  case 'x': case 'e': case 's': case 'd': case 'c':
  case 'f': case 'b': case 'g':
  case 'F': case 'B': case 'G':
  case K_CTRL('f'): case K_CTRL('b'): case K_CTRL('g'):
  case '2': case '8': case '4': case '6': case '-': case '+': case '5':
  case '/': case '*':
  case 'D':
  case 'T':
  case 'C':
  case 'p': case 'n':
    setrotation_(RAD(rotation_x), RAD(rotation_y), RAD(rotation_z));
    cleardevice();
    expose();
    break;
  }
  return !0;
}
int resize(void)
{
  int x, y;

  getgeometry(&x, &y, &width, &height);
  setgeometry(x, y, width, height);
  return !0;
}

int main(void)
{
  int gd = DETECT, gm;

  initgraph(&gd, &gm, "-npage 1 -geometry 640x480 -title graph");
  set_key_press_handler(key_press);
  set_expose_handler(expose);
  set_configure_handler(resize);
  setcolor(BLACK);
  setbkcolor(getmaxcolor());
  cleardevice();
  setrotation_(RAD(rotation_x), RAD(rotation_y), RAD(rotation_z));
  expose();
  xbgiloop();
  closegraph();
  return 0;
}
