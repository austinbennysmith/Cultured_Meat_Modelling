#include "navier-stokes/centered.h"
#include "view.h"
#include "fractions.h"

#define MAXLEVEL 9

const double tmax = 1000.0;

double thetaNOW;
double omegaNOW;

const double period = 80.0; // how many seconds it takes to go through a complete rocking cycle
double BB = (2.0*3.14159265)/period;

const double maxDegrees = 7.0; // degrees through which the reactor rotates
double maxRads = maxDegrees*(3.14159265/180.0);

// The following doubles will be used in the acceleration event to avoid really long lines of code:
double gravityX;
double gravityY;
double coriolisX;
double coriolisY;
double centripetalX;
double centripetalY;

#define Re 3000.0
#define Fr 1.0

const double semiminor = 1.0;
const double semimajor = semiminor*3.0;

const double ymax = semiminor+0.5; // ymax of domain (used in masking & profiling, etc.)
const double ymin = -semiminor-0.5; // ymin of domain (used in masking & profiling, etc.)

// FILE *fp_params;

// RC
// FILE * fp_stats;

// FILE * fp_interface;

u.t[top] = dirichlet(0.0);
u.n[top] = dirichlet(0.0);

u.t[bottom] = dirichlet(0.0);
u.n[bottom] = dirichlet(0.0);

u.t[left] = dirichlet(0.0);
u.n[left] = dirichlet(0.0);

u.t[right] = dirichlet(0.0);
u.n[right] = dirichlet(0.0);

scalar circle[];

int main() {
  L0 = 2.0*semimajor+2.0;
  origin(-L0/2., -semiminor-0.5);// Change -0.5 to -L0/16??
  // periodic(right);
  init_grid (1 << MAXLEVEL);

  // RC
  // {
  //   char name[200];
  //   sprintf(name, "logstats.dat");
  //   fp_stats = fopen(name, "w");
  // }

  // I rescale the system so that water has unit density, and the oil properties are just defined in terms of water
  // rho1 = 1.0; // water density
  // rho2 = rho_ratio; // oil density
  // mu1 = 1/Re; // water dynamic viscosity
  // mu2 = mu_ratio*mu1; // oil dynamic viscosity
  // f.sigma=1/We; // change this later

  DT = 1.0e-2; // RC
  NITERMIN = 1; // default 1
  NITERMAX = 200; // default 100
  TOLERANCE = 1e-4; // default 1e-3

 //  char params[200];
 //  sprintf(params, "params.txt");
 //  fp_params=fopen(params, "w");
 //  {
 //    char params[200];
	// sprintf(params, "params.txt");
	// fp_params=fopen(params, "w");
 //  }

  // fprintf(fp_params, "rho1: %g \n", rho1);
  // fprintf(fp_params, "rho2: %g \n", rho2);
  // fprintf(fp_params, "mu1: %g \n", mu1);
  // fprintf(fp_params, "mu2: %g \n", mu2);
  // fprintf(fp_params, "sigma: %g \n", f.sigma);
  // fprintf(fp_params, "refLength: %g \n", refLength);
  // fprintf(fp_params, "refVelocity: %g \n", refVelocity);
  // fprintf(fp_params, "Reynolds Number: %g \n", Re);
  // // fprintf(fp_params, "Weber Number: %g \n", We);
  // fprintf(fp_params, "Froude Number: %g \n", Fr);
  // fprintf(fp_params, "Dimensionless gravity: %g \n", 1/sq(Fr));
  // fprintf(fp_params, "L0: %g \n", L0);
  // fclose(fp_params);

  // {
  //   char intName[200];
  //   sprintf(intName, "loginterface.dat");
  //   fp_interface = fopen(intName, "w");
  // }
  run();

  // fclose(fp_interface);
  // fclose(fp_stats);
}

