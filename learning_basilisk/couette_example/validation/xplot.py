import matplotlib.pyplot as plt
import numpy as np
xprof = np.genfromtxt("xprof5.txt", delimiter=" ")
print("xprof shape:", xprof.shape)
a = xprof[:, 1]
print("a", a)
print("a shape:", a.shape)
yvals = xprof[:, 0]
yvalsunique = []
for i in yvals:
	if i not in yvalsunique:
		yvalsunique.append(i)
print("all y vals:", yvalsunique)
print("y vals len", len(yvalsunique))

B = a.reshape(1001, 100)
print(B[:, :])
plt.contourf(B.transpose())
cbar = plt.colorbar()
cbar.set_label("X Velocity")
plt.title("Evolution of x profile over time for Couette flow")
plt.xlabel("Time")
plt.ylabel("Height (y)")
plt.show()
