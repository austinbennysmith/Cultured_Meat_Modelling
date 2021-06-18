import numpy as np 
import matplotlib.pyplot as plt 

FILE = 'tempy'
FILE2 = 'tempy2'
tempy = np.genfromtxt(FILE, delimiter=" ")
tempy2 = np.genfromtxt(FILE2, delimiter=" ")
t=67
mask = tempy[:, 0]==t # for example
mask2 = tempy2[:, 0]==t
platerange=np.linspace(2.5, 10, 5)
plate=[2.0 for i in range(5)]
plt.plot(tempy[mask, 1], tempy[mask, 2], color='green', label='u=0.99 (Boundary Layer Edge)')
plt.plot(tempy2[mask, 1], tempy2[mask, 2], color='green')
plt.plot(platerange, plate, label='plate', color='red')
plt.ylim([0, 4])
plt.xlim([0, 10])
plt.title("Edges of Boundary Layer, t="+str(t))
plt.xlabel('X')
plt.ylabel('Y')
plt.legend()
plt.show()

# fig, axarr = plt.subplots(nrows=5, ncols=5, figsize=(40, 40))
# axlist = axarr.flatten()