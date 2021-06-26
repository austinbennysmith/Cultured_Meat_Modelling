import numpy as np 
import matplotlib.pyplot as plt
from scipy.stats import norm
from scipy.optimize import curve_fit

def gaussian(x, a, b, c):
	return a*np.exp(-np.power(x-b, 2)/(2*np.power(c, 2)))

def linear (x, m):
	return 0.5+m*x

FILE = input("FILENAME?")
CHOICE = input("For gaussians, type 1. For variace plot, type 2.")
CHOICE = int(CHOICE)
myarray = np.genfromtxt(FILE, delimiter=' ')

mask = myarray[:, 2]==0
domainSize = len(myarray[mask, :])
dt = myarray[domainSize+1, 3]

VARIANCElist = []
TIMElist = []

for i in range(0, int(myarray.shape[0]/domainSize), int(1/dt)): # If doing fig, ax, either reorganize somehow or subtract 1 from the second argument
	myarrayNOW = myarray[i*domainSize:(i+1)*domainSize, :]
	myarrayNOW = myarrayNOW[myarrayNOW[:, 0].argsort()]

	# Here I fit a guassian curve to the data to find out what the variance is:
	pars, cov = curve_fit(f=gaussian, xdata=myarrayNOW[:, 0], ydata=myarrayNOW[:, 1], p0=[0.2, 0.2, 0.2], bounds =  (-np.inf, np.inf))
	# Appending the variance to my list of variances so that I can graph the linear increase in variance against time:
	VARIANCElist.append(pars[2]) # pars[2] is the variance since c, the [2] parameter in the gaussian() function defined earlier, is the variance in the gaussian equation.
	# Appending the current time to the TIMElist:
	TIMElist.append(myarrayNOW[0, 3])

	if CHOICE == 1:
		# Plotting the gaussian fit
		plt.plot(myarrayNOW[:, 0], gaussian(myarrayNOW[:, 0], pars[0], pars[1], pars[2]), '.')
		# Plotting the actual data, which should match the gaussian fit pretty closely:
		plt.plot(myarrayNOW[:, 0], myarrayNOW[:, 1], label="t="+str(myarrayNOW[0, 3])+", var="+str(round(pars[2], 2)))

	#NOTE: if the simulations runs long enough, the data starts to be basically a line rather than a gaussian.
	# If this happens, the gaussian fit probably won't produce good results for the variance.
	# In such cases, it may be helpful to test for the variance and break at a certain point if the variance gets too high.
	# if pars[2]>5:
	# 	break
if CHOICE == 2:
	VARIANCElist = np.array(VARIANCElist)
	TIMElist = np.array(TIMElist)
	linPAR, linCOV = curve_fit(linear, TIMElist, VARIANCElist)
	# Here I plot the linear increase in variance as well as a best-fit line that gives the slope. The slope should roughly equal the diffusion coefficient.
	plt.plot(TIMElist, linear(TIMElist, linPAR[0]), label="Fit: y="+str(round(linPAR[0], 2))+"x+0.5")
	# Here I plot the actual data:
	plt.plot(TIMElist, VARIANCElist, label='Data')
	plt.title("Variance vs Time")
	plt.xlabel("Time")
	plt.ylabel("Variance")
if CHOICE ==1:
	plt.title("Change in Gaussian over time")
	plt.xlabel("x (spatial domain)")
	plt.ylabel("T (function value)")
# Unrelated stuff that I was playing with for a while:
# x_values = np.arange(-5, 5, 0.1)
# a = [1, 0.75, 0.5, 0.25, 0]
# for i in a:
# 	y_values = norm(0, i)
# 	plt.plot(x_values, y_values.pdf(x_values), label=str(i))

# y_values = norm(0, 0.5)
# plt.plot(x_values, y_values.pdf(x_values), label=str(0.5))

# plt.xlim([-2, 2])
# plt.ylim([-1, 1])
plt.legend()
plt.show()