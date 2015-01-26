#!/usr/bin/python

import sys
import pylab
import matplotlib.pyplot as plt

header = raw_input()

rkx = []
rky = []
ax = []
ay = []

for line in sys.stdin:
    data = line.strip().split('\t')
    rkx.append(data[0])
    rky.append(data[1])
    ax.append(data[2])
    ay.append(data[3])

fig = plt.figure()

ax1 = fig.add_subplot(111, xlabel = "X", ylabel = "Y")
ax1.plot(rkx, rky, label = "RungeKutta")
ax1.plot(ax, ay, label = "Adams")
ax1.legend(loc = "upper left")

plt.show()
