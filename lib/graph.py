import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

x = []
y = []

with open ("CRCstat.csv", "r") as f:
    for line in f:
        line = line.split(";")
        x = line

for element in x:
    if element == '':
        x.remove(element)
    else:
        element = int(element)

for i in range(len(x)):
    x[i] = int(x[i])
for i in range(len(x)):
    y.append(i)

elements = 0
numlists = 0

for i in range(len(x)):
    if x[i] != 0:
        elements += x[i]
        numlists += 1

print("load factor = ", elements/numlists)


plt.bar(y,x)

plt.title('Plot for ASCII sum hash')
plt.xlabel('List')
plt.ylabel('Collisions')

plt.show()
