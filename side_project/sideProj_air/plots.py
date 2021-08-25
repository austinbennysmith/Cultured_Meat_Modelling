# -*- coding: utf-8 -*-
# #define FILTERED //RC
# #define mu(f)  (1./(clamp(f,0,1)*(1./mu1 - 1./mu2) + 1./mu2)) //RC
# 
# FILE * fp1;
# 
# // Using axi.h since the flow is axisymmetric.
# // x (horizontal) is the axis about which the rotation occurs
# // y (vertical) is the radial direction
# #include "axi.h"
# #include "navier-stokes/centered.h"
# #include "two-phase.h"
# #include "tension.h"
# #include "view.h"
# // #include "fractions.h"
# 
# // Contact angle stuff didn't work:
# // #include "contact.h"
# 
# // // scalar f[]; * interfaces = {f};
# 
# // vector h[];
# // h.t[right] = contact_angle(90.);
# // h.t[left] = contact_angle(90.);
# 
# #define LEVEL 8 // RC was 4, needs to be bigger to capture the setup
# 
# // Dimensional quantities:
# // Using 2 immisible fluids that have the same properties
# #define rhoWater1 1000.0
# #define rhoWater2 1.225 // density of air, kg/m^3
# #define muWater1 0.001 // 
# #define muWater2 1.81e-5 // viscosity of air
# 
# #define sig 0.0728  //surface tension (twice that you would see between water & air)
# 
# #define refLength 0.2  // height of the domain
# #define refVelocity 0.1  // velocity of the top plate
# 
# // Dimensionless quantities:
# #define rho_ratio (rhoWater2/rhoWater1)
# #define mu_ratio (muWater2/muWater1)
# #define Re (rhoWater1*refVelocity*refLength/muWater1)  // Reynolds number
# #define We (rhoWater1*pow(refVelocity,2)*refLength/sig)
# 
# #define yrim 0.1
# 
# // Boundary Conditions:
# u.n[left] = dirichlet(0.0); // Left inflow
# // u.n[left] = (f[] == 1.0 ? dirichlet(1.0) : dirichlet(0.0))
# // f[left]  = ( y <= yrim ? 1.0 : 0.0 );
# 
# //Right outflow
# u.n[right] = neumann(0.0);
# p[right] = dirichlet(0.0);
# pf[right] = dirichlet(0.0);
# 
# // Free-slip condition on top (Neumann boundary condition du/dx=0, du/dy=0)
# // Don't need to do free slip on bottom due to axisymmetry
# u.n[top] = neumann(0.0);
# u.t[top] = neumann(0.0);
# 
# // Boundary Internal Domain (seems not to work very well on its own)
# bid left_ellipseBound;
# bid right_ellipseBound;
# 
# // No slip along the ellipse:
# u.t[left_ellipseBound] = dirichlet(0.0);
# u.n[left_ellipseBound] = dirichlet(0.0);
# 
# u.t[right_ellipseBound] = dirichlet(0.0);
# u.n[right_ellipseBound] = dirichlet(0.0);
# 
# // Pinning the contact line to the ellipse:
# f[left_ellipseBound] = (y <= yrim ? 1.0 : 0.0);
# f[right_ellipseBound] = (y <= yrim ? 1.0 : 0.0);
# 
# int main() {
#   L0 = 8.;
#   // origin(-L0/2, -0.5);
#   init_grid (1 << LEVEL);
# 
# 	// I rescale the system so that water has unit density, and the oil properties are just defined in terms of water
#   rho1 = 1.0; // water density
#   rho2 = rho_ratio; // oil density
#   mu1 = 1/Re; // water dynamic viscosity
#   mu2 = mu_ratio*mu1; // oil dynamic viscosity
#   f.sigma=1/We; // change this later
# 
#   DT = 1.0e-3; // RC
#   NITERMIN = 1; // default 1
#   NITERMAX = 300; // default 100
#   TOLERANCE = 1e-3; // default 1e-3
# 
#   run();
# }
# 
# event init(t = 0) {
#  
#   // initially velocity is 0 everywhere
#   // foreach () {
#   //   u.x[] = 0.;
#   //   u.y[] = 0.;
#   // }
# 
#   // RC cut the top and bottom of domain
#   // mask (y > 0.5 ? top : none);
#   // mask (y < -0.5 ? bottom : none);
# 
#   // Left Ellipse:
#   // mask (0.3*sq(x) + 2.0*sq(y-2.0) < 0.8 ? bottom : none);
#   // Right Ellipse:
#   // mask (0.3*sq(x-8.0) + 2.0*sq(y-2.0) < 0.8 ? bottom : none);
# 
#   // mask(sq(x)+sq(y)<0.5);
#   
#   fraction (f, y-2.0);
# }
# 
# scalar left_ellipse[];
# event left_ellipseFlow (i++) {
#   fraction (left_ellipse, -(0.3*sq(x) + 2.0*sq(y-2.0) - 1.0));
#   foreach() {
#     foreach_dimension() {
#       u.x[] = (1. - left_ellipse[])*u.x[];
#       u.y[] = (1. - left_ellipse[])*u.y[];
#     }
#   }
#   boundary ((scalar *){u});
# }
# 
# scalar right_ellipse[];
# event right_ellipseFlow (i++) {
#   fraction (right_ellipse, -(0.3*sq(x-8.0) + 2.0*sq(y-2.0) - 1.0));
#   foreach() {
#     foreach_dimension() {
#       u.x[] = (1. - right_ellipse[])*u.x[];
#       u.y[] = (1. - right_ellipse[])*u.y[];
#     }
#   }
#   boundary ((scalar *){u});
# }
# 
# event adapt(i++)
# {
#   // Going fast to get video editing working:
#   adapt_wavelet((scalar *){f, u.x, u.y}, (double[]){1e-5, 1e-2, 1e-2}, LEVEL, 4);
# }
# 
# event end (t = 100) { // RC restricted to 400
#   printf ("i = %d t = %g\n", i, t);
# }
# 
# event gfsview (t += 1.0) { // RC
#     char name_gfs[200];
#     sprintf(name_gfs,"Slice-%0.1f.gfs",t);
# 
#     FILE* fp_gfs = fopen (name_gfs, "w");
#     output_gfs(fp_gfs);
#     fclose(fp_gfs);
# }
# 
# event xmovie (t+=1.0, t<=100.0)
# {
#  // view (fov=9, width=800, height=350);
#  clear();
#  // cells(lc={0.5,0.5,0.5}, lw=0.5);
#  squares("u.x", spread=-1, linear=true, map=cool_warm);
#  draw_vof ("f", fc = {0.0,0.0,0.0}, lw=2);
#  // draw_vof("left_ellipse", lc = {0.0,0.0,0.0}, lw=2);
#  // cells();
#  save ("xmovie.mp4");
# }
# 
# event ymovie (t+=1.0, t<=100.0)
# {
#  // view (fov=9, width=800, height=350);
#  clear();
#  squares("u.y", spread=-1, linear=true, map=cool_warm);
#  draw_vof ("f", lc = {0.0,0.0,0.0}, lw=2);
#  // draw_vof("left_ellipse", lc = {0.0,0.0,0.0}, lw=2);
#  // draw_vof("circle", lc = {0.0,0.0,0.0}, lw=2);
#  // cells(); // Movie is black when this line is included
#  save ("ymovie.mp4");
# }
