import numpy as np 
import matplotlib.pyplot as plt
# import statistics as stats
from scipy.stats import norm

FILE = input("FILENAME?")
myarray = np.genfromtxt(FILE, delimiter=' ')

mask = myarray[:, 2]==0
domainSize = len(myarray[mask, :])

VARIANCElist = []
# fig, axarr = plt.subplots(nrows=2, ncols=5, figsize=(40, 40))
# axlist = axarr.flatten()
for i in range(0, int(myarray.shape[0]/domainSize)): # If doing fig, ax, either reorganize somehow or subtract 1 from the second argument
	# interf=interf[interf[:, 0].argsort()] # When doing parallel processing, the output gets jumbled. This line sorts the output file so that the x values are in order, which makes the plots look correct.
	myarrayNOW = myarray[i*domainSize:(i+1)*domainSize, :]
	
	print(myarrayNOW[:, 0])
	n = len(myarrayNOW)
	mean = round(sum(myarrayNOW[:, 1]*myarrayNOW[:, 0])/n, 2)
	deviations = np.array([(i-mean)**2 for i in myarrayNOW[:, 0]])*myarrayNOW[:, 1]
	VARIANCE = np.sqrt(sum(deviations)/n)
	VARIANCElist.append(VARIANCE)


	# pdf = norm.pdf(myarrayNOW[:, 1])
	# prob = pdf/pdf.sum()
	# mu = myarrayNOW[:, 1].dot(prob)
	# mom2 = np.power(myarrayNOW[:, 1], 2).dot(prob)
	# VARIANCE = mom2-mu**2
	# print(VARIANCE)

	plt.scatter(myarrayNOW[:, 0], myarrayNOW[:, 1], label="t="+str(myarrayNOW[0, 2])+", var="+str(VARIANCE))
	print(myarrayNOW)
	# if i==100:
	# 	break
# plt.plot(VARIANCElist)
plt.legend()
plt.show()