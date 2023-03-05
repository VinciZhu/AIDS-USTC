# Intro to AI

## Part I: Searching

PEAS: Performance, Environment, Actuators, Sensors

问题形式化: 初始状态、行动集合、转移模型、目标测试、路径代价

### Uninformed

| Algorithm | Complete                    | Optimal                 | Time                      | Space                     | Evaluation function |
| --------- | --------------------------- | ----------------------- | ------------------------- | ------------------------- | ------------------- |
| BFS       | Yes (finite branch)         | Yes                     | $O(b^{d+1})$              | $O(b^{d+1})$              |
| UCS       | Yes (lower bounded cost)    | Yes (non-negative cost) | $O(b^{[C^*/\epsilon]+1})$ | $O(b^{[C^*/\epsilon]+1})$ | $f(n)=g(n)$         |
| DFS       | No (infinite depth or loop) | No                      | $O(b^m)$                  | $O(bm)$                   |
| DLS       | No ($l<d$)                  | No                      | $O(b^l)$                  | $O(bl)$                   |
| IDS       | Yes (finite branch)         | Yes (non-negative cost) | $O(b^d)$                  | $O(bd)$                   |
| Bidir     | Yes (BFS)                   | Yes (uniform cost)      | $O(b^{d/2})$              | $O(b^{d/2})$              |

### Informed

| Algorithm | Complete | Optimal          | Time     | Space    | Evaluation function |
| --------- | -------- | ---------------- | -------- | -------- | ------------------- |
| GBFS      | No       | No               | $O(b^m)$ | $O(b^m)$ | $f(n)=h(n)$         |
| A\*       | Yes      | Yes (admissible) | $O(b^d)$ | $O(b^d)$ | $f(n)=g(n)+h(n)$    |

**Theorem:**
A* with admissible heuristic is optimal.
For graph search, A* with consistent heuristic is optimal.

**Theorem:**
Given admissible heuristic $h_1(n), h_2(n)$, we have $h(n) = \max(h_1(n), h_2(n))$ is admissible and dominates $h_1(n)$ and $h_2(n)$.

**Theorem:**
The cost of an optimal solution to a relaxed problem is an admissible and consistent heuristic for the original problem.

### Genetic

**模式定理**: 若群体规模为$M$, 则遗传操作可从这$M$个个体中生成和检测$M^3$个模式, 并在此基础上能够不断形成和优化积木块, 直到找到最优解.

**个体选择概率:**
适应度比例(蒙特卡洛)、线性排序、非线性排序

**选择:**
转盘赌、锦标赛、随机竞争、Boltzmann 锦标赛、$(\mu,\lambda)$ 或 $\mu+\lambda$、最佳个体保存

**交叉:**
一点交叉、二点交叉、均匀交叉、部分匹配交叉、顺序交叉、循环交叉、部分离散或整体离散、部分算术或整体算术

**变异:**
位点、逆转、插入、互换、移动、自适应、均匀性、正态性、非一致性、自适应

### Adversarial

- Minimax: $O(b^h)$
- $\alpha-\beta$ pruning: $O(b^\frac{h}{2})$, $O(b^\frac{3h}{4})$, $O(b^h)$

## Part II: Reasoning

定理: $KB \models α$ 当且仅当

- $M(KB) \subseteq M(α)$
- $(KB \implies α)$ 是有效的
- $(KB \land \neg α)$ 是不可满足的

枚举推理复杂度:

- 确定: 时间 $O(2^n)$, 空间 $O(n)$
- 不确定: 时间 $O(2^n)$, 空间 $O(2^n)$, $O(2^kn)$, $O(n)$

变量消元复杂度:

- 单连通网络: $O(2^kn)$
- 多连通网络: NP-hard

定理: 局部语义 $\iff$ 全局语义

定理: 给定马尔可夫覆盖 (父节点 + 子节点 + 子节点的父节点), 节点条件独立于所有其他节点

定理: 节点不是证据变量或查询变量的祖先 $\implies$ 节点是无关的

定理: 节点在 moral 图中通过证据变量对查询变量是可分离的 $\implies$ 节点是无关的

定理: 直接采样、拒绝采样、似然加权采样、Gibbs 采样的计算结果均为一致的概率估计

HMM:

- 前向-后向算法:
  $$
  \begin{aligned}
  f_{1:t} & = P(X_t | e_{1:t}) \\
  & \propto P(e_t | X_t)\sum_{x_{t-1}}P(X_t | x_{t-1})P(x_{t-1} | e_{1:t-1}) \\
  & = P(e_t | X_t)\sum_{x_{t-1}}P(X_t | x_{t-1})f_{1:t-1}(x_{t-1}) \\
  & = O_{t}T^\top f_{1:t-1}
  \end{aligned}
  $$

  $$
  \begin{aligned}
  b_{t+1:T} & = P(e_{t+1:T} | X_t) \\
  & = \sum_{x_{t+1}}P(x_{t+1} | X_t)P(e_{t+1} | x_{t+1})P(e_{t+2:T} | x_{t+1}) \\
  & = \sum_{x_{t+1}}P(x_{t+1} | X_t)P(e_{t+1} | x_{t+1})b_{t+2:T}(x_{t+1}) \\
  & = TO_{t+1} b_{t+2:T}
  \end{aligned}
  $$

  - 滤波: $P(X_t | e_{1:t}) = f_{1:t}$, 时间、空间 $O(1)$
  - 预测: $P(X_{t+k} | e_{1:t})$
  - 平滑: $P(X_k | e_{1:t}) \propto f_{1:k}b_{k+1:t}$, 时间 $O(S^2t)$, 空间 $O(St)$

- Viterbi 算法:

  $$
  \begin{aligned}
  m_{1:t} & = \max_{x_{1:t-1}}P(x_{1:t-1},X_t | e_{1:t}) \\
  & \propto P(e_t | X_t)\max_{x_{t-1}}P(X_t | x_{t-1})\max_{x_{1:t-2}}P(x_{1:t-2},x_{t-1} | e_{1:t-1}) \\
  & = P(e_t | X_t)\max_{x_{t-1}}P(X_t | x_{t-1})m_{1:t-1}(x_{t-1})
  \end{aligned}
  $$
  - 最可能路径: $\argmax_{x_{1:t}}P(x_{1:t} | e_{1:t})$






## Part III: Learning
