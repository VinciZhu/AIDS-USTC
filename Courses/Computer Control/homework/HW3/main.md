# Homework 3

## Problem 1

$G(s) = \frac{\frac{K}{s(s+2)}}{1+\frac{K}{s(s+2)}} = \frac{K}{s^2+2s+K},\ K>0.$ 二阶系统.

$\omega_n = \sqrt{K},\ \zeta = \frac{1}{\sqrt{K}}.$ 欠阻尼 $\implies$ $K > 1.$

$M_p = e^{-\frac{-\pi\zeta}{\sqrt{1-\zeta^2}}} = e^{-\frac{\pi}{\sqrt{K-1}}} < 10\%.$

$\implies$ $\sqrt{K-1} < \frac{\pi}{\ln 10}$ $\implies$ $K <  1 + (\frac{\pi}{\ln 10})^2.$

$\therefore 1 < K < 1 + (\frac{\pi}{\ln 10})^2.$

## Problem 2

$t_r \approx \frac{1.8}{\omega_n} \le 0.6$ $\implies$ $\omega_n \ge 3.$

$M_p = e^{-\frac{\pi\zeta}{\sqrt{1-\zeta^2}}} \le 17\%$ $\implies$ $\zeta \ge - \frac{\ln 0.17}{\sqrt{(\ln 0.17)^2 + \pi^2}} \approx 0.49.$

$t_s \approx \frac{4.4}{\sigma} \le 8.8$ $\implies$ $\sigma \ge 0.5.$

![Range of poles](HW3_prob2.png)

## Problem 3

1. $J_m s \Omega_m(s) + (b+\frac{K_t K_e}{R_a}) \Omega_m(s) = \frac{K_t}{R_a} V_a(s).$

   $\implies$ $\frac{\Omega_m(s)}{V_a(s)} = \frac{K_t}{R_a J_m s + R_a b + K_t K_e} = \frac{0.2}{s+0.104}.$

2. $V_a(s) = \frac{10}{s},\ \Omega_m(s) = \frac{2}{s(s+0.104)} = \frac{250}{13}\left(\frac{1}{s}-\frac{1}{s+0.104}\right).$

   $\xrightarrow{\mathcal{L}^{-1}}$ $\omega(t) = \frac{250}{13} (1-e^{-0.104t}) 1(t) \ \text{rad/s}.$

   $\therefore$ $\omega(+\infty) = \frac{250}{13}\ \text{rad/s}.$

3. $J_m s^2 \Theta_m(s) + (b+\frac{K_t K_e}{R_a}) s \Theta_m(s) = \frac{K_t}{R_a} V_a(s).$

   $\implies$ $\frac{\Theta_m(s)}{V_a(s)} = \frac{K_t}{R_a J_m s^2 + R_a b + K_t K_e s} = \frac{0.2}{s^2+0.104s}.$

4. $\frac{\Theta_m(s)}{K(\Theta_r(s)-\Theta_m(s))} = \frac{0.2}{s^2+0.104s}.$

   $\implies$ $\frac{\Theta_m(s)}{\Theta_r(s)} = \frac{0.2K}{s^2+0.104s+0.2K}.$

5. 二阶系统, $\omega_n = \sqrt{0.2K},\ \zeta = \frac{0.052}{\sqrt{0.2K}}.$

   $M_p = e^\frac{-\pi\zeta}{\sqrt{1-\zeta^2}} < 20\%$ $\implies$ $\zeta > - \frac{\ln 0.2}{\sqrt{(\ln 0.2)^2 + \pi^2}} \approx 0.456.$

   $\implies$ $K < 0.065$, i.e. $K$ 的最大值为 $0.065$.

6. $t_r \approx \frac{2.16\zeta+0.60}{\omega_n} < 4 \ \text{s}$ $\implies$ $K > 0.334.$

