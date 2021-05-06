import matplotlib.pyplot as plt
import numpy as np
for i in range(7, 11):
	FILE = 'xprofLEVEL'+str(i)+'_noFILTER.txt'
	xprof = np.genfromtxt(FILE, delimiter=" ")
	#print(xprof.shape)
	endArray = xprof[-100:, :]
	horiz = []
	for j in range(len(endArray[:, 2])):
		horiz.append(0.3)
	print(endArray)
	plt.plot(endArray[:, 1], endArray[:, 2], label='LEVEL '+str(i)+' Numerical')
#plt.plot(endArray[:, 2], horiz)
plt.axvline(0.3, c='r', label='Interface: y=0.3')
plt.plot(endArray[:, 1], 1.239669421*(endArray[:, 1]+0.5), ':', label='Analytical: u=1.24(y+0.5)')
plt.plot(endArray[:, 1], 0.041322314*(endArray[:, 1]+0.5)+0.958677686, ':', label='Analytical: u=0.96+0.041(y+0.5)')
plt.xlabel('y')
plt.ylabel('x velocity')
plt.title('Equillibrium X Velocity profile')
plt.legend()
#plt.xlim([0.2, 0.4])
#plt.ylim([0.8, 1.1])
plt.show()
