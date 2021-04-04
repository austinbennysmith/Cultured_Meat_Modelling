#include "navier-stokes/centered.h"
// RC #include "embed.h"
//Webpages on which I'm trying to base the validation (not working yet):
//http://basilisk.fr/sandbox/easystab/multi_domain_2D.m
//http://basilisk.fr/src/test/poiseuille.c

FILE *fp1 ;

#define LEVEL 4
#define Re 100

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

  run();

  // RC
  fclose(fp_stats);
}

event init(t = 0) {

  // RC set viscosity to 1/Re
  const face vector muc[] = {1./Re,1./Re};
  mu = muc;

  // flow out of the right -> into the left
  periodic(right);

  /*vertex scalar phi[];
  foreach_vertex() {
    phi[] = intersection(0.5-y, 0.5+y);
  }
  boundary({phi});*/

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

event end (t = 100) {
  printf ("i = %d t = %g\n", i, t);
}

//The following successfuly gives profiles, but not the types of profiles I want (it does t slices rather than x and y slices)
event profiles (t = end)
{
  FILE * fp = fopen("xprof", "w");
  for (double y = -0.5; y <= 0.5; y += 0.01)
    fprintf (fp, "%g %g\n", y, interpolate (u.x, 0, y));
  fclose (fp);
  
  fp = fopen("yprof", "w");
  for (double x = -0.5; x <= 0.5; x += 0.01)
    fprintf (fp, "%g %g\n", x, interpolate (u.y, x, 0));
  fclose (fp);

  fp = fopen("norm", "w");
  vector e[];
// One way to do validation that isn't working:
//  scalar err[];
//  foreach() {
//    e.x[] = u.x[] - y;
//    e.y[] = u.y[];
//  }
//  err=norm(e);
//  fprintf(fp, "%g", err);
// Another way that's not working:
//  scalar err[];
//  theo=y;
//  err=norm(u-theo, 2)
}

// Below I tried to get the profile at x=4. For some reason it throws an error.
//event profiles (double x = 4)
//{
//  FILE * fp = fopen("xprof", "w");
//  for (double t = 0; t <= end; t += 0.01)
//    fprintf (fp, "%g %g\n", y, interpolate (u.y, t, 0));
//  fclose (fp);  
//}

//scalar a[]
//foreach() {
//  a[] = u.x[4, 0];
//}

// RC added this for profiling
event logstats (t += 1.0) {

    timing s = timer_timing (perf.gt, i, perf.tnc, NULL);
 
    // i, timestep, no of cells, real time elapsed, cpu time
    fprintf(fp_stats, "i: %i t: %g dt: %g #Cells: %ld Wall clock time (s): %g CPU time (s): %g \n", i, t, dt, grid->n, perf.t, s.cpu);
//    fprintf(u.x[4, 0]);
    fflush(fp_stats);
}
