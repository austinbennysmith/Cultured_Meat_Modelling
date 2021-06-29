import numpy as np 
import matplotlib.pyplot as plt 

U = 2.0

FILE1 = "dt_-2/advection_ALONE/out"
FILE2 = "dt_-3/advection_ALONE/out"
FILE3 = "dt_-4/advection_ALONE/out"

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
alltimes = alltimes[::10]

# I want to plot the stuff at 3 points: 1/3 of the duration through, 2/3, and the last time
point0 = alltimes[0]
point1 = alltimes[int(np.floor(len(alltimes)/3))]
point2 = alltimes[int(2*np.floor(len(alltimes)/3))]
point3 = alltimes[-1]
allpoints = [point0, point1, point2, point3]

Xanalytical = myarray[mask, 0]
Yanalytical = np.exp(-(Xanalytical)*(Xanalytical))
allDiffs = []
for time in alltimes:
	maskNOW = myarray[:, 3]==time
	arrNOW = myarray[maskNOW, :]

	distance = U*time
	# print(10-(distance%10))
	# print(Xanalytical[Xanalytical>max(Xanalytical)-(10 - (distance % 10))])
	Yleft = Yanalytical[Xanalytical>=max(Xanalytical)-(10 - (distance % 10))]
	Yright = Yanalytical[Xanalytical<max(Xanalytical)-(10 - (distance % 10))]
	Yall = np.concatenate((Yleft, Yright))

	Diff = np.linalg.norm(Yall-arrNOW[:, 1])
	allDiffs.append(Diff)

allDiffs = np.array(allDiffs)
plt.plot(alltimes, allDiffs, label="dt="+dtstr)
plt.title("Advection Analytical vs Numerical L2 Norm")
plt.xlabel("Time")
plt.ylabel("L2 Norm")
plt.legend()
plt.show()