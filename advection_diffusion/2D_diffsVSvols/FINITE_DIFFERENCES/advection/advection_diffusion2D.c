#include "run.h"
#include "view.h"

scalar T[];

// T[right] = 0.0;
// T[left] = 0.0;
// T[top] = 0.0;
// T[bottom] = 0.0;

// T[right] = neumann(0.0);
// T[left] = neumann(0.0);
// T[top] = neumann(0.0);
// T[bottom] = neumann(0.0);

FILE * fp_params;

double dt;
float U = 2.0;

// See: http://basilisk.fr/sandbox/M1EMN/BASIC/heat.c
int main() {
  // init_grid(1<<LEVEL);
  periodic(right);
  periodic(top);
  L0 = 100.;
  X0 = Y0 = -L0/2;
  N=128;
  // N = 100;
  // CFL = -4.0;
  // DT = (L0/N)*(L0/N)/2 ;
// #define EPS 0.1 
  
  {
  char params[200];
  sprintf(params, "params.txt");
  fp_params=fopen(params, "w");
  }

  fprintf(fp_params, "Delta: %g \n", L0/N);
  fprintf(fp_params, "dt: %g \n", dt);
  fprintf(fp_params, "CFL: %g \n", CFL);
  fclose(fp_params);

  run();
}

event init (t = 0) {
  // mask (y > 5.0 ? top : none);
  // mask (y < -5.0 ? bottom : none);
  // periodic(right);
  foreach()
    // T[] =  1./EPS*(fabs(x)<EPS)/2;
  	// T[] = sin((pi/5)*x)+5;
  	T[] = exp(-(0.1*x*x+0.1*y*y));
  	// T[] = sin((pi/5.0)*x);
  boundary ({T});
}

event printdata (t += 1.0; t < 100.0) {
  foreach()
    fprintf (stdout, "%g %g %g %g\n", x, y, T[], t);
  fprintf (stdout, "\n\n");
}

event integration (i++) {
  // double dt = DT;
  scalar dT[];
  dt = 0.05;
  // foreach() {
  //   // My ACTUAL advection-diffusion scheme:
  //   qh[] = (T[-1,0]-T[0,0])/Delta;
  //   qv[] = - U*(T[0,0]+T[-1,0])/2.0 - ((sq(U)*dt)/(2.0*Delta))*(T[0,0]-T[-1,0]);
  // }
  // boundary ({qh});
  // boundary({qv});
  foreach() {
    // dT[] = ( qh[0,0]  - qh[1,0] )/Delta + ( qv[0,0]  - qv[0,1] )/Delta;

    //   // Alternative method for advection (FINITE DIFFERENCES, forward time, Lax-Wendroff space):
    dT[] = (U/(2*Delta))*(T[1,0]-T[-1,0]) + ((sq(U)*dt)/(2*sq(Delta)))*(T[1,0]-2*T[0,0]+T[-1,0]);
  }

  foreach()
    T[] = T[] + dt*dT[];
  boundary ({T});
}

event profiles (t = 0; t+=1.0; t<=1000)
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

event Tmovie (t+=10.0, t<1000.0)
{
 clear();
 // cells(lc={0.5,0.5,0.5}, lw=0.5);
 // draw_vof ("cs", "fs", filled=-1, fc = {1.0,1.0,1.0}, lw=2);
 squares("T", spread=-1, linear=true, map=cool_warm);
 // cells();
 save ("Tmovie.mp4");
}

// event ymovie (t+=0.1)
// {
//  clear();
//  // cells(lc={0.5,0.5,0.5}, lw=0.5);
//  // draw_vof ("cs", "fs", filled=-1, fc = {1.0,1.0,1.0}, lw=2);
//  squares("u.y", spread=-1, linear=true, map=cool_warm);
//  // cells();
//  save ("ymovie.mp4");
// }