#include "navier-stokes/centered.h"
#define LEVEL 6
double tau_y,mu_0,mumax;
int main() {
  L0 = 1.;
  origin (0., 0);
  tau_y=0.25;
  mu_0 = 1;
  mumax=1000;
  periodic (right);
  u.t[top] = neumann(0);
  u.n[top] = neumann(0);
  uf.n[top] = neumann(0);
  u.n[bottom] = dirichlet(0);
  uf.n[bottom] = dirichlet(0);
  u.t[bottom] = dirichlet(0);
  p[top] = neumann(0);
  pf[top] = neumann(0);
  p[bottom] = neumann(0);
  pf[bottom] = neumann(0);
  DT = 0.05;
  run(); 
}
face vector muv[];
scalar D2c[];

event init (t = 0) {
  mu = muv;
  const face vector mdpdx[] = {1.0,0.};
  a = mdpdx;
  foreach() {
    u.x[] = 0;
    u.y[] = 0;
  }
}
event logfile (i++)
  fprintf (stderr, "%d %g %d %d\n", i, t, mgp.i, mgu.i);
scalar un[];
event init_un (i = 0) {
    foreach()
    un[] = u.x[];
}
event conv (t += 0.1; i <= 10000) {
    double du = change (u.x, un);
    fprintf(stdout,"t= %g \n",t);
    if (i > 0 && du < 1e-5)
        return 1; /* stop */
}
event bingham(i++) {
    scalar muB[];
  foreach() {
        double D2 = 0.;
            foreach_dimension() {
                double dxx = u.x[1,0] - u.x[-1,0];
                double dxy = (u.x[0,1] - u.x[0,-1] + u.y[1,0] - u.y[-1,0])/2.;
                D2 += sq(dxx) + sq(dxy);
            }
            if (D2 > 0.) {
                D2 = sqrt(D2)/(2.*Delta);
                D2c[] = D2;
                muB[] =  min(tau_y/(sqrt(2.)*D2) + mu_0 , mumax );    }
            }
    boundary ({muB});
    foreach_face() {
        muv.x[] = (muB[] + muB[-1,0])/2.;
    }
    boundary ((scalar *){muv});
}
event profiles (t += .1)
{
    FILE * fp = fopen("xprof", "w");
    scalar shear[];
    foreach()
    shear[] = (u.x[0,1] - u.x[0,-1])/(2.*Delta);
    boundary ({shear});
    for (double y = 0.; y < 1.0; y += 1./pow(2.,LEVEL))
        fprintf (fp, "%g %g %g %g\n", y, interpolate (u.x, L0/2, y), interpolate (shear, L0/2, y),
                  interpolate (D2c, L0/2, y));
    fclose (fp);
}
event adapt (i++) {
//  adapt_wavelet ({u}, (double[]){3e-2,3e-2}, 7, 4);
}


