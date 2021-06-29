## Here I plot my numerial solution to the heat equation in the top plot, with my analytical solution in the bottom plot.

import numpy as np 
import matplotlib.pyplot as plt 
from scipy.integrate import quad

def A0integrand(x):
	return (1/10)*np.exp(-np.square(x))
def Aintegrand(x, n):
	return (1/5)*np.exp(-np.square(x))*np.cos((n*np.pi*x)/5)
def Bintegrand(x, n):
	return (1/5)*np.exp(-np.square(x))*np.sin((n*np.pi*x)/5)

FILE1 = "dt_-2/diffusion_ALONE/out"
FILE2 = "dt_-3/diffusion_ALONE/out"
FILE3 = "dt_-4/diffusion_ALONE/out"

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

Xanalytical = myarray[mask, 0] # I call it Xanalytical, but really it's x for both the numerical & analytical solutions. I use it for the analytical as well because in order to norm comparisons, the arrays need to be the same length.
print(Xanalytical)

for time in alltimes:
	#Plotting the numerical solution:
	maskNOW = myarray[:, 3]==time
	arrNOW = myarray[maskNOW, :]
	# Xanalytical = arrNOW[:, 0]
	plt.plot(Xanalytical, arrNOW[:, 1], label="Numerical t="+str(time))

	#Plotting the analytical solution:
	# Getting A0 (has to be found separately from the other An)
	I0 = quad(A0integrand, -5, 5)
	A0 = I0[0]
	# Initializing the array that will be iteratively added to:
	Asum = A0*np.cos((0*np.pi*Xanalytical)/5)*np.exp(-time*np.square((0*np.pi)/5))
	Bsum = np.zeros(len(Xanalytical))
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
		Asummand = An*np.cos((n*np.pi*Xanalytical)/5)*np.exp(-time*np.square((n*np.pi)/5))
		Bsummand = Bn*np.sin((n*np.pi*Xanalytical)/5)*np.exp(-time*np.square((n*np.pi)/5))
		
		Asum = Asum+Asummand
		Bsum = Bsum+Bsummand

		SUM = Asum+Bsum
	# print(IAnLIST)
	# plt.plot(AnLIST)
	plt.plot(Xanalytical, SUM, '.', label="Analytical t="+str(time))
plt.title("Heat Equation Numerical & Analytical, dt="+dtstr)
plt.legend()
plt.xlabel("x")
plt.ylabel("T")
plt.show()