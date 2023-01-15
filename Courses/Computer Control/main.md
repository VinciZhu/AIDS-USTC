# 大作业: 四旋翼无人机控制

<div align="center">姓名: 朱云沁 &emsp; 学号: PB20061372 &emsp; 日期: 2022 年 12 月 30 日</div>

---

<br>

已知四旋翼无人机参数如下:

<figcaption> <b>表 1.</b> 四旋翼无人机参数 </figcaption>

| <div align="center"> 参数 </div> | <div align="center"> 取值 </div>            |
| :------------------------------- | :------------------------------------------ |
| 质量 $m$                         | $0.03\ \mathrm{kg}$                         |
| 重力加速度 $g$                   | $9.81\ \mathrm{m/s^2}$                      |
| 转动惯量 $I_x,I_y$               | $1.5\times 10^{-5}\ \mathrm{kg\cdot m^2}$   |
| 转动惯量 $I_z$                   | $3\times 10^{-5}\ \mathrm{kg\cdot m^2}$     |
| 阻力系数 $k_x, k_y, k_z$         | $4.5\times 10^{-3}\ \mathrm{kg/s}$          |
| 阻力矩系数 $k_p, k_q, k_r$       | $4.5\times 10^{-4}\ \mathrm{kg\cdot m^2/s}$ |
| 悬停高度 $z_d$                   | $2\ \mathrm{m}$                             |
| 悬停偏航角 $\psi_d$              | $\pi/4\ \mathrm{rad}$                       |

假设四旋翼无人机在高度 $z_d$ 处以偏航角 $\psi_d$ 悬停. 此时, 位移为 $(x, y, z) = (0, 0, z_d)$, 速度为 $(\dot x, \dot y, \dot z) = (0, 0, 0)$; 滚转, 俯仰, 偏航角为 $(\phi, \theta, \psi) = (0, 0, \psi_d)$, 相应的角速度为 $(\phi, \theta, \psi)$ $= (0, 0, \psi_d)$. 无人机恰好不下降, 即升力 $u_1 = mg$; 滚转, 俯仰, 偏航力矩 $u_2 = u_3 = u_4 = 0$.

记高度, 偏航角, 升力的增量分别为

$$
\Delta z = z-z_d,\quad \Delta \psi = \psi-\psi_d,\quad \Delta u_1 = u-mg.
$$

<div>取状态向量</div>

$$
\mathcal{X} = [x, y, \Delta z, \dot x, \dot y, \dot z, \phi, \theta, \Delta\psi, p, q, r]^T,
$$

<div>输入向量</div>

$$
\mathcal{U} = [\Delta u_1, u_2, u_3, u_4]^T,
$$

<div>以及输出向量</div>

$$
\mathcal{Y} = [x, y, \Delta z, \Delta \psi]^T.
$$

则四旋翼无人机线性化动力学模型为如下状态空间表达式

$$
\dot{\mathcal{X}} = A\mathcal{X} + B\mathcal{U},\quad \mathcal{Y} = C\mathcal{X}.
$$

其中, 系统矩阵, 输入矩阵, 输出矩阵分别为

$$
A = \left[\begin{array}{cccccccccccc}0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0\\0 & 0 & 0 & - \frac{k_{x}}{m} & 0 & 0 & g \sin{\left(\psi_d \right)} & g \cos{\left(\psi_d \right)} & 0 & 0 & 0 & 0\\0 & 0 & 0 & 0 & - \frac{k_{y}}{m} & 0 & - g \cos{\left(\psi_d \right)} & g \sin{\left(\psi_d \right)} & 0 & 0 & 0 & 0\\0 & 0 & 0 & 0 & 0 & - \frac{k_z}{m} & 0 & 0 & 0 & 0 & 0 & 0\\0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0\\0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0\\0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1\\0 &times 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & - \frac{k_p}{I_{x}} & 0 & 0\\0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & - \frac{k_{q}}{I_{y}} & 0\\0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & - \frac{k_{r}}{I_z}\end{array}\right]
$$

$$
B = \left[\begin{matrix}0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\\frac{1}{m} & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & 0 & 0 & 0\\0 & \frac{1}{I_{x}} & 0 & 0\\0 & 0 & \frac{1}{I_{y}} & 0\\0 & 0 & 0 & \frac{1}{I_z}\end{matrix}\right],\quad
C = \left[\begin{array}{cccccccccccc}1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0\\0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0\end{array}\right].
$$

初始化 Jupyter Notebook 环境, 并利用 sympy 库表征如上状态空间模型, 代码如下:

