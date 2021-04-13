#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"
#include "view.h"

#define MAX_LEVEL 7
#define TIME_STEP 1./25 // Timestep for movie and log file.
#define MAX_TIME 10.0 // Time to stop at.
#define beta 0.93 // Location of the fluid interface

// Fluid 1 is water at 25°C
#define rhoWater 0.9970
#define muWater 0.8937
// Source: retrieved 7/9/20 from
// https://en.wikipedia.org/wiki/Water_(data_page)#Liquid_physical_properties

// Fluid 2 is sunflower oil at 25°C
#define rhoOil 0.9188
#define muOil 49.14
// Source: retrieved 7/9/20 from
// https://en.wikipedia.org/wiki/Sunflower_oil#Physical_properties

#define Fr 1./sqrt(9.81)
#define We 1.*1.*1./0.037

int main () {
  init_grid(1 << MAX_LEVEL);

  // Set up fluids, doing this in the init event doesn't work.

  // Fluid 1 is water 
  rho1 = rhoWater;
  mu1 = muWater;

  // Fluid 2 is sunflower oil
  rho2 = rhoOil;
  mu2 = muOil;

  // Surface tension coefficient
  f.sigma = 1./We;

  run();
}

event acceleration (i++)
{
  face vector av = a;
  foreach_face(y)
    av.y[] -= 1./sq(Fr);
}

event init(t = 0) {

  // Flow out of the right -> into the left.
  periodic(right);

  // positive -> fluid 1
  // negative -> fluid 2 
  // bottom beta% is oil.
  fraction (f, beta-y + 0.04*sin(4*pi*x));

  // Initially velocity is 0 everywhere.
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
  
  // No-slip boundary conditions.
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);

}

event adapt (i++) {
  // error thresholds for            f     u.x   u.y
  adapt_wavelet ({f, u}, (double []){1e-2, 1e-2, 1e-2}, MAX_LEVEL);
}

