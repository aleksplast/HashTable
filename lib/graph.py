import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

x = []
y = []

with open ("Rorstat.csv", "r") as f:
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
lists = 0

for i in range(len(x)):
    if x[i] != 0:
        elements += x[i]
        lists += 1

print("Load factor = ", elements/lists)
print(np.var(x))

plt.bar(y,x)

plt.title('Plot for Ror Hash')
plt.xlabel('Basket')
plt.ylabel('Collisions')

plt.show()
