#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"
#include "view.h"

#define MAX_LEVEL 7

#define beta 0.3 // Location of the fluid interface

// Fluid 1 is water at 25°C
#define rhoWater 0.9970
//#define rhoWater 1000
#define muWater 0.008937
// Source: retrieved 7/9/20 from
// https://en.wikipedia.org/wiki/Water_(data_page)#Liquid_physical_properties

// Fluid 2 is sunflower oil at 25°C
#define rhoOil 0.9188
//#define rhoOil 917
#define muOil 0.4914
// Source: retrieved 7/9/20 from
// https://en.wikipedia.org/wiki/Sunflower_oil#Physical_properties

#define Fr 1./sqrt(9.81)
#define We 13.736
//#define We 1.*1.*1./0.037

#define rho_ratio rhoOil/muWater

u.t[top] = dirichlet(1.0);
u.n[top] = dirichlet(0.0);

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet(0.0);

int main () {
  L0 = 8.;
  origin(-L0/2., -0.5);
  periodic(right);
  init_grid(1 << MAX_LEVEL);
  // Set up fluids, doing this in the init event doesn't work.

  // Fluid 1 is water 
//  rho1 = rhoWater;
  rho1 = 1.0;
  mu1 = muWater;

  // Fluid 2 is sunflower oil
//  rho2 = rhoOil;
  rho2 = rho_ratio;
  mu2 = muOil;

  // Surface tension coefficient
  f.sigma = 1./We;

  run();
}

event acceleration (i++)
{
  face vector av = a;
  foreach_face(y)
    av.y[] -= 9.8;
}

event init(t = 0) {
  // Initially velocity is 0 everywhere.
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }

  mask (y > 0.5 ? top : none);
  mask (y < -0.5 ? bottom : none);

//  fraction (f, y-beta);
  fraction(f, beta-y);  

  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);  
}

//event adapt (i++) {
  // error thresholds for            f     u.x   u.y
//  adapt_wavelet ({f, u}, (double []){1e-2, 1e-2, 1e-2}, MAX_LEVEL);
//}

event profiles (t = 0; t+=1.0; t<=100) // RC restricted the output a little, don't overdo it at first!
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
