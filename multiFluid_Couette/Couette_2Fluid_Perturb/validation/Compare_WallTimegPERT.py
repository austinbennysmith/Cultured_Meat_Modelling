import numpy as np 
import matplotlib.pyplot as plt 

# logstats1 = np.genfromtxt('gPERT_1Thread/logstats.dat', delimiter=' ', comments=None)
# logstats4 = np.genfromtxt('gPERT_4Threads/logstats.dat', delimiter=' ', comments=None)
logstats1 = np.genfromtxt('gPERT_4Threads_noAd/logstats.dat', delimiter=' ', comments=None)
logstats4 = np.genfromtxt('gPERT_4ThreadsAd/logstats.dat', delimiter=' ', comments=None)
logstats1 = logstats1[:, ~np.all(np.isnan(logstats1), axis=0)]
logstats4 = logstats4[:, ~np.all(np.isnan(logstats4), axis=0)]

speedup = logstats1[:, -2]/logstats4[:, -2] # speedup factor is Wall clock time for 4 CPUS divided by wall clock time for 1 CPU
# for i in range(len(speedup)):
# 	if np.isnan(speedup[i])==True:
# 		np.delete(speedup, i)

plt.plot(speedup)
# plt.title("Wall Clock Time Ratio, 1 CPU:4 CPUs")
plt.title("Wall Clock Time Ratio, non-AMR:AMR")
plt.xlabel("Simulation time") # Clearer way to label?
# plt.ylabel("1 CPU Wall Clock Time/4 CPU Wall Clock Time")
plt.ylabel("non-AMR Wall Clock Time/AMR Wall Clock Time")
plt.show()