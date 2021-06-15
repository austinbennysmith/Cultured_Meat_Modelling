#include "grid/cartesian1D.h"
#include "run.h"

scalar T[];

// T[right] = neumann(0.0);
// T[left] = neumann(0.0);

FILE * fp_params;

double dt;
float U = 2.0;

// See: http://basilisk.fr/sandbox/M1EMN/BASIC/heat.c
int main() {
  periodic(right);
  L0 = 10.;
  X0 = -L0/2;
  // N = 100;
  // CFL = 0.01;
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
  periodic(right);
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

event integration (i++) {
  // double dt = DT;
  scalar dT[],q[];
  dt = 0.01;
  foreach()
  	// Helpful sentence from a paper (at https://www.researchgate.net/profile/Wim-Desmet/publication/251548727_Finite_Volume_Convective_Flux_Reconstruction_Using_High-Order_Skew-Symmetric-Like_Schemes/links/02e7e52f1183f86850000000/Finite-Volume-Convective-Flux-Reconstruction-Using-High-Order-Skew-Symmetric-Like-Schemes.pdf):
  	// "in the absence of sources and sinks, the rate of change in time of the sum of the conserved variable phi in a volume V equals the sum of the flux on the surface S of the volume"
  	// To get the flux q[], I want to estimate the rate of change of T (aka, get T'). To do that, I need to do a 2nd-order centered estimate for T'.
  	// Info on approximations of derivatives: https://www.dam.brown.edu/people/alcyew/handouts/numdiff.pdf
    // q[]=(T[1,0]-T[-1,0])/(2*Delta); // heat equation alone
    // q[]=(T[0,0] - T[-1,0])/(Delta)- U*(T[1, 0]+T[-1, 0])/2.;
    // q[]=-(T[0,0] - T[-1,0])/Delta;

 	// My ACTUAL advection-diffusion scheme:
  	q[] = -(T[0,0]-T[-1,0])/Delta + U*(T[0,0]+T[-1,0])/2.0;

  	// Advection alone:
  	// q[] = U*(T[0,0]+T[-1,0])/2.0;

  	//Diffusion alone:
  	// q[] = -(T[0,0]-T[-1,0])/Delta;

  // q[]=U*(T[0, 0]+T[-1, 0])/2.;
  boundary ({q});
  foreach()
    dT[] = ( q[0,0]  - q[1,0] )/Delta;
  foreach()
    T[] += dt*dT[];
  boundary ({T});
}