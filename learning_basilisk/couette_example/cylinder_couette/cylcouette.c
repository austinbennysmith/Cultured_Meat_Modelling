#include "grid/multigrid.h"
#include "embed.h"
#include "navier-stokes/centered.h"
#include "view.h"

int main()
{
  origin (-L0/2., -L0/2.);
  
  stokes = true;
  TOLERANCE = 1e-5;
  for (N = 16; N <= 256; N *= 2)
    run();
}

scalar un[];

#define WIDTH 0.5

event init (t = 0) {
  mu = fm;
  vertex scalar phi[];
  foreach_vertex()
    phi[] = difference (sq(0.5) - sq(x) - sq(y),
			sq(0.25) - sq(x) - sq(y));
  boundary ({phi});
  fractions (phi, cs, fs);
  u.n[embed] = dirichlet (x*x + y*y > 0.14 ? 0. : - y);
  u.t[embed] = dirichlet (x*x + y*y > 0.14 ? 0. :   x);
  foreach()
    un[] = u.y[];
}
//event logfile (t += 0.01; i <= 1000) {
//  double du = change (u.y, un);
//  if (i > 0 && du < 1e-6)
//    return 1; /* stop */
//}

