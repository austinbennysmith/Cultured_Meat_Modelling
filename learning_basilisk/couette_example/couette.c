#include "navier-stokes/centered.h"

FILE *fp1 ;

#define LEVEL 5
#define Re 100

u.t[top] = dirichlet( 1.0 );
u.n[top] = dirichlet( 0.0 );

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet( 0.0 );

int main() {
  origin(-0.5, -0.5);
  init_grid (1 << LEVEL);
  run();
}

event init(t = 0) {

  periodic(right);

  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }
}

event end (t = 4) {
  printf ("i = %d t = %g\n", i, t);
}
