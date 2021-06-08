#include "navier-stokes/centered.h"
#include "view.h"
// RC #include "embed.h"

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

event xmovie (t+=1.0, t<=5.0)
{
 clear();
 // cells(lc={0.5,0.5,0.5}, lw=0.5);
 // draw_vof ("cs", "fs", filled=-1, fc = {1.0,1.0,1.0}, lw=2);
 squares("u.x", spread=-1, linear=true, map=cool_warm);
 // cells();
 save ("xmovie.mp4");
}