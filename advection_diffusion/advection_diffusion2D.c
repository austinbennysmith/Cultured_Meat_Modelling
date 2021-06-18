//see sandbox/jmf/tutorial for 2D diffusion example code

// #include "grid/cartesian1D.h"
#include "run.h"
#include "view.h"

#define LEVEL 9
scalar T[];

// T[right] = dirichlet(0.0);
// T[left] = dirichlet(0.0);
// T[top] = dirichlet(0.0);
// T[bottom] = dirichlet(0.0);

FILE * fp_params;

double dt;
float U = 2.0;

// See: http://basilisk.fr/sandbox/M1EMN/BASIC/heat.c
int main() {
  init_grid(1<<LEVEL);
  periodic(right);
  periodic(top);
  L0 = 10.;
  X0 = Y0 = -L0/2;
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
  periodic(right);
  foreach()
    // T[] =  1./EPS*(fabs(x)<EPS)/2;
  	// T[] = sin((pi/5)*x)+5;
  	T[] = exp(-(x*x+y*y));
  	// T[] = sin((pi/5.0)*x);
  boundary ({T});
}

event printdata (t += 1.0; t < 1000.0) {
  foreach()
    fprintf (stdout, "%g %g %g %g\n", x, y, T[], t);
  fprintf (stdout, "\n\n");
}

double cDelta;
event integration (i++) {
  // double dt = DT;
  scalar dT[],qh[],qv[];
  dt = 0.01;
  foreach() {
  	// Helpful sentence from a paper (at https://www.researchgate.net/profile/Wim-Desmet/publication/251548727_Finite_Volume_Convective_Flux_Reconstruction_Using_High-Order_Skew-Symmetric-Like_Schemes/links/02e7e52f1183f86850000000/Finite-Volume-Convective-Flux-Reconstruction-Using-High-Order-Skew-Symmetric-Like-Schemes.pdf):
  	// "in the absence of sources and sinks, the rate of change in time of the sum of the conserved variable phi in a volume V equals the sum of the flux on the surface S of the volume"
  	// To get the flux q[], I want to estimate the rate of change of T (aka, get T'). To do that, I need to do a 2nd-order centered estimate for T'.
  	// Info on approximations of derivatives: https://www.dam.brown.edu/people/alcyew/handouts/numdiff.pdf
    // q[]=(T[1,0]-T[-1,0])/(2*Delta); // heat equation alone
    // q[]=(T[0,0] - T[-1,0])/(Delta)- U*(T[1, 0]+T[-1, 0])/2.;
    // q[]=-(T[0,0] - T[-1,0])/Delta;

 	// My ACTUAL advection-diffusion scheme:
  	// qh[] = -(T[0,0]-T[-1,0])/Delta + U*((T[0,0]+T[-1,0])/2.0 - ((T[0,0]-T[-1,0])/2));
   //  qv[] = -(T[0,1]-T[0,-1])/Delta;

  	// // Advection alone:
  	// qh[] = U*((T[0,0]+T[-1,0])/2.0 - ((T[0,0]-T[-1,0])/2));
   //  qv[] = -(T[0,1]-T[0,-1])/Delta;

  	//Diffusion alone:
  	qh[] = -(T[0,0]-T[-1,0])/Delta;
    qv[] = -(T[0,0]-T[0,-1])/Delta;

  // q[]=U*(T[0, 0]+T[-1, 0])/2.;
  }
  boundary ({qh});
  boundary({qv});
  foreach()
    dT[] = ( qh[0,0]  - qh[1,0] )/Delta + ( qv[0,0]  - qv[0,1] )/Delta;
  foreach()
    T[] += dt*dT[];
  boundary ({T});
}