```python
import numpy as np
from sympy import *
from sympy.abc import t, s
import control

import matplotlib as mpl
import matplotlib.pyplot as plt

mpl.rcParams['mathtext.fontset'] = 'cm'
mpl.rcParams['font.size'] = 8
mpl.rcParams['font.family'] = 'serif'
mpl.rcParams['lines.linewidth'] = 0.8
mpl.rcParams['lines.markerfacecolor'] = 'none'

# 固定参数
m, g, k_x, k_y, k_z, k_p, k_q, k_r, I_x, I_y, I_z, z_d, psi_d = symbols(
    'm g k_x k_y k_z k_p k_q k_r I_x I_y I_z z_d psi_d')
params = {
    m:      0.03,       # 质量
    g:      9.81,       # 重力加速度
    k_x:    4.5e-3,     # 阻力系数 x 分量
    k_y:    4.5e-3,     # 阻力系数 y 分量
    k_z:    4.5e-3,     # 阻力系数 z 分量
    k_p:    4.5e-4,     # 阻力矩系数 p 分量
    k_q:    4.5e-4,     # 阻力矩系数 q 分量
    k_r:    4.5e-4,     # 阻力矩系数 r 分量
    I_x:    1.5e-5,     # 转动惯量 x 分量
    I_y:    1.5e-5,     # 转动惯量 y 分量
    I_z:    3e-5,       # 转动惯量 z 分量
    z_d:    2,          # 初始 z 坐标 (悬停高度)
    psi_d:  0.25 * pi,  # 初始偏航角
}

# 状态向量
x, y, Deltaz, xdot, ydot, zdot, phi, theta, Deltapsi, p, q, r = symbols(
    'x y Δz xdot ydot zdot phi theta Δψ p q r')
X = Matrix([x, y, Deltaz, xdot, ydot, zdot, phi, theta, Deltapsi, p, q, r])

# 初始状态
initial_state = {
    x:          0,
    y:          0,
    Deltaz:     0,
    xdot:       0,
    ydot:       0,
    zdot:       0,
    phi:        0,
    theta:      0,
    Deltapsi:   0,
    p:          0,
    q:          0,
    r:          0,
}

# 输入向量
Deltau_1, u_2, u_3, u_4 = symbols('Δu_1 u_2 u_3 u_4')
U = Matrix([Deltau_1, u_2, u_3, u_4])

display(U)

# 输出向量
Y = Matrix([x, y, Deltaz, Deltapsi])

display(Y)

# 系统矩阵
A = zeros(12, 12)
A[0, 3] = A[1, 4] = A[2, 5] = 1
A[6, 9] = A[7, 10] = A[8, 11] = 1
A[3, 6], A[3, 7] = g * sin(psi_d), g * cos(psi_d)
A[4, 6], A[4, 7] = -g * cos(psi_d), g * sin(psi_d)
A[3, 3], A[4, 4], A[5, 5] = -k_x / m, -k_y / m, -k_z / m
A[9, 9], A[10, 10], A[11, 11] = -k_p / I_x, -k_q / I_y, -k_r / I_z

display(A)

# 输入矩阵
B = zeros(12, 4)
B[5, 0] = 1 / m
B[9, 1], B[10, 2], B[11, 3] = 1 / I_x, 1 / I_y, 1 / I_z

display(B)

# 输出矩阵
C = zeros(4, 12)
C[0, 0] = C[1, 1] = C[2, 2] = C[3, 8] = 1

display(C)
```

1.  计算矩阵 $A$ 的特征值, 并判断系统的稳定性.

    **解:** 运行如下代码:

    ```python
    # 系统矩阵的特征值
    eigenvals = A.subs(params).eigenvals()
    print(eigenvals)

    # 判断系统的稳定性
    if all([re(eigenval) < 0 for eigenval in eigenvals]):
        print('系统稳定')
    ```

    由输出结果知, 矩阵 $A$ 的特征值为 $\lambda=0, -0.15, -15, -30$, 代数重数分别为 $6, 3, 1, 2.$ 该系统在虚轴有重复极点 $\lambda=0$, 故系统不稳定.

2.  给出从输入 $\Delta U_1(s)$ 到输出 $\Delta Z(s)$ 的高度控制子系统传递函数 $G_z(s)$, 以及从输入 $\Delta U_4(s)$ 到输出 $\Delta \varPsi(s)$ 的偏航角控制子系统传递函数 $G_{\psi}(s)$.

    **解:** 由状态空间模型, 得到高度控制子系统的微分方程为

    $$
    \ddot z = -\frac{k_z}{m}\dot z + \frac{1}{m}\Delta u_1.
    $$

    故高度控制子系统的传递函数为

    $$
    G_z(s) = \frac{\frac{1}{m}}{s^2 + \frac{k_z}{m}s} = \frac{100}{3(s^2 + 0.15s)}.
    $$

    偏航角控制子系统的微分方程为

    $$
    \ddot{\psi} = -\frac{k_r}{I_z}\dot{\psi} + \frac{1}{I_z} u_4.
    $$

    故偏航角控制子系统的传递函数为

    $$
    G_\psi(s) = \frac{\frac{1}{I_z}}{s^2 + \frac{k_r}{I_z}s} = \frac{10^5}{3(s^2 + 15s)}.
    $$

3.  考虑四旋翼无人机的偏航角控制子系统. 输入如下偏航力矩, 分别绘制偏航角响应曲线:

    1.  脉冲输入 $u_4(t) = 3\times 10^{-5}\cdot \delta(t)$;
    2.  阶跃输入 $u_4(t) = 3\times 10^{-5}\cdot 1(t)$;
    3.  正弦输入 $u_4(t) = 3\times 10^{-5}\cdot \sin(t)\cdot1(t)$;

    根据输出结果, 给出偏航角在脉冲输入下的稳态值. 用终值定理验证该稳态值.

    **解:** 运行如下代码:

    ```python
    def plot_response(T, yout, ax=None):
        if ax is None:
            ax = plt.gca()
        ax.plot(T, yout)
        ax.set_xlim(left=0)
        ax.grid(True)


    def sympy_to_control(G, s=s):
        num, den = fraction(G)
        num = np.array(Poly(num, s).all_coeffs(), dtype=float)
        den = np.array(Poly(den, s).all_coeffs(), dtype=float)
        return control.tf(num, den)

    # 偏航角传递函数
    sys = sympy_to_control(G_psi.subs(params))
    display(sys)

    fig, ax = plt.subplots(3, 1, figsize=(4, 6))

    # 脉冲输入
    T = np.linspace(0, 1, 1000)
    T, yout = control.impulse_response(sys, T)
    plot_response(T, 3e-5 * yout, ax[0])
    ax[0].hlines(0.067, 0, 1, linestyles='dashed')

    # 阶跃输入
    T = np.linspace(0, 0.1, 1000)
    T, yout = control.step_response(sys, T)
    plot_response(T, 3e-5 * yout, ax[1])

    # 正弦输入
    T = np.linspace(0, 10, 1000)
    T, yout = control.forced_response(sys, T, U=np.sin(T))
    plot_response(T, 3e-5 * yout, ax[2])
    ax[2].set_xlabel(r'$t / \rm{s}$')

    titles = [
        r'$\rm{(a)}\ u_4(t) = 3 \times 10^{-5} \cdot \delta(t)$',
        r'$\rm{(b)}\ u_4(t) = 3 \times 10^{-5} \cdot 1(t)$',
        r'$\rm{(c)}\ u_4(t) = 3 \times 10^{-5} \cdot \sin(t)$'
    ]

    for ax, title in zip(ax, titles):
        ax.set_ylim(bottom=0)
        ax.set_ylabel(r'$\Delta\psi / \rm{rad}$')
        ax.set_title(title)

    fig.tight_layout()
    fig.savefig('figs/p3.svg')
    ```

    得到三种情况下的响应曲线如下:

    ![](figs/p3.svg)
    <figcaption> <b>图 1.</b> 第 3 题中的高度响应曲线. (a) 脉冲输入; (b) 阶跃输入; (c) 正弦输入 </figcaption> <br>

    由图 1 (a) 数据可知, 偏航角在脉冲输入下的稳态值约为 $0.067\ \mathrm{rad}$. 用终值定理验证:

    $$
    \Delta\psi(\infty) = \lim_{s\to 0} sG_\psi U_4(s) = \lim_{s\to 0} \frac{1}{s + 15} \approx 0.067.
    $$

    与仿真结果一致.

