#!/usr/bin/python

import sys
import pylab
import matplotlib.pyplot as plt

class Data(object):
    def __init__(self):
        self.header_ = []
        self.data_ = []
    
    def readHeader(self, s):
        self.header_.append(s.strip().split('\t'))

    def read(self, s):
        buf = s.strip().split('\t')
        self.data_.append(buf)

    def get(self, i, j):
        return float(self.data_[i][j])

data = Data()

data.readHeader(raw_input())
for l in sys.stdin:
    data.read(l)

x = []
gauss_time = []
qr_time = []
gauss_iterations = []
qr_iterations = []
x3 = []
gauss_ratio = []
qr_ratio = []

for i in xrange(len(data.data_)):
    size = data.get(i, 0)
    gauss_time_ = data.get(i, 1)
    gauss_iterations_ = data.get(i, 2)
    qr_time_ = data.get(i, 3)
    qr_iterations_ = data.get(i, 4)

    x.append(size)
    gauss_time.append(gauss_time_)
    gauss_iterations.append(gauss_iterations_)
    qr_time.append(qr_time_)
    qr_iterations.append(qr_iterations_)
    x3.append(x[-1] ** 3)
    gauss_ratio.append(gauss_iterations[-1] / x3[-1])
    qr_ratio.append(qr_iterations[-1] / x3[-1])
    

fig = plt.figure()

ax1 = fig.add_subplot(221, xlabel = "Matrix size", ylabel = "Spent time")
ax1.plot(x, gauss_time, label = "Gauss")
ax1.plot(x, qr_time, label = "QR")
ax1.legend(loc = "upper left")

ax2 = fig.add_subplot(222, xlabel = "Matrix size", ylabel = "Iterations")
ax2.plot(x, gauss_iterations, label = "Gauss")
ax2.plot(x, qr_iterations, label = "QR")
ax2.plot(x, x3, ls = "--", label = "x^3")
ax2.legend(loc = "upper left")

plt.show()
