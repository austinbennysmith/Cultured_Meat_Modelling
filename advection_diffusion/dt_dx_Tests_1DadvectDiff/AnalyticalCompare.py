## Plotting analytical solutions to the advection-diffusion equation.
## This combines the two codes for advection & diffusion analytical solutions.

import numpy as np 
import matplotlib.pyplot as plt 
from scipy.integrate import quad

U = 2.0

FILE1 = "dt_-2/advection_diffusion/out"
FILE2 = "dt_-3/advection_diffusion/out"
FILE3 = "dt_-4/advection_diffusion/out"

CHOICE = int(input("Type 2 for dt=1e-2, 3 for 1e-3, or 4 for 1e-4"))

if CHOICE == 2:
	myarray = np.genfromtxt(FILE1, delimiter=' ')
	dtstr="1e-2"
elif CHOICE == 3:
	myarray = np.genfromtxt(FILE2, delimiter=' ')
	dtstr="1e-3"
elif CHOICE == 4:
	myarray = np.genfromtxt(FILE3, delimiter=' ')
	dtstr="1e-4"

mask = myarray[:, 3] == 0
domainSize = len(myarray[mask, :])

alltimes = np.unique(myarray[:, 3])

X = myarray[mask, 0]

def A0integrand(x):
	return (1/10)*np.exp(-np.square(x))
def Aintegrand(x, n):
	return (1/5)*np.exp(-np.square(x))*np.cos((n*np.pi*x)/5)
def Bintegrand(x, n):
	return (1/5)*np.exp(-np.square(x))*np.sin((n*np.pi*x)/5)

fig, axarr = plt.subplots(nrows=2, ncols=1, figsize=(20, 20))
axlist=axarr.flatten()

for t in range(10):
	# Plotting the numerical data:
	maskNOW = myarray[:, 3] == t
	arrNOW = myarray[maskNOW, :]
	# Xanalytical = arrNOW[:, 0]
	axlist[0].plot(X, arrNOW[:, 1], label="dt="+dtstr+", t="+str(t))

	# Getting A0 (has to be found separately from the other An)
	I0 = quad(A0integrand, -5, 5)
	A0 = I0[0]
	# Initializing the array that will be iteratively added to:
	Asum = A0*np.cos((0*np.pi*X)/5)*np.exp(-t*np.square((0*np.pi)/5))
	Bsum = np.zeros(domainSize)
	# print(Asum)

	# AnLIST = []

	for n in range(1, 20): # Ideally this would be done for infinite steps. However, the sum converges I think (An decreases monotonically, can be checked by plotting it) so it should be a dcent approximation for a sufficiently small number of steps
		IAn = quad(Aintegrand, -5, 5, args=(n))
		An = IAn[0]
		# print("An: ", An)

		IBn = quad(Bintegrand, -5, 5, args=(n))
		Bn = IBn[0]
		# print("Bn: ", Bn)
		# AnLIST.append(An)
		Asummand = An*np.cos((n*np.pi*X)/5)*np.exp(-t*np.square((n*np.pi)/5))
		Bsummand = Bn*np.sin((n*np.pi*X)/5)*np.exp(-t*np.square((n*np.pi)/5))
		
		Asum = Asum+Asummand
		Bsum = Bsum+Bsummand

		SUM = Asum+Bsum
	
	# Shiting the graph by the veolcity * time elapsed:
	distance = U*t
	Yleft = SUM[X>=max(X)-(10 - (distance % 10))]
	Yright = SUM[X<max(X)-(10 - (distance % 10))]
	Yall = np.concatenate((Yleft, Yright))

	axlist[1].plot(X, Yall, label="dt="+dtstr+", t="+str(t))
axlist[1].legend()
axlist[1].set_title("Advection-Diffusion Analytical Solution")
axlist[1].set_xlabel("x")
axlist[1].set_ylabel("T")
axlist[0].legend()
axlist[0].set_title("Advection-Diffusion Numerical Results")
axlist[0].set_xlabel("x")
axlist[0].set_ylabel("T")
plt.show()