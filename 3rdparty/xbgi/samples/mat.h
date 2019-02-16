double *vec(int N)
{
  return (double *)malloc(sizeof(double)*N);
}
void free_vec(double *v)
{
  free(v);
}
void init_vec(int N, double *a)
{
  int i;

  for (i=0; i<N; i++)
    a[i] = 0.0;
}
void unit_mat(int M, int N, double **a)
{
  int i, j;
  
  for (i=0; i<N; i++)
    for (j=0; j<M; j++)
      if (i==j)
        a[i][j] = 1.0;
      else
        a[i][j] = 0.0;
}
double norm_vec(int N, double *a)
{
  int i;
  double s = 0.0;
  
  for (i=0; i<N; i++)
    s = s + a[i] * a[i];
  return sqrt(s);
}
void cp_vec(int N, double a[], double b[])
{
  int i;
  for (i=0; i<N; i++)
    b[i] = a[i];
}
double **mat(int M, int N)
{
  int i;
  double **m;

  m = (double **)malloc(sizeof(double*)*M);
  m[0] = (double *)malloc(sizeof(double)*(M*N));
  for (i=1; i<M; i++)
    m[i] = m[i-1] + N;
  return m;
}
void free_mat(double **m)
{
  free(m[0]);
  free(m);
}
void mat_mul_vec(int M, int N, double **a, double *b, double *c)
{
  int i, j;
  double s, *tmp = vec(N);

  cp_vec(N, b, tmp);
  for (i=0; i<M; i++) {
    s = 0.0;
    for (j=0; j<N; j++)
      s += a[i][j]*tmp[j];
    c[i] = s;
  }
  free_vec(tmp);
}
void cp_mat(int M, int N, double **a, double **b)
{
  int i, j;

  for (i=0; i<M; i++)
    for (j=0; j<N; j++)
      b[i][j] = a[i][j];
}
double innprod_vec(int N, double *a, double *b)
{
  int i;
  Float s = 0.0;
  
  for (i=0; i<N; i++)
    s = s + a[i] * b[i];
  return s;
}
void vec_plu_vec(int N, double *a, double *b, double *c)
{
  int i;

  for (i=0; i<N; i++)
    c[i] = a[i] + b[i];
}
void vec_min_vec(int N, double *a, double *b, double *c)
{
  int i;

  for (i=0; i<N; i++)
    c[i] = a[i] - b[i];
}
void sca_mul_vec(int N, double a, double *b, double *c)
{
  int i;

  for (i=0; i<N; i++)
    c[i] = a * b[i];
}
void graschmi(int M, int N,
	      double **e, double **u, double **e2, double **u2)
{
  int i, j;
  double **E, **U, *w, *s;

  E = mat(M, N);
  U = mat(M, N);
  w = vec(N);
  s = vec(N);
  cp_mat(M, N, u, U);
  for (i=0; i<M; i++) {
    init_vec(N, s);
    for (j=0; j<i; j++) {
      sca_mul_vec(N, innprod_vec(N, e[i], U[j]), U[j], w);
      vec_plu_vec(N, w, s, s);
    }
    vec_min_vec(N, e[i], s, E[i]);
    sca_mul_vec(N, 1.0/norm_vec(N, E[i]), E[i], U[i]);
  }
  cp_mat(M, N, E, e2);
  cp_mat(M, N, U, u2);
  free_mat(E);
  free_mat(U);
  free_vec(s);
  free_vec(w);
}
