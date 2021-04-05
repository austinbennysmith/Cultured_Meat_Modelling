import matplotlib.pyplot as plt
import numpy as np
level=[]
errors = []
for i in range(2, 8):
	level.append(i)
	filename = "yprof%d.txt" %i
	yprof = np.genfromtxt(filename, delimiter=" ")
	#print(xprof)
	steady = yprof[-802:, 1]
	#print("computed:", len(steady))
	#print("computed:", steady)
	theoretical = np.zeros(802)
	#print(theoretical)
	#print("theoretical:", theoretical)
	#print("theoretical:", len(theoretical))
	error = np.linalg.norm(steady-theoretical)
	#print("error:", error)
	#other = np.linspace(-0.5, 0.5, 101)
	#print(other)
	errors.append(error)
print(errors)
plt.semilogy(level,errors)
plt.title("Error vs Mesh Refinement")
plt.xlabel("Level")
plt.ylabel("L2 Norm")
plt.show()
