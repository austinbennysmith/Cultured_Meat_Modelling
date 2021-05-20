import numpy as np
import matplotlib.pyplot as plt
fig, axarr = plt.subplots(nrows=5, ncols=5, figsize=(40, 40))
axlist = axarr.flatten()
for i in range(0, 100, 4):
	FILE = 'interface_'+str(i)+'.dat'
	# OUTFILE = 'interfacesLiquid-'+str(i)+'.0.png'
	print(FILE)
	interf = np.genfromtxt(FILE, delimiter=' ')
	interf=interf[interf[:, 0].argsort()] # When doing parallel processing, the output gets jumbled. This line sorts the output file so that the x values are in order, which makes the plots look correct.
	print(interf)
	axlist[int(i/4)].plot(interf[:,  0], interf[:, 1], label="t="+str(i))
	axlist[int(i/4)].legend()
	axlist[int(i/4)].set_xlabel("x")
	axlist[int(i/4)].set_ylabel("y")
	# plt.plot(interf[:,  0], interf[:, 1])
	# plt.savefig(OUTFILE)
#interf = np.genfromtxt('interfacesLiquid-10.0.dat', delimiter=' ')
#plt.plot(interf[:,  0], interf[:, 1])
plt.suptitle("2-Fluid Couette Interface Over time")
plt.show()