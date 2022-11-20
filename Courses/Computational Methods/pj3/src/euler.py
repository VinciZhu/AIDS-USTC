import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)

out_dir = '../assets/output/'

# Butcher tableau for modified Euler method, midpoint method, and Ralston method
MODIFIED_EULER = 2, [0.0, 1.0], [[0.0, 0.0], [1.0, 0.0]], [0.5, 0.5]
MIDPOINT = 2, [0.0, 0.5], [[0.0, 0.0], [0.5, 0.0]], [0.0, 1.0]
RALSTON = 2, [0.0, 2.0 / 3.0], [[0.0, 0.0], [2.0 / 3.0, 0.0]], [0.25, 0.75]


def runge_kutta(f, y0, begin, end, n, butcher=RALSTON, print_flag=False):
    s, a, b, c = butcher
    x = begin
    y = y0.copy()
    h = (end - begin) / n
    if (print_flag):
        df = pd.DataFrame(columns=['x'] + [f'y{i}' for i in range(y.size)])
        df.loc[0] = [x] + y0.tolist()
    k = np.zeros((s, y.size))
    for step in range(1, n + 1):
        for i in range(s):
            tmp = np.zeros(y.shape)
            for j in range(i):
                tmp += b[i][j] * k[i - 1]
            k[i] = f(x + a[i] * h, y + tmp * h)
        x += h
        for i in range(s):
            y += h * c[i] * k[i]
        if (print_flag): df.loc[step] = [x] + y.tolist()
    return y, df


def f(x, Y):
    u, v = Y[0], Y[1]
    return np.array(
        [0.09 * u * (1 - u / 20) - 0.45 * u * v, 0.06 * v * (1 - v / 15) - 0.001 * u * v])


u0, v0 = 1.6, 1.2
y0 = np.array([u0, v0])
begin, end, n_list = 1.0, 6.0, [5, 10, 200]

udf = pd.DataFrame({'x': np.linspace(begin, end, n_list[0] + 1)})
vdf = pd.DataFrame({'x': np.linspace(begin, end, n_list[0] + 1)})

fig, ax = plt.subplots(1, 2, figsize=(8, 4), constrained_layout=True)
for n in n_list:
    df_ = runge_kutta(f, y0, begin, end, n, butcher=MODIFIED_EULER, print_flag=True)[1]
    udf = pd.merge_asof(udf,
                        df_.get(['x', 'y0']).rename(columns={'y0': f'n={n}'}),
                        on='x',
                        direction='nearest')
    vdf = pd.merge_asof(vdf,
                        df_.get(['x', 'y1']).rename(columns={'y1': f'n={n}'}),
                        on='x',
                        direction='nearest')
    df_.plot(ax=ax[0], x='x', y=f'y0', label=f'$n={n}$')
    df_.plot(ax=ax[1], x='x', y=f'y1', label=f'$n={n}$')
ax[0].set_xlabel(r'$x$')
ax[0].set_ylabel(r'$u$')
ax[0].grid()
ax[0].legend()
ax[1].set_xlabel(r'$x$')
ax[1].set_ylabel(r'$v$')
ax[1].grid()
ax[1].legend()
fig.savefig('../assets/output/euler.pdf')
udf.to_csv(out_dir + 'euler1.csv')
vdf.to_csv(out_dir + 'euler2.csv')