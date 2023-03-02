# 运筹学基础: 定理证明

## 线性规划

- 存在可行解 $\implies$ 存在基可行解
- 存在最优可行解 $\implies$ 存在最优基可行解
- 给定非退化的基可行解和进基变量
  - 存在离基变量 $\implies$ 构造更好的基可行解
  - 不存在离基变量 $\implies$ 无界解
- 最优性条件: $c_B^\top B^{-1}A - c^\top \ge 0$ $\implies$ 最优解
- 存在可行解, 大 M 法得到最优解 $\implies$ 人工变量 $R=0$
- 对偶问题的对偶问题是原问题
- 弱对偶性: $z \le w$
- 强对偶性: $z = w, \ y^\top =c_B^\top B^{-1}$
- 原问题无界解 $\iff$ 对偶问题无可行解
- 原始问题可行性 + 对偶问题的可行性
  - 最优性 $\iff$ complementary slackness: $(y^\top A - c^\top)x = 0$
- Farkas' lemma: 给定 $x$, 满足$Ax\le 0$
  - $c^\top x \le 0$ $\iff$ $\exist\, y\ge 0,\ \text{s.t. } c^\top = y^\top A$
- 灵敏度分析: $\frac{\partial z^*}{\partial b}=y^*$
- 可行解集的极点 $\iff$ 基可行解

## 非线性规划

- 无约束问题
  - 一阶必要条件
  - 二阶充分条件
- 隐函数定理
- 等式约束问题 + LICQ
  - 一阶必要条件(KKT)
  - 二阶充分条件
- 等式约束问题的灵敏度分析: $\left. \frac{\partial f^*}{\partial b}\right|_{b=0}=\lambda^*$
- 不等式约束问题 + LICQ
  - 一阶必要条件(KKT)
  - 二阶充分条件
- 凸集、凸函数的运算性质
- 凸函数的下水平集、极小值点集是凸集
- 凸函数的局部极小值点是全局极小值点
- 凸函数的一阶判据、二阶判据
- KKT 条件是凸规划的充分条件
- 二分法、黄金分割法的收敛性
- 用二阶近似确定梯度下降法的最优步长
- 梯度下降法求解无约束凸规划的收敛性
- 牛顿法求解无约束二次规划仅需单次迭代
- 不等式约束二次规划的 KKT 条件
  > $$\left[\begin{array}{cccc} -D & A^\top & -I & O \\ A & O & O & I \end{array}\right] \left[\begin{array}{c} x \\ \lambda \\ \mu \\ s \end{array}\right] = \left[\begin{array}{c} c \\ b \end{array}\right]$$
  > $$x, \lambda, \mu, s \ge 0$$
  > $$\lambda s = \mu x = 0$$
- 等式约束二次规划的闭式解
- 用一阶近似寻找可行方向
- 无约束惩罚问题的最优解 + 原约束问题的可行解 $\implies$ 原约束问题的最优解

## 层次分析法

比较矩阵: $a_{ij}>0,\ a_{ij}a_{ji}=1$ $\implies$ $\lambda_{\max}\ge n$
  - 一致性: $a_{ij}a_{jk}=a_{ik}$ $\iff$ 
    - $\lambda_{\max}= n$
    - $\text{rank}(A)= 1$
    - 列(行)向量两两线性相关
  - 2 维比较矩阵总是一致的

## 二人零和对策

- $v^- \le v_A \le v_B \le v^+$
- 纯策略意义下的鞍点 $\iff$ 纯策略意义下的最优解(强对偶性)
- 纳什均衡局势 $\iff$ 混合策略意义下的最优解(强对偶性) $\iff$ $e_i^\top A y^*\le v \le x^{*\top} A e_j$
- 存在纳什均衡局势
- 纯策略被严格优超 $\implies$ 在最优混合策略中对应的概率为 0