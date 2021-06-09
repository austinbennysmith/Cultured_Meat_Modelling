#include "grid/cartesian1D.h"
#include "run.h"

scalar T[];

// T[right] = dirichlet(0.0);
// T[left] = dirichlet(0.0);

double dt;
float U = 3.0;

// See: http://basilisk.fr/sandbox/M1EMN/BASIC/heat.c
int main() {
  L0 = 10.;
  X0 = -L0/2;
  N = 200;
  DT = (L0/N)*(L0/N)/2 ;
#define EPS 0.1  
  run();
}

event init (t = 0) {
  // periodic(right);
  foreach()
    // T[] =  1./EPS*(fabs(x)<EPS)/2;
  	T[] = sin((pi/5)*x)+5;
  boundary ({T});
}

event printdata (t += 1.0; t < 10) {
  foreach()
    fprintf (stdout, "%g %g %g\n", x, T[], t);
  fprintf (stdout, "\n\n");
}

event integration (i++) {
  double dt = DT;
  scalar dT[],q[];
  dt = dtnext (dt);
  foreach()
    q[]=-(T[0,0] - T[-1,0])/Delta - U*(T[0, 0]+T[-1, 0])/2.;
  boundary ({q});
  foreach()
    dT[] = - ( q[1,0]  - q[0,0] )/Delta;
  foreach()
    T[] += dt*dT[];
  boundary ({T});
}
