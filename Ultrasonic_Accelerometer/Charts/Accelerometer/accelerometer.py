import matplotlib.pyplot as plt

xu,yu = [], []
xk,yk = [], []
xs,ys = [], []
xm, ym = [], []

for line in open('X1Unfiltered.txt', 'r'):
    values = [float(s) for s in line.split()]
    print(values[0])
    yu.append(values[0])
    xu.append(values[1])

for line in open('X1KalmanFilter.txt', 'r'):
    values = [float(s) for s in line.split()]
    yk.append(values[0])
    xk.append(values[1])

for line in open('X1SMA.txt', 'r'):
    values = [float(s) for s in line.split()]
    ys.append(values[0])
    xs.append(values[1])

for line in open('data.txt', 'r'):
    values = [float(s) for s in line.split()]
    ym.append(values[3])
    xm.append(values[4])

plt.plot(xu,yu, c = 'r', label="Unfiltered Data")
plt.plot(xk, yk, c = 'tab:blue', label="Kalman Filter Data")
plt.plot(xs, ys, c = 'tab:green', label = 'Simple Moving Average Data')
plt.plot(xm, ym, c="tab:purple", label="Median Filter Data")
plt.title(label = "Accelerometer X degree Algorithm Comparison", fontweight = "bold")
plt.xlabel("nth digit")
plt.ylabel("x-  Degree")
plt.legend()
plt.show()