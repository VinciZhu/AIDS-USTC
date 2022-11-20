import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from math import log

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)


def romberg(f, a, b, M=100, eps=0.0, print_flag=False):
    k = 0
    R = [[float('inf')], [trapezoid(f, a, b, 1)]]
    if print_flag: print(f'1,{R[1]}')
    while abs(R[0][k - 1] - R[1][k]) >= eps and k < M - 1:
        k += 1
        R[0] = R[1]
        R[1] = [trapezoid(f, a, b, 2**k)]
        for j in range(1, k + 1):
            R[1].append((4**j * R[1][j - 1] - R[0][j - 1]) / (4**j - 1))
        if print_flag: print(f'{k+1},{R[1]},{abs(R[0][k - 1] - R[1][k])}')
    return R[1][k]


romberg(log, 1, 2, eps=1e-4, print_flag=True)

x_range = np.linspace(1, 100, 100)
fig, ax = plt.subplots(figsize=(8, 4), constrained_layout=True)
ax.plot(x_range, [romberg(log, 1, x, M=1) for x in x_range],
        label=r'$R_{1,1}(\ln{x})$')
ax.plot(x_range, [romberg(log, 1, x, M=2) for x in x_range],
        label=r'$R_{2,2}(\ln{x})$')
ax.plot(x_range, [romberg(log, 1, x, M=3) for x in x_range],
        label=r'$R_{3,3}(\ln{x})$')
ax.plot(x_range, [romberg(log, 1, x, eps=1e-4) for x in x_range],
        label=r'$R_{k,k}(\ln{x})$')
ax.set_xticks(np.append(ax.get_xticks(), 1))
ax.set_xlim(1, 100)
ax.set_ylim(0)
ax.set_xlabel(r'$b$')
ax.set_ylabel(r'$y$')
ax.grid()
ax.legend()
fig.savefig('../assets/output/romberg.pdf')