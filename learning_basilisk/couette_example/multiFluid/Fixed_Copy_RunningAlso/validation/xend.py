import matplotlib.pyplot as plt
import numpy as np
xprof = np.genfromtxt("xprofALL.txt", delimiter=" ")
print(xprof.shape)
endArray = xprof[-100:, :]
print(endArray)
plt.plot(endArray[:, 1], endArray[:, 2])
plt.show()
