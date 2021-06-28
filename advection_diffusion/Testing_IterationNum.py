## This code was written in the process of developing DiffAnalytic.py, which plots analytical solutions to the heat equation with periodic boundary conditions at various time steps.
## The analytical solution involves infinite sums, which I must approximate.
## Here I plot the sums for increasing numbers of iterations, to find out how many terms I need to sum up to get something approximating what I want.
## It looks like 10 iterations is more than enough.
import numpy as np 
import matplotlib.pyplot as plt 
from scipy.integrate import quad

X = np.linspace(-5, 5, 1000)
def A0integrand(x):
	return (1/10)*np.exp(-np.square(x))
def Aintegrand(x, n):
	return (1/5)*np.exp(-np.square(x))*np.cos((n*np.pi*x)/5)
def Bintegrand(x, n):
	return (1/5)*np.exp(-np.square(x))*np.sin((n*np.pi*x)/5)

# The Analytical Solution approximated here is based on Example 5 here: https://tutorial.math.lamar.edu/classes/de/solvingheatequation.aspx
# Note that it seems for this initial condition, the B term contributes nothing since all the Bns are 0 due to symmetry.
# Getting A0 (has to be found separately from the other An)
t = 1
for Max in range(2, 6):
	I0 = quad(A0integrand, -5, 5)
	A0 = I0[0]
	# Initializing the array that will be iteratively added to:
	Asum = A0*np.cos((0*np.pi*X)/5)*np.exp(-t*np.square((0*np.pi)/5))
	Bsum = np.zeros(1000)
# print(Asum)

# AnLIST = []
	for n in range(1, Max): # Ideally this would be done for infinite steps. However, the sum converges I think (An decreases monotonically, can be checked by plotting it) so it should be a dcent approximation for a sufficiently small number of steps
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
	# print(IAnLIST)
	# plt.plot(AnLIST)
	plt.plot(X, SUM, label=str(Max))
plt.legend()
plt.show()