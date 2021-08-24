import numpy as np
import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation

my_dpi = 144 # https://stackoverflow.com/questions/13714454/specifying-and-saving-a-figure-with-exact-size-in-pixels

# stations = np.genfromtxt("with_stations/stations")
# stations = np.genfromtxt("with_stations_old/stations")
# stations = np.genfromtxt("with_air_viscUp1/blobL9/stations")
stations = np.genfromtxt("with_air_viscUp1/circleL9/stations")
# stations1 = np.genfromtxt("with_stations_air/stations")
# print(stations1)
# stations = stations1[:-150000, :]
# print(stations)

uniquetimes = []
for i in stations[:, 0]:
	if i not in uniquetimes:
		uniquetimes.append(i)
# print(uniquetimes)
uniquetimes = np.array(uniquetimes)
print(uniquetimes)

arrList = []
xvals = np.arange(-3, 3, 0.1)
yvals = np.arange(-1, 1.1, 0.1)
for time in uniquetimes:

	tmask = stations[:, 0] == time # start by only looking at t=0

	stations0 = stations[tmask, :]

	stationsFinal = np.empty((21, 60))
	stationsFinal[:] = np.nan

	# The origin as defined in Basilisk is at stations0[31, 11]
	# Thus, any point [x, y] in Basilisk space is at stationsFinal[x*10+31, y*10+11]
	for line in stations0:
		# print(line)
		xnow = round(line[1], 1)
		ynow = round(line[2], 1)
		line[1] = xnow
		line[2] = ynow
		# print(line)
		xpos = int(xnow*10+30)
		ypos = int(ynow*10+10)
		# if abs(line[2])<1e-10:
		# 	# print(abs(line[2]))
		# 	ypos = 10
		# print(ypos)
		stationsFinal[ypos, xpos] = line[3]
	arrList.append(stationsFinal)
	# for i in stationsFinal:
	# 	print(i)

	# plt.pcolormesh(xvals, yvals, stationsFinal, shading='auto')
	# plt.colorbar()
	# plt.show()

finalArray = np.stack(arrList)

sigma2 = []
chi = []
for t in range(len(finalArray[:, 0, 0])):
	# if t!=0:
	# 	break
	nowAr = finalArray[t, :, :].flatten()
	nowAr2 = np.square(nowAr)

	sigma2now = np.nanmean(nowAr2) - np.square(np.nanmean(nowAr))
	sigma2.append(sigma2now)

	if t == 0:
		sigma2MAX = sigma2now

	# print(sigma2now)
	# print(sigma2MAX)

	chiNow = 1 - sigma2now/sigma2MAX
	chi.append(chiNow)

chi = np.array(chi)
All_Chi = np.zeros((len(chi), len(chi)))

# fig, ax = plt.subplots(figsize=(800/my_dpi, 350/my_dpi), dpi=my_dpi)
fig, ax = plt.subplots(figsize=(800/my_dpi, 600/my_dpi))

for time in uniquetimes:
	for time2 in uniquetimes:
		if time2 <= time:
			All_Chi[int(time), int(time2)] = chi[int(time2)]
		if time2 > time:
			All_Chi[int(time), int(time2)] = np.nan

def animate(i):
	ax.plot(uniquetimes, All_Chi[i, :], color='k')
anim = FuncAnimation(
	fig, animate, interval=100, frames=len(uniquetimes))
plt.draw()
plt.xlim([min(uniquetimes), max(uniquetimes)])
# # print(max(Advection_StabilityOld[:, 1]))
plt.ylim([min(chi[:]), max(chi[:])])
plt.xlabel('Dimensionless Time')
plt.ylabel('Mixing State χ')
plt.title('Mixing State χ over Time')
anim.save("with_stations_air.mp4", dpi=my_dpi)
plt.show()