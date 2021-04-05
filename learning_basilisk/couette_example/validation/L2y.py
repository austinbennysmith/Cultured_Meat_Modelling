import matplotlib.pyplot as plt
import numpy as np
yprof = np.genfromtxt("yprof5.txt", delimiter=" ")
#print(yprof)
steady = yprof[-802:, 1]
#print("steady:", steady)
theoretical = np.zeros(802)
#print("lengths:", len(steady), len(theoretical))
#print("theoretical:", theoretical)
error = np.linalg.norm(steady-theoretical)
print("error:", error)
