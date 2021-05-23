import matplotlib.pyplot as plt
import numpy as np
# when Oscar moves to Python 3 the following line will have to use input() instead of raw_input().
#FILE = raw_input("Which file?")
FILE = input("Which file?")
xprof = np.genfromtxt(FILE, delimiter=" ")
print("xprof shape:", xprof.shape)
#xprof = xprof[:25000, :]
a = xprof[:, 2]
print("a", a)
print("a shape:", a.shape)
yvals = xprof[:, 1]
yvalsunique = []
for i in yvals:
	if i not in yvalsunique:
		yvalsunique.append(i)
print("all y vals:", yvalsunique)
print("y vals len", len(yvalsunique))

B = a.reshape(int(len(xprof)/100), 100)
print(B[:, :])
fig, ax = plt.subplots(1, 1)
SpaceArr = np.linspace(-0.5, 0.49, 100)
print('LENGTH:', len(xprof)/100)
print('MAX:', max(xprof[:, 0]))
TimeArr = np.linspace(0, max(xprof[:, 0]), int(len(xprof)/100))



stationDict = {}
for j in range(-4, 4, 4):
	stationArr = []
	for i in range(len(TimeArr)):
		interf_FILE = 'interface_'+str(i)+'.dat'
		# OUTFILE = 'interfacesLiquid-'+str(i)+'.0.png'
		# print(FILE)
		interf = np.genfromtxt(interf_FILE, delimiter=' ')
		mask1 = interf[:, 0]==j
		station = interf[mask1, :][0, 1] #due to the way output_facets works in the c program, there will be two points with x=1, so I just pick the first one as my station by indexing to row 0 (and column 1 to get the actual interface height).
		stationArr.append(station)
	stationDict["Station "+str(j)]=stationArr


minmaxFILE = np.genfromtxt("loginterface.dat")
intMin = minmaxFILE[:, 5]
intMax = minmaxFILE[:, 6]

cax = ax.contourf(TimeArr, SpaceArr, B.transpose(), 100)
ax.plot(TimeArr, intMin, label="ymin")
ax.plot(TimeArr, intMax, label="ymax")
for k in range(-4, 4, 4):
	ax.plot(TimeArr, stationDict["Station "+str(k)], label='interface station x='+str(k))
cbar = fig.colorbar(cax)
cbar.set_label("X Velocity")
ax.set_title("2-fluid Couette x profile evolution")
ax.set_xlabel("Time")
ax.set_ylabel("Height (y)")
ax.legend()
plt.show()