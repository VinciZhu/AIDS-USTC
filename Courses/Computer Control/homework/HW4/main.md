# Homework 4

1.  被控对象 $Z$ 传递函数

    $$\begin{aligned}
            G(z) & = \mathcal{Z}\left\{\frac{1-e^{-TS}}{s^2(s+1)}\right\} = (1-z^{-1})\mathcal{Z}\left\{\frac{1}{s + 1} - \frac{1}{s} + \frac{1}{s^{2}}\right\} \\
                & = \frac{1-z^{-1}}{1-e^{-T}z^{-1}} - 1 + \frac{Tz^{-1}}{1-z^{-1}}
        \end{aligned}$$

    开环 $Z$ 传递函数


    $$W_o(z) = KG(z) = K\left(\frac{1-z^{-1}}{1-e^{-T}z^{-1}} - 1 + \frac{Tz^{-1}}{1-z^{-1}}\right)$$


    闭环 $Z$ 传递函数

    $$\begin{aligned}
            W_c(z) & = \frac{W_o(z)}  {1+W_o(z)} = \frac{K\left(\frac{1-z^{-1}}{1-e^{-T}z^{-1}} - 1 + \frac{Tz^{-1}}{1-z^{-1}}\right)}  {1+K \left(\frac{1-z^{-1}}{1-e^{-T}z^{-1}} - 1 + \frac{Tz^{-1}}{1-z^{-1}}\right) }                        \\
                & = \frac{K \left(T + e^{-T} - 1\right) z^{-1} + K \left(- T e^{-T} - e^{-T} + 1\right) z^{-2}}{1 + (K \left(T + e^{-T} - 1\right) - e^{-T} - 1) z^{-1} + \left(K \left(- T e^{-T} - e^{-T} + 1\right) + e^{-T}\right) z^{-2}}
        \end{aligned}$$

    特征方程

    $$1 + (K \left(T + e^{-T} - 1\right) - e^{-T} - 1) z^{-1} + \left(K \left(- T e^{-T} - e^{-T} + 1\right) + e^{-T}\right) z^{-2} = 0$$

    令 $z^{-1} = \frac{1-w}{1+w}$, 整理得

    $$\begin{aligned}
            & \left(K \left(- T e^{-T} - T - 2 e^{-T} + 2\right) + 2 e^{-T} + 2\right) w^2 \\
            + & \left(K \left(2 T e^{-T} + 2 e^{-T} - 2\right) - 2 e^{-T} + 2\right) w
            + KT \left(- e^{-T} + 1\right) = 0
        \end{aligned}$$


    劳斯阵列

    $$\begin{aligned}
            w^2:\quad & K \left(- T e^{-T} - T - 2 e^{-T} + 2\right) + 2 e^{-T} + 2 & KT \left(- e^{-T} + 1\right) \\
            w^1:\quad & K \left(2 T e^{-T} + 2 e^{-T} - 2\right) - 2 e^{-T} + 2     &                              \\
            w^0:\quad & KT \left(- e^{-T} + 1\right)                                &                              \\
        \end{aligned}$$

    考虑 $K, T>0$, 则 $KT \left(- e^{-T} + 1\right) > 0$. 要使系统稳定, 应有

    $$K \left(- T e^{-T} - T - 2 e^{-T} + 2\right) + 2 e^{-T} + 2 > 0$$

    $$K \left(2 T e^{-T} + 2 e^{-T} - 2\right) - 2 e^{-T} + 2 > 0$$

    1.  当 $T=0.1$ 时,

    $$K < \frac{2 e^{-0.1} + 2}{2.1 e^{-0.1} - 1.9} \approx 24024.000$$
    $$K < \frac{e^{-0.1} - 1}{1.1 e^{-0.1} - 1} \approx 20.339$$
    $$\therefore 0 < K < 20.339$$

    2.  当 $T=1$ 时,

    $$K < \frac{2 e + 2}{3 - e} \approx 26.397$$
    $$K < \frac{e - 1}{2 - e} \approx 2.392$$
    $$\therefore 0 < K < 2.392$$

2.  1.  被控对象 $Z$ 传递函数

        $$\begin{aligned}
                G(z) & = \mathcal{Z}\left\{\frac{10(1-e^{-TS})}{s^2(s+1)}\right\} = 10(1-z^{-1})\mathcal{Z}\left\{\frac{1}{s + 1} - \frac{1}{s} + \frac{1}{s^{2}}\right\} \\
                    & = 10\left(\frac{1-z^{-1}}{1-e^{-T}z^{-1}} - 1 + \frac{Tz^{-1}}{1-z^{-1}}\right)
            \end{aligned}$$

        开环 $Z$ 传递函数

        $$\begin{aligned}
                W_o(z) & =  (1.5-0.5z^{-1})G(z)                                                                                                                                                \\
                    & =         \frac{(15 T + 15 e^{-T} - 15) z^{-1} + (- 15 T e^{-T} - 5 T - 20 e^{-T} + 20) z^{-2} + (5 T e^{-T} + 5 e^{-T} - 5) z^{-3}}{(1 - z^{-1})(1 - e^{-T} z^{-1})}
            \end{aligned}$$

        分母含有因子 $(1-z^{-1})$, 故系统为 1 型系统. 速度误差常数为

        $$\begin{aligned}
                K_v & =  \lim_{z\to1} (1-z^{-1})W_o(z)                                                                                         \\
                    & =      \frac{(15 T + 15 e^{-T} - 15) + (- 15 T e^{-T} - 5 T - 20 e^{-T} + 20) + (5 T e^{-T} + 5 e^{-T} - 5)}{1 - e^{-T}} \\
                    & =      \frac{10 T  - 10 T e^{-T} }{1 - e^{-T}} = 10T
            \end{aligned}$$

        当 $T = 0.2$ 时, $K_v = 2$.

    1.  对于单位位置信号 $1(t)$, 稳态误差为 0; 对于单位速度信号 $t \cdot 1(t)$, 稳态误差为 $\frac{T}{K_v} = 0.1$.

        故对于 $r(t) = (1+2t) \cdot 1(t)$, 稳态误差 $e_{ss} = 0 + 2 \times 0.1 =0.2$


3.  系统的特征方程
    
    $$\left|\begin{array}{cc}
                z   & -1    \\
                4.8 & z-1.4
            \end{array}\right| = z^2-1.4z+4.8 = 0$$

    特征根 $z_{1,2} = 0.7 \pm \mathrm{j}2.076$, $|z_{1,2}| = 2.191 > 1$, 位于单位圆外, 系统不稳定.
