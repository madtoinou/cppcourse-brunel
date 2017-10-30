#import numpy as np
#import pylab as pl

data = np.genfromtxt('spikes.dat')

select = np.array([d for d in data if d[1] < 50])

data1=select.transpose()
pl.scatter(0.1*data1[0], data1[1], alpha=0.8, edgecolors='none');
pl.show()