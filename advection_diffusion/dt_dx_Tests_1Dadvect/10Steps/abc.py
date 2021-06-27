from scipy.signal import gaussian
import numpy as np 
import matplotlib.pyplot as plt 

x = np.linspace(-5, 5, 64)
window = gaussian(64, std=7, sym=False)
plt.plot(window)
plt.show()
