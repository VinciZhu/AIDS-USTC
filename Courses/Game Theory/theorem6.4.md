# 定理 6.4 证明勘误

<center>PB20061372 &ensp; 朱云沁 &ensp; June 15, 2023</center>

---

<div class='prob'>

**定理 6.4:** (Shapley, 1971) 凸博弈核心非空.

</div>

<div class='sol'>

**证明:** 定义 $S_k = \{1, 2, \dots, k\}$ 为编号最小的 $k$ 个局中人的联盟. 其中, $S_0 = \varnothing, S_n = N.$ 进一步, 定义 $x_i = v(S_{i}) - v(S_{i-1})$. 下证, 向量 $\mathbf{x}=(x_1,x_2,\dots,x_n)$ 是一个分配, 并且属于核心 $C(v)$.

注意到 $\sum_{i\in N} x_i = v(S_n) - v(S_0) = v(N) - v(\emptyset) = v(N)$. 由定理 6.1, 只需证 $\sum_{i\in T} x_i \ge v(T)$ 对任意联盟 $T \subseteq N$ 成立.

设 $N-T = \{j_1, j_2, \dots, j_{m}\}$, 其中 $j_1< j_2< \dots< j_{m}$. 作如下观察

$$
\left\{
\begin{array}{lllll}
S_{j_1-1}   & \subseteq & T                                     & \subseteq & N - \{j_1\} \\
S_{j_2-1}   & \subseteq & T \cup \{j_1\}                        & \subseteq & N - \{j_2\} \\
S_{j_3-1}   & \subseteq & T \cup \{j_1, j_2\}                   & \subseteq & N - \{j_3\} \\
\vdots                                                                                    \\
S_{j_{m}-1} & \subseteq & T \cup \{j_1, j_2, \dots j_{m-1}\}    & \subseteq & N - \{j_m\} \\
\end{array}
\right.
$$

由于 $x_i = v(S_{i-1}\cup\{i\}) - v(S_{i-1})$, 结合凸博弈的性质, 我们有

$$
\left\{
\begin{array}{lllllllll}
x_{j_1} & \le & v(T\cup\{j_1\})                     & - & v(T)                                  \\
x_{j_2} & \le & v(T\cup\{j_1, j_2\})                & - & v(T\cup \{j_1\})                      \\
x_{j_3} & \le & v(T\cup\{j_1, j_2, j_3\})           & - & v(T\cup \{j_1, j_2\})                 \\
\vdots                                                                                          \\
x_{j_m} & \le & v(T\cup\{j_1, j_2, \dots, j_{m}\})  & - & v(T\cup \{j_1, j_2, \dots, j_{m-1}\}) \\
\end{array}
\right.
$$

上式两边求和, 得 $\sum_{i\in N-T} x_i \le v(N) - v(T)$. 又 $\sum_{i\in N} x_i = v(N)$, 故 $\sum_{i\in T} x_i \ge v(T)$. 证毕.

</div>

<div class='sol'>

**注 1:** 上述证明中, 我们利用了合作博弈 $\langle N, v \rangle$ 是凸博弈的等价定义:

$$
v(S\cup\{i\}) - v(S) \le v(T\cup\{i\}) - v(T),\ \forall S \subseteq T \subseteq N-\{i\}.
$$

</div>

<div class='sol'>

**注 2:** 上述核心元素 $\mathbf{x}$ 的构造并不唯一. Shapley 的对称性公设告诉我们, 局中人的所得应当与编号顺序无关. 不难发现, 对于原博弈 $\langle N, v \rangle$ 的任意置换博弈 $\langle N^\pi, v^\pi \rangle$, 我们可以类似地构造出一个分配, 使其属于核心 $C(v^\pi)$, 进而由逆置换 $\pi^{-1}$ 得到原博弈的核心元素 $\mathbf{x}^\pi \in C(v)$.

具体而言, $\mathbf{x}^\pi$ 的构造过程如下: 令 $\pi: N \to N$ 为对局中人集合 $N$ 的任意置换运算, $\pi(i)$ 为置换后局中人的新编号. 定义 $S^\pi_k = \{i: \pi(i) \leq k\}$ 为置换后编号最小的 $k$ 个局中人的联盟, 即

$$
\begin{cases}
S^\pi_0 = \varnothing, \\
S^\pi_1 = \{\pi^{-1}(1)\}, \\
S^\pi_2 = \{\pi^{-1}(1),\pi^{-1}(2)\}, \\
\vdots \\
S^\pi_n = \{\pi^{-1}(1),\pi^{-1}(2),\dots,\pi^{-1}(n)\} = N.
\end{cases}
$$

<p class='noindent'>

令 $x^\pi_i = v(S^\pi_{\pi(i)}) - v(S^\pi_{\pi(i)-1})$, 则向量 $\mathbf{x}^\pi=(x^\pi_1,x^\pi_2,\dots,x^\pi_n)$ 是一个分配, 并且属于核心 $C(v)$.

显然, $\mathbf{x}^\pi$ 不一定与 $\mathbf{x}$ 相同. Shapley 已在原论文中证明, 凸博弈的核心为所有形如 $\mathbf{x}^\pi$ 的分配的凸包 (核心为紧凸的多边形, 而 $\mathbf{x}^\pi$ 为其顶点), 而 Sharpley 值为核心的重心

$$
\bm{\phi} = \frac{1}{n!} \sum_{\pi: N \to N} \mathbf{x}^\pi.
$$

<p class='noindent'>

可见 Sharpley 理论之美妙.

![core](core.png)

<figcaption>

四人凸博弈的核心示例 (Shapley, 1971)

</figcaption>

</div>
