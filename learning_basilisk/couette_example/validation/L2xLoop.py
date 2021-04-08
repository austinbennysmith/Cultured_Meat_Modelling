import matplotlib.pyplot as plt
import numpy as np
level=[]
errors = []
for i in range(2, 8):
	level.append(i)
	filename = "xprof%d.txt" %i
	xprof = np.genfromtxt(filename, delimiter=" ")
	#print(xprof)
	steady = xprof[-100:, 1]
	#print("computed:", len(steady))
	#print("computed:", steady)
	theoretical = np.linspace(0, 1, 101)
	theoretical = theoretical[:-1]
	#print(theoretical)
	#print("theoretical:", theoretical)
	#print("theoretical:", len(theoretical))
	error = np.linalg.norm(steady-theoretical)
	#print("error:", error)
	#other = np.linspace(-0.5, 0.5, 101)
	#print(other)
	errors.append(error)
print(errors)
plt.semilogy(level[1:],errors[1:], label='DATA')

Apoint1=[level[1], errors[1]]
Apoint2=[level[-1], errors[-1]]
Axvals=[Apoint1[0], Apoint2[0]]
Ayvals=[Apoint1[1], Apoint2[1]]
Aslope=(Apoint2[1]-Apoint1[1])/(Apoint2[0]-Apoint1[0])
plt.plot(Axvals, Ayvals, label='Whole plot Fit (slope='+str(Aslope)+')')

Bpoint1=[level[1], errors[1]]
Bpoint2=[level[2], errors[2]]
Bxvals=[Bpoint1[0], Bpoint2[0]]
Byvals=[Bpoint1[1], Bpoint2[1]]
Bslope=(Bpoint2[1]-Bpoint1[1])/(Bpoint2[0]-Bpoint1[0])
plt.plot(Bxvals, Byvals, label='Beginning plot Fit (slope='+str(Bslope)+')')

plt.title("Error vs Mesh Refinement")
plt.xlabel("Level")
plt.ylabel("L2 Norm")
plt.legend()
plt.show()
