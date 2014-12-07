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
x2 = []
x4 = []
gauss_ratio_x3 = []
qr_ratio_x3 = []
x3_ratio_x3 = []
x2_ratio_x2 = []
gauss_ratio_x2 = []
qr_ratio_x2 = []
gauss_ratio_x4 = []
qr_ratio_x4 = []
x4_ratio_x4 = []

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
    x2.append(x[-1] ** 2)
    gauss_ratio_x3.append(gauss_iterations[-1] / x3[-1])
    qr_ratio_x3.append(qr_iterations[-1] / x3[-1])
    x3_ratio_x3.append(x3[-1] / x3[-1])
    gauss_ratio_x2.append(gauss_iterations[-1] / x2[-1])
    qr_ratio_x2.append(qr_iterations[-1] / x2[-1])
    x2_ratio_x2.append(x2[-1] / x2[-1])
    x4.append(x[-1] ** 4)
    gauss_ratio_x4.append(gauss_iterations[-1] / x4[-1])
    qr_ratio_x4.append(qr_iterations[-1] / x4[-1])
    x4_ratio_x4.append(x4[-1] / x4[-1])

fig = plt.figure()

ax1 = fig.add_subplot(331, xlabel = "Matrix size", ylabel = "Spent time")
ax1.plot(x, gauss_time, label = "Gauss")
ax1.plot(x, qr_time, label = "QR")
ax1.legend(loc = "upper left")

ax2 = fig.add_subplot(332, xlabel = "Matrix size (x)", ylabel = "Iterations")
ax2.plot(x, gauss_iterations, label = "Gauss")
ax2.plot(x, qr_iterations, label = "QR")
ax2.plot(x, x2, ls = "--", label = "x^2")
ax2.legend(loc = "upper left")

ax3 = fig.add_subplot(333, xlabel = "Matrix size (x)", ylabel = "Iterations / x^2")
ax3.plot(x, gauss_ratio_x2, label = "Gauss")
ax3.plot(x, qr_ratio_x2, label = "QR")
ax3.plot(x, x2_ratio_x2, label = "x^2")
ax3.legend(loc = "upper left")

ax4 = fig.add_subplot(334, xlabel = "Matrix size (x)", ylabel = "Iterations")
ax4.plot(x, gauss_iterations, label = "Gauss")
ax4.plot(x, qr_iterations, label = "QR")
ax4.plot(x, x3, ls = "--", label = "x^3")
ax4.legend(loc = "upper left")

ax5 = fig.add_subplot(335, xlabel = "Matrix size (x)", ylabel = "Iterations / x^3")
ax5.plot(x, gauss_ratio_x3, label = "Gauss")
ax5.plot(x, qr_ratio_x3, label = "QR")
ax5.plot(x, x3_ratio_x3, label = "x^3")
ax5.legend(loc = "upper left")

ax6 = fig.add_subplot(336, xlabel = "Matrix size (x)", ylabel = "Iterations")
ax6.plot(x, gauss_iterations, label = "Gauss")
ax6.plot(x, qr_iterations, label = "QR")
ax6.plot(x, x4, ls = "--", label = "x^4")
ax6.legend(loc = "upper left")

ax7 = fig.add_subplot(337, xlabel = "Matrix size (x)", ylabel = "Iterations / x^4")
ax7.plot(x, gauss_ratio_x4, label = "Gauss")
ax7.plot(x, qr_ratio_x4, label = "QR")
ax7.plot(x, x4_ratio_x4, label = "x^4")
ax7.legend(loc = "upper left")

plt.show()
