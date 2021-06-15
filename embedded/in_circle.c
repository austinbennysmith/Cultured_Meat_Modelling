#include "embed.h"
#include "navier-stokes/centered.h"
#include "view.h"

#define LEVEL 9

#define rhoWater 1000.0 //kg m^-3
#define muWater 0.001

#define refLength 0.1 // Radius of cylinder
#define refVelocity 0.1

#define Re (rhoWater*refVelocity*refLength/muWater)  // Reynolds number

FILE * fp_params;

FILE * fp_stats;

// Top & bottom Free-Slip condition (Neumann boundary condition du/dx=0, du/dy=0)
// u.n[top] = neumann(0.0);
// u.t[top] = neumann(0.0);

// u.n[bottom] = neumann(0.0);
// u.t[bottom] = neumann(0.0);

// Left inflow
// u.n[left] = dirichlet(0.0);

// // Right outflow
// u.n[right] = neumann(0.0);
// p[right] = dirichlet(0.0);
// pf[right] = dirichlet(0.0);

// No slip on the cylinder
u.n[embed] = dirichlet(1.0);
u.t[embed] = dirichlet(1.0);

face vector muv[];

int main() {
	// periodic(right);
	// L0=8.0;
	init_grid(1<<LEVEL);
	mu=muv;
	// const face vector muc[] = {1./Re, 1./Re};
	// mu=muc;

	
	// size(16.);
	// origin(-3, -L0/2.);
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

	// fprintf(fp_params, "mu1: %g %g\n", mu.x, mu.y);
	// fprintf(fp_params, "refLength: %g \n", refLength);
	// fprintf(fp_params, "refVelocity: %g \n", refVelocity);
	fprintf(fp_params, "Reynolds Number: %g \n", Re);
	fclose(fp_params);

	run();

	fclose(fp_stats);
}

event init(t=0) {
	mask (y > 1.0 ? top : none);
    mask (y < 0.0 ? bottom : none);
	
	vertex scalar phi[];
	foreach_vertex()
		phi[]=-(x-4.0)*(x-4.0)-(y-0.5)*(y-0.5)+sq(0.1);
	boundary({phi});
	fractions(phi, cs, fs);
}

// event adapt (i++) {
// 	adapt_wavelet ((scalar *){cs, u.x, u.y}, (double[]){1e-3, 1e-2, 1e-2}, 9, 4)
// }

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