import matplotlib.pyplot as plt
import numpy as np
# when Oscar moves to Python 3 the following line will have to use input() instead of raw_input().
FILE = raw_input("Which file?")
xprof = np.genfromtxt(FILE, delimiter=" ")
print("xprof shape:", xprof.shape)
#xprof = xprof[:25000, :]
a = xprof[:, 2]
print("a", a)
print("a shape:", a.shape)
yvals = xprof[:, 1]
yvalsunique = []
for i in yvals:
	if i not in yvalsunique:
		yvalsunique.append(i)
print("all y vals:", yvalsunique)
print("y vals len", len(yvalsunique))
B = a.reshape(len(xprof)/100, 100)
print(B[:, :])
fig, ax = plt.subplots(1, 1)
SpaceArr = np.linspace(-0.5, 0.49, 100)
print('LENGTH:', len(xprof)/100)
print('MAX:', max(xprof[:, 0]))
TimeArr = np.linspace(0, max(xprof[:, 0]), len(xprof)/100)
line = []
for i in range(len(TimeArr)):
	line.append(0.3)
cax = ax.contourf(TimeArr, SpaceArr, B.transpose(), 100)
ax.plot(TimeArr, line, 'w')
cbar = fig.colorbar(cax)
cbar.set_label("X Velocity")
ax.set_title("Evolution of x profile over time for Couette flow")
ax.set_xlabel("Time")
ax.set_ylabel("Height (y)")
plt.show()
