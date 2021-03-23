#include "grid/multigrid.h"
#include "run.h"
#include "diffusion.h"
scalar C1[], C2[];
double k = 1., ka = 4.5, D = 8.;
double mu, kb;
double dt;
mgstats mgd1, mgd2;
int main()
{
  init_grid (128);
  size (64);
  TOLERANCE = 1e-4;
  mu = 0.04; run();
  mu = 0.1;  run();
  mu = 0.98; run();
}
event init (i = 0)
{
  double nu = sqrt(1./D);
  double kbcrit = sq(1. + ka*nu);
  kb = kbcrit*(1. + mu);
  foreach() {
    C1[] = ka ; 
    C2[] = kb/ka + 0.01*noise();
  }
  boundary ({C1, C2});
}
event movie (i = 1; i += 10)
{
  output_ppm (C1, linear = true, spread = 2, file = "f.ppm", n = 200);
  fprintf (stderr, "%d %g %g %d %d\n", i, t, dt, mgd1.i, mgd2.i);
}
event final (t = 3000)
{
  char name[80];
  sprintf (name, "mu-%g.png", mu);
  output_ppm (C1, file = name, n = 200, linear = true, spread = 2);
}
event integration (i++)
{
  dt = dtnext (1.);
  scalar r[], beta[];

  foreach() {
    r[] = k*ka;
    beta[] = k*(C1[]*C2[] - kb - 1.);
    }
  mgd1 = diffusion (C1, dt, r = r, beta = beta);
  foreach() {
    r[] = k*kb*C1[];
    beta[] = - k*sq(C1[]);
  }
  const face vector c[] = {D, D};
  mgd2 = diffusion (C2, dt, c, r, beta);
}
