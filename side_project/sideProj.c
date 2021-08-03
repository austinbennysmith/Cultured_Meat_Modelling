#define FILTERED //RC
#define mu(f)  (1./(clamp(f,0,1)*(1./mu1 - 1./mu2) + 1./mu2)) //RC

#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"
#include "view.h"

#define LEVEL 8 // RC was 4, needs to be bigger to capture the setup

// Dimensional quantities:
// Using 2 immisible fluids that have the same properties
#define rhoWater1 1000.0
#define rhoWater2 1000.0
#define muWater1 0.001 // approximatley the viscosity of water
#define muWater2 0.001 // approximateley the viscosity of oil

#define sig 0.1456  //surface tension (twice that you would see between water & oil)

#define refLength 0.2  // height of the domain
#define refVelocity 0.1  // velocity of the top plate

// Dimensionless quantities:
#define rho_ratio (rhoOil/rhoWater)
#define mu_ratio (muOil/muWater)
#define Re (rhoWater*refVelocity*refLength/muWater)  // Reynolds number
#define We (rhoWater*pow(refVelocity,2)*refLength/sig)