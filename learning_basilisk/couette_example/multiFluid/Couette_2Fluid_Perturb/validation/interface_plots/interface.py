import numpy as np
import matplotlib.pyplot as plt
#fig, axarr = plt.subplots(nrows=3, ncols=4, figsize=(20, 20))
#axarr[-1, -1].axis('off')
#axlist = axarr.flatten()
for i in range(25):
	FILE = 'interfacesLiquid-'+str(i)+'.0.dat'
	OUTFILE = 'interfacesLiquid-'+str(i)+'.0.png'
	print(FILE)
	interf = np.genfromtxt(FILE, delimiter=' ')
	#print(interf)
#	axlist[i-8].plot(interf[:,  0], interf[:, 1])
	plt.plot(interf[:,  0], interf[:, 1])
	plt.savefig(OUTFILE)
#interf = np.genfromtxt('interfacesLiquid-10.0.dat', delimiter=' ')
#plt.plot(interf[:,  0], interf[:, 1])
#plt.show()