4.  考虑四旋翼无人机的高度控制子系统. 假设选取比例控制器, 即 $\Delta u_1 = -k\Delta z$, $k > 0$. 选取增益 $k$ 使得高度响应曲线分别满足如下要求 (初始条件 $\Delta z(0) = 1, \dot z(0) = 0$):

    1.  高度响应曲线发散;
    2.  高度响应曲线收敛到非零稳态值;
    3.  高度响应曲线收敛到零且没有振荡;
    4.  高度响应曲线经过振荡后手收敛到零.

    **解:**
    比例控制器下, 闭环传递函数为

    $$
    G_c(s) = \frac{kG_z(s)}{1+kG_z(s)} = \frac{\frac{100k}{3}}{s^2 + 0.15s + \frac{100k}{3}}.
    $$

    求解微分方程, 得零输入响应为

    $$
    \Delta Z(s) = \frac{s + \frac{k_z}{m}}{s^2 + \frac{k_z}{m}s + \frac{k}{m}}\Delta z(0) = \frac{s + 0.15}{s^2 + 0.15s + \frac{100k}{3}}
    $$

    特征方程 $s^2 + 0.15s + \frac{100k}{3} = 0$ 的根位于左半平面, 系统稳定, 故 (1) 无法满足.

    由终值定理知, 稳态响应 $\Delta z(\infty) = \lim_{s\to 0} s\Delta Z (s) = 0$, 故 (2) 无法满足.

    高度响应振荡当且仅当 $\Delta Z(s)$ 存在共轭极点, 即

    $$
    0.15^2 - 4\frac{100k}{3} < 0.
    $$

    解得 $k > 1.9625 \times 10^{-4}$.

    选取 $k = 1\times 10^{-4}$, 使得 (3) 满足; 当 $k = 1\times 10^{-2}, 1 \times 10^{-3}, 2\times 10^{-4}$, 使得 (4) 满足. 运行如下代码, 绘制响应曲线:

    ```python
    # 高度传递函数
    tf = G_z.subs(params)
    display(tf)

    # 初始条件
    Deltaz_0 = 1


    def plot_p4(k):
        # 比例控制器
        ctr = k
        # 闭环传递函数
        tfc = simplify(ctr * tf / (1 + ctr * tf))

        sys = sympy_to_control(tfc)
        sys = control.tf2ss(sys)
        # 利用观察矩阵求解初始状态向量
        X_0 = np.linalg.solve(control.obsv(sys.A, sys.C), [Deltaz_0, 0])

        T = np.linspace(0, 200, 1000)
        T, yout = control.initial_response(sys, T, X0=X_0)
        plot_response(T, yout)
        if np.min(yout) < 0:
            print(f'k = {k} 振荡')


    plt.figure(figsize=(4, 3))

    k_list = [0.01, 0.001, 0.0002, 0.0001]
    for k in k_list:
        plot_p4(k)

    plt.legend([f'$k = {k}$' for k in k_list])
    plt.xlabel(r'$t / \rm{s}$')
    plt.ylabel(r'$\Delta z / \rm{m}$')
    plt.savefig('figs/p4.svg')
    ```

    得到 $k$ 的四种取值下, 高度的零输入响应曲线如下:

    ![](figs/p4.svg)
    <figcaption> <b>图 2.</b> 第 4 题的高度响应曲线</figcaption> <br>

    与上述分析结果一致.

