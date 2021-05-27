import numpy as np 
import matplotlib.pyplot as plt 

Ythreads1 = np.genfromtxt("2Couette_1Thread/yprof")
Ythreads4 = np.genfromtxt("2Couette_4Threads/yprof")

mask1=Ythreads1[:, 0]==max(Ythreads1[:, 0])
mask4=Ythreads4[:, 0]==max(Ythreads4[:, 0])
endArray1 = Ythreads1[mask1, :]
endArray4 = Ythreads4[mask4, :]

ANALYTICAL=[]
for i in range(801):
	ANALYTICAL.append(0)
ANALYTICAL=np.array(ANALYTICAL)
DIFF1=[np.linalg.norm(endArray1[i, 2]-ANALYTICAL[i]) for i in range(len(ANALYTICAL))]
DIFF4=[np.linalg.norm(endArray4[i, 2]-ANALYTICAL[i]) for i in range(len(ANALYTICAL))]

fig, axarr = plt.subplots(nrows=2, ncols=1, figsize=(20, 20))
axlist=axarr.flatten()
axlist[0].plot(endArray1[:, 1], ANALYTICAL, ':', color='k', label='Analytical', zorder=3)
axlist[0].axvline(0.3, c='r', label='Interface: y=0.3')
axlist[0].plot(endArray1[:, 1], Ythreads1[-801:, 2], label='1 thread numerical', lw=2)
axlist[0].plot(endArray1[:, 1], Ythreads4[-801:, 2], '-.', label='4 threads numerical')
axlist[0].legend()
axlist[0].set_xlabel('y')
axlist[0].set_ylabel('Velocity')
axlist[0].set_title('Analytical & Numerical Solutions')
axlist[1].plot(endArray1[:, 1], DIFF1, label="u.y_1t-analytical")
axlist[1].plot(endArray1[:, 1], DIFF4, '-.', label="u.y_4t-analytical")
axlist[1].axvline(0.3, c='r', label='Interface: y=0.3')
axlist[1].legend()
axlist[1].set_xlabel('y')
axlist[1].set_ylabel('Norm (Numerical-Analytical)')
axlist[1].set_title("Norms between Analytical & Numerical Solutions")
plt.show()