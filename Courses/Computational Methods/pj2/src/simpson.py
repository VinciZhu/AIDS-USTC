import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from math import log

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)


def simpson(f, a, b, n):
    h = (b - a) / n
    s = f(a) + f(b)
    for i in range(1, n):
        if i % 2 == 0:
            s += 2 * f(a + i * h)
        else:
            s += 4 * f(a + i * h)
    return h * s / 3


def adaptive_simpson(f, a, b, M=100, eps=0, print_flag=False):
    k = 0
    S1 = simpson(f, a, b, 1)
    S2 = float('inf')
    if print_flag: print(f'1,{S1},')
    while abs(S1 - S2) >= 15 * eps and k < M - 1:
        k += 1
        S2 = S1
        S1 = simpson(f, a, b, 2**k)
        if print_flag: print(f'{2**k},{S1},{abs(S1-S2)/15}')
    return S1


print(adaptive_simpson(log, 1, 2, M=5, print_flag=True))

x_range = np.linspace(1, 100, 100)
fig, ax = plt.subplots(figsize=(8, 4), constrained_layout=True)
ax.plot(x_range, [simpson(log, 1, x, 1) for x in x_range],
        label=r'$S_1(\ln{x})$')
ax.plot(x_range, [simpson(log, 1, x, 2) for x in x_range],
        label=r'$S_2(\ln{x})$')
ax.plot(x_range, [simpson(log, 1, x, 4) for x in x_range],
        label=r'$S_4(\ln{x})$')
ax.plot(x_range, [simpson(log, 1, x, 8) for x in x_range],
        label=r'$S_8(\ln{x})$')
ax.plot(x_range, [adaptive_simpson(log, 1, x, eps=1e-4) for x in x_range],
        label=r'$S_n(\ln{x})$')
ax.set_xticks(np.append(ax.get_xticks(), 1))
ax.set_xlim(1, 100)
ax.set_ylim(0)
ax.set_xlabel(r'$b$')
ax.set_ylabel(r'$y$')
ax.grid()
ax.legend()
fig.savefig('../assets/output/simpson.pdf')