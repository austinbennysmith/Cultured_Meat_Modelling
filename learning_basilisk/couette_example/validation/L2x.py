import matplotlib.pyplot as plt
import numpy as np
xprof = np.genfromtxt("xprof2.txt", delimiter=" ")
print(xprof)
steady = xprof[-100:, 1]
print("computed:", len(steady))
print("computed:", steady)
theoretical = np.linspace(0, 1, 101)
theoretical = theoretical[:-1]
print(theoretical)
#print("theoretical:", theoretical)
#print("theoretical:", len(theoretical))
error = np.linalg.norm(steady-theoretical)
print("error:", error)
#other = np.linspace(-0.5, 0.5, 101)
#print(other)
