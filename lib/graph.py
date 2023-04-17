import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

x = []
y = []

with open ("MurMurstat.csv", "r") as f:
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

print(np.std(x)/sum(x))

plt.bar(y,x)

plt.title('Plot for ASCII sum hash')
plt.xlabel('List')
plt.ylabel('Collisions')

plt.show()
