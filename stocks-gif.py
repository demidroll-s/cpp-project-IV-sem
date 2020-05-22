# Секция 1. Импорт библиотек
import pandas as pd
import math
import matplotlib.pyplot as plt
import moviepy.editor as mpy
import glob
import csv
import os

plt.rc('text', usetex = True)
plt.rc('text.latex',unicode = True)
plt.rcParams['text.latex.preamble'] = [r'\usepackage[utf8]{inputenc}',
            r'\usepackage[russian]{babel}',
            r'\usepackage{amsmath}']

def plot_maker(df, i, n_scenario, y_min, y_max):
    h = 10 * i
    #k = 255 - 17 * j
    #s = str(hex(k))[2:]
    ax = df.iloc[:h].plot(figsize=(16,12), linewidth=1.0, color = ['#173F5F', '#20639B', '#2CAEA3', '#F6D55C', '#ED553B', '#B88BAC'])
    ax.set_ylim(y_min, y_max)
    ax.get_legend().remove()
    plt.xlabel(r'\bf{Time}', {'color': 'darkblue', 'fontsize': 24})
    plt.ylabel(r'\bf{Underlying price $P$}', {'color': 'darkblue', 'fontsize': 24})
    plt.title(r'\bf{Underlying price dynamics}', {'color': 'darkblue', 'fontsize': 28})
    plt.xticks(color='k', size = 18)
    plt.yticks(color='k', size = 18)
    plt.grid(axis='x')
    kwargs={'linestyle':'--', 'lw':0.5}
    plt.grid(True, **kwargs)
    k = 100 + i
    path = "Results/BSM/pngs/" + str(k) + ".png"
    plt.savefig(path)

#Секция 2. Преобразование .txt в .csv
in_file = open('n_scenarios.txt', 'r') 
lines = []
n_scenarios = 0

for line in in_file:
    lines.append(line)
for line in lines:
    n_scenarios = int(line)

s = ['' for i in range(n_scenarios + 1)]
s[0] = 'TIME'
for i in range(n_scenarios):
    s[i + 1] = 'PRICE' + str(i + 1)

with open('bsm-output.txt', 'r') as in_file:
    stripped = (line.strip() for line in in_file)
    lines = (line.split(" ") for line in stripped if line)
    with open('Results/BSM/bsm-data.csv', 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(s)
        writer.writerows(lines)

# Секция 3. Преобразование данных в датафреймы
df = pd.read_csv('Results/BSM/bsm-data.csv')
df.set_index('TIME', inplace=True)
data = df.values.tolist()

max_ = [0 for i in range(len(df.index))]
min_ = [0 for i in range(len(df.index))]
for i in range(len(df.index)):
    max_[i] = max(data[i])
    min_[i] = min(data[i])
max_price = max(max_)
min_price = min(min_)
y_min = (math.trunc(min_price / 5) - 1) * 5
y_max = (math.trunc(max_price / 5) + 2) * 5

# Секция 5. Построение графиков
l = int(len(df.index) / 10) #number of frames

n_scenarios = 6
plt.style.use('fivethirtyeight')
for i in range(0, l + 1):
    plot_maker(df, i, n_scenarios, y_min, y_max)

# Секция 6. Генерация GIF
gif_name = 'Results/BSM/Dynamics'
fps = 6
file_list = sorted(glob.glob('Results/BSM/pngs/*.png'))
clip = mpy.ImageSequenceClip(file_list, fps=fps)
clip.write_gif('{}.gif'.format(gif_name), fps=fps)


