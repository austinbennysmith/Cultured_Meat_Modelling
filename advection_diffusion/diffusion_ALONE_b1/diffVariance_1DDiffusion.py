import numpy as np 
import matplotlib.pyplot as plt
# import statistics as stats
from scipy.stats import norm
from scipy.optimize import curve_fit
# from scipy import asarray as ar,exp

def gaussian(x, a, b, c):
	return a*np.exp(-np.power(x-b, 2)/(2*np.power(c, 2)))

# def gaussian(x, sigma, mu):
# 	return (1/(sigma*np.sqrt(2*pi)))*np.exp(-0.5*((x-mu)/sigma)**2)

FILE = input("FILENAME?")
myarray = np.genfromtxt(FILE, delimiter=' ')

mask = myarray[:, 2]==0
domainSize = len(myarray[mask, :])

VARIANCElist = []
# fig, axarr = plt.subplots(nrows=2, ncols=5, figsize=(40, 40))
# axlist = axarr.flatten()
for i in range(0, int(myarray.shape[0]/domainSize), 100): # If doing fig, ax, either reorganize somehow or subtract 1 from the second argument
	myarrayNOW = myarray[i*domainSize:(i+1)*domainSize, :]
	myarrayNOW = myarrayNOW[myarrayNOW[:, 0].argsort()]

	pars, cov = curve_fit(f=gaussian, xdata=myarrayNOW[:, 0], ydata=myarrayNOW[:, 1], p0=[0.2, 0.2, 0.2], bounds =  (-np.inf, np.inf))
	xar = np.linspace(-5, 5, 100)
	VARIANCElist.append(pars[2])
	# plt.plot(myarrayNOW[:, 0], gaussian(myarrayNOW[:, 0], pars[0], pars[1], pars[2]), '.')


	# plt.plot(myarrayNOW[:, 0], myarrayNOW[:, 1], label="t="+str(myarrayNOW[0, 2])+", var="+str(pars[2]))
	# print(myarrayNOW)
	# if i==100:
	# 	break
plt.plot(VARIANCElist)

x_values = np.arange(-5, 5, 0.1)
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