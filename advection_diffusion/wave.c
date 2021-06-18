#include "grid/cartesian1D.h"
#include "run.h"

scalar T[];
scalar Tbefore[];

T[right] = dirichlet(0.0);
T[left] = neumann(0.0);

FILE * fp_params;

double dt;
float U = 2.0;

// See: http://basilisk.fr/sandbox/M1EMN/BASIC/heat.c
int main() {
  periodic(right);
  L0 = 10.;
  X0 = -L0/2;
  // N = 100;
  // CFL = -4.0;
  // DT = (L0/N)*(L0/N)/2 ;
// #define EPS 0.1 
  
  {
  char params[200];
  sprintf(params, "params.txt");
  fp_params=fopen(params, "w");
  }

  fprintf(fp_params, "N: %d \n", N);
  fprintf(fp_params, "DT: %g \n", DT);
  fprintf(fp_params, "CFL: %g \n", CFL);
  fclose(fp_params);

  run();
}

event init (t = 0) {
  // periodic(right);
  foreach()
    // T[] =  1./EPS*(fabs(x)<EPS)/2;
  	// T[] = sin((pi/5)*x)+5;
  	T[] = exp(-x*x);
  	// T[] = sin((pi/5.0)*x);
  boundary ({T});
}

event printdata (t += 1.0; t < 1000.0) {
  foreach()
    fprintf (stdout, "%g %g %g\n", x, T[], t);
  fprintf (stdout, "\n\n");
}

double cDelta;
event integration (i++) {
  // double dt = DT;
  scalar dT[],q[];
  dt = 0.01;
  foreach()
  	q[] = -sq(U)*(T[0,0]-T[-1,0])/Delta;
  boundary ({q});
  foreach()
    T[] = sq(dt)*((q[0,0]-q[1,0])/Delta)+2T[0,0]-Tbefore[0,0];
  boundary ({T});
}