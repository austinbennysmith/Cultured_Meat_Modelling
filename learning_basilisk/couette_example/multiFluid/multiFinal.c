#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"

FILE *fp1 ;

#define LEVEL 5

// Dimensional quantities:
#define rhoWater 1000 // density of water
#define rhoOil 917 // density of olive oil at 20C
#define muWater 0.001 // approximatley the viscosity of water
#define muOil 0.03 // approximateley the viscosity of oil
#define sig 0.0728  //surface tension of water

#define refLength 1  // height of the domain
#define refVelocity 1  // velocity of the top plate

// Dimensionless quantities:
#define rho_ratio rhoOil/muWater
#define mu_ratio muOil/muWater
#define Re rhoWater*refVelocity*refLength/muWater  // Reynolds number
#define We rhoWater*pow(refVelocity,2)*refLength/sig


// RC
FILE * fp_stats;

u.t[top] = dirichlet(1.0);
u.n[top] = dirichlet(0.0);

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet(0.0);

int main() {
  L0 = 8.;
  origin(-L0/2., -0.5);
  init_grid (1 << LEVEL);

  // RC
  {
    char name[200];
    sprintf(name, "logstats.dat");
    fp_stats = fopen(name, "w");
  }

  // I rescale the system so that water has unit density, and the oil properties are just defined in terms of water
  rho1 = 1.0; // water density
  rho2 = rho_ratio; // oil density
  mu1 = 1./Re; // water dynamic viscosity
  mu2 = mu_ratio*mu1; // oil dynamic viscosity
  f.sigma=1./We;

  run();

  // RC
  fclose(fp_stats);
}

event init(t = 0) {

  // RC set viscosity to 1/Re
  //const face vector muc[] = {1./Re,1./Re};
  //mu = muc;

  // flow out of the right -> into the left
  periodic(right);

  // vertex scalar phi[];
  // foreach_vertex() {
  //  phi[] = intersection(0.5-y, 0.5+y);
  // }
  // boundary({phi});*/
  
  fraction (f, y-0.2);
  
  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
  // RC cut the top and bottom of domain
  mask (y > 0.5 ? top : none);
  mask (y < -0.5 ? bottom : none);
  
  // boundary conditions
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);

}

event end (t = 400) {
  printf ("i = %d t = %g\n", i, t);
}

event profiles (t = 0; t+=0.1; t<=100)
{
  FILE * fp = fopen("xprof", "a");
  for (double y = -0.5; y <= 0.5; y += 0.01)
    fprintf (fp, "%g %g\n", y, interpolate (u.x, 0, y));
  fclose (fp);
  
  fp = fopen("yprof", "a");
  for (double x = -4; x <= 4; x += 0.01)
    fprintf (fp, "%g %g\n", x, interpolate (u.y, x, 0));
  fclose (fp);
}


// RC added this for profiling
event logstats (t += 1.0) {

    timing s = timer_timing (perf.gt, i, perf.tnc, NULL);
 
    // i, timestep, no of cells, real time elapsed, cpu time
    fprintf(fp_stats, "i: %i t: %g dt: %g #Cells: %ld Wall clock time (s): %g CPU time (s): %g \n", i, t, dt, grid->n, perf.t, s.cpu);
    fflush(fp_stats);
}

