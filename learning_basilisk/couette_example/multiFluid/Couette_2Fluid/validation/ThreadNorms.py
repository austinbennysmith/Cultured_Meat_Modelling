import numpy as np 
import matplotlib.pyplot as plt 
Xthreads1 = np.genfromtxt("2Couette_1Thread/xprof")
Xthreads4 = np.genfromtxt("2Couette_4Threads/xprof")
XdiffArr = []
for i in range(int(Xthreads1.shape[0]/100)):
	Xmask1=Xthreads1[:, 0]==i
	Xmask4=Xthreads4[:, 0]==i
	Xthreads1Now=Xthreads1[Xmask1, :]
	Xthreads4Now=Xthreads4[Xmask4, :]
	Xdiff = np.linalg.norm(Xthreads4Now-Xthreads1Now)
	XdiffArr.append(Xdiff)

Ythreads1 = np.genfromtxt("2Couette_1Thread/yprof")
Ythreads4 = np.genfromtxt("2Couette_4Threads/yprof")
unique = []

print(len(Ythreads1[:, 0]))
for i in Ythreads1[:, 0]:
	if i not in unique:
		unique.append(i)
print(unique)

YdiffArr = []
for i in unique:
	Ymask1=Ythreads1[:, 0]==i
	Ymask4=Ythreads4[:, 0]==i
	Ythreads1Now=Ythreads1[Ymask1, :]
	Ythreads4Now=Ythreads4[Ymask4, :]
	Ydiff = np.linalg.norm(Ythreads4Now-Ythreads1Now)
	YdiffArr.append(Ydiff)

plt.plot(XdiffArr, label="u.x norm")
plt.plot(YdiffArr, label="u.y norm")
plt.title("1 vs 4 Threads L2 Velocity Norms")
plt.xlabel("Time")
plt.ylabel("L2 Norm")
plt.legend()
plt.show()
print(XdiffArr)