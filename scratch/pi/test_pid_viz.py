import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("test_pid.txt")
plt.plot(data, label=["Xr", "e", "u", "y"])
plt.legend(loc="upper right")
plt.show()
