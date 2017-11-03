#! /usr/bin/python3

import matplotlib.pyplot as plt
import sys
import random

data = []
entr = (len(sys.argv)>=2 and sys.argv[1]) or input("spikes.dat")
sor1 = (len(sys.argv)>=3 and sys.argv[2]) or input("ScatterPlot")
sor2 = (len(sys.argv)>=4 and sys.argv[3]) or input("FreqPlot?")
def traitement(st):
    x,y = st.split()
    return [float(x),int(y)]
    
with open(entr) as f:
    data = list(zip(*sorted(map(traitement,f.readlines()))))

plt.clf()
plt.plot(data[0],data[1],"b.")
plt.savefig(sor1)
plt.clf()
absc = [0] + list(data[0])
ordon = list(range(len(data[0])+1))
plt.plot(absc,ordon)
plt.savefig(sor2)