5.  考虑阻力系数 $k_z = 0$ 的四旋翼无人机高度控制子系统. 假设输入升力 $\Delta u_1$ 存在时滞 $T = 1 \times 10^{-3}$ s, 则高度响应为 $\Delta Z(s) = \frac{e^{-Ts}}{ms^2} \Delta U_1(s)$. 利用一阶 Pade 近似 $e{-Ts} = \frac{2-Ts}{2+Ts}$, 将开环传递函数近似为

    $$
    G_z(s) = \frac{2-Ts}{ms^2(2+Ts)}.
    $$

    是否存在增益的变化范围, 使得在如下结构的反馈控制器 $K(s)$ 下, 高度子系统稳定:

    1.  $K(s) = k_p$;
    2.  $K(s) = k_p + k_d s$.

    如果存在, 选取相应增益, 绘制高度响应曲线 (初始条件 $\Delta z(0) = 1, \dot z(0) = 0$).

    **解:** PD 控制器下, 闭环传递函数为

    $$
    G_c(s) = \frac{KG_z(s)}{1 + KG_z(s)} = \frac{- T k_d s^{2} + (- T k_p + 2 k_d) s + 2 k_p}{T m s^{3}+ (- T k_d + 2 m) s^{2} + (- T k_p + 2 k_d) s + 2 k_p }.
    $$

    代入数据, 得特征方程

    $$
    3 \times 10^{-5} s^{3} + (0.06 - 0.001 k_d) s^{2} + (2 k_d - 0.001 k_p) s + 2k_p= 0
    $$

    劳斯阵列为

    $$
    \left[\begin{matrix}3 \times 10^{-5} & 2 k_d - 0.001 k_p & 0 & 0\\0.06 - 0.001 k_d & 2.0 k_p & 0 & 0\\\frac{- 6 \times 10^{-5} k_p + \left(0.06 - 0.001 k_d\right) \left(2 k_d - 0.001 k_p\right)}{0.06 - 0.001 k_d} & 0 & 0 & 0\\2 k_p & 0 & 0 & 0\end{matrix}\right]
    $$

    故闭环系统稳定当且仅当

    $$
    \begin{gathered}
    60 - k_d > 0 \\
    60k_p + (k_d - 60)(2000k_d - k_p) > 0 \\
    2k_p > 0
    \end{gathered}
    $$

    解得 $0 < k_d < 60$ 且 $0 < k_p < 2000\times\frac{k_d(k_d - 60)}{k_d - 120}$. 可知比例控制器 (1) 不能使系统稳定.

    在上述范围内, 选取 $k_d = 50, 20$, $k_p = 1\times 10^3, 1\times 10^4$, 使得系统稳定. 运行如下代码, 绘制高度响应曲线:

    ```python
    Td, k_P, k_D, T_D, p_I = symbols('T k_p k_d T_d p_i', positive=True)
    # PD 控制器
    K = k_P + k_D * s
    # 开环传递函数
    G_o = simplify(K * G_z * (2 - Td * s) / (2 + Td * s))
    # 闭环传递函数
    G_c = simplify(G_o / (1 + G_o))
    num, den = fraction(G_c)
    num, den = Poly(num, s), Poly(den, s)
    G_c = num / den

    def plot_p5(k_p, k_d):
        sys = sympy_to_control(
            G_c.subs({
                m: 0.03,
                k_z: 0,
                Td: 1e-3,
                k_P: k_p,
                k_D: k_d
            }))
        sys = control.tf2ss(sys)
        # 初始输出为 -1, 各阶导数为 0
        X_0 = np.linalg.solve(control.obsv(sys.A, sys.C), [-1, 0, 0])

        T = np.linspace(0, 0.1, 1000)
        # 阶跃参考输入
        T, yout = control.step_response(sys, T, X0=X_0)
        plot_response(T, yout)


    plt.figure(figsize=(4, 3))

    k_list = [(1000, 50), (10000, 50), (1000, 20), (10000, 20)]
    labels = []
    for k_p, k_d in k_list:
        plot_p5(k_p, k_d)
        labels.append(f'$k_p = {k_p}, k_d = {k_d}$')

    plt.legend(labels)
    plt.xlabel(r'$t / \rm{s}$')
    plt.ylabel(r'$\Delta z / \rm{m}$')
    plt.savefig('figs/p5.svg')
    ```

    得到 PD 控制器的四种增益取值下, 阶跃响应曲线如下:

    ![](figs/p5.svg)
    <figcaption> <b>图 3.</b> 第 5 题的高度响应曲线</figcaption> <br>

6.  考虑阻力系数 $k_z = 0$ 的四旋翼无人机高度控制子系统 $\Delta Z(s) = \frac{1}{ms^2} \Delta U_1(s)$. 研究 PD 和 PI 控制器对高度控制子系统的稳定性及性能的影响. 其中, PD 控制器使得开环传递函数为 $G_{\rm PD}(s) = k_p\frac{T_ds+1}{ms^2}$, PD 控制器使得开环传递函数为 $G_{\rm PI}(s) = k_p\frac{s+p_i}{ms^2}$.

    1.  分别针对如下情形, 绘制闭环系统以 $k_p$ 为变化参数的根轨迹:

        1. $T_d = 1,\ T_d = 2,\ T_d = 4$;
        2. $p_i = 1,\ p_i = 2,\ p_i = 4$.

    2.  根据上述根轨迹的图形, 回答如下问题:

        1.  PD 控制器是否可以使得闭环系统是稳定的?
        2.  当 $T_d$ 增大时, 关于闭环系统的极点, 你能得到什么结论?
        3.  PI 控制器是否可以使得闭环系统是稳定的?
        4.  当 $p_i$ 增大时, 关于闭环系统的极点, 你能得到什么结论?

    **解:** 运行如下代码, 绘制根轨迹:

    ```python
    # PD 控制器: 开环传递函数
    G_PD = k_P * (T_D * s + 1) * G_z
    # PI 控制器: 开环传递函数
    G_PI = k_P * (s + p_I) / s * G_z

    display(G_PD, G_PI)

    def plot_p6(G, param):
        fig, ax = plt.subplots(3, 1, figsize=(4, 6))

        for i, val in enumerate([1, 2, 4]):
            L = G.subs({k_P: 1, m: 0.03, k_z: 0, param: val})
            sys = sympy_to_control(L)
            _ = control.root_locus(sys,
                                xlim=(-5, 5),
                                ylim=(-2, 2),
                                grid=False,
                                ax=ax[i])
            ax[i].set_title(None)
            ax[i].set_aspect(1)

        return fig, ax

    # PD 控制器: 根轨迹
    fig, ax = plot_p6(G_PD, T_D)
    titles = [
        r'$\rm{(a)}\ T_d = 1$', r'$\rm{(b)}\ T_d = 2$', r'$\rm{(c)}\ T_d = 4$'
    ]
    for i in range(3):
        ax[i].set_title(titles[i])
    fig.tight_layout()
    fig.savefig('figs/p6-pd.svg')

    # PI 控制器: 根轨迹
    fig, ax = plot_p6(G_PI, p_I)
    titles = [
        r'$\rm{(a)}\ p_i = 1$', r'$\rm{(b)}\ p_i = 2$', r'$\rm{(c)}\ p_i = 4$'
    ]
    for i in range(3):
        ax[i].set_title(titles[i])
    fig.tight_layout()
    fig.savefig('figs/p6-pi.svg')
    ```

    PD 控制器的三种 $T_d$ 取值下, 根轨迹如下:

    ![](figs/p6-pd.svg)
    <figcaption> <b>图 4.</b> 第 6 题中 PD 控制下的根轨迹</figcaption> <br>

    PI 控制器的三种 $p_i$ 取值下, 根轨迹如下:

    ![](figs/p6-pi.svg)
    <figcaption> <b>图 5.</b> 第 6 题中 PI 控制下的根轨迹</figcaption> <br>

    由图 4 知, PD 控制下, 闭环系统的 2 个极点均位于左半平面, 故 PD 控制器可以使闭环系统稳定. 当 $T_d$ 增大时, $L(s) = \frac{T_ds+1}{ms^2}$的零点向原点靠近, 使得闭环系统两条分支上的极点分别向原点与负无穷靠近.

    由图 5 知, PI 控制下, 闭环系统存在位于右半平面的根轨迹分支, 故 PI 控制器无法使闭环系统稳定. 当 $p_i$ 增大时, $L(s) = \frac{s+p_i}{ms^3}$的零点向负无穷靠近, 使得闭环系统位于负实轴分支的极点向负无穷靠近; 右半平面的两条分支, 其渐近线与正实轴的夹角减小, 使得其上的极点实部增大.

