import matplotlib.pyplot as pyp
import matplotlib.pyplot as plt
import numpy as np
data = np.loadtxt("Koordin.txt")
pyp.plot(data[:, 0], data[:, 1])
data = np.loadtxt("Cloud.txt")
pyp.scatter(data[:, 0], data[:, 1],10,marker='o',color='k')
pyp.show()
plt.show()