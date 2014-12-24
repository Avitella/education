#!/usr/bin/python

import sys
import pylab
import matplotlib.pyplot as plt

header = raw_input().strip().split('\t') # Skip header
x = []
y = []

for l in sys.stdin:
    a = l.strip().split('\t')
    x.append(a[0])
    y.append(a[1])

pylab.plot(x, y)
pylab.show()
