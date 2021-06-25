#include "run.h"
#include "view.h"

scalar T[];

FILE * fp_params;

double dt;
const double mydt = 1e-2;
const double MAXTIME = 100.0/mydt; // I want to run the simulation for 10 whole time steps, that is 10*dt if dt=1. Since dt!=1, I must define a MAXTIME which will be used in the printdata event to tell the code when to stop
float U = 2.0;

// See: http://basilisk.fr/sandbox/M1EMN/BASIC/heat.c
int main() {
  // init_grid(1<<LEVEL);
  periodic(right);
  periodic(top);
  L0 = 100.;
  X0 = Y0 = -L0/2;
  N=128e0;
  
  {
  char params[200];
  sprintf(params, "params.txt");
  fp_params=fopen(params, "w");
  }

  fprintf(fp_params, "Advection Stability Condition: |U*dt/dx|<=1, where dx=L0/N \n");
  fprintf(fp_params, "|a*dt/dx|= %g \n", fabs(U*mydt/(L0/N)));
  fprintf(fp_params, "Diffusion Stability Condition: b*mu<=0.5, where b=diffusion coefficient (=1 here) and mu=dt/dx^2, where dx=L0/N \n");
  fprintf(fp_params, "b*mu=mu= %g \n", mydt/(sq(L0/N)));
  fprintf(fp_params, "dt = %g \n", mydt);
  fprintf(fp_params, "dx = %g \n", L0/N);
  fprintf(fp_params, "N = %d \n", N);
  fclose(fp_params);

  run();
}

event init (t = 0) {
  foreach()
  	T[] = exp(-(0.1*x*x+0.1*y*y));
  boundary ({T});
}

event printdata (t += 1.0; t < MAXTIME) {
  if ((t*mydt) == floor(t*mydt)) { // I only print output on whole number times so that there's not too much data for Python to handle efficiently in postprocessing.
    foreach()
      fprintf (stdout, "%g %g %g %g\n", x, T[], t, t*mydt);
    fprintf (stdout, "\n\n");
  }
}

event integration (i++) {
  // double dt = DT;
  scalar dT[],qh[];
  dt = mydt;
  foreach() {
    // My advection scheme:
    qh[] = - U*(T[0,0]+T[-1,0])/2.0 - ((sq(U)*dt)/(2.0*Delta))*(T[0,0]-T[-1,0]);
  }
  boundary ({qh});
  foreach() {
    dT[] = ( qh[0,0]  - qh[1,0] )/Delta;

    //   // Alternative method for advection-diffusion (FINITE DIFFERENCES, forward time, centered space for diffusion, Lax-Wendroff for advection):
    // dT[] = (T[1,0]-2*T[0,0]+T[-1,0])/(sq(Delta)) + (U/(2*Delta))*(T[1,0]-T[-1,0]) + ((sq(U)*dt)/(2*sq(Delta)))*(T[1,0]-2*T[0,0]+T[-1,0]) + (T[0,1]-2*T[0,0]+T[0,-1])/(sq(Delta)) + (U/(2*Delta))*(T[0,1]-T[0,-1]) + ((sq(U)*dt)/(2*sq(Delta)))*(T[0,1]-2*T[0,0]+T[0,-1]);
  }

  foreach()
    T[] = T[] + dt*dT[];
  boundary ({T});
}

event profiles (t = 0; t+=1.0; t<=MAXTIME)
{
  FILE * fp = fopen("xprof", "a");
  for (double y = -L0/2; y <= L0/2; y += 0.01)
    fprintf (fp, "%g %g %g\n", t, y, interpolate (T, 0, y));
  fclose (fp);
  
  fp = fopen("yprof", "a");
  for (double x = -L0/2; x <= L0/2; x += 0.01)
    fprintf (fp, "%g %g %g\n", t, x, interpolate (T, x, 0));
  fclose (fp);
}

event Tmovie (t+=10.0, t<MAXTIME)
{
 clear();
 // cells(lc={0.5,0.5,0.5}, lw=0.5);
 // draw_vof ("cs", "fs", filled=-1, fc = {1.0,1.0,1.0}, lw=2);
 squares("T", spread=-1, linear=true, map=cool_warm);
 // cells();
 save ("Tmovie.mp4");
}