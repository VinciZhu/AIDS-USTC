# Homework 6


1.  1.  $G(s)$ 的幅值与相位分别为
        $$
        \begin{gathered}
        M(\omega) = |G(\mathrm{j}\omega)|=\frac{1}{\sqrt{\omega^2+100} }, \\            
        \phi(\omega) = \angle G(\mathrm{j}\omega) = -\arctan\left(\frac{\omega}{10}\right).
        \end{gathered}
        $$

        将数据带入得
        | $\omega$ | $\vert G(\mathrm{j}\omega)\rvert$ | $\angle G(\mathrm{j}\omega)$ |
        | :------: | :-------------------------------: | :--------------------------: |
        |   $1$    |              $0.100$              |       $-5.711\degree$        |
        |   $2$    |              $0.098$              |       $-11.310\degree$       |
        |   $5$    |              $0.089$              |       $-26.565\degree$       |
        |   $10$   |              $0.071$              |       $-45.000\degree$       |
        |   $20$   |              $0.045$              |       $-63.435\degree$       |
        |   $50$   |              $0.020$              |       $-78.690\degree$       |
        |  $100$   |              $0.010$              |       $-84.289\degree$       |

    1.  传递函数的 Bode 形式为
        $$G(\mathrm{j}\omega) = 0.1\cdot\frac{1}{\mathrm{j}\omega/10 + 1}$$

        -   幅频对数特性曲线
            
            $0<\omega<10$, 水平渐近线的值为 $0.1$;<br>
            $\omega=10$, 实际幅值约为 $0.1/0.707 = 0.0707$;<br>
            $\omega>10$, 渐近线斜率为 $-1$.

            如图 1(a) 所示.

        -   相频特性曲线

            $0\le\omega<2$, 水平渐近线的值为 $0\degree$;<br>
            $\omega = 2$, 实际相位约为 $0\degree-11\degree=-11\degree$;<br>
            $\omega\approx10$, 近似过$(2,0\degree), (50,-90\degree)$的直线;<br>
            $\omega = 50$, 实际相位约为 $-90\degree+11\degree=-79\degree$;<br>
            $\omega>50$, 水平渐近线的值为 $-90\degree$;<br>


            如图 1(b) 所示.

        ![图 1](img/1.jpg)

        与 (1) 中计算结果相符.

2.  传递函数的 Bode 形式为
    $$G(\mathrm{j}\omega)=0.375(\mathrm{j}\omega)^{-2}\cdot\frac{\mathrm{j}\omega/3+1}{\mathrm{j}\omega/8+1}.$$

    -   幅频对数特性曲线

        $0<\omega<3$, 渐近线的斜率为 $-2$, 过点 $(1,0.375)$;<br>
        $\omega=3$, 实际幅值约为 $0.0417 \times 1.4 = 0.0584$;<br>
        $3<\omega<8$, 渐近线斜率为 $-1$;<br>
        $\omega=8$, 实际幅值约为 $0.0156 \times 0.707 = 0.0110$;<br>
        $\omega>8$, 渐近线斜率为 $-2$.

        如图 2(a) 所示.

    -   相频特性曲线

        $0<\omega<3$, 水平渐近线的值为 $-180\degree$;<br>
        $\omega\approx 3$, 一阶项 $\mathrm{j}\omega/3 + 1$ 的相位曲线近似过 $(0.6,-90\degree), (15,0\degree)$ 的直线;<br>
        $3<\omega<8$, 水平渐近线的值为 $-90\degree$;<br>
        $\omega\approx 8$, 一阶项 $(\mathrm{j}\omega/8 + 1)^{-1}$ 的相位曲线近似过 $(1.6,0\degree), (40,-90\degree)$ 的直线;<br>
        $\omega>8$, 水平渐近线的值为 $-180\degree$;<br>

        如图 2(b) 所示.

    ![图 2](img/2.jpg)

3.  由渐近线的斜率变化知, 传递函数有如下 Bode 形式
    $$G(\mathrm{j}\omega) = K_0(\mathrm{j}\omega)^{-1}\cdot(\mathrm{j}\omega\tau+1)$$

    当 $\omega=1$ 时, 渐近线的值为 $10$, 故 $K_0=10$. 转折频率 $\omega = 10$, 故 $\tau = 0.1$

    传递函数为
    $$G(s) = 10s^{-1} \cdot (s/10 + 1) = 1 + \frac{10}{s}.$$

