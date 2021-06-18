#include "embed.h"
#include "navier-stokes/centered.h"
#include "view.h"

#define LEVEL 9

#define rhoWater 1000.0 //kg m^-3
#define muWater 0.001

// #define refLength 0.1
// #define refVelocity 0.1

#define Re 1e3  // Reynolds number

FILE * fp_params;

FILE * fp_stats;

// Top & bottom outflow
u.n[top] = neumann(0.0);
p[top] = dirichlet(0.0);
pf[top] = dirichlet(0.0);

u.n[bottom] = neumann(0.0);
p[bottom] = dirichlet(0.0);
pf[bottom] = dirichlet(0.0);

// u.n[top] = neumann(0.0);
// u.t[top] = neumann(0.0);

// u.n[bottom] = neumann(0.0);
// u.t[bottom] = neumann(0.0);

// Left inflow
u.n[left] = dirichlet(1.0);

// Right outflow
u.n[right] = neumann(0.0);
p[right] = dirichlet(0.0);
pf[right] = dirichlet(0.0);

// No slip on the plate
u.n[embed] = dirichlet(0.0);
u.t[embed] = dirichlet(0.0);

face vector muv[];

int main() {
	L0=10.0;
	init_grid(1<<LEVEL);
	mu=muv;

	{
    char params[200];
	sprintf(params, "params.txt");
	fp_params=fopen(params, "w");
    }

	{
	char name[200];
	sprintf(name, "logstats.dat");
	fp_stats = fopen(name, "w");
	}

	fprintf(fp_params, "Reynolds Number: %g \n", Re);
	fclose(fp_params);

	run();

	fclose(fp_stats);
}

event init(t=0) {
	mask (y > 4.0 ? top : none);
    mask (y < 0.0 ? bottom : none);
	
	vertex scalar phi[];
	foreach_vertex()
		phi[]=0.0009*(x-7.5)*(x-7.5)+(y-2.0)*(y-2.0)-sq(0.1);
	boundary({phi});
	fractions(phi, cs, fs);
}

event adapt (i++) {
	adapt_wavelet ((scalar *){cs, u.x, u.y}, (double[]){1e-3, 1e-2, 1e-2}, 9, 4)
}

event properties(i++)
{
	foreach_face()
		muv.x[]=fm.x[]/Re;
	boundary((scalar *){muv});
}

event end (t = 100) { // RC restricted to 400
  printf ("i = %d t = %g\n", i, t);
}

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

event profiles (t = 0; t+=1.0)
{
  FILE * fp = fopen("xprof", "a");
  for (double y = 0.0; y <= 2.0; y += 0.01)
    fprintf (fp, "%g %g %g\n", t, y, interpolate (u.x, 2.7, y));
  fclose (fp);
  
  fp = fopen("yprof", "a");
  for (double x = 0; x <= 10; x += 0.01)
    fprintf (fp, "%g %g %g\n", t, x, interpolate (u.y, x, 0));
  fclose (fp);
}

double uxdiffs[201];
double BoundLayer[1001];
int my_int;
float my_float;
double min;
double ycoord;
int ytemp;

double uxdiffs2[201];
double BoundLayer2[1001];
int my_int2;
float my_float2;
double min2;
double ycoord2;
int ytemp2;

// Boundary Layer above the plate:
event blayer (t+=1.0) {
	FILE * fp = fopen("blayer", "a");
	FILE * fp2 = fopen("temp", "a");
	FILE * fp3 = fopen("tempy", "a");
	for (double x=2.51; x<= 10; x += 0.01) {
		for (double y=2.0; y<=4.0; y+=0.01) {
			my_float = 100.0*(y-2.0);
			my_int = (int)my_float;
			// uxdiffs[my_int] = interpolate(u.y, x, y);
			// uxdiffs[my_int] = fabs(0.99-interpolate(u.x, x, y));
			uxdiffs[my_int] = interpolate(u.x, x, y);
		}
		// min=uxdiffs[0];
		min=2.0;
		ycoord=0.0;
		ytemp=0;
		for (int i=0; i<201; i++) {
			if (uxdiffs[i]<=0.99) {
				ytemp=i;
				ycoord=(double)ytemp;
				ycoord=(0.01*ycoord)+2.0;
				min=ycoord;
			}
			// if (min>uxdiffs[i]) {
			// 	min=uxdiffs[i];
			// 	ytemp=i;
			// 	ycoord=(double)ytemp;
			// 	ycoord=(0.01*ycoord)+2.0;
			// }
		}
		fprintf(fp2, "%g %g %g\n", t, x, min);
		fprintf(fp3, "%g %g %g\n", t, x, ycoord);
	}
	fclose (fp2);
	fclose(fp3);
			// uxvals[(int)y*100] = yq*100;
			// printf("%lf\n", &uxvals[(int)y*100]);
    		// fprintf (fp, "%g %g %g\n", t, y, interpolate (u.x, 0, y));
	for (int loop=0; loop<201; loop++)
		fprintf(fp, "%g %g\n", t, uxdiffs[loop]);
	// fprintf(fp, "%g\n", uxvals[9]);
  	fclose (fp);
}


// Boundary Layer below the plate:
event blayer2 (t+=1.0) {
	FILE * fp4 = fopen("temp2", "a");
	FILE * fp5 = fopen("tempy2", "a");
	for (double x=2.51; x<= 10; x += 0.01) {
		for (double y=0.0; y<=2.0; y+=0.01) {
			my_float2 = 100.0*(y);
			my_int2 = (int)my_float2;
			// uxdiffs[my_int] = interpolate(u.y, x, y);
			// uxdiffs[my_int] = fabs(0.99-interpolate(u.x, x, y));
			uxdiffs2[my_int2] = interpolate(u.x, x, y);
		}
		// min=uxdiffs[0];
		min2=0.0;
		ycoord2=0.0;
		ytemp2=0;
		for (int i=0; i<201; i++) {
			if (uxdiffs2[i]>=0.99) {
				ytemp2=i;
				ycoord2=(double)ytemp2;
				ycoord2=(0.01*ycoord2);
				min2=ycoord2;
			}
			// if (min>uxdiffs[i]) {
			// 	min=uxdiffs[i];
			// 	ytemp=i;
			// 	ycoord=(double)ytemp;
			// 	ycoord=(0.01*ycoord)+2.0;
			// }
		}
		fprintf(fp4, "%g %g %g\n", t, x, min2);
		fprintf(fp5, "%g %g %g\n", t, x, ycoord2);
	}
	fclose (fp4);
	fclose(fp5);
}

// event xmovie (t+=0.1)
// {
//  clear();
//  // cells(lc={0.5,0.5,0.5}, lw=0.5);
//  // draw_vof ("cs", "fs", filled=-1, fc = {1.0,1.0,1.0}, lw=2);
//  squares("u.x", spread=-1, linear=true, map=cool_warm);
//  // cells();
//  save ("xmovie.mp4");
// }

// event ymovie (t+=0.1)
// {
//  clear();
//  // cells(lc={0.5,0.5,0.5}, lw=0.5);
//  // draw_vof ("cs", "fs", filled=-1, fc = {1.0,1.0,1.0}, lw=2);
//  squares("u.y", spread=-1, linear=true, map=cool_warm);
//  // cells();
//  save ("ymovie.mp4");
// }