event acceleration (i++)
{
  thetaNOW = maxRads*sin(BB*t); // Derivation in notebook. Should write this up at some point.
  omegaNOW = BB*maxRads*cos(BB*t); // Derivative of omegaNOW w/respect to t
  face vector av = a;
  // Which of the following 2 ways of doing it is better??
  foreach_face(x) {
    gravityX = (1/sqrt(2))*sq(1/Fr)*sin(thetaNOW);
    coriolisX = 2.0*((u.y[]+u.y[-1])/2.0)*BB*maxRads*cos(BB*t);
    centripetalX = x*sq(BB)*sq(maxRads)*sq(cos(BB*t));
    av.x[] -= gravityX + coriolisX + centripetalX;
    // av.x[] -= (1/sqrt(2))*sq(1/Fr)*sin(thetaNOW) + 2.0*((u.y[]+u.y[-1])/2.0)*BB*maxRads*cos(BB*t) + x*sq(BB)*sq(maxRads)*sq(cos(BB*t));
  }
  foreach_face(y) {
    gravityY = (1/sqrt(2))*sq(1/Fr)*cos(thetaNOW);
    coriolisY = -2.0*((u.x[]+u.x[-1])/2.0)*BB*maxRads*cos(BB*t);
    centripetalY = sq(BB)*sq(maxRads)*sq(cos(BB*t))*(y+semiminor);
    av.y[] -= gravityY + coriolisY + centripetalY;
    // av.y[] -= (1/sqrt(2))*sq(1/Fr)*cos(thetaNOW) - 2.0*((u.x[]+u.x[-1])/2.0)*BB*maxRads*cos(BB*t) + sq(BB)*sq(maxRads)*sq(cos(BB*t))*(y+semiminor);
    // av.x[] -= (1/sqrt(2))*sq(1/Fr)*sin(thetaNOW);
  }
}

event init(t = 0) {
 
  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 0.;
    u.y[] = 0.;
  }

  // RC cut the top and bottom of domain
  // Could try changing this to -0.5 and 0.5 just to see
  mask (y > ymax ? top : none);
  mask (y < ymin ? bottom : none);
  
  // mask (circle < 1.0 ? top : none);

  refine(level<MAXLEVEL && (1.0/sq(semimajor))*sq(x) + (1.0/sq(semiminor))*sq(y) < 1.0);
  unrefine(level<MAXLEVEL && (1.0/sq(semimajor))*sq(x) + (1.0/sq(semiminor))*sq(y) > sq(1.0));
  // adapt_wavelet((scalar *){f, u.x, u.y}, (double[]){1e-6, 1e-2, 1e-2}, MAXLEVEL, 4);

  // fraction (f, -y);

  // foreach() {
  //   TT[] = exp(-(10*x*x+10*y*y));
  // }
  // fraction (TT, -(0.05*sq(x) + sq(y+0.7) - sq(0.2)));
  // fraction (TT, intersection((y), (-((1.0/sq(semimajor))*sq(x) + (1.0/sq(semiminor))*sq(y) - 1.0))));
  // boundary({TT});

  // boundary conditions
  // u.t[top] = dirichlet(1.);
  // u.t[bottom] = dirichlet(0.);

}

event circle_flow (i++) {
  fraction (circle, ((1.0/sq(semimajor))*sq(x) + (1.0/sq(semiminor))*sq(y) - 1.0));
  foreach() {
    foreach_dimension() {
      u.x[] = (1. - circle[])*u.x[];
      u.y[] = (1. - circle[])*u.y[];
    }
  }
  boundary ((scalar *){u});
}

event end (t = tmax) { // RC restricted to 400
  printf ("i = %d t = %g\n", i, t);
}

event gfsview (t += 10.0) { // RC
    char name_gfs[200];
    sprintf(name_gfs,"Slice-%0.1f.gfs",t);

    FILE* fp_gfs = fopen (name_gfs, "w");
    output_gfs(fp_gfs);
    fclose(fp_gfs);
}