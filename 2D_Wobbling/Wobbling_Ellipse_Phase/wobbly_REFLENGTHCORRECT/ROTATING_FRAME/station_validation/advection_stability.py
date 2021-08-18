import numpy as np 
import matplotlib.pyplot as plt 

uxmax = np.genfromtxt("with_stations_air/ux_max")
uymax = np.genfromtxt("with_stations_air/uy_max")
UMAX = np.genfromtxt("with_stations_air/UMAX")
Advection_Stability = np.genfromtxt("with_stations_air/advection_stability")

fig, ax = plt.subplots(nrows=2, ncols=2, figsize=(20, 20))
axlist = ax.flatten()

axlist[0].plot(uxmax[:, 0], uxmax[:, 1])
axlist[0].set_xlabel('Dimensionless Time')
axlist[0].set_ylabel('Max. Horizontal Velocity')
axlist[0].set_title('Max. Horizontal Velocity vs Time')

axlist[1].plot(uymax[:, 0], uymax[:, 1])
axlist[1].set_xlabel('Dimensionless Time')
axlist[1].set_ylabel('Max. Vertical Velocity')
axlist[1].set_title('Max. Vertical Velocity vs Time')

axlist[2].plot(UMAX[:, 0], UMAX[:, 1])
axlist[2].set_xlabel('Dimensionless Time')
axlist[2].set_ylabel('Max. Velocity Magnitude (Umax)')
axlist[2].set_title('Max. Velocity Magnitude vs Time')

axlist[3].plot(Advection_Stability[:, 0], Advection_Stability[:, 1])
axlist[3].set_xlabel('Dimensionless Time')
axlist[3].set_ylabel('Umax*dt/dx')
axlist[3].set_title('Advection Stability (CFL) Condition vs Time')

plt.savefig('advection_stability.png')
plt.show()