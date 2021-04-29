import matplotlib.pyplot as plt
import numpy as np
xprof = np.genfromtxt("xprof3_5.txt", delimiter=" ")
print(xprof.shape)
endArray = xprof[-100:, :]
horiz = []
for i in range(len(endArray[:, 2])):
	horiz.append(0.3)
print(endArray)
plt.plot(endArray[:, 2], endArray[:, 1])
plt.plot(endArray[:, 2], horiz)
plt.xlabel('x velocity')
plt.ylabel('y')
#plt.title('Velocity profile with beta=0.3')
plt.show()
