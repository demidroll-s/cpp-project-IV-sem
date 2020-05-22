import csv

s = ['' for i in range(7)]
s[0] = 'MODEL'
s[1] = 'INITIAL STOCK PRICE'
s[2] = 'RISK FREE RATE'
s[3] = 'VOLATILITY'
s[4] = 'DRIFT'
s[5] = 'DATE'
s[6] = 'MATURITY'

with open('bsm-table.txt', 'r') as in_file:
    stripped = (line.strip() for line in in_file)
    lines = (line.split(" ") for line in stripped if line)
    with open('Results/Auxiliary/bsm-table.csv', 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(s)
        writer.writerows(lines)

s = ['' for i in range(5)]
s[0] = 'INITIAL STOCK PRICE'
s[1] = 'RISK FREE RATE'
s[2] = 'VOLATILITY'
s[3] = 'DRIFT'
s[4] = 'DATE'

with open('delta-table-simulation.txt', 'r') as in_file:
    stripped = (line.strip() for line in in_file)
    lines = (line.split(" ") for line in stripped if line)
    with open('Results/Auxiliary/delta-table-simulation.csv', 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(s)
        writer.writerows(lines)

with open('delta-table-pricing.txt', 'r') as in_file:
    stripped = (line.strip() for line in in_file)
    lines = (line.split(" ") for line in stripped if line)
    with open('Results/Auxiliary/delta-table-pricing.csv', 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(s)
        writer.writerows(lines)

s = ['' for i in range(2)]
s[0] = 'MATURITY'
s[1] = 'NUMBER OF SCENARIOS'

with open('delta-table-option.txt', 'r') as in_file:
    stripped = (line.strip() for line in in_file)
    lines = (line.split(" ") for line in stripped if line)
    with open('Results/Auxiliary/delta-table-option.csv', 'w') as out_file:
        writer = csv.writer(out_file)
        writer.writerow(s)
        writer.writerows(lines)
