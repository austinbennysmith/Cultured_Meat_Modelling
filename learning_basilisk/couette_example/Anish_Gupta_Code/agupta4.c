#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"
#include "view.h"

#define MAX_LEVEL 7

#define beta 0.3 // Location of the fluid interface

#define rhoWater 1000 // density of water
#define rhoOil 917 // density of olive oil at 20C
#define muWater 0.001 // approximatley the viscosity of water
#define muOil 0.03 // approximateley the viscosity of oil

#define sig 0.0728

#define refLength 0.01  // height of the domain
#define refVelocity 0.01  // velocity of the top plate

// Dimensionless quantities:
#define rho_ratio rhoOil/muWater
#define mu_ratio muOil/muWater
#define Re rhoWater*refVelocity*refLength/muWater  // Reynolds number
//#define We rhoWater*pow(refVelocity,2)*refLength/sig
#define We 30

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

  rho1 = 1.0; // water density
  rho2 = rho_ratio; // oil density
  mu1 = 1./Re; // water dynamic viscosity
  mu2 = mu_ratio*mu1; // oil dynamic viscosity
  f.sigma=1./We;
  
  DT = 1.0e-4;
  run();
}

//event acceleration (i++)
//{
//  face vector av = a;
//  foreach_face(y)
//    av.y[] -= 1./sq(Fr);
//}

event init(t = 0) {
  // Initially velocity is 0 everywhere.
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }

  mask (y > 0.5 ? top : none);
  mask (y < -0.5 ? bottom : none);

  fraction (f, y-beta);
  
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);  
}

//event adapt (i++) {
  // error thresholds for            f     u.x   u.y
//  adapt_wavelet ({f, u}, (double []){1e-2, 1e-2, 1e-2}, MAX_LEVEL);
//}

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
