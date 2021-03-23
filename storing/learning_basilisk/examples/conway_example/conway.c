#include "grid/cartesian.h"
#include "run.h"
scalar a[], b[], age[];
int main()
{
  origin (-0.5, -0.5);
  init_grid (256);
  run();
}
event init (i = 0)
{
  foreach() {
    a[] = (x*x + y*y < sq(0.2))*(noise() > 0.);
    age[] = a[];
  }
  boundary({a});
}
event movie (i += 5; i < 1000)
{
scalar m[];
  foreach()
    m[] = age[] ? 1 : -1;

  output_ppm (age, mask = m, n = 512, file = "age.gif", opt = "--delay 1");
}
event life (i++)
{
  foreach() {
  int neighbors = - a[];
    for (int i = -1; i <= 1; i++)
      for  (int j = -1; j <= 1; j++)
	neighbors += a[i,j];
  b[] = a[] ? (neighbors == 2 || neighbors == 3) : (neighbors == 3);
    age[] = b[]*(age[] + 1);
  }
  boundary({b});
swap (scalar, a, b);
}

