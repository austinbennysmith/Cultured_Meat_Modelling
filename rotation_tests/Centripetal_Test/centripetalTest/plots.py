# -*- coding: utf-8 -*-
# #include "navier-stokes/centered.h"
# #include "view.h"
# #include "embed.h"
# 
# #define LEVEL 8 // RC was 4, needs to be bigger to capture the setup
# #define Re 100 // Reynolds number
# 
# // bid circle;
# // u.t[circle] = dirichlet(1.0);
# // u.n[circle] = dirichlet(0.0);
# 
# u.n[top] = dirichlet(0.0);
# u.t[top] = dirichlet(1.0);
# 
# u.n[bottom] = dirichlet(0.0);
# u.t[bottom] = dirichlet(0.0);
# 
# // u.n[top] = dirichlet(0.0);
# // u.t[top] = dirichlet(1.0);
# 
# // u.n[top] = dirichlet(0.0);
# // u.t[top] = dirichlet(1.0);
# 
# u.n[embed] = dirichlet(0.0);
# u.t[embed] = dirichlet(0.0);
# 
# int main() {
#   L0 = 8.;
#   origin(-4.0, -4.0);
#   init_grid (1 << LEVEL);
#   periodic(right);
# 
# 	// I rescale the system so that water has unit density, and the oil properties are just defined in terms of water
#   // rho = rhoWater;
#   // mu = muWater; // water dynamic viscosity
# 
#   DT = 1.0e-2; // RC
#   NITERMIN = 1; // default 1
#   NITERMAX = 200; // default 100
#   TOLERANCE = 1e-4; // default 1e-3
# 
#   run();
# }
# 
# event init(t = 0) {
# 	const face vector muc[] = {1./Re,1./Re};
# 	mu=muc;
# 
# 	vertex scalar phi[];
# 	foreach_vertex()
# 		phi[]=sq(x)+sq(y)-sq(0.1);
# 	boundary({phi});
# 	fractions(phi, cs, fs);
# }
# 
# event end (t = 100) { // RC restricted to 400
#   printf ("i = %d t = %g\n", i, t);
# }
