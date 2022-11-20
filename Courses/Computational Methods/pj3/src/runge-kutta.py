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
    y = Y[0]
    return np.array([y * np.sin(np.pi * x)])


y0 = np.array([1.0])
begin, end, n_list = 0.0, 7, [10, 20, 40, 80, 160]

df = pd.DataFrame({'x': np.linspace(begin, end, n_list[0] + 1)})

fig, ax = plt.subplots(figsize=(8, 4), constrained_layout=True)
for n in n_list:
    df_ = runge_kutta(f, y0, begin, end, n, print_flag=True)[1].rename(columns={'y0': f'n={n}'})
    df = pd.merge_asof(df, df_, on='x', direction='nearest')
    df_.plot(ax=ax, x='x', y=f'n={n}', label=f'$n={n}$')
ax.set_xlabel(r'$x$')
ax.set_ylabel(r'$y$')
ax.grid()
ax.legend()
fig.savefig('../assets/output/runge-kutta.pdf')
df.to_csv(out_dir + 'runge-kutta.csv')