import numpy as np
import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation

# stations = np.genfromtxt("with_stations/stations")
stations = np.genfromtxt("with_stations_Peclet/stations")

uniquetimes = []
for i in stations[:, 0]:
	if i not in uniquetimes:
		uniquetimes.append(i)
# print(uniquetimes)
uniquetimes = np.array(uniquetimes)

fig, ax = plt.subplots(figsize=(10,6))

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
cax = ax.pcolormesh(xvals, yvals, finalArray[0, :, :], shading='auto')
fig.colorbar(cax)
def animate(i):
	cax.set_array(finalArray[i, :, :].flatten())
anim = FuncAnimation(
	fig, animate, interval=100, frames=len(uniquetimes)-1)
plt.draw()
plt.title("Tracer Values throughout Ellipse")
plt.xlabel("x")
plt.ylabel("y")
# anim.save("stations.mp4")
anim.save("stations_Peclet.mp4")
plt.show()
# print(finalArray.shape)

sigma2 = []
chi = []
for t in range(len(finalArray[:, 0, 0])):
	# if t!=0:
	# 	break
	nowAr = finalArray[t, :, :].flatten()
	nowAr2 = np.square(nowAr)

	# nowArmask = nowAr[:] > 0.5
	# # print(nowAr[nowArmask].shape)
	# nowAr2mask = nowAr2[:] > 0.5

	# print(nowAr[nowArmask])
	# print(nowAr2[nowAr2mask])

	# print(np.nanmean(nowAr))

	sigma2now = np.nanmean(nowAr2) - np.square(np.nanmean(nowAr))
	sigma2.append(sigma2now)

	if t == 0:
		sigma2MAX = sigma2now

	# print(sigma2now)
	# print(sigma2MAX)

	chiNow = 1 - sigma2now/sigma2MAX
	chi.append(chiNow)

	# numList = []
	# for i in range(len(nowAr[0, :])):
	# 	for j in range(len(nowAr[:, 0])):
	# 		if nowAr[i][j] > 0.0000001:
	# 			numList.append(nowAr[i][j])

	# average = np.nanmean(nowAr)
	# print(average)

	# for line in finalArray[t, :, :]:
	# 	print(line)

fig2, ax2 = plt.subplots(nrows=1, ncols=2, figsize=(20, 10))
ax2list = ax2.flatten()

ax2list[0].plot(uniquetimes, sigma2)
ax2list[0].set_title("Concentration Variance over Time")
ax2list[0].set_xlabel("Time")
ax2list[0].set_ylabel("Cocnentration Variance")

ax2list[1].plot(uniquetimes, chi)
ax2list[1].set_title("Mixing State χ over Time")
ax2list[1].set_xlabel("Time")
ax2list[1].set_ylabel("Mixing State χ")

# plt.savefig("var_chi.png")
plt.savefig("var_chi_Peclet.png")
plt.show()