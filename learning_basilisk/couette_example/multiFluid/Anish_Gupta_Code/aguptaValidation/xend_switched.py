import matplotlib.pyplot as plt
import numpy as np
FILE = raw_input("File name?")
xprof = np.genfromtxt(FILE, delimiter=" ")
print(xprof.shape)
endArray = xprof[-100:, :]
horiz = []
for i in range(len(endArray[:, 2])):
	horiz.append(0.3)
print(endArray)
plt.plot(endArray[:, 1], endArray[:, 2])
#plt.plot(endArray[:, 2], horiz)
plt.axvline(0.3)
plt.plot(endArray[:, 1], 1.244*(endArray[:, 1]+0.5), ':')
plt.plot(endArray[:, 1], 0.0226*(endArray[:, 1]+0.5)+0.977369, ':')
plt.xlabel('y')
plt.ylabel('x velocity')
plt.title('Equillibrium X Velocity profile with beta=0.3')
plt.show()
