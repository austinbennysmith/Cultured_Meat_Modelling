import matplotlib.pyplot as plt
import numpy as np
yprof = np.genfromtxt("yprof.txt", delimiter=" ")
print(yprof)
for i in range(len(yprof)):
	if yprof[i, 0]==4:
		yprofnew = np.delete(yprof, (i), axis=0)
yprof = yprofnew
print("yprof shape:", yprof.shape)
a = yprof[:, 1]
print("a", a)
print("a shape:", a.shape)
xvals = yprof[:, 0]
xvalsunique = []
for i in xvals:
        if i not in xvalsunique:
                xvalsunique.append(i)
print("all x vals:", xvalsunique)
print("x vals len", len(xvalsunique))

B = a.reshape(1001, 801)
print(B[:, :])
plt.contourf(B.transpose())
cbar = plt.colorbar()
cbar.set_label("Y Velocity")
plt.title("Evolution of y profile over time for Couette flow")
plt.xlabel("Time")
plt.ylabel("Height (x)")
plt.show()