7. 单位阶跃响应:

   ![Range of $K$](HW3_prob3.png)

   |                  | $K=0.5$ | $K=1$  | $K=2$  |
   | ---------------- | ------- | ------ | ------ |
   | RiseTime         | 3.688   | 2.503  | 1.72   |
   | SettlingTime     | 72.715  | 72.24  | 75.113 |
   | SettlingMin      | 0.649   | 0.521  | 0.404  |
   | SettlingMax      | 1.592   | 1.692  | 1.772  |
   | Overshoot        | 59.231  | 69.227 | 77.169 |
   | Undershoot       | 0.0     | 0.0    | 0.0    |
   | Peak             | 1.592   | 1.692  | 1.772  |
   | PeakTime         | 10.072  | 7.073  | 4.984  |
   | SteadyStateValue | 1.0     | 1.0    | 1.0    |

   $K > 0.334$, 超调量 $M_p > 20\%$, 上升时间 $t_r <4\ \text{s}$.
   与前两小问的计算结果一致.

## Problem 4

劳斯阵列:

$\left[\begin{matrix}
1 & 10 & 5 & 0 & 0 & 0\\
5 & 10 & K & 0 & 0 & 0\\
8 & \frac{25-K}{5} & 0 & 0 & 0 & 0\\
\frac{K+55}{8} & K & 0 & 0 & 0 & 0\\
\frac{-K^2-350K+1375}{5(K + 55)} & 0 & 0 & 0 & 0 & 0\\
K & 0 & 0 & 0 & 0 & 0
\end{matrix}\right].$

系统稳定 $\iff$ $K > 0\ \wedge\ K+55 > 0\ \wedge\ -K^2-350K+1375 > 0.$

$\iff$ $0 < K < 80 \sqrt{5}-175.$

$K$ 不满足取值范围:

![$K=-10000$](HW3_prob4a.png)

![$K=1000$](HW3_prob4b.png)

$K$ 满足取值范围:

![$K=80 \sqrt{5}-176$](HW3_prob4c.png)

![$K=1$](HW3_prob4d.png)

## Problem 5

$G(s) = \frac{KK_o(s+z)}{(s+p)(s^2-a^2)+KK_o(s+z)}.$

劳斯阵列:

$\left[\begin{matrix}1 & K K_{o} - a^{2} & 0 & 0\\p & K K_{o} z - a^{2} p & 0 & 0\\\frac{K K_{o} \left(p - z\right)}{p} & 0 & 0 & 0\\K K_{o} z - a^{2} p & 0 & 0 & 0\end{matrix}\right]
.$

系统稳定 $\iff$ $p > 0\ \wedge\ K K_o(p-z) > 0\ \wedge\ K K_o z-a^2 p  > 0.$

## Problem 6

$G_o(s)=G_c(s)G_p(s)=\frac{10(s+2)}{s^2(s+5)}$, 2 型系统.

加速度误差常数 $K_a = \lim_{s\to0} s^2G_o(s) = 4.$

## Problem 7

$G_o(s)=\frac{K}{s(4s+1)}$, 1 型系统.

速度误差常数 $K_v = \lim_{s\to0} sG_o(s) = K = 1.$

## Problem 8

$G(s)=\frac{3K}{4(s+1)}.$

$E(s)=(1-G(s))R(s)=\frac{4s+4-3K}{4s(s+1)}.$

$e_{\text{ss}} = \lim_{s\to0} sE(s) = 1-\frac{3K}{4} = 0.$

$\implies$ $K=\frac{4}{3}.$

## Problem 9

1. $G_o(s)=\frac{K_1K_2/Is}{s(1+K_1K_2K_3/Is)} =\frac{K_1K_2}{s(25s+K_1K_2K_3)}$, 1 型系统.

   $e_\text{ss} = \frac{1}{\lim_{s\to0}sG_o(s)} = K_3 < 0.01.$

2. $G(s)=\frac{G_o(s)}{1+G_o(s)}=\frac{\frac{K_1K_2}{25}}{s^2+\frac{K_1K_2K_3}{25}s+\frac{K_1K_2}{25}}.$

   二阶系统, $\omega_n = \frac{\sqrt{K_1K_2}}{5},\ \zeta = \frac{\sqrt{K_1K_2}K_3}{10}.$

   $M_p = e^{-\frac{\pi\zeta}{\sqrt{1-\zeta^2}}} < 10\%$ $\implies$ $\zeta > - \frac{\ln 0.1}{\sqrt{(\ln 0.1)^2 + \pi^2}} \approx 0.591.$

   $K_1K_2 = \frac{100\zeta^2}{K^2_3} > \frac{100\times0.591^2}{0.01^2}\approx349464.$
