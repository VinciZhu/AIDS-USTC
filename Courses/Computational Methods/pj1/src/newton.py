import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
mpl.rc('font', family='serif', size=15)
mpl.rc('mathtext', fontset='stix')
mpl.rc('text', usetex=True)

df = pd.read_csv('data_points.csv')
X, Y = df['x'].to_numpy(dtype=int), df['f(x)'].to_numpy(dtype=float)


def divided_diff(X, Y):
    n = len(X)
    g = Y.copy()
    for i in range(1, n):
        for j in range(n-1, i-1, -1):
            g[j] = (g[j] - g[j-1]) / (X[j] - X[j-i])
    return g


def newton_interp(X, G, x):
    n = len(X)
    y = G[n-1]
    for i in range(n-2, -1, -1):
        y = G[i] + (x - X[i]) * y
    return y


G = divided_diff(X[:-1], Y[:-1])
def N(x): return newton_interp(X[:-1], G, x)


x_range = np.linspace(1900, 2020, 100)
fig, ax = plt.subplots(figsize=(8, 4))
ax.plot(X, Y, 'ro', label=r'$f(x)$')
ax.plot(x_range, [N(x) for x in x_range], label=r'$N_{5}(x)$')
ax.set_xlim(1900, 2010)
ax.set_xticks(np.arange(1900, 2020, 10))
ax.set_ylim(0.5e5, 2.5e5)
ax.set_xlabel(r'$x$ (year)')
ax.set_ylabel(r'Population ($10^3$)')
ax.grid()
ax.legend()

fig.savefig('newton-interpolation.pdf')
print(N(1910), N(1965), N(2002), N(2012))
