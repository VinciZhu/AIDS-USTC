import numpy as np
import numpy.linalg as la
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)
mpl.rc('text.latex', preamble=r'\usepackage{bm}')

out_dir = '../assets/output/'


# Jacobi iteration
def jacobi(f, u0, ue=None, eps=1e-5, max_iter=100000, print_flag=False):
    u = np.vstack((0, u0, 0))
    v = np.empty(u0.shape)
    df = pd.DataFrame(columns=[f'||u-ue||2'] + [f'||Δu||∞'])
    if print_flag:
        if ue is None: ue = np.zeros(u0.shape)
        df.loc[0] = [la.norm(u0 - ue, np.inf), np.nan]
    for k in range(max_iter):
        m = 0
        for i in range(1, u.shape[0] - 1):
            v[i - 1] = (u[i - 1] + u[i + 1] + f[i - 1]) / 2
            m = np.max([m, np.abs(v[i - 1, 0] - u[i, 0])])
        if print_flag: df.loc[k + 1] = [la.norm(v - ue, np.inf), m]
        for i in range(1, u.shape[0] - 1):
            u[i] = v[i - 1]
        if m < eps: return (v, df) if print_flag else (v, k, la.norm(v - ue, np.inf))
    raise RuntimeError('Failed to converge.')


# Gauss-Seidel iteration
def gauss_seidel(f, u0, ue=None, eps=1e-5, max_iter=100000, print_flag=False):
    u = np.vstack((0, u0, 0))
    v = np.empty(u0.shape)
    df = pd.DataFrame(columns=[f'||u-ue||2'] + [f'||Δu||∞'])
    if print_flag:
        if ue is None: ue = np.zeros(u0.shape)
        df.loc[0] = [la.norm(u0 - ue, np.inf), np.nan]
    for k in range(max_iter):
        m = 0
        v[0] = (u[2] + f[0]) / 2
        for i in range(2, u.shape[0] - 1):
            v[i - 1] = (v[i - 2] + u[i + 1] + f[i - 1]) / 2
            m = np.max([m, np.abs(v[i - 1, 0] - u[i, 0])])
        if print_flag: df.loc[k + 1] = [la.norm(v - ue, np.inf), m]
        for i in range(1, u.shape[0] - 1):
            u[i] = v[i - 1]
        if m < eps: return (v, df) if print_flag else (v, k, la.norm(v - ue, np.inf))
    raise RuntimeError('Failed to converge.')


# Main
uk_dict1, uk_dict2 = {}, {}

for n in [10, 20, 40, 80, 160]:
    h = 1 / n
    x = np.linspace([h], [1 - h], n - 1)

    f = np.pi**2 * np.sin(np.pi * x)
    f *= h**2

    u0 = np.zeros((n - 1, 1))
    ue = np.sin(np.pi * x)

    uk_dict1[n] = jacobi(f, u0, ue, eps=1e-10)
    uk_dict2[n] = gauss_seidel(f, u0, ue, eps=1e-10)

# Data CSV
dict = {'x': np.linspace(0.1, 0.9, 9)}
for n in [10, 20, 40, 80, 160]:
    h = 1 / n
    dict[f'u{h}'] = uk_dict1[n][0][:, 0][int(n / 10 - 1)::int(n / 10)]
dict['ue'] = np.sin(np.pi * dict['x'])
df = pd.DataFrame(dict)
df.to_csv(out_dir + 'jacobi.csv')

dict = {'x': np.linspace(0.1, 0.9, 9)}
for n in [10, 20, 40, 80, 160]:
    h = 1 / n
    dict[f'u{h}'] = uk_dict2[n][0][:, 0][int(n / 10 - 1)::int(n / 10)]
dict['ue'] = np.sin(np.pi * dict['x'])
df = pd.DataFrame(dict)
df.to_csv(out_dir + 'gauss-seidel.csv')

# Data plot
fig, ax = plt.subplots(1, 2, figsize=(8, 4), constrained_layout=True)

n = 10
h, x = 1 / n, np.linspace(0, 1, n + 1)
ax[0].plot(x, np.vstack((0, uk_dict1[n][0], 0)), 'C1o-', mec='1.0', linewidth=1, label=r'$u_{' + f'{h}' + '}(x)$')

n = 160
h, x = 1 / n, np.linspace(0, 1, n + 1)
ax[1].plot(x, np.vstack((0, uk_dict1[n][0], 0)), linewidth=1, label=r'$u_{' + f'{h}' + '(x)}$')

for i in [0, 1]:
    ax[i].set_xlabel(r'$x$')
    ax[i].set_xlim(0.0, 1.0)
    ax[i].set_ylim(0.0, 1.05)
    ax[i].grid()
    ax[i].legend()

fig.savefig(out_dir + 'jacobi.pdf')

fig, ax = plt.subplots(1, 2, figsize=(8, 4), constrained_layout=True)

n = 10
h, x = 1 / n, np.linspace(0, 1, n + 1)
ax[0].plot(x, np.vstack((0, uk_dict2[n][0], 0)), 'C1o-', mec='1.0', linewidth=1, label=r'$u_{' + f'{h}' + '}(x)$')

n = 160
h, x = 1 / n, np.linspace(0, 1, n + 1)
ax[1].plot(x, np.vstack((0, uk_dict2[n][0], 0)), linewidth=1, label=r'$u_{' + f'{h}' + '(x)}$')

for i in [0, 1]:
    ax[i].set_xlabel(r'$x$')
    ax[i].set_xlim(0.0, 1.0)
    ax[i].set_ylim(0.0, 1.05)
    ax[i].grid()
    ax[i].legend()

fig.savefig(out_dir + 'gauss-seidel.pdf')

# Error analysis
df = pd.DataFrame([[n, 1 / n, uk_dict1[n][2], uk_dict2[n][2]] for n in [10, 20, 40, 80, 160]], columns=['n', 'h', 'eh1', 'eh2'])
df['logh'] = np.log(df['h'])
df['logeh1'] = np.log(df['eh1'])
df['logeh2'] = np.log(df['eh2'])
df.to_csv(out_dir + 'linear-itr-error.csv')

# Convergence
df = pd.DataFrame([[n, uk_dict1[n][1], uk_dict2[n][1]] for n in [10, 20, 40, 80, 160]], columns=['n', 'k1', 'k2'])
df.to_csv(out_dir + 'linear-itr-k.csv')

fig, ax = plt.subplots(figsize=(8, 4), constrained_layout=True)

ax.set_xticks(df['n'])
ax.set_xlabel(r'$n$')
ax.set_ylim(0, 90000)
ax.plot(df['n'], df['k1'], 'C0o-', mec='1.0', linewidth=1, label=r'$k$ of Jacobi Iter.')
ax.plot(df['n'], df['k2'], 'C1o-', mec='1.0', linewidth=1, label=r'$k$ of Gauss-Seidel Iter.')
ax.grid()
ax.legend()

fig.savefig(out_dir + 'linear-itr-k.pdf')