#include "navier-stokes/centered.h"

FILE *fp1 ;
#define LEVEL 8

u.t[top] = dirichlet( y );
u.n[top] = dirichlet( 0.0 );

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet( 0.0 );

event init (t=0.)
{
  foreach()
    u.x[]=y;

  boundary (all);
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
  float mu1 = 1.0 ; // drop
  init_grid (1 << LEVEL);
  run();
}

event end (t = 4) {
  printf ("i = %d t = %g\n", i, t);
}
