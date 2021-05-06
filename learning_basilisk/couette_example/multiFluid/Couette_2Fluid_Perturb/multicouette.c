#define FILTERED //RC
#define mu(f)  (1./(clamp(f,0,1)*(1./mu1 - 1./mu2) + 1./mu2)) //RC

#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"

FILE *fp1 ;
<<<<<<< HEAD
//FILE * fp_interface;
=======
>>>>>>> 6b1a0847f0100c8e0a5f764ec7d5be8ae1a5997b

#define LEVEL 7 // RC was 4, needs to be bigger to capture the setup

// Dimensional quantities:
#define rhoWater 1.0
#define rhoOil 0.917
#define muWater 0.001 // approximatley the viscosity of water
#define muOil 0.03 // approximateley the viscosity of oil

#define sig 0.0728  //surface tension of water

#define refLength 0.01  // height of the domain
#define refVelocity 0.01  // velocity of the top plate

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
  periodic(right);
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

  DT = 1.0e-2; // RC
  NITERMIN = 1; // default 1
  NITERMAX = 200; // default 100
  TOLERANCE = 1e-4; // default 1e-3
<<<<<<< HEAD
  // Pointers to files
  //{
    //char name[200];
    //sprintf(name, "loginterface.dat");
    //fp_interface = fopen(name, "w");
  //}
  //fclose(fp_interface);
=======

>>>>>>> 6b1a0847f0100c8e0a5f764ec7d5be8ae1a5997b
  run();

  // RC
  fclose(fp_stats);
}

event init(t = 0) {
 
  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }

  // RC cut the top and bottom of domain
  mask (y > 0.5 ? top : none);
  mask (y < -0.5 ? bottom : none);
  
  fraction (f, 0.3-y+.025*sin((pi/4)*x));

  // boundary conditions
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);

}

// RC How would you add gravity?

<<<<<<< HEAD
event end (t = 100) { // RC restricted to 400
  printf ("i = %d t = %g\n", i, t);
}

event profiles (t = 0; t+=1.0; t<=100) // RC restricted the output a little, don't overdo it at first!
=======
event end (t = 1000) { // RC restricted to 400
  printf ("i = %d t = %g\n", i, t);
}

event profiles (t = 0; t+=1.0; t<=1000) // RC restricted the output a little, don't overdo it at first!
>>>>>>> 6b1a0847f0100c8e0a5f764ec7d5be8ae1a5997b
{
  FILE * fp = fopen("xprof", "a");
  for (double y = -0.5; y <= 0.5; y += 0.01)
    fprintf (fp, "%g %g %g\n", t, y, interpolate (u.x, 0, y));
  fclose (fp);
  
  fp = fopen("yprof", "a");
  for (double x = -4; x <= 4; x += 0.01)
<<<<<<< HEAD
    fprintf (fp, "%g %g %g %g\n", t, x, interpolate (u.y, x, 0), interpolate (f, x, 0));
=======
    fprintf (fp, "%g %g %g\n", t, x, interpolate (u.y, x, 0));
>>>>>>> 6b1a0847f0100c8e0a5f764ec7d5be8ae1a5997b
  fclose (fp);
}


<<<<<<< HEAD
event saveInterfaces (t += 1.0) {
    char nameInterfaces1[200];
    sprintf(nameInterfaces1,"interfacesLiquid-%0.1f.dat",t);
    FILE * fp1 = fopen(nameInterfaces1, "w");
    output_facets (f, fp1);	
    fclose(fp1);
}


//event loginterface (t += 1.0) {
    //scalar posX[],posY[];
    //position (f, posX, {1,0}); // (1,0) indicates the unit vector in the x-direction
    //position (f, posY, {0,1}); // (0,1) indicates the unit vector in the y-direction
    //fprintf(fp_interface, "%i %g %1.4f %1.4f %1.4f %1.4f %1.4f \n", i, t, statsf(f).sum, statsf(posX).min, statsf(posX).max, statsf(posY).min, statsf(posY).max);
    //fflush(fp_interface);
//}

=======
>>>>>>> 6b1a0847f0100c8e0a5f764ec7d5be8ae1a5997b
// RC added this for profiling
event logstats (t += 1.0) {

    timing s = timer_timing (perf.gt, i, perf.tnc, NULL);
 
    // i, timestep, no of cells, real time elapsed, cpu time
    fprintf(fp_stats, "i: %i t: %g dt: %g #Cells: %ld Wall clock time (s): %g CPU time (s): %g \n", i, t, dt, grid->n, perf.t, s.cpu);
    fflush(fp_stats);
}

event gfsview (t += 10.0) { // RC
    char name_gfs[200];
    sprintf(name_gfs,"Slice-%0.1f.gfs",t);

    FILE* fp_gfs = fopen (name_gfs, "w");
    output_gfs(fp_gfs);
    fclose(fp_gfs);
}