7.  考虑有阻力的四旋翼无人机高度控制子系统 $\Delta Z(s) = \frac{1}{ms(s+\frac{k_z}{m})} \Delta U_1(s)$. 采用 PD 控制器, 使得开环传递函数为 $G_{\rm PD}(s) = k_p\frac{T_d s+1}{ms(s+\frac{k_z}{m})}$. 当 $k_p = 0.03$ 时, 分别对 $T_d = 1,T_d = 2,T_d = 4$ 绘制 Bode 图. 当 $T_d$ 增大时, 增益裕度与相位裕度如何变化?

    **解:** 运行如下代码:

    ```python
    plt.figure(figsize=(4, 6))

    for i, val in enumerate([1, 2, 4]):
        L = G_PD.subs({k_P: 0.03, m: 0.03, k_z: 4.5e-3, T_D: val})
        sys = sympy_to_control(L)
        _ = control.bode(sys, omega_limits=(1e-2, 1e1), margins=True)
        print(control.margin(sys))

    labels = [r'$T_d = 1$', r'$T_d = 2$', r'$T_d = 4$']
    plt.legend(labels)
    plt.suptitle(None)
    plt.savefig('figs/p7.svg')
    ```

    得到 Bode 图如下:

    ![](figs/p7.svg)
    <figcaption> <b>图 6.</b> 第 7 题中 PD 控制下的 Bode 图</figcaption> <br>

    输出结果表明, $T_d = 1,T_d = 2,T_d = 4$ 三种情况下, 系统增益裕度均为无穷, 相位裕度分别为 $\rm PM = 58.446\degree, PM = 80.491\degree, PM = 88.573\degree$. 当 $T_d$ 增大时, 系统的相位裕度增大, 能够改善系统的瞬态响应特性.

