#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"
#include "view.h"

#define MAX_LEVEL 7
#define beta 0.3 // Location of the fluid interface

// Fluid 1 is water at 25°C
#define rhoWater 1.0
#define muWater 1.0
#define rhoOil 0.917
#define muOil 30

//#define Fr 1./sqrt(9.81)
#define We 13.73626

u.t[top] = dirichlet(1.0);
u.n[top] = dirichlet(0.0);

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet(0.0);


int main () {
  L0 = 8.;
  origin(-L0/2., -0.5);
  periodic(right);
  init_grid(1 << MAX_LEVEL);

  rho1 = rhoWater;
  mu1 = muWater;
  rho2 = rhoOil;
  mu2 = muOil;
  f.sigma = 1./We;

  run();
}

event acceleration (i++)
{
  face vector av = a;
  foreach_face(y)
    av.y[] -= 9.81;
}

event init(t = 0) {
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }

  mask (y > 0.5 ? top : none);
  mask (y < -0.5 ? bottom : none);

  fraction (f, beta-y);

  // No-slip boundary conditions.
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);

}

event profiles (t = 0; t+=1.0; t<=1000) // RC restricted the output a little, don't overdo it at first!
{
  FILE * fp = fopen("xprof", "a");
  for (double y = -0.5; y <= 0.5; y += 0.01)
    fprintf (fp, "%g %g %g\n", t, y, interpolate (u.x, 0, y));
  fclose (fp);
  
  fp = fopen("yprof", "a");
  for (double x = -4; x <= 4; x += 0.01)
    fprintf (fp, "%g %g %g\n", t, x, interpolate (u.y, x, 0));
  fclose (fp);
}