4.  1.  开环传递函数的 Bode 形式为
        $$G(\mathrm{j}\omega)=K (\mathrm{j}\omega)^{-1}\cdot \frac{1}{\mathrm{j}\omega+1}\cdot\frac{1}{(\mathrm{j}\omega/5)^2+0.4(\mathrm{j}\omega/5)+1}$$

        当 $K=1$ 时,
        -   幅频对数特性曲线

            $0<\omega<1$, 渐近线的斜率为 $-1$, 过点 $(1,1)$;<br>
            $\omega=1$, 实际幅值约为 $1 \times 0.707 = 0.707$;<br>
            $1<\omega<5$, 渐近线斜率为 $-2$;<br>
            $\omega=5$, 谐振峰值略小于 $0.1 \times \frac{1}{2\times0.4} = 0.125$;<br>
            $\omega>5$, 渐近线斜率为 $-4$.

            如图 3(a) 所示.

        -   相频特性曲线

            $0<\omega<1$, 水平渐近线的值为 $-90\degree$;<br>
            $\omega\approx 1$, 一阶项 $(\mathrm{j}\omega + 1)^{-1}$ 的相位曲线近似过 $(0.2,-90\degree), (5,-180\degree)$ 的直线;<br>
            $1<\omega<5$, 水平渐近线的值为 $-180\degree$;<br>
            $\omega=5$, 实际相位略大于 $-270\degree$;<br>
            $\omega>5$, 水平渐近线的值为 $-360\degree$;<br>
            
            如图 3(b) 所示.

        ![图 3](img/3.jpg)

    2.  注意到 $\angle G(\mathrm{j}\omega_\mathrm{c}) = -180\degree + \mathrm{PM} = -135\degree$, 故 
        $$\mathrm{Re}[G(\mathrm{j}\omega_\mathrm{c})]=\mathrm{Im}[G(\mathrm{j}\omega_\mathrm{c})] < 0.$$

        化简得
        $$0.04\omega_\mathrm{c}^3 - 1.08\omega_\mathrm{c} = 0.12\omega_\mathrm{c}^2 - 1 < 0.$$
        
        解得 $\omega_\mathrm{c}\approx 0.8665$. 代入 $|G(\mathrm{j}\omega_\mathrm{c})| = 1$, 得 $K\approx 1.1151$

        令 $\mathrm{Im}[G(\mathrm{j}\omega_\mathrm{crit})]=0$, $\mathrm{Re}[G(\mathrm{j}\omega_\mathrm{crit})]<0$, 得
        $$0.12\omega_\mathrm{crit}^2 - 1 = 0,\quad 0.04\omega_\mathrm{crit}^3 - 1.08\omega_\mathrm{crit} < 0$$

        解得 $\omega_\mathrm{crit} = \frac{5\sqrt{3}}{3} \approx 2.88675$. $\mathrm{GM} = |G(\mathrm{j}\omega_\mathrm{crit})|^{-1}\approx5.58$.

    3.  1 型系统, 速度误差常数为 $K_v = \lim_{s\to 0}sG(s)=K=1.1151$.

5.  超前补偿有如下形式
    $$D(s) = \frac{Ts+1}{\alpha Ts +1}$$

    未施加补偿器时, Bode 图如图 4 所示.

    ![图 4](img/4.jpg)

    穿越频率 $\omega_\mathrm{c}\approx 2$, 相位裕度 $\mathrm{PM}\approx 5\degree$.

    选取超前补偿的最大相位 $\phi_{\max} = 70\degree$, 则 $\sin 70\degree = \frac{1-\alpha}{1+\alpha}$, 得超前比率 $\frac{1}{\alpha} \approx 32$.

    选取超前补偿的最大相位频率 $\omega_{\max} = 4$, 则零点转折频率 $ \frac{1}{T} = 2\sqrt{\alpha}\approx 0.7$, 极点转折频率 $ \frac{1}{T\alpha} = 44.8$.

    候选的补偿器为
    $$D(s) = \frac{s/1.4+1}{s/44.8+1}$$

    此时, 开环传递函数的 Bode 形式为
    $$ DG(\mathrm{j}\omega) = 5(\mathrm{j}\omega)^{-1}\cdot\frac{\mathrm{j}\omega/1.4+1}{(\mathrm{j}\omega+1)(\mathrm{j}\omega/5+1)(\mathrm{j}\omega/44.8+1)} $$
 
    Bode 图如图 5 所示.

    ![图 5](img/5.jpg)
   
    穿越频率 $\omega_\mathrm{c}\approx 3$, 相位裕度 $\mathrm{PM}\approx 45\degree$, 满足设计要求.
    
    对于系统的带宽, 有 $\omega_\mathrm{c}\le\omega_\mathrm{BW}\le2\omega_\mathrm{c}$, 故 $\omega_\mathrm{BW}\approx 5$.

6.  未施加补偿器时, 取 $K=1$, 则开环传递函数的 Bode 图如图 6 所示.

    ![图 6](img/6.jpg)

    选取 $\omega_\mathrm{c}\approx 4$, 则相位裕度 $\mathrm{PM}\approx 45\degree$, $\left|G(\mathrm{j}\omega_\mathrm{c})\right| = 1 \approx 0.2K$, 得 $K = 5$.

    滞后补偿有如下形式
    $$D(s)=\alpha\frac{Ts+1}{\alpha Ts+1}.$$

    对于单位斜坡输入, 闭环系统的稳态误差为
    $$e_\mathrm{ss}=\lim_{s\to0}\frac{s}{s^2(1+DG(s))} = \frac{1}{5\alpha}.$$

    选取 $\alpha = 40$, 则 $e_\mathrm{ss} = 0.005< 0.01$. 选取零点转折频率 $\frac{1}{T}=\frac{1}{10}\omega_\mathrm{c}=0.4$, 极点转折频率 $\frac{1}{T\alpha}=0.01$.

    候选的补偿器为
    $$D(s)=40\frac{s/0.4+1}{s/0.01+1}.$$

    此时, 开环传递函数的 Bode 形式为
    $$ DG(\mathrm{j}\omega) = 200(\mathrm{j}\omega)^{-1}\cdot\frac{\mathrm{j}\omega/0.4+1}{(\mathrm{j}\omega/0.01+1)(\mathrm{j}\omega/5+1)(\mathrm{j}\omega/50+1)} $$
 
    Bode 图如图 7 所示.

    ![图 7](img/7.jpg)

    相位裕度 $\mathrm{PM}\approx 45\degree$, 满足设计要求.

