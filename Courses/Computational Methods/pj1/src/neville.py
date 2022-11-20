import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
mpl.rc('font', family='serif', size=15)
mpl.rc('mathtext', fontset='stix')
mpl.rc('text', usetex=True)

df = pd.read_csv('data_points.csv')
X, Y = df['x'].to_numpy(dtype=int), df['f(x)'].to_numpy(dtype=float)


def neville_interp(X, Y, x):
    n = len(X)
    p = np.array(Y)
    for i in range(1, n):
        for j in range(n-i):
            p[j] = ((x - X[j]) * p[j+1] - (x - X[j+i])
                    * p[j]) / (X[j+i] - X[j])
    return p[0]


def P(x): return neville_interp(X[:-1], Y[:-1], x)


x_range = np.linspace(1900, 2020, 100)
fig, ax = plt.subplots(figsize=(8, 4))
ax.plot(X, Y, 'ro', label=r'$f(x)$')
ax.plot(x_range, [P(x) for x in x_range], label=r'$P_{0,1,\dots,5}(x)$')
ax.set_xlim(1900, 2010)
ax.set_xticks(np.arange(1900, 2020, 10))
ax.set_ylim(0.5e5, 2.5e5)
ax.set_xlabel(r'$x$ (year)')
ax.set_ylabel(r'Population ($10^3$)')
ax.grid()
ax.legend()

fig.savefig('neville-interpolation.pdf')
print(P(1910), P(1965), P(2002), P(2012))
