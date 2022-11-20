import numpy as np
import numpy.linalg as la
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)
mpl.rc('text.latex', preamble=r'\usepackage{bm}')

out_dir = '../assets/output/'


# Newton iteration
def newton(g, J, u0, ue=None, eps=1e-5, max_iter=100, print_flag=False):
    u, gu = u0.copy(), g(u0)
    df = pd.DataFrame(columns=[f'||u-ue||2'] + [f'||g(u)||∞'] + [f'||Δu||∞'])
    if print_flag:
        if ue is None: ue = np.zeros(u0.shape)
        df.loc[0] = [la.norm(u0 - ue, np.inf), la.norm(gu, np.inf), np.nan]
    for k in range(max_iter):
        Ju = J(u)
        du = la.solve(Ju, -gu)
        u += du
        gu = g(u)
        if print_flag:
            df.loc[k + 1] = [la.norm(u - ue, np.inf), la.norm(gu, np.inf), la.norm(du, np.inf)]
        if la.norm(du, np.inf) < eps:
            return (u, df) if print_flag else (u, k, la.norm(u - ue, np.inf))
    raise RuntimeError('Failed to converge.')


# Main
def g(u):
    g1 = np.empty((n - 1, 1))
    g1[0] = 2 * u[0] - u[1] + h**2 * u[0]**3 - h**2 * f[0]
    g1[n - 2] = -u[n - 3] + 2 * u[n - 2] + h**2 * u[n - 2]**3 - h**2 * f[n - 2]
    for i in range(1, n - 2):
        g1[i] = -u[i - 1] + 2 * u[i] - u[i + 1] + h**2 * u[i]**3 - h**2 * f[i]
    return g1


def J(u):
    J1 = J0.copy()
    for i in range(0, n - 1):
        J1[i, i] += 3 * h**2 * u[i]**2
    return J1


uk_dict, df_dict = {}, {}

for n in [10, 20, 40, 80, 160]:
    h = 1 / n
    x = np.linspace([h], [1 - h], n - 1)

    f = np.sin(np.pi * x)
    f = np.pi**2 * f + f**3

    u0 = np.zeros((n - 1, 1))
    ue = np.sin(np.pi * x)

    J0 = np.zeros((n - 1, n - 1))
    J0[0, 0] = 2
    for i in range(1, n - 1):
        J0[i - 1, i] = -1
        J0[i, i - 1] = -1
        J0[i, i] = 2

    uk_dict[n], df_dict[n] = newton(g, J, u0, ue, eps=1e-8, print_flag=True)

# Data plot
fig, ax = plt.subplots(1, 2, figsize=(8, 4), constrained_layout=True)

n = 10
h, x = 1 / n, np.linspace(0, 1, n + 1)
ax[0].plot(x, np.vstack((0, uk_dict[n], 0)), 'C1o-', mec='1.0', linewidth=1, label=r'$u_{' + f'{h}' + '}(x)$')

n = 160
h, x = 1 / n, np.linspace(0, 1, n + 1)
ax[1].plot(x, np.vstack((0, uk_dict[n], 0)), linewidth=1, label=r'$u_{' + f'{h}' + '(x)}$')

for i in [0, 1]:
    ax[i].set_xlabel(r'$x$')
    ax[i].set_xlim(0.0, 1.0)
    ax[i].set_ylim(0.0, 1.05)
    ax[i].grid()
    ax[i].legend()

fig.savefig(out_dir + 'newton.pdf')

# Data CSV
dict = {'x': np.linspace(0.1, 0.9, 9)}
for n in [10, 20, 40, 80, 160]:
    h = 1 / n
    dict[f'u{h}'] = uk_dict[n][:, 0][int(n / 10 - 1)::int(n / 10)]
dict['ue'] = np.sin(np.pi * dict['x'])
df = pd.DataFrame(dict)
df.to_csv(out_dir + 'newton.csv')

# Error analysis
df = pd.DataFrame([[n, 1 / n, df_dict[n]['||u-ue||2'].iloc[-1]] for n in [10, 20, 40, 80, 160]], columns=['n', 'h', 'eh'])
df['logh'] = np.log(df['h'])
df['logeh'] = np.log(df['eh'])
df.to_csv(out_dir + 'newton-error.csv')