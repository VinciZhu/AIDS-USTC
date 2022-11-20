import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from math import log
from numpy.polynomial.legendre import leggauss

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)


def gauss_legendre(f, a, b, n):
    x, w = leggauss(n)
    return (b - a) / 2 * sum(
        [w[i] * f((a + b + (b - a) * x[i]) / 2) for i in range(n)])


print(gauss_legendre(lambda x: x**5 + x, -3, 1, 1))
print(gauss_legendre(lambda x: x**5 + x, -3, 1, 2))
print(gauss_legendre(lambda x: x**5 + x, -3, 1, 3))
print(gauss_legendre(log, 1, 2, 1))
print(gauss_legendre(log, 1, 2, 2))
print(gauss_legendre(log, 1, 2, 3))

x_range = np.linspace(1, 100, 100)
fig, ax = plt.subplots(figsize=(8, 4), constrained_layout=True)
ax.plot(x_range, [gauss_legendre(log, 1, x, 1) for x in x_range],
        label=r'$G_1(\ln{x})$')
ax.plot(x_range, [gauss_legendre(log, 1, x, 2) for x in x_range],
        label=r'$G_2(\ln{x})$')
ax.plot(x_range, [gauss_legendre(log, 1, x, 3) for x in x_range],
        label=r'$G_3(\ln{x})$')
ax.plot(x_range, [gauss_legendre(log, 1, x, 4) for x in x_range],
        label=r'$G_4(\ln{x})$')
ax.set_xticks(np.append(ax.get_xticks(), 1))
ax.set_xlim(1, 100)
ax.set_ylim(0)
ax.set_xlabel(r'$b$')
ax.set_ylabel(r'$y$')
ax.grid()
ax.legend()
fig.savefig('../assets/output/gauss-legendre.pdf')