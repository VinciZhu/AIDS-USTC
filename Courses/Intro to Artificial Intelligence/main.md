# Intro to AI: Stereo Disparity Estimation

<center>PB20061372 &ensp; Yunqin Zhu &ensp; Jan. 15, 2023</center>
<br>

<hr>

## Introduction

The task of this project is to write a MATLAB program that computes pixel disparities between a stereo pair of images, where the ./input is a rectified pair of images, and the output is a matrix with its values indicating the disparity of the stereo correspondence for each pixel in the left image.

There are two algorithms I implemented: (1) Dynamic Programming (DP), which optimizes the energy separately for each horizontal scanline; (2) Graph Cut (GC), which optimizes the energy on the full 2D grid. Both of them take into account the global smoothness of the disparity map and outperform the naive window-based matching method.

The code framework I followed in the project is from this writeup at Princeton University:

`www.cs.princeton.edu/courses/archive/fall13/cos429/assignment3/assignment3`

## Theoretical Background

Basically, the stereo matching problem can be formulated as to find the disparity map $\boldsymbol {d}$ that minimizes the following energy function:

$$
E({\boldsymbol {d}}) = E_d({\boldsymbol {d}})+E_s({\boldsymbol {d}}) = \sum _{p}D(p,d_{p})+\sum _{p,q\in {\mathcal {N}}}R(p,d_{p},q,d_{q})
$$

where the so-called data term $D(p,d_{p})$ is the pixel-wise dissimilarity cost at pixel $p$ with disparity $d_{p}$, and the smoothness term $R(p,d_{p},q,d_{q})$ is the regularization cost between pixels $p$ and $q$ with disparities $d_{p}$ and $d_{q}$ respectively, for all pairs of neighbouring pixels $\mathcal {N}$.

In this project, I formulate the data term as the Sum of Absolute Differences (SAD) with a clamp to reduce the effect of outliers. That is,

$$
D(p,d_{p})=\min\left\{\frac{1}{|\mathcal{W}(p)|}\sum_{q\in \mathcal{W}(p)}\left|\boldsymbol {I}_{q}-\boldsymbol {I}_{q+d_{p}}\right|, \tau\right\}
$$

where $\mathcal{W}(p)$ is the window centered at pixel $p$, $\boldsymbol {I}_{q}$ is the intensity of pixel $q$ in the left image, $\boldsymbol {I}_{q+d_{p}}$ is the intensity of the corresponding pixel in the right image. Similarly, I formulate the smoothness term as the absolute difference between the disparities of two neighbouring pixels and clamp its range. That is,

