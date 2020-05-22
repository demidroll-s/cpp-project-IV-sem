import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import figure
import math
from scipy.stats import norm
import matplotlib.mlab as mlab
import csv

plt.rc('text', usetex = True)
plt.rc('text.latex',unicode = True)
plt.rcParams['text.latex.preamble'] = [r'\usepackage[utf8]{inputenc}',
            r'\usepackage[russian]{babel}',
            r'\usepackage{amsmath}']

#Секция 1. Чтение данных из .txt
data = []
with open("delta-output.txt") as f:
    for line in f:
        data.append([float(x) for x in line.split()])

result = [0 for i in range(len(data))]
for i in range(len(result)):
    result[i] = data[i][1]

#Секция 2. Преобразование .txt в .csv
s = ['' for i in range(2)]
s[0] = 'SIMULATION_NUMBER'
s[1] = 'BANK ACCOUNT'
with open('delta-output.txt', 'r') as in_file:
    stripped = (line.strip() for line in in_file)
    lines = (line.split(" ") for line in stripped if line)
    with open('Results/Delta-hedging/delta-data.csv', 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(s)
        writer.writerows(lines)

#Секция 3. Построение графиков
min = 10 ** 10
max = -10 ** 10
for i in range(len(result)):
    if(result[i] > max):
        max = result[i]
    if(result[i] < min):
        min = result[i]

# the histogram of the data
plt.style.use('fivethirtyeight')
n, bins, patches = plt.hist(result, 50, density = True, facecolor = 'goldenrod', alpha = 0.75)

max_patches = 0
below_zero = 0

for i in range(len(patches)):
    if (float(patches[i].get_height()) > max_patches):
        max_patches = float(patches[i].get_height())
    if (bins[i] > 0):
        below_zero = below_zero + float(patches[i].get_height()) * float(patches[i].get_width())

#approximation
ax = plt.subplot()
(mu, sigma) = norm.fit(result)
y = ((1 / (np.sqrt(2 * np.pi) * sigma)) * np.exp(-0.5 * (1 / sigma * (bins - mu))**2))
ax.plot(bins, y, '--', color = 'darkblue', label = r'$\mu = %.3f, \: \sigma = %.3f$' %(mu, sigma))

#plot design
plt.xlabel(r'\bf{Bank balance after hedging at the moment $T$}', {'color': 'darkblue', 'fontsize': 24})
plt.ylabel(r'\bf{Frequency}', {'color': 'darkblue', 'fontsize': 24})
plt.title(r'\bf{Delta hedging}', {'color': 'darkblue', 'fontsize': 28})
plt.xticks(color='k', size = 18)
plt.yticks(color='k', size = 18)
plt.legend(fontsize='xx-large')
plt.grid(True)
fig = plt.gcf()
fig.set_size_inches(16, 12)
plt.savefig("Results/Delta-hedging/Delta-hedging.png")