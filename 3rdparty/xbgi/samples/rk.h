void rk(double h, int N,
        void (*dXdt)(double t, double X[], double dXdt[]),
        double t, double X0[], double X[])
{
  int i;
  double *d1=vec(N), *d2=vec(N), *d3=vec(N);
  double *Xa=vec(N), *dX=vec(N);

  dXdt(t, X0, dX);
  for (i = 0; i < N; i++) {
    d1[i] = h*dX[i];
    Xa[i] = X0[i] + 0.5*d1[i];
  }
  dXdt(t + 0.5*h, Xa, dX);
  for (i = 0; i < N; i++) {
    d2[i] = h*dX[i];
    Xa[i] = X0[i] + 0.5*d2[i];
  }
  dXdt(t + 0.5*h, Xa, dX);
  for (i = 0; i < N; i++) {
    d3[i] = h*dX[i];
    Xa[i] = X0[i] + d3[i];
  }
  dXdt(t + h, Xa, dX);
  for (i = 0; i < N; i++)
    X[i] = X0[i] + (d1[i] + d2[i]*2 + d3[i]*2 + h*dX[i])/6.0;
  free_vec(d1); free_vec(d2); free_vec(d3);
  free_vec(Xa); free_vec(dX);
}
