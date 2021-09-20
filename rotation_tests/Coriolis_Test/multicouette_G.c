#define FILTERED //RC
#define mu(f)  (1./(clamp(f,0,1)*(1./mu1 - 1./mu2) + 1./mu2)) //RC

#include "navier-stokes/centered.h"
#include "two-phase.h"
#include "tension.h"
#include "view.h"

FILE *fp1 ;

#define LEVEL 8 // RC was 4, needs to be bigger to capture the setup

// Dimensional quantities:
#define rhoWater 1000.0
#define rhoOil 917.0
#define muWater 0.001 // approximatley the viscosity of water
#define muOil 0.03 // approximateley the viscosity of oil

#define sig 0.0728  //surface tension of water

#define refLength 0.00001  // height of the domain
#define refVelocity 10.0  // velocity of the top plate

// Dimensionless quantities:
#define rho_ratio (rhoOil/rhoWater)
#define mu_ratio (muOil/muWater)
#define Re (rhoWater*refVelocity*refLength/muWater)  // Reynolds number
#define We (rhoWater*pow(refVelocity,2)*refLength/sig) // Weber number
#define Fr (refVelocity/(sqrt(9.8*refLength))) // Froude number

FILE * fp_params;

FILE * fp_stats;

FILE * fp_interface;

double coriolisX;
double coriolisY;

// u.t[top] = dirichlet(0.0);
// u.n[top] = dirichlet(0.0);

// u.t[bottom] = dirichlet(0.0);
// u.n[bottom] = dirichlet(0.0);

// Top & bottom outflow:
u.n[top] = neumann(0.0);
p[top] = dirichlet(0.0);
pf[top] = dirichlet(0.0);

u.n[bottom] = neumann(0.0);
p[bottom] = dirichlet(0.0);
pf[bottom] = dirichlet(0.0);

// Top & bottom Free-Slip condition (Neumann boundary condition du/dx=0, du/dy=0)
// u.n[top] = neumann(0.0);
// u.t[top] = neumann(0.0);

// u.n[bottom] = neumann(0.0);
// u.t[bottom] = neumann(0.0);

// Left inflow
u.n[left] = dirichlet(1.0);
u.t[left] = dirichlet(0.0);

// Right outflow
u.n[right] = neumann(0.0);
p[right] = dirichlet(0.0);
pf[right] = dirichlet(0.0);

// Right free slip
// u.n[right] = neumann(0.0);
// u.t[right] = neumann(0.0);

double omegaNOW;

int main() {
  L0 = 8.;
  origin(-L0/2., -0.5);
  // periodic(right);
  init_grid (1 << LEVEL);

  // RC
  {
    char name[200];
    sprintf(name, "logstats.dat");
    fp_stats = fopen(name, "w");
  }

  // I rescale the system so that water has unit density, and the oil properties are just defined in terms of water
  rho1 = 1.0; // water density
  rho2 = rho_ratio; // oil density
  mu1 = 1/Re; // water dynamic viscosity
  mu2 = mu_ratio*mu1; // oil dynamic viscosity
  f.sigma=1/We;

  DT = 1.0e-2; // RC
  NITERMIN = 1; // default 1
  NITERMAX = 200; // default 100
  TOLERANCE = 1e-4; // default 1e-3

  char params[200];
  sprintf(params, "params.txt");
  fp_params=fopen(params, "w");
  {
    char params[200];
  sprintf(params, "params.txt");
  fp_params=fopen(params, "w");
  }

  fprintf(fp_params, "rho1: %g \n", rho1);
  fprintf(fp_params, "rho2: %g \n", rho2);
  fprintf(fp_params, "mu1: %g \n", mu1);
  fprintf(fp_params, "mu2: %g \n", mu2);
  fprintf(fp_params, "sigma: %g \n", f.sigma);
  fprintf(fp_params, "refLength: %g \n", refLength);
  fprintf(fp_params, "refVelocity: %g \n", refVelocity);
  fprintf(fp_params, "Reynolds Number: %g \n", Re);
  fprintf(fp_params, "Weber Number: %g \n", We);
  fprintf(fp_params, "Froude Number: %g \n", Fr);
  fprintf(fp_params, "Dimensionless gravity: %g \n", 1/sq(Fr));
  fclose(fp_params);


  {
    char intName[200];
    sprintf(intName, "loginterface.dat");
    fp_interface = fopen(intName, "w");
  }
  run();

  fclose(fp_interface);
  fclose(fp_stats);
}

