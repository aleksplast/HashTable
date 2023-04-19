import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

x = []
y = []

with open ("Strlenstat.csv", "r") as f:
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

print(np.var(x))

plt.bar(y,x)

plt.title('Plot for Strlen Hash')
plt.xlabel('Basket')
plt.ylabel('Collisions')

plt.show()