8.  当偏航角为 0 时, 无人机在 $x$ 方向的动力学模型可以用如下单输入单输出系统描述:

    $$
    \frac{\mathrm{d}}{\mathrm{d} t} \begin{bmatrix}
    x \\ \dot{x} \\ \theta \\ q
    \end{bmatrix} = \begin{bmatrix}
    0 & 1 & 0 & 0 \\
    0 & -\frac{k_x}{m} & g & 0 \\
    0 & 0 & 0 & 1 \\
    0 & 0 & 0 & \frac{k_q}{I_y}
    \end{bmatrix} \begin{bmatrix}
    x \\ \dot{x} \\ \theta \\ q
    \end{bmatrix} + \begin{bmatrix}
    0 \\ 0 \\ 0 \\ \frac{1}{I_y}
    \end{bmatrix} u_3, \quad
    x = \begin{bmatrix}
    1 & 0 & 0 & 0
    \end{bmatrix} \begin{bmatrix}
    x \\ \dot{x} \\ \theta \\ q
    \end{bmatrix}.
    $$

    多数商业无人机无法直接获得俯仰力矩 $u_3$, 而是设计期望的俯仰角速度 $q$ 作为输入. 于是, 上述模型进一步简化为

    $$
    \frac{\mathrm{d}}{\mathrm{d} t} \begin{bmatrix}
    x \\ \dot{x} \\ \theta
    \end{bmatrix} = \begin{bmatrix}
    0 & 1 & 0  \\
    0 & -\frac{k_x}{m} & g  \\
    0 & 0 & 0  \\
    \end{bmatrix} \begin{bmatrix}
    x \\ \dot{x} \\ \theta
    \end{bmatrix} + \begin{bmatrix}
    0 \\ 0 \\ 1
    \end{bmatrix} q, \quad
    x = \begin{bmatrix}
    1 & 0 & 0
    \end{bmatrix} \begin{bmatrix}
    x \\ \dot{x} \\ \theta
    \end{bmatrix}.
    $$

    1.  写出从输入 $q$ 到输出 $x$ 的 $x$ 轴方向动力学模型的传递函数 $G_x(s)$.
    2.  设计如下形式的超前补偿器:

        $$
        K(s) = k\frac{Ts+1}{\alpha Ts+1},\quad 0.1\le \alpha < 0.1.
        $$

        使得无人机 x 轴方向动力学子系统至少满足以下要求中的任意三个要求:

        1.  渐近稳定;
        2.  对阶跃参考信号的稳态跟踪误差为零;
        3.  穿越频率不小于 $1.5$ rad/s;
        4.  相位裕度不小于 $40\degree$.

        判断是否存在超前补偿使得系统满足以上四个要求.

    3.  绘制无人机 $x$ 轴位置时间响应曲线 (初始条件 $x(0) = 1$, $\dot x(0) = 0$, $\theta(0) = 0$).

    **解:** 为了方便本题与第 9 题的求解, 封装如下函数

    ```python
    # 计算开环、闭环传递函数
    def sys_p89(G, args={k: 1, Td: 1, alpha: 1}):
        tf = G.subs(params) * K.subs(args)
        sys = sympy_to_control(tf)
        sysc = sympy_to_control(simplify(tf / (1 + tf)))
        return sys, sysc


    # 绘制 Bode 图
    def plot_p89_bode(sys):
        plt.figure(figsize=(4, 4))
        print(control.margin(sys))
        _ = control.bode(sys, omega_limits=(1e-2, 1e1), margins=True)
        plt.suptitle(None)


    # 绘制阶跃响应
    def plot_p89_response(sys, T, ref, zero_state=False, ax=None):
        if ax is None:
            plt.figure(figsize=(4, 3))
        sys = control.tf2ss(sys)
        x_0 = np.zeros(sys.A.shape[0])
        if not zero_state:
            x_0[0] = 1
        X_0 = np.linalg.solve(control.obsv(sys.A, sys.C), x_0)

        T, yout = control.forced_response(sys, T, U=ref, X0=X_0)
        plot_response(T, yout, ax=ax)
        if ax is None:
            plt.xlabel(r'$t / \rm{s}$')
            plt.ylabel(r'$x / \rm{m}$')
    ```

    从输入 $q$ 到输出 $x$ 的 $x$ 轴方向动力学模型的传递函数 $G_x(s)$ 为

    $$
    G_x(s) = \begin{bmatrix}
    1 & 0 & 0
    \end{bmatrix} \left(sI - \begin{bmatrix}
    0 & 1 & 0 \\
    0 & -\frac{k_x}{m} & g \\
    0 & 0 & 0
    \end{bmatrix}\right)^{-1} \begin{bmatrix}
    0 \\ 0 \\ 1
    \end{bmatrix}
    = \frac{g}{s^2(s+\frac{k_x}{m})}.
    $$

    代入数据, 得超前补偿下开环传递函数为

    $$
    KG_x(s) = \frac{9.81 k \left(T s + 1\right)}{s^{2} \left(s + 0.15\right) \left(T \alpha s + 1\right)}.
    $$

    该系统为 2 型系统, 对阶跃参考信号的稳态跟踪误差为

    $$
    e_{\rm ss} = \lim_{s\to 0} \frac{1}{1 + KG_x(s)} = 0,
    $$

    必定满足要求. 闭环系统的特征方程为

    $$
    T \alpha s^{4} + \left(0.15 T \alpha + 1\right) s^{3} + 0.15 s^{2} + 9.81 T k s + 9.81 k = 0,
    $$

    劳斯阵列为

    $$
    \left[\begin{matrix}T \alpha & 0.15 & 9.81 k & 0 & 0\\0.15 T \alpha + 1 & 9.81 T k & 0 & 0 & 0\\\frac{- 9.81 T^{2} \alpha k + 0.0225 T \alpha + 0.15}{0.15 T \alpha + 1.0} & 9.81 k & 0 & 0 & 0\\\frac{- 96.2361 T^{3} \alpha k^{2} + k \left(- 0.220725 T^{2} \alpha^{2} + 0.220725 T^{2} \alpha - 2.943 T \alpha + 1.4715 T - 9.81\right)}{- 9.81 T^{2} \alpha k + 0.0225 T \alpha + 0.15} & 0 & 0 & 0 & 0\\9.81 k & 0 & 0 & 0 & 0\end{matrix}\right].
    $$

    得到系统稳定的充分必要条件

    $$
    \begin{gathered}
    T > \frac{1}{0.15(1-\alpha)}, \\
    k < \frac{0.15(0.15T\alpha+1)}{9.81T^2\alpha}, \\
    k < \frac{(0.15T(1-\alpha)-1)(0.15T\alpha+1)}{9.81T^3\alpha}.
    \end{gathered} \tag{1}
    $$

    可知 $k$ 存在上界, 不应选取过大的 $k$. 无补偿 ($k=1$) 时, 系统的 Bode 图如下:

    ![](./figs/p8-bode0.svg)
    <figcaption> <b>图 7.</b> 第 8 题中无补偿时的 Bode 图. </figcaption> <br>

    可知系统的穿越频率约为 $2.13$ rad/s, 相位裕度约为 $-85.99\degree$, 系统不稳定. 选取 $\alpha=0.1$, 从而提供尽可能大的超前相位 ($\phi_{\max} = \sin^{-1}\frac{1-\alpha}{1+\alpha} \approx 54.9\degree$). 
    
    假设四个要求全部满足, 则系统在穿越频率 $\omega_c > 1.5$ rad/s 处的相位至少为 $-140\degree$. 由于超前补偿至多提供约 $54.9\degree$ 的超前相位, 这要求无补偿的系统在穿越频率处至少有 $-194.9\degree$ 的相位, 显然与事实矛盾. 因此, 不存在超前补偿使题中四个要求全部满足. 我们将设计一个满足 (a), (b), (d) 三个要求的超前补偿.

    依据 (1) 式条件, 选取 $T = 100$ s, 则最大相位频率 $\omega_{\max}=\frac{1}{T\sqrt{\alpha}}\approx 3 \times 10^{-2}$, 有可能实现要求的相位裕度. 此时, 由 (1) 式解得 $k < 3.185 \times 10^{-5}$. 经过试验, 发现当 $k=3 \times 10^{-6}$ 时, 补偿后的相位裕度满足要求. 此时, 系统的 Bode 图为:

    ![](./figs/p8-bode.svg)
    <figcaption> <b>图 8.</b> 第 8 题中补偿后的 Bode 图. </figcaption> <br>

    可知系统的穿越频率约为 $0.021$ rad/s, 相位裕度约为 $44.71\degree$, 增益裕度约为 $10.62$, 满足设计要求. 绘制得到阶跃参考输入, 初始条件 $x(0) = 1$, $\dot x(0) = 0$, $\theta(0) = 0$ 下, 无人机 $x$ 轴方向位移的零输入, 零状态以及全响应曲线如下:

    ![](./figs/p8-resp.svg)
    <figcaption> <b>图 9.</b> 第 8 题中位移的零输入, 零状态以及全响应曲线. </figcaption> <br>

    可见, 系统稳定, 稳态误差为 0, 符合预期.

    求解本题所用的代码如下:

    ```python
    # 无补偿
    sys, _ = sys_p89(G_x)
    # Bode 图
    plot_p89_bode(sys)
    plt.tight_layout()
    plt.savefig('figs/p8-bode0.svg')

    # 有补偿
    sys, sysc = sys_p89(G_x, {k: 3e-6, Td: 100, alpha: 0.1})
    # Bode 图
    plt.tight_layout()
    plot_p89_bode(sys)
    plt.savefig('figs/p8-bode.svg')

    T = np.linspace(0, 1e3, 10000)
    fig, ax = plt.subplots(figsize=(4, 3))
    # 零状态响应
    plot_p89_response(sysc, T, np.ones_like(T), zero_state=True, ax=ax)
    # 零输入响应
    plot_p89_response(sysc, T, np.zeros_like(T), ax=ax)
    # 全响应
    plot_p89_response(sysc, T, np.ones_like(T), ax=ax)

    plt.xlabel(r'$t / \rm{s}$')
    plt.ylabel(r'$x / \rm{m}$')
    plt.legend([r'Zero State Response', r'Zero Input Response', r'Full Response'])
    plt.tight_layout()
    plt.savefig('figs/p8-resp.svg')

    # 计算超调量, 上升时间等
    print(control.step_info(sysc))
    ```