$$
R(p,d_{p},q,d_{q})=\min\left\{\left|d_{p}-d_{q}\right|, \tau'\right\}
$$

The energy function, on a per-scanline basis, can be minimized in polynomial time using Dynamic Programming, which leads to our first implementation. To be specific, for each row $y$ of the disparity map, we compute the following aggregated cost function:

$$
C_y^{1}(d) = D((1,y), d) \\
C_y^{x}(d) = D((x,y), d) + \min_{d'} \left\{ C_y^{x-1}(d') + R((x-1,y), d', (x,y), d) \right\}, \quad x = 2, 3, \dots, W \\
$$

where $W$ is the width of the image. By choosing the minimun $C_y^W(d)$ and backtracking, we can then find the optimal disparity $d_{(x,y)}^*$ for each pixel $(x,y)$ in the row. In such cases, since no regularization is performed across scanlines, the resulting disparity map can demonstrate streaking artifacts.

Actually, for the smoothness term we use, it is possible to find a solution on the full 2D grid in polynomial time using Graph Cut optimization, which leads to our second implementation. For simplicity, our code will be based on GCMex, the MATLAB wrapper of Veksler, Boykov, Zabih and Kolmogorov's Graph Cut algorithm.

## Implementation Details

See the `./code  ` folder in the attached zip file. The maximum disparity is set to 60. The window size is set to 7x7. The clamp thresholds $\tau$ and $\tau'$ for the data and smoothness terms is set to 10 and 1.7 respectively. Futhermore, to trade off between the data and smoothness terms, I multiply the data term by a factor $\lambda$ = 0.04. After running the code, the disparity maps will be saved in the `./disparity` folder. The code also computes the Root Mean Square Error (RMSE) on each test image to evaluate the performance of the algorithms.

## Results and Analysis

<figcaption class='table-caption'> Test images and output disparities of two stereo matching algorithms </figcaption>

|    Dataset    |       Input left        |       Input right       |        Ground truth         |                   Disparity (DP)                    | Disparity (GC)                            |
| :-----------: | :---------------------: | :---------------------: | :-------------------------: | :-------------------------------------------------: | ----------------------------------------- |
|  2001 Venus   | ![](./input/test01_l.png) | ![](./input/test01_r.png) | ![](./groundtruth/test01.jpg) | ![](./disparity/test01_L1_L1_dynamic_programming.jpg) | ![](./disparity/test01_L1_L1_graph_cut.jpg) |
| 2001 Sawtooth | ![](./input/test02_l.png) | ![](./input/test02_r.png) | ![](./groundtruth/test02.jpg) | ![](./disparity/test02_L1_L1_dynamic_programming.jpg) | ![](./disparity/test02_L1_L1_graph_cut.jpg) |
| 2001 Tsukuba  | ![](./input/test03_l.png) | ![](./input/test03_r.png) | ![](./groundtruth/test03.jpg) | ![](./disparity/test03_L1_L1_dynamic_programming.jpg) | ![](./disparity/test03_L1_L1_graph_cut.jpg) |
|  2003 Teddy   | ![](./input/test04_l.png) | ![](./input/test04_r.png) | ![](./groundtruth/test04.jpg) | ![](./disparity/test04_L1_L1_dynamic_programming.jpg) | ![](./disparity/test04_L1_L1_graph_cut.jpg) |
|  2006 Baby2   | ![](./input/test05_l.png) | ![](./input/test05_r.png) | ![](./groundtruth/test05.jpg) | ![](./disparity/test05_L1_L1_dynamic_programming.jpg) | ![](./disparity/test05_L1_L1_graph_cut.jpg) |
|  2006 Cloth1  | ![](./input/test06_l.png) | ![](./input/test06_r.png) | ![](./groundtruth/test06.jpg) | ![](./disparity/test06_L1_L1_dynamic_programming.jpg) | ![](./disparity/test06_L1_L1_graph_cut.jpg) |
|  2003 Cones   | ![](./input/test07_l.png) | ![](./input/test07_r.png) | ![](./groundtruth/test07.jpg) | ![](./disparity/test07_L1_L1_dynamic_programming.jpg) | ![](./disparity/test07_L1_L1_graph_cut.jpg) |

As is shown in Table 1, both algorithms can produce reasonable disparity maps. The DP algorithm is more sensitive to noise and produces more streaking artifacts. The GC algorithm, on the other hand, is more robust to noise and produces smoother disparity maps.

<figcaption class='table-caption'> RMSE on the test dataset </figcaption>

|     | 2001 Venus | 2001 Sawtooth | 2001 Tsukuba | 2003 Teddy | 2006 Baby2 | 2006 Cloth1 | 2003 Cones |
| :-: | :--------: | :-----------: | :----------: | :--------: | :--------: | :---------: | :--------: |
| DP  |   1.0864   |    1.7392     |    3.1689    |   6.9476   |   4.3338   |   0.58045   |   5.7699   |
| GC  |  0.88611   |    1.6715     |     3.2      |   6.4777   |   4.782    |   0.88025   |   6.1692   |

However, as is shown in Table 2, the GC algorithm does not necessarily produce results with lower RMSE, and the performance varies from one image to another. Part of the reason is that we use the same window radius for all test cases, which is not optimal for either GC or DP algorithms. Besides, in our MATLAB implementations, the computational cost of the GC algorithm is much higher (about 3 times) than that of the DP algorithm. Instead of asserting that one algorithm is better than the other, we should carefully choose the algorithm that best suits the application.


