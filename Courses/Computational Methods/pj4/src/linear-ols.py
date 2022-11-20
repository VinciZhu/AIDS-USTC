import numpy as np
import numpy.linalg as la
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)
mpl.rc('text.latex', preamble=r'\usepackage{bm}')

out_dir = '../assets/output/'


# Linear OLS
def fit(N, h, e):
    a, b, c, d = 0, 0, 0, 0
    for i in range(N):
        x, y = np.log(h[i]), np.log(e[i])
        a += x
        b += y
        c += x**2
        d += x * y
    return ((N * d - a * b), (b * c - a * d)) / (N * c - a**2)


# Newton iteration
df = pd.read_csv('../assets/output/newton-error.csv')

c = fit(df.shape[0], df['h'].array, df['eh'].array)
print(c)

fig, ax = plt.subplots(figsize=(8, 4), constrained_layout=True)
ax.set_xlabel(r'$\log h$')
ax.scatter(df['logh'], df['logeh'], zorder=2, label=r'$\log e_h$', marker='o')
ax.plot([-5.2, -2.2], np.polyval(c, [-5.2, -2.2]), label=r'$\beta_0 + \beta \log h$', zorder=1, linewidth=1, c='C1')
ax.grid()
ax.legend()
fig.savefig(out_dir + 'newton-error.pdf')

# Jacobi and Gauss-Seidel iterations
df = pd.read_csv('../assets/output/linear-itr-error.csv')

c1 = fit(df.shape[0], df['h'].array, df['eh1'].array)
c2 = fit(df.shape[0], df['h'].array, df['eh2'].array)
print(c1)
print(c2)

fig, ax = plt.subplots(2, 1, figsize=(8, 8), constrained_layout=True)

ax[0].set_xlabel(r'$\log h$')
ax[0].scatter(df['logh'], df['logeh1'], zorder=2, label=r'$\log e_h$ (Jacobi Iter.)', marker='o')
ax[0].plot([-5.2, -2.2], np.polyval(c1, [-5.2, -2.2]), label=r'$\beta_0 + \beta \log h$', zorder=1, linewidth=1, c='C1')
ax[0].grid()
ax[0].legend()

ax[1].set_xlabel(r'$\log h$')
ax[1].scatter(df['logh'], df['logeh2'], zorder=2, label=r'$\log e_h$ (Gauss-Seidel Iter.)', marker='o', c='C2')
ax[1].plot([-5.2, -2.2], np.polyval(c2, [-5.2, -2.2]), label=r'$\beta_0 + \beta \log h$', zorder=1, linewidth=1, c='C3')
ax[1].grid()
ax[1].legend()

fig.savefig(out_dir + 'linear-itr-error.pdf')