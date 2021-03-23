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


int main() {
  origin(-0.5, -0.5);
  float mu1 = 1.0 ; // drop
  init_grid (1 << LEVEL);
  run();
}

event init (t=0.)
{
  foreach()
  u.x[]=y;

  boundary(all);
}
