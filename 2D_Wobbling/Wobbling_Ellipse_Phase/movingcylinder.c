#include "navier-stokes/centered.h"
#include "fractions.h"
#include "view.h"

int main(){
  L0 = 8.;
  origin (-0.5, -L0/2.);
  N = 512;
  const face vector muc[] = {0.00078125,0.00078125};
  mu = muc;
  run();
}

event init (t = 0) {
  mask(y > 0.5 ? top: y < -0.5 ? bottom : none);
}

scalar cylinder[];

event moving_cylinder (i++) {
  coord vc = {1.,0.}; // the velocity of the cylinder
  fraction (cylinder, - (sq(x - vc.x*t) + sq(y - vc.y*t) - sq(0.0625)));
  foreach()
    foreach_dimension()
	  u.x[] = cylinder[]*vc.x + (1. - cylinder[])*u.x[];
  boundary ((scalar *){u});
}

event logfile (i++)
fprintf (stderr, "%d %g %d %d %d %d\n", i, t,
	mgp.i, mgp.nrelax, mgu.i, mgu.nrelax);

event images (t += 0.1; t <= 10.0) {
  static FILE * fp = popen ("ppm2gif > vort.gif", "w");
  scalar omega[];
  vorticity (u, omega);
  scalar m[];
  foreach()
    m[] = 0.5 - cylinder[];
  boundary ({m});

  output_ppm (omega, fp, box = {{-0.5,-0.5},{7.5,0.5}}, mask = m,
	      min=-10, max=10, linear=true);
}

event adapt (i++) {
  adapt_wavelet ((scalar *){u}, (double[]){3e-2,3e-2}, 9, 4);
}

event vortmovie (t+=1.0, t<=10.0)
{
  scalar omega[];
  // vorticity(u, omega);

  view (fov=3, width=2600, height=400);
  clear();
  squares("omega", spread=-1.0, linear=true, map=cool_warm);

  draw_vof ("f", lc = {1.0,1.0,1.0}, lw=2);
  save("Vorticity.mp4");
}

event gfsview (t += 1.0) { // RC
    char name_gfs[200];
    sprintf(name_gfs,"Slice-%0.1f.gfs",t);

    FILE* fp_gfs = fopen (name_gfs, "w");
    output_gfs(fp_gfs);
    fclose(fp_gfs);
}