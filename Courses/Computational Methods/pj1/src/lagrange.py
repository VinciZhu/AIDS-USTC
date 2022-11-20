import pandas as pd
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
mpl.rc('font', family='serif', size=15)
mpl.rc('mathtext', fontset='stix')
mpl.rc('text', usetex=True)

df = pd.read_csv('data_points.csv')
X, Y = df['x'].to_numpy(dtype=int), df['f(x)'].to_numpy(dtype=float)


def lagrange_interp(X, Y, x):
    n = len(X)
    y = 0
    for i in range(n):
        l = 1
        for j in range(i):
            l *= (x - X[j]) / (X[i] - X[j])
        for j in range(i+1, n):
            l *= (x - X[j]) / (X[i] - X[j])
        y += l * Y[i]
    return y


def L1(x): return lagrange_interp(X[:-1], Y[:-1], x)
def L2(x): return lagrange_interp(X[1:], Y[1:], x)
def R(x): return (x - X[0]) / (X[0] - X[-1]) * (L1(x) - L2(x))


out_df = pd.DataFrame([[x, L1(x), L2(x), R(x)] for x in [
                      1910, 1965, 2002, 2012]], columns=['x', 'L1', 'L2', 'R'])

x_range = np.linspace(1900, 2020, 100)
fig, (ax1, ax2) = plt.subplots(2, figsize=(8, 8), constrained_layout=True)
ax1.plot(X, Y, 'ro', label=r'$f(x)$')
ax1.plot(x_range, [L1(x) for x in x_range], label=r'$L_5(x)$')
ax1.plot(x_range, [L2(x) for x in x_range], label=r'$\tilde{L}_5(x)$')
ax1.set_title('a)', loc='left')
ax1.set_xlim(1900, 2010)
ax1.set_xticks(np.arange(1900, 2020, 10))
ax1.set_ylim(0.5e5, 2.5e5)
ax1.set_xlabel(r'$x$ (year)')
ax1.set_ylabel(r'Population ($10^3$)')
ax1.grid()
ax1.legend()

ax2.plot(x_range, [R(x) for x in x_range],
         label=r'$$f(x)-L_5(x)\approx \frac{x-x_0}{x_0-x_{6}}(L_5(x)-\tilde{L}_5(x))$$')
ax2.set_title('b)', loc='left')
ax2.set_xlim(1900, 2010)
ax2.set_xticks(np.arange(1900, 2020, 10))
ax2.set_ylim(-1e4, 1e4)
ax2.set_xlabel(r'$x$ (year)')
ax2.set_ylabel(r'Approx. error ($10^3$)')
ax2.grid()
ax2.legend()

fig.savefig('lagrange-interpolation.pdf')
print(out_df)
