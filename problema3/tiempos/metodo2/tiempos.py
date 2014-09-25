
# -*- encoding: utf-8 -*-
import csv
import matplotlib.pyplot as plt
import numpy as np

x = []
y = []
indicex = 0

with open('SinPoda3/N=10,peso=M+1.csv', 'r') as f:
	reader = csv.reader(f, delimiter = ' ')
	for row in reader:
		indicex += 1
		x.append(indicex)	
		y.append(row)
def plot():
	fig = plt.figure()
	plt.plot(x, y)
	fig.suptitle('Sin precalcular')
	axes = plt.gca()
	plt.xlabel(u'cantidad de productos')
	plt.ylabel(u'tiempo llevado por el backtracking')
plot()
plt.savefig('SinPoda3/N=10,peso=M+1.png')

#plt.show(block=False)
