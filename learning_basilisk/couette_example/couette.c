#include "navier-stokes/centered.h"

FILE *fp1 ;

#define LEVEL 8
#define rhoWater 0.9970
#define muWater 0.8937
#define Re 100

u.t[top] = dirichlet( 1.0 );
u.n[top] = dirichlet( 0.0 );

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet( 0.0 );

event init(t = 0) {

  periodic(right);

  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
  
  u.t[top] = dirichlet(1.);
  u.t[bottom] = dirichlet(0.);

}

// event viewer (t = 20; t <= 100; t += 0.1) {
//  int x
//  view(x = 4);
//  clear();
//  scatter(loc);
//  save("contour.mp4");
//}

int main() {
  origin(-0.5, -0.5);
  float mu1 = muWater ; // drop
  float rho1 = rhoWater ;
  init_grid (1 << LEVEL);
  run();
}

event end (t = 4) {
  printf ("i = %d t = %g\n", i, t);
}
