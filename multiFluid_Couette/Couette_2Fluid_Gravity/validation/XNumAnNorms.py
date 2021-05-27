import numpy as np 
import matplotlib.pyplot as plt 

Xthreads1 = np.genfromtxt("2Couette_1Thread/xprof")
Xthreads4 = np.genfromtxt("2Couette_4Threads/xprof")
# Ythreads1 = np.genfromtxt("2Couette_1Thread/yprof")
# Ythreads4 = np.genfromtxt("2Couette_4Threads/yprof")

# FILE = input("File name?")
# xprof = np.genfromtxt(FILE, delimiter=" ")
# print(xprof.shape)
endArray1 = Xthreads1[-100:, :]
endArray4 = Xthreads4[-100:, :]
# horiz = []
# for i in range(len(endArray[:, 2])):
# 	horiz.append(0.3)
# print(endArray)
# plt.plot(endArray[:, 1], endArray[:, 2], label='Numerically computed steady state')
#plt.plot(endArray[:, 2], horiz)

botLine=1.239669421*(endArray1[:, 1]+0.5)
topLine=0.041322314*(endArray1[:, 1]+0.5)+0.958677686
mask1=botLine[:]<topLine[:]
mask2=topLine[:]<botLine[:]
botLineSHORT=botLine[mask1]
topLineSHORT=topLine[mask2]
ANALYTICAL=np.concatenate((botLineSHORT, topLineSHORT), axis=0)
DIFF1=[np.linalg.norm(endArray1[i, 2]-ANALYTICAL[i]) for i in range(len(ANALYTICAL))]
DIFF4=[np.linalg.norm(endArray4[i, 2]-ANALYTICAL[i]) for i in range(len(ANALYTICAL))]
# print(ANALYTICAL.shape)
# print(botLine.shape)
# print(topLine.shape)

# plt.axvline(0.3, c='r', label='Interface: y=0.3')
# plt.plot(endArray[:, 1], 1.239669421*(endArray[:, 1]+0.5), ':', label='Analytical: u=1.24(y+0.5)')
# plt.plot(endArray[:, 1], 0.041322314*(endArray[:, 1]+0.5)+0.958677686, ':', label='Analytical: u=0.96+0.041(y+0.5)')

# plt.plot(endArray[:, 1], botLine, ':', label='Analytical: u=1.24(y+0.5)')
# plt.plot(endArray[:, 1], topLine, ':', label='Analytical: u=0.96+0.041(y+0.5)')
# plt.plot(endArray[:, 1], ANALYTICAL, ':', label='Analytical')
# plt.xlabel('y')
# plt.ylabel('x velocity')
# plt.title('Equillibrium X Velocity profile')
# plt.legend()
# plt.show()

fig, axarr = plt.subplots(nrows=2, ncols=1, figsize=(20, 20))
axlist=axarr.flatten()
axlist[0].plot(endArray1[:, 1], ANALYTICAL, ':', color='k', label='Analytical', zorder=3)
axlist[0].axvline(0.3, c='r', label='Interface: y=0.3')
axlist[0].plot(endArray1[:, 1], Xthreads1[-100:, 2], label='1 thread numerical', lw=2)
axlist[0].plot(endArray1[:, 1], Xthreads4[-100:, 2], '-.', label='4 threads numerical')
axlist[0].legend()
axlist[0].set_xlabel('x')
axlist[0].set_ylabel('Velocity')
axlist[0].set_title('Analytical & Numerical Solutions')
axlist[1].plot(endArray1[:, 1], DIFF1, label="u.x_1t-analytical")
axlist[1].plot(endArray1[:, 1], DIFF4, '-.', label="u.x_4t-analytical")
axlist[1].axvline(0.3, c='r', label='Interface: y=0.3')
axlist[1].legend()
axlist[1].set_xlabel('x')
axlist[1].set_ylabel('L2 Norm (Numerical-Analytical)')
axlist[1].set_title("Norms between Analytical & Numerical Solutions")
plt.show()