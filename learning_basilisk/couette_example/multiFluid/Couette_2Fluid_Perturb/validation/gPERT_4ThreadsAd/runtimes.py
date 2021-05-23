import numpy as np
import matplotlib.pyplot as plt
logstats = np.genfromtxt('logstats.dat', delimiter=' ', comments=None)
print("logstats shape:", logstats.shape)
# The file is generated with some columns having text. I just want the columns with actual numbers, so I delete unnecessary ones below:
print(logstats)
# for col in range(len(logstats[0, :])):
# 	if any(isinstance(x, nan) for x in logstats[:, col]):
# 		np.delete(logstats, col, 1) # Deleting the column with string-type elements

logstats = logstats[:, ~np.all(np.isnan(logstats), axis=0)]
speedup = logstats[:, -1]/logstats[:, -2]
plt.plot(speedup)
plt.title("Ratio of CPU time to Wall Clock time")
plt.xlabel("Simulation time") # Clearer way to label?
plt.ylabel("CPU time/Wall clock time")
plt.show()