import numpy as np
import numpy.linalg as la
import matplotlib as mpl
import matplotlib.pyplot as plt
import pandas as pd

mpl.rc('font', family='serif', size=15)
mpl.rc('text', usetex=True)

out_dir = '../assets/output/'


def newton(f, Jf, x0, eps=1e-5, max_iter=100, print_flag=False):
    x, fx = x0.copy(), f(x0)
    if (print_flag):
        df = pd.DataFrame(columns=[f'x{i}' for i in range(x.size)] +
                          [f'f{i}(x)' for i in range(x.size)] + [f'Δx{i}' for i in range(x.size)])
        df.loc[0] = x0[:, 0].tolist() + fx[:, 0].tolist() + [np.nan] * x.size
    for k in range(max_iter):
        Jx = Jf(x)
        dx = la.solve(Jx, -fx)
        x += dx
        fx = f(x)
        if (print_flag):
            df.loc[k + 1] = x[:, 0].tolist() + fx[:, 0].tolist() + dx[:, 0].tolist()
        if la.norm(dx, np.inf) < eps:
            return x, df
    raise RuntimeError('Failed to converge.')


def f(X):
    x, y = X[0, 0], X[1, 0]
    return np.array([[x**2 + y**2 - 1], [x**3 - y]])


def Jf(X):
    x, y = X[0, 0], X[1, 0]
    return np.array([[2 * x, 2 * y], [3 * x**2, -1]])


x0 = np.array([[0.8], [0.6]])

x, df = newton(f, Jf, x0, print_flag=True)
df.to_csv(out_dir + 'newton.csv')