9.  在实际中, 我们采用级联控制结构实现对 $x$ 轴方向的控制. 内环控制器 (采用比例控制, 比例系数为 5) 能够快速跟踪期望的俯仰角 $\theta$, 外环控制器通过 $θ$ 控制无人机 $x$ 轴方向的位置.

    1.  针对无人机 $x$ 轴方向动力学与内环控制组成的系统 $G_{\rm out}(s)$, 设计如下形式的超前补偿器:

        $$
        K_{\rm out}(s) = k\frac{Ts+1}{\alpha Ts+1},\quad 0.1\le \alpha < 0.1.
        $$

        使得无人机 x 轴方向动力学子系统至少满足以下要求:

        1.  渐近稳定;
        2.  对阶跃参考信号的稳态跟踪误差为零;
        3.  穿越频率不小于 $1.5$ rad/s;

    2.  绘制无人机 $x$ 轴位置时间响应曲线 (初始条件 $x(0) = 1$, $\dot x(0) = 0$, $\theta(0) = 0$).
    3.  从超调量和上升时间等角度, 比较本题与第 8 题中控制得到的闭环系统性能.

    **解:** 无人机在 $x$ 方向的动力学模型简化为

    $$
    \frac{\mathrm{d}}{\mathrm{d} t} \begin{bmatrix}
    x \\ \dot{x}
    \end{bmatrix} = \begin{bmatrix}
    0 & 1 \\
    0 & -\frac{k_x}{m}
    \end{bmatrix} \begin{bmatrix}
    x \\ \dot{x}
    \end{bmatrix} + \begin{bmatrix}
    0 \\ g
    \end{bmatrix} \theta,\quad
    x = \begin{bmatrix}
    1 & 0
    \end{bmatrix} \begin{bmatrix}
    x \\ \dot{x}
    \end{bmatrix}.
    $$

    故 $x$ 轴方向动力学子系统的传递函数为

    $$
    G_x(s) = \begin{bmatrix}
    1 & 0
    \end{bmatrix} \left(sI - \begin{bmatrix}
    0 & 1 \\
    0 & -\frac{k_x}{m} \\
    \end{bmatrix}\right)^{-1} \begin{bmatrix}
    0 \\ g
    \end{bmatrix}
    = \frac{g}{s(s+\frac{k_x}{m})}.
    $$

    $x$ 轴方向动力学与内环控制组成的系统的传递函数为

    $$
    G_{\mathrm{out}}(s) = \frac{\frac{5}{s}}{1+\frac{5}{s}} G_x(s) = \frac{5g}{s(s+5)(s+\frac{k_x}{m})}.
    $$

    代入数据, 得超前补偿下开环传递函数为

    $$
    K_{\mathrm{out}}G_{\mathrm{out}}(s) = \frac{49.05 k \left(T s + 1\right)}{s \left(s + 0.15\right) \left(s + 5\right) \left(T \alpha s + 1\right)}.
    $$

    故闭环系统对阶跃参考信号的稳态跟踪误差为

    $$
    e_{\rm ss} = \lim_{s\to 0} \frac{1}{1 + K_{\mathrm{out}}G_{\mathrm{out}}(s)} = 0,
    $$

    必定满足要求. 闭环系统的特征方程为

    $$
    T \alpha s^{4} + (5.15 T \alpha + 1) s^{3} + (0.75 T \alpha + 5.15) s^{2} + (49.05 T k + 0.75) s + 49.05 k = 0.
    $$

    劳斯阵列为 (省略号部分过于复杂, 不予考虑)

    $$
    \left[\begin{matrix}T \alpha & 0.75 T \alpha + 5.15 & 49.05 k & 0 & 0\\5.15 T \alpha + 1 & 49.05 T k + 0.75 & 0 & 0 & 0\\\frac{3.8625 T^{2} \alpha^{2} - 49.05 T^{2} \alpha k + 26.5225 T \alpha + 5.15}{5.15 T \alpha + 1.0} & 49.05 k & 0 & 0 & 0\\ \cdots & 0 & 0 & 0 & 0\\49.05 k & 0 & 0 & 0 & 0\end{matrix}\right].
    $$

    得到系统稳定的一个必要条件

    $$
    k < \frac{3.8625T^2\alpha^2 + 26.5225T\alpha + 5.15}{49.05T^2\alpha}.
    $$

    可知 $k$ 存在上界, 不应选取过大的 $k$. 无补偿 ($k=1$) 时, 系统的 Bode 图如下:

    ![](./figs/p9-bode0.svg)
    <figcaption> <b>图 10.</b> 第 9 题中无补偿时系统的 Bode 图. </figcaption> <br>

    可知系统的穿越频率约为 $2.91$ rad/s, 相位裕度约为 $-27.24\degree$. 考虑到额外的裕度需求, 应当选取 $\alpha=0.1$, 从而提供尽可能大的超前相位 ($\phi_{\max} = \sin^{-1}\frac{1-\alpha}{1+\alpha} \approx 54.9\degree$).

    选取 $\omega_{\max} = 1.5$ rad/s 为补偿后的穿越频率, 则 $T = \frac{1}{\omega_{\max}\sqrt{\alpha}} \approx 2$ s, 故选取 $T = 2$ s.

    此时, 令劳斯阵列首列元素大于 0, 解得 $k < 0.4375$. 超前补偿将使穿越频率增大, 但同时较小的 $k$ 将使穿越频率减小, 故不应选取过小的 $k$. 经过试验, 发现当 $k=0.08$ 时, 补偿后的穿越频率满足要求, 且系统有较好的相位裕度. 此时, 系统的 Bode 图为:

    ![](./figs/p9-bode.svg)
    <figcaption> <b>图 11.</b> 第 9 题中补偿后系统的 Bode 图. </figcaption> <br>

    可知系统的穿越频率约为 $1.51$ rad/s, 相位裕度约为 $43.77\degree$. 绘制得到阶跃参考输入, 初始条件 $x(0) = 1$, $\dot x(0) = 0$, $\theta(0) = 0$ 下, 无人机 $x$ 轴方向位移的零输入, 零状态以及全响应曲线如下:

    ![](./figs/p9-resp.svg)
    <figcaption> <b>图 12.</b> 第 9 题中位移的零输入, 零状态以及全响应曲线. </figcaption> <br>

    可见, 系统稳定, 稳态误差为 0, 符合预期.

    求解本题所用的代码如下:

    ```python
    # 无补偿
    sys, _ = sys_p89(G_out)
    # Bode 图
    plot_p89_bode(sys)
    plt.tight_layout()
    plt.savefig('figs/p9-bode0.svg')

    # 有补偿
    sys, sysc = sys_p89(G_out, {k: 0.08, Td: 2, alpha: 0.1})
    # Bode 图
    plot_p89_bode(sys)
    plt.tight_layout()
    plt.savefig('figs/p9-bode.svg')

    T = np.linspace(0, 10, 1000)
    fig, ax = plt.subplots(figsize=(4, 3))
    # 零状态响应
    plot_p89_response(sysc, T, np.ones_like(T), zero_state=True, ax=ax)
    # 零输入响应
    plot_p89_response(sysc, T, np.zeros_like(T), ax=ax)
    # 全响应
    plot_p89_response(sysc, T, np.ones_like(T), ax=ax)

    plt.xlabel(r'$t / \rm{s}$')
    plt.ylabel(r'$x / \rm{m}$')
    plt.legend([r'Zero State Response', r'Zero Input Response', r'Full Response'])
    plt.tight_layout()
    plt.savefig('figs/p9-resp.svg')

    # 计算超调量, 上升时间等
    print(control.step_info(sysc))
    ```

    最后, 计算得第 8, 9 题中系统的超调量 $M_p$, 上升时间 $t_r$, 调节时间 $t_s$, 如下表所示:

    <figcaption><b>表 2.</b> 超调量, 上升时间与调节时间</figcaption>

    | 题号 | 超调量 $M_p$ (%) | 上升时间 $t_r$ (s) | 调节时间 $t_s$ (s) |
    | :--: | :--------------: | :----------------: | :----------------: |
    |  8   |      33.816      |       48.730       |      292.383       |
    |  9   |      30.934      |       0.703        |       3.726        |

    可见, 第 9 题中系统的超调量 $M_p$, 上升时间 $t_r$, 调节时间 $t_s$ 均小于第 8 题中系统, 具有更好的瞬态响应特性. 其中, 上升时间与调节时间的优势较为明显. 对于第 8 题中以 $q$ 为控制输入, 穿越频率 $\omega_c$ 较小的系统, 需要约 5 min 才能将误差降至 2%, 显然不可接受; 而对于第 9 题中以 $\theta$ 为控制输入, 穿越频率 $\omega_c$ 较大的系统, 只需 3.7 s 的调节时间, 控制效果较好.
