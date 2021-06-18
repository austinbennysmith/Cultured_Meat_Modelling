import matplotlib.pyplot as plt 
import numpy as np 

FILE = input("FILENAME?")
myarray = np.genfromtxt(FILE, delimiter=' ')

for i in range(100):
	mask1 = myarray[:, 0]==i
	myarray2 = myarray[mask1, :]
	mask2 = myarray2[:, 2]<100
	myarray2 = myarray2[mask2, :]
	mask3 = myarray2[:, 2]>-100
	myarray2 = myarray2[mask3, :]
	domainSize = len(myarray2[:, :])

	plt.plot(myarray2[:, 1], myarray2[:, 2], label=str(i))
plt.legend()
plt.show()