// event acceleration (i++)
// {
//   face vector av = a;
//   foreach_face(x)
//     av.x[] -= 0.1*exp(x);
//   foreach_face(y)
//     av.y[] -= 0.1*1/sq(Fr); // This needs to be changed
// }

event acceleration (i++)
{
  face vector av = a;
  omegaNOW = 2.0;
  foreach_face(x) {
    coriolisX = 2.0*omegaNOW*((u.y[]+u.y[-1])/2.0);
    av.x[] += 0.1*coriolisX;
  //   av.x[] -= 1.0;
  }
  foreach_face(y) {
    coriolisY = -2.0*omegaNOW*((u.x[]+u.x[-1])/2.0);
    av.y[] += 0.1*coriolisY;
    // av.y[] -= Bo;
  }
}

event init(t = 0) {
 
  // initially velocity is 0 everywhere
  foreach () {
    u.x[] = 1.;
    u.y[] = 0.;
  }

  // RC cut the top and bottom of domain
  mask (y > 0.5 ? top : none);
  mask (y < -0.5 ? bottom : none);
  
  fraction (f, 0.3-y);
}

// event adapt (i++)
// {
//   adapt_wavelet({u, f}, (double[]){1e-2, 1e-2, 1e-2}, LEVEL);
// }

event end (t = 100) { // RC restricted to 400
  printf ("i = %d t = %g\n", i, t);
}

event profiles (t = 0; t+=1.0; t<=100) // RC restricted the output a little, don't overdo it at first!
{
  FILE * fp = fopen("xprof", "a");
  for (double y = -0.5; y <= 0.5; y += 0.01)
    fprintf (fp, "%g %g %g\n", t, y, interpolate (u.x, 0, y));
  fclose (fp);
  
  fp = fopen("yprof", "a");
  for (double x = -4; x <= 4; x += 0.01)
    fprintf (fp, "%g %g %g\n", t, x, interpolate (u.y, x, 0));
  fclose (fp);
}


// RC added this for profiling
event logstats (t += 1.0) {

    timing s = timer_timing (perf.gt, i, perf.tnc, NULL);
 
    // i, timestep, no of cells, real time elapsed, cpu time
    fprintf(fp_stats, "i: %i t: %g dt: %g #Cells: %ld Wall clock time (s): %g CPU time (s): %g \n", i, t, dt, grid->n, perf.t, s.cpu);
    fflush(fp_stats);
}

event gfsview (t += 1.0) { // RC
    char name_gfs[200];
    sprintf(name_gfs,"Slice-%0.1f.gfs",t);

    FILE* fp_gfs = fopen (name_gfs, "w");
    output_gfs(fp_gfs);
    fclose(fp_gfs);
}

event xmovie (t+=1.0)
{
 clear();
 squares("u.x", min=-1, max=1, linear=true, map=cool_warm);
 draw_vof ("f", lc = {1.0,1.0,1.0}, lw=2);
    // cells();
 save ("xmovie.mp4");
}

event ymovie (t+=1.0)
{
 clear();
 squares("u.y", min=-1, max=1, linear=true, map=cool_warm);
 draw_vof ("f", lc = {1.0,1.0,1.0}, lw=2);
    // cells();
 save ("ymovie.mp4");
}

event interface (t+=1)
{
  char name_interface[100];
  sprintf(name_interface, "interface_%g.dat", t);

  FILE * fp2 = fopen(name_interface, "w");
  output_facets (f, fp2);
}

event loginterface (t += 1.0) {    
    scalar posX[],posY[];
    position (f, posX, {1, 0});
    position (f, posY, {0,1});
    fprintf(fp_interface, "%i %g %1.4f %1.4f %1.4f %1.4f %1.4f\n", i, t, statsf(f).sum, statsf(posX).min, statsf(posX).max, statsf(posY).min, statsf(posY).max);
    fflush(fp_interface);
}