import numpy as np
import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation

my_dpi = 144 # https://stackoverflow.com/questions/13714454/specifying-and-saving-a-figure-with-exact-size-in-pixels

Advection_Stability = np.genfromtxt("with_stations_air/advection_stability")
Advection_StabilityOld = np.genfromtxt("with_stations_air/advection_stability")
print(max(Advection_StabilityOld[:, 1]))

print(Advection_Stability.shape)

All_Advect = np.zeros((len(Advection_Stability[:,1]), len(Advection_Stability[:,1])))

# plt.plot(Advection_Stability[:, 0], Advection_Stability[:, 1])
# plt.show()

uniquetimes = []
for i in Advection_Stability[:, 0]:
	if i not in uniquetimes:
		uniquetimes.append(i)
# print(uniquetimes)
uniquetimes = np.array(uniquetimes)

fig, ax = plt.subplots(figsize=(800/my_dpi, 350/my_dpi), dpi=my_dpi)

for time in uniquetimes:
	for time2 in uniquetimes:
		if time2 <= time:
			All_Advect[int(time), int(time2)] = Advection_Stability[int(time2), 1]
		if time2 > time:
			All_Advect[int(time), int(time2)] = np.nan
			# Advection_Stability[int(time), 1] = np.nan
	# All_Advect[int(time), :] = 

# plt.plot(uniquetimes, All_Advect[-1, :])
# plt.xlim([min(uniquetimes), max(uniquetimes)])
# # print(max(Advection_StabilityOld[:, 1]))
# plt.ylim([min(Advection_StabilityOld[:, 1]), max(Advection_StabilityOld[:, 1])])
# plt.show()

# print(All_Advect[3, :])
# ax.plot(uniquetimes, All_Advect[0, :])
def animate(i):
	ax.plot(uniquetimes, All_Advect[i, :], color='k')
anim = FuncAnimation(
	fig, animate, interval=100, frames=len(uniquetimes))
plt.draw()
plt.xlim([min(uniquetimes), max(uniquetimes)])
# # print(max(Advection_StabilityOld[:, 1]))
plt.ylim([min(Advection_StabilityOld[:, 1]), max(Advection_StabilityOld[:, 1])])
plt.xlabel('Dimensionless Time')
plt.ylabel('Umax*dt/dx')
plt.title('Advection Stability Criterion')
anim.save("graphy.mp4", dpi=my_dpi)
plt.show()