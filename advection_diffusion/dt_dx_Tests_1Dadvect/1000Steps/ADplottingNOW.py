import numpy as np 
import matplotlib.pyplot as plt 

FILE1 = "dt_-2/advection_ALONE/out"
FILE2 = "dt_-3/advection_ALONE/out"
FILE3 = "dt_-4/advection_ALONE/out"

# myarray1 = np.genfromtxt(FILE1, delimiter=' ')
myarray2 = np.genfromtxt(FILE2, delimiter=' ')
myarray3 = np.genfromtxt(FILE3, delimiter=' ')

arrayLIST = [myarray2, myarray3]
dtstrLIST = []

for arr in arrayLIST:
	if np.array_equal(arr, myarray1)==True:
		dtstr="1e-2"
	elif np.array_equal(arr, myarray2)==True:
		dtstr="1e-3"
	elif np.array_equal(arr, myarray3)==True:
		dtstr="1e-4"
	dtstrLIST.append(dtstr)
	alltimes = np.unique(arr[:, 3])

	mask = arr[:, 2]==0
	domainSize = len(arr[mask, :])
	dt = arr[domainSize+1, 3]

	# I want to plot the stuff at 3 points: 1/3 of the duration through, 2/3, and the last time
	point0 = alltimes[0]
	point1 = alltimes[int(np.floor(len(alltimes)/3))]
	point2 = alltimes[int(2*np.floor(len(alltimes)/3))]
	point3 = alltimes[-1]
	allpoints = [point0, point1, point2, point3]

	for point in allpoints:
		maskNOW = arr[:, 3]==point
		arrNOW = arr[maskNOW, :]
		plt.plot(arrNOW[:, 0], arrNOW[:, 1], label="dt="+dtstr+", t="+str(point))
plt.legend()
plt.title("Comparison: dt="+dtstrLIST[0]+" vs "+dtstrLIST[1])
plt.xlabel("x (domain length)")
plt.ylabel("T (scalar value)")
plt.show()