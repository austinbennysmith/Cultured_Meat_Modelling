import numpy as np 
import matplotlib.pyplot as plt 

SOL = np.genfromtxt("graph.txt", delimiter=" ")

DATA = np.genfromtxt("xprof", delimiter=" ")
tend = 400
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

etaMask = np.logical_and(eta[:]<=205, eta[:]>=100)
eta2 = (eta[etaMask]-110)/10
fprime2 = fprime[etaMask]

# plt.plot(eta, fprime)
# plt.plot(eta[:round(0.25*len(eta))], fprime[:round(0.25*len(eta))])
plt.plot(eta2, fprime2, label='Numerical results')

plt.plot(SOL[:, 0], SOL[:, 1], label="Similarity solution")
plt.xlabel('eta = y(U/u x)^(1/2)')
plt.ylabel("f'(eta) = u/U")
plt.legend()
plt.title("Blasius Boundary Layer")
plt.show()