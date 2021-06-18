import numpy as np 
import matplotlib.pyplot as plt 

SOL = np.genfromtxt("graph.txt", delimiter=" ")

DATA = np.genfromtxt("xprofABOVE", delimiter=" ")
tend = 72
mask = DATA[:, 0]==tend
DATA = DATA[mask, :]
x = 2.7
U = 1.0
mu = 0.001 # Water viscosity
rho = 1000.0 # Water density
v = mu/rho # Kinematic viscosity
y = DATA[:, 1] - 2.0
print("Y shape", y.shape)
print(y)
eta = y*np.sqrt(U/(v*x))
u = DATA[:, 2]
fprime = u/U

etaMask=eta[:]<100
eta = eta[etaMask]/10
fprime = fprime[etaMask]
plt.scatter(eta, fprime)

plt.plot(SOL[:, 0], SOL[:, 1], label="Similarity solution")
plt.xlabel('eta = y(U/v x)^(1/2)')
plt.ylabel("f'(eta) = u/U")
plt.legend()
plt.show()