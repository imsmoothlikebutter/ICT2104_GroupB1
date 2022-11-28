import matplotlib.pyplot as plt

xu,yu = [], []
xk,yk = [], []
xs, ys = [], []
xm, ym = [], []

for line in open('test.txt', 'r'):
    values = [float(s) for s in line.split()]
    yu.append(values[0])
    xu.append(values[3])

for line in open('test.txt', 'r'):
    values = [float(s) for s in line.split()]
    yk.append(values[1])
    xk.append(values[3])

for line in open('test.txt','r'):
    values = [float(s) for s in line.split()]
    ys.append(values[2])
    xs.append(values[3])

plt.plot(xu,yu, c = 'r', label="Unfiltered Data")
plt.plot(xk, yk, c = 'tab:blue', label="Kalman Filter Data")
plt.plot(xs,ys, c = 'tab:green', label = "Simple Moving Average Data")
plt.title(label = "Ultrasonic Algorithm Comparison", fontweight = "bold")
plt.xlabel("nth digit")
plt.ylabel("Distance")
plt.legend()
plt.show()