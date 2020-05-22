import numpy as np
import matplotlib.pyplot as plt
import math

plt.rc('text', usetex = True)
plt.rc('text.latex',unicode = True)
plt.rcParams['text.latex.preamble'] = [r'\usepackage[utf8]{inputenc}', r'\usepackage[russian]{babel}', r'\usepackage{amsmath}']
            
data = []
with open("bsm-output.txt") as f:
    for line in f:
        data.append([float(x) for x in line.split()])

def approx(X, Y, d):
    m = len(X)
    xav = 0
    yav = 0
    x2av = 0
    y2av = 0
    xyav = 0
    #1 approximation : y = kx + b
    if (d == 1):
        for n in range(len(X)):
            xyav = xyav + X[n]*Y[n] / m
            y2av = y2av + X[n]*Y[n] / m
            x2av = x2av + X[n]*X[n] / m
            xav = xav + X[n]/m
            yav = yav + Y[n]/m
        k = ((xyav) - xav * yav)/(x2av - xav*xav)
        b = yav - k * xav
        d_k = 1/math.sqrt(m) * math.sqrt(abs((y2av - yav * yav)/(x2av - xav * xav) - k**2))
        d_b = d_k * math.sqrt(x2av - xav*xav)
        final_data = [k, d_k, b, d_b]
    else:
    #2 approximation : y = kx
        if (d == 2):
            for n in range(len(X)):
                xyav = xyav + X[n]*Y[n] / m
                y2av = y2av + Y[n]*Y[n] / m
                x2av = x2av + X[n]*X[n] / m
            k = (xyav)/(x2av)
            d_k = 1/math.sqrt(m) * math.sqrt (abs((y2av)/(x2av) - k**2))
            final_data = [k, d_k]
    return final_data

def get_numbers():
    with open("bsm.txt") as input_file:
        for line in input_file:
            line = line.strip()
            for number in line.split():
                yield float(number)

in_file = open('n_scenarios.txt', 'r') 
lines = []

n_scenario = 0

for line in in_file:
    lines.append(line)
for line in lines:
    n_scenario = int(line)

times = [0 for i in range(len(data))]
price = [[0 for i in range(len(data))] for j in range(n_scenario)]

for i in range(len(data)):
    times[i] = data[i][0]
    for j in range(n_scenario):
        price[j][i] = data[i][j+1]

average = 0

plt.style.use('fivethirtyeight')
color = ['#173F5F', '#20639B', '#2CAEA3', '#F6D55C', '#ED553B', '#B88BAC']
color_new = color
for i in range(4):
    color_new.extend(color)
    
for j in range(n_scenario):
    k = 255 - 51 * j
    s = str(hex(k))[2:]
    plt.plot(times, price[j], lw = 1.0, color = color[j])
    average = average + price[j][len(data) - 1]/ n_scenario

t = [0 for i in range(2)]
q = [0 for i in range(2)]
t[0] = 0
t[1] = 4
q[0] = 100

q[1] = average
k = (q[1] - q[0])/(t[1] - t[0])

plt.plot(t, q, lw = 1.0, color = 'maroon')

plt.xticks(color='k', size = 18)
plt.yticks(color='k', size = 18)

plt.xlabel(r'\bf{Time $T$, years}', {'color': 'darkblue', 'fontsize': 24})
plt.ylabel(r'\bf{Underlying price $P$}', {'color': 'darkblue', 'fontsize': 24})
plt.title(r'\bf{Underlying price simulation}', {'color': 'darkblue', 'fontsize': 28})

kwargs={'linestyle':'--', 'lw':0.5}
plt.grid(True, **kwargs)

fig = plt.gcf()
fig.set_size_inches(16, 12)
plt.savefig("Results/BSM/Stocks-simulation.png")