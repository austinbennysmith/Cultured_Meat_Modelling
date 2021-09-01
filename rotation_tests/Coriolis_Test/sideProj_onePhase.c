// Using axi.h since the flow is axisymmetric.
// x (horizontal) is the axis about which the rotation occurs
// y (vertical) is the radial direction
#include "axi.h"
#include "navier-stokes/centered.h"
#include "view.h"

#define LEVEL 8 // RC was 4, needs to be bigger to capture the setup
#define Re 100 // Reynolds number

// Boundary Conditions:
u.n[left] = dirichlet(1.0); // Left inflow

//Right outflow
u.n[right] = neumann(0.0);
p[right] = dirichlet(0.0);
pf[right] = dirichlet(0.0);

// Free-slip condition on top (Neumann boundary condition du/dx=0, du/dy=0)
// Don't need to do free slip on bottom due to axisymmetry
u.n[top] = neumann(0.0);
u.t[top] = neumann(0.0);

int main() {
	L0 = 8.;
	// origin(-L0/2, -0.5);
	init_grid (1 << LEVEL);

	// I rescale the system so that water has unit density, and the oil properties are just defined in terms of water
  // rho = rhoWater;
  // mu = muWater; // water dynamic viscosity

  DT = 1.0e-2; // RC
  NITERMIN = 1; // default 1
  NITERMAX = 200; // default 100
  TOLERANCE = 1e-4; // default 1e-3

  run();
}

event init(t = 0) {

  const face vector muc[] = {1./Re,1./Re};
  mu=muc;
  // initially velocity is 0 everywhere
  // foreach () {
  //   u.x[] = 0.;
  //   u.y[] = 0.;
  // }

  // RC cut the top and bottom of domain
  // mask (y > 0.5 ? top : none);
  // mask (y < -0.5 ? bottom : none);
  
  // fraction (f, -y);
}

event end (t = 100) { // RC restricted to 400
  printf ("i = %d t = %g\n", i, t);
}

event gfsview (t += 1.0) { // RC
    char name_gfs[200];
    sprintf(name_gfs,"Slice-%0.1f.gfs",t);

    FILE* fp_gfs = fopen (name_gfs, "w");
    output_gfs(fp_gfs);
    fclose(fp_gfs);
}