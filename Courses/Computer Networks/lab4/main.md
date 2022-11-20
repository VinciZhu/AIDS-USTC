# TCP/UDP 通信程序设计
<div style="text-align: right"> PB20061372 朱云沁 </div>

## 实验目的

1.  学习 socket 编程的基本概念和方法.
2.  理解 TCP 与 UDP 的区别与联系.

## 实验原理

### BSD Sockets API

- `socket()` 创建一个特定类型的新 socket, 由一个整数标识, 并为其分配系统资源.
- `bind()` 通常在服务器端使用, 将一个 socket 与一个 socket 地址结构绑定, 即一个指定的本地IP地址和一个端口号.
- `listen()` 在服务器端使用, 使一个绑定的 TCP socket 进入监听状态.
- `connect()` 用于客户端, 为一个 socket 分配一个空闲的本地端口号. 若为 TCP socket, 尝试建立一个新的TCP连接.
- `accept()` 在服务器端使用. 接受来自远程客户端建立 TCP 连接的请求, 创建一个与该连接的 socket 地址对相关的新 socket.
- `send()`, `recv()`, `sendto()`, `recvfrom()` 用于发送和接收数据. 也可以使用标准函数 `write()` 和 `read()`.
- `close()` 使系统释放分配给一个 socket 的资源. 若为 TCP socket, 终止连接.

### Socket 地址结构

IPv4 中通常使用如下结构:

```c++
struct sockaddr_in {
	__uint8_t       sin_len;
	sa_family_t     sin_family;
	in_port_t       sin_port;
	struct  in_addr sin_addr;
	char            sin_zero[8];
};
```

各部分含义及举例说明见思考题.

### 辅助函数

-   `inet_addr()` 将 Internet 主机地址从 IPv4 的点分八进制表示法转换为网络字节顺序的二进制数据.
-   `htonl()`, `htons()`, `ntohl()`, `ntohs()` 将主机字节顺序与网络字节顺序相互转换.
-   `perror()` 打印错误信息至标准错误输出. 本实验中, 对此函数进行封装, 实现错误处理.

## 实验内容

### 示例程序解读

#### 实验任务

附带的代码参考中有简单的 TCP 和 UDP 通信程序, 理解这两份代码.

#### 文件树及各文件作用

利用 `tree` 工具查看文件树. 经过分析, 将各文件大致作用罗列如下:

```bash
demo
├── Makefile		# 利用 GNU Make 编译 TCP、UDP 服务器和客户端程序.
├── net.h			# 引入 Unix 库函数, 定义 IP、端口、缓冲区长度、TCP 侦听队列长度等常量, 封装错误处理.
├── tcp_client.c	# TCP 客户端源文件, 与指定主机建立 TCP 连接, 随后发送 "hello".
├── tcp_server.c	# TCP 服务器源文件, 阻塞式接受任意主机的 TCP 连接并接收报文.
├── udp_client.c	# UDP 客户端源文件, 向指定主机发送内容为 "hello" 的 UDP 报文.
└── udp_server.c	# UDP 服务器源文件, 阻塞式接收任意主机发送的 UDP 报文.
```

#### 客户端程序流程对比

阅读 `tcp_client.c` 和 `udp_client.c` 两份源代码. 经过理解, 将 TCP、UDP 客户端程序流程对比如下:

<table><thead><tr><th>tcp_client.c</th><th>udp_client.c</th></tr></thead>
<tbody>
<tr><td><p>

1. 创建流 socket, 使用 IPv4 与 TCP 协议.
2. 将服务器地址与端口号转换为网络字节顺序, 存入地址结构体.
3. 利用地址结构体, 向服务器请求建立连接.
4. 发送 "hello" 报文至服务器. 
5. 关闭 socket, 终止 TCP 连接.

<br>

</p></td><td><p>

1. 创建数据报 socket, 使用 IPv4 与 UDP 协议.
2. 将服务器地址与端口号转换为网络字节顺序, 存入地址结构体.
3. 利用地址结构体, 向服务器发送 "hello" 报文.
4. 关闭 socket.

<br>

</p></td></tr>
</tbody></table>

#### 服务器程序流程对比

阅读 `tcp_server.c` 和 `udp_server.c` 两份源代码. 经过理解, 将 TCP、UDP 服务器程序流程对比如下:

<table><thead><tr><th>tcp_server.c</th><th>udp_server.c</th></tr></thead>
<tbody>
<tr><td><p>

1. 创建流 socket, 使用 IPv4 与 TCP 协议.
2. 将地址与端口号转换为网络字节顺序, 存入地址结构体, 与 socket 绑定.
3. 使绑定的 socket 进入监听状态.
4. 阻塞式接受客户端连接, 返回一个新 socket 与客户端通信.
5. 通过新 socket 接收客户端发送的报文, 将内容与长度打印至标准输出.
6. 关闭两个 socket, 终止 TCP 连接.

</p></td><td><p>

1. 创建数据报 socket, 使用 IPv4 与 UDP 协议.
2. 将地址与端口号转换为网络字节顺序, 存入地址结构体, 与 socket 绑定.
3. 阻塞式接收报文, 将内容与长度打印至标准输出, 并得到客户端的地址结构体.
4. 关闭 socket.

</p></td></tr>
</tbody></table>

可知, 有连接、无连接的通信存在差异, 详见思考题.

### TCP 回射程序

#### 实验任务

完成一个 TCP 回射程序, 要求如下:

1.	客户端从标准输入读入一行文本, 发送给服务器. 
2.  服务器接收这行文本, 再将其发送回客户端
3.  客户端接收到这行回射的文本,将其显示在标准输出上.

#### 设计思路

遵循示例程序的规范, 使用 `Socket()` 创建 socket, 使用 `Close()` 关闭 socket. 在服务器程序中, `Bind()`、`Listen()`、`Accept()` 分别用于绑定 socket 地址、监听 socket、接受客户端连接. 在客户端程序中, `Connect()` 用于向服务器发起连接请求.

与示例程序不同, 出于学习的目的, 我们将 `read()`、`write()` 函数封装为 `Read()`、`Write()` 函数, 通过读写 socket 文件描述符实现数据收发. 此外, 服务器 IP、端口号通过命令行参数传入.

客户端、服务器均设计为循环结构:
- 客户端循环读取标准输入, 将输入的每一行文本发送给服务器, 并接收服务器回射的文本, 直到收到 SIGINT 信号. 
- 服务器循环接收客户端发送的文本, 并将其回射给客户端. 若客户端关闭连接, 服务器不会直接退出, 而是阻塞式等待下一个连接. 直到收到 SIGINT 信号, 服务器关闭 socket 并退出.

程序流程图如下:

![图 1: TCP 回射程序流程图](img/echo-flow.svg)

完整代码见附录 [`echo/client.c`](#echoclientc)、[`echo/server.c`](#echoserverc)

#### 实验环境说明

出于学习的目的, 我们选择不在本地主机上测试, 而是将两台设备分别作为客户端与服务器, 代码通过 Git 同步, 跨平台分别编译运行. 其中, 客户端环境为 macOS, 主机名为 “Ned's Mac”; 服务器环境为 Termux (Android 终端, 提供了不完整的 Linux 内核), 主机名为 “Ned's Phone”. 两者均为 arm64 架构. 服务器程序的端口统一为 8080.

我们使用 GNU Make 构建二进制文件, 在 Makefile 中编写简易脚本用于代码同步、获取本机 IP 地址、启动服务器等. 详见附录 [`Makefile`](#makefile).

#### 实验结果

![图 2: TCP 回射程序客户端输入输出](img/echo-client.png)

![图 3: TCP 回射程序服务器输入输出](img/echo-server.jpeg)

通信过程如下:

1. 服务器程序启动, 在地址 114.214.218.9:8080 上监听.
2. 客户端程序启动, 请求连接服务器.
3. 服务器接受连接, 与客户端地址 114.214.210.173:61738 进行通信.
4. 用户输入“hello world!”, 客户端发送报文, 服务器接收.
5. 服务器发送回射报文“hello world!”, 客户端接收.
6. 用户输入“goodbye world!”, 客户端发送报文, 服务器接收.
7. 服务器发送回射报文“goodbye world!”, 客户端接收.
8. 客户端收到 SIGINT 信号, 关闭连接并退出, 服务器进入等待状态.
9. 服务器收到 SIGINT 信号, 停止监听并退出.

正确实现了 TCP 回射程序的功能.

### UDP 通信程序

#### 实验任务

完成一个 UDP 通信程序, 要求如下:

1.  客户端创建 10 个 socket, 每个 socket 发送 1 个数据包给服务器, 内容为任意字符串. 
2.  服务器在每次收到数据包时, 将发送端的 IP 地址和端口号显示在标准输出上.
3.  客户端使用 `connect()` 和 `send()` 实现.

#### 设计思路

根据要求, 客户端应当调用 `Connect()` 和 `Send()`. 由于 UDP 是无连接协议, `connect()` 实际上指定了 socket 发送和接收数据的远端地址, 从而允许使用 `send()` 等函数, 同时防止接受其他来源的数据包.

与 TCP 连接不同, 服务器 socket 无需进入监听状态, 可使用 `Recvfrom()` 直接接收数据包并返回客户端 socket 地址. 我们依然使用命令行参数设定服务器 IP 与端口号, 服务器循环接收数据包并输出, 直到收到 SIGINT 信号. 

但是, 出于学习的目的, 我们在客户端采用多线程的方式创建 socket、发送 UDP 报文. 具体而言:

1.  客户端主线程循环调用 `pthread_create()` 创建 10 个子线程.
2.  子线程分别运行 `thread_func()` 函数. 该函数创建 socket, 使用 `Connect()` 连接服务器, 使用 `Send()` 发送数据包, 最后关闭 socket.
3.  主线程循环调用 `pthread_join()` 等待子线程结束.

程序流程图如下:

![图 4: UDP 通信程序流程图](img/udp-flow.svg)

完整代码见附录 [`udp\client.c`](#udpclientc) 和 [`udp\server.c`](#udpserverc).

#### 实验结果

![图 5: UDP 通信程序客户端输入输出](img/udp-client.png)

![图 6: UDP 通信程序服务器输入输出](img/udp-server.jpeg)

通信过程如下:

1. 服务器程序启动, 绑定地址.
2. 客户端程序启动, 10 个子线程并行连接服务器, 发送随机字符串.
3. 服务器收到 10 个数据包, 输出源地址.

正确实现了 UDP 通信程序的功能. 此外, 数据包乱序到达服务器, 符合预期.

### TCP 通信程序

#### 实验任务

完成一个 TCP 通信程序, 要求利用 `fork()`, 实现两终端实时通信.

#### 设计思路

考虑实现一个基于 TCP 协议的交互式通信程序, 遵循 REPL (Read-Eval-Print Loop) 模式, 循环读取用户输入的内置命令, 完成相应的操作, 并输出结果. 该程序应当支持如下命令:

-	`listen <ip> <port>`: 监听指定地址, 等待客户端连接.
-	`connect <ip>:<port>`: 连接服务器, 参数为服务器 IP 地址和端口号.
-	`send <msg>`: 发送消息, 参数为消息内容.
-	`close`: 关闭连接.
-	`exit`: 退出程序.

以下两种情况, 需使用多进程:

-	用户输入 `listen` 命令后, 程序创建服务器 socket 并进入监听状态. 为了使 `Accept()` 函数不阻塞前台输入, 可以采用如下方案: 调用 `fork()` 创建一个后台子进程, 该子进程循环调用 `select()`, 检查侦听队列中是否有新的连接请求. 如果有, 则子进程退出, 利用 SIGCHLD 信号通知父进程. 此时, 父进程调用 `Accept()` 将立即返回.

-	当程序接受远程连接, 或用户输入 `connect` 命令建立连接时, 本地程序与远端程序开始实时通信. 此时, 程序应当能够异步接收远端报文, 而不阻塞前台输入. 为了实现这一点, 调用 `fork()` 创建一个后台子进程, 该子进程循环调用 `Recv()` 接收报文并打印至标准输出, 直到本地或远端程序关闭连接, 即: 本地用户输入 `close` 或 `exit`, 调用 `kill()` 终止子进程; 或者远端程序关闭连接, 本地子进程 `Recv()` 返回 0, 发出 SIGCHLD 信号通知父进程更改状态.

将程序表征为有限状态机, 其状态转移图如下:

![图 7: TCP 通信程序状态转移图](img/tcp-fsm.svg)

其中, 各状态释义如下:
-	Begin: 初始状态. 对应源代码中 `STATE_BEGIN`.
-	Wait: 程序等待远端连接. 对应源代码中 `STATE_WAIT`.
-	Server: 程序已接受远端连接, 作为服务器与远端通信. 对应源代码中 `STATE_SERVER`.
-	Cilent: 程序已主动建立连接, 作为客户端与远端通信. 对应源代码中 `STATE_CLIENT`.
-	End: 程序退出. 对应源代码中 `STATE_END`.

完整代码见附录 [`tcp.c`](#tcptcpc).

#### 实验结果

![图 8: TCP 通信程序客户端输入输出](img/tcp-client.png)

![图 9: TCP 通信程序服务器输入输出](img/tcp-server.jpg)

通信过程如下:

1.  两终端分别启动程序.
1.	Termux 终端: 输入 `listen` 命令, 在地址 114.214.245.137:8080 上监听.
1.	macOS 终端: 输入 `connect` 命令, 与地址 114.214.245.137:8080 建立连接.
1.	macOS 终端: 输入 `send` 命令, 依次发送报文 "HelloMyPhone!"、"HowAreYou?".
1.	Termux 终端: 接收到报文, 依次输出 "HelloMyPhone!"、"HowAreYou?".
1.  Termux 终端: 输入 `send` 命令, 依次发送报文 "ImFine"、"HappyUstc".
1.	macOS 终端: 接收到报文, 依次输出 "ImFine"、"HappyUstc".
1.	macOS 终端: 输入 `send` 命令, 发送报文 "IdontThinkSo".
1.  Termux 终端: 接收到报文, 输出 "IdontThinkSo".
1.  macOS 终端: 输入 `close` 命令, 关闭连接.
1.  Termux 终端: 接收到 Termux 终端关闭连接的报文.
1.  macOS 终端: 输入 `exit` 命令, 退出程序.
1.  Termux 终端: 输入 `exit` 命令, 停止监听并退出程序.

正确实现了 TCP 实时通信程序的功能.

## 思考题

1.  **解释 `struct sockaddr_in` 结构体各个部分的含义, 并用具体的数据举例说明.**

	socket 地址以 `struct sockaddr` 为通用格式. 若基于 IPv4 协议, 则 socket 地址被定义为接口 IP 地址与 16 位端口号的组合, 此时可用 `struct sockaddr_in` 进行解释. 在 man page 中, 该结构体的定义如下:

	```C++
	struct sockaddr_in {
		sa_family_t    sin_family; /* address family: AF_INET */
		in_port_t      sin_port;   /* port in network byte order */
		struct in_addr sin_addr;   /* internet address */
	};
	```

	在 macOS 实现中, `struct sockaddr_in` 的定义如下

	```c++
	/*
	* Socket address, internet style.
	*/
	struct sockaddr_in {
		__uint8_t       sin_len;
		sa_family_t     sin_family;
		in_port_t       sin_port;
		struct  in_addr sin_addr;
		char            sin_zero[8];
	}
	```

	下面针对 macOS 实现展开说明.

	-	`sin_len`
	
		结构体长度, 类型为 `uint8_t`. 对于 `struct sockaddr_in`, 该成员无需显式设置或检查. 在 4.3BSD-Reno 中被加入, 不作为 POSIX 规范. 调试过程中发现, 该成员始终为 0.

	-	`sin_family`
	
		socket 使用的协议族, 类型为 `sa_family_t` (`unsigned char`). 决定了 `struct sockaddr` 中 `sa_data` 成员的解释方式. 对于 `struct sockaddr_in`, 应当被设置为 `AF_INET`.
		
	-	`sin_port`
	
		网络字节顺序的端口号, 类型为 `in_port_t` (`unsigned short`). 端口号由 TCP、UDP 等传输层协议实现, 范围为 0 到 65535, 分为以下 3 类:
		1. well-known port, 0~1023: 由 IANA 分配和控制, 分配给一些常见的服务, 比如 80 端口用于 Web 服务器.
        2. registered port, 1024~49151: 不受 IANA 控制, 但 IANA 会登记并提供这些端口的使用情况清单.
        3. dynamic/private port, 49152~65535: 不受 IANA 管理, 通常作为临时端口.
   
		设置该成员时, 必须调用 `htons()` 将端口号由主机字节顺序转换为网络字节顺序. 
		
		以本次实验为例, 服务器监听端口号为 8080, 因此 `sin_port` 被设置为 0x1f90 (8080 的十六进制表示, 大端字节顺序).

	-	`sin_addr`
	
		主机接口的 IP 地址, 类型为 `struct in_addr`. 由于历史原因, 网络字节顺序的主机 IP 地址存放在该结构体的 `s_addr` 成员中, 类型为 `in_addr_t` (`uint32_t`). IP 地址由 IPv4 协议实现, 用点分十进制表示的范围为 0.0.0.0~255.255.255.255. 

		设置该成员时, 可以将形如 `INADDR_*` 的常量 (例如 `INADDR_LOOPBACK`) 通过 `htonl()` 转换为网络字节顺序, 或使用`inet_aton()` 将主机地址从点分十进制字符串转换为网络字节顺序, 或使用 `gethostbyname()` 直接解析域名、主机名字符串.

		面向连接的 socket 不允许使用组播、广播地址.

		以本次实验的 TCP 通信程序部分为例, Termux 终端的 IP 地址为 "114.214.245.137", 大端字节 16 进制为 0x72d6f589 因此 `sin_addr.s_addr` 被设置为 0x72d6f589.

	-	`sin_zero[8]`

		保留字段, 用于填充 `struct sockaddr_in` 以与 `struct sockaddr` 保持相同的大小. 通常, 其值被设置为 '\0' (以 `char` 表示).

2.  **说明面向连接的客户端和非连接的客户端在建立 socket 时有什么区别.**

	函数 `socket()` 为一个新套接字分配系统资源, 返回文件描述符. man page 对 `socket()` 的定义如下:

	```C++
	int socket(int domain, int type, int protocol);
	```

	1.	面向连接的客户端, 调用 `socket()` 时, 参数 `type` 应当设置为 `SOCK_STREAM`, 指定类型为流 socket, 提供有序、可靠、基于连接的字节流传输.

		无连接的客户端, 调用 `socket()` 时, 参数 `type` 应当设置为 `SOCK_DGRAM`, 指定类型为数据报 socket, 提供无连接的数据传输, 不能保证顺序和可靠性.
	
	2.	面向连接的客户端, 通常使用 TCP 协议, 调用 `socket()` 时参数 `protocol` 设置为 `IPPROTO_TCP`.

		无连接的客户端, 通常使用 UDP 协议, 调用 `socket()` 时参数 `protocol` 设置为 `IPPROTO_UDP`.

	3.	面向连接的客户端, socket 端口号在调用 `connect()` 时由系统分配. 也可调用 `bind()` 绑定.

		无连接的客户端, socket 端口号在调用 `connect()` 或 `sendto()` 时由系统分配. 也可调用 `bind()` 绑定.
	

3.  **说明面向连接的客户端和无连接的客户端在收发数据时有什么区别.**

	1.  面向连接的客户端, 首先调用 `connect()` 建立连接, 之后直接调用 `send()`、`recv()`、`write()`、`read()` 等函数收发数据, 无需再次指定服务器 IP、端口.

		无连接的客户端, 收发数据应当调用 `sendto()`、`recvfrom()` 等函数, 每次均传入服务器 `struct sockaddr` 的指针, 用于指定目标地址或返回源地址. 也可调用 `connect()` 告知操作系统服务器 IP、端口, 之后直接调用 `send()`、`recv()`、`write()`、`read()` 等函数收发数据.

	2.  面向连接的客户端, 点到点通信. 接收数据时, 操作系统依据 (源 IP 地址, 源端口号, 目的 IP 地址, 目的端口号) 四元组标识, 将数据包交付给对应的 socket, 因而一个 socket 只能接收来自于同一对 IP、端口的数据包. 同样, 发送数据时, 只能发送给建立连接的服务器.

		无连接的客户端, 一对多、多对一或多对多通信. 接收数据时, 操作系统依据 (目的 IP 地址, 目的端口号) 二元组标识, 将数据包交付给对应的 socket, 因而一个 socket 可以接收来自于不同对 IP、端口的数据包. 发送数据时, 可以指定发送给任意服务器.

	3.  面向连接的客户端, 收发数据时, 操作系统通过确认、重传等机制保证数据的顺序和可靠性. 若连接中断, 则 `send()`、`recv()` 等函数会返回错误.

		无连接的客户端, 收发数据时, 操作系统不保证数据的顺序和可靠性, 无法得知数据是否丢失或重复.

	4.  面向连接的客户端, 收发数据时, TCP 协议还提供拥塞控制、流量控制等服务.

		无连接的客户端不具有这些服务.


4.  **比较面向连接的通信和无连接通信, 它们各有什么优点和缺点? 适合在哪种场合下使用?**

-	面向连接的通信
	-   优点
		1.  确认、重传等机制, 保证可靠、有序的字节流传输.
		2.  提供流量控制、拥塞控制, 保证传输的稳定性.
	-   缺点
		1.  三次握手, 四次挥手, 建立连接和断开连接需要时间.
		2.  传输数据时, 操作系统需要维护连接状态, 占用系统资源.
		3.  数据报首部开销大, 20 字节.
		4.  每条 TCP 连接只能是点到点通信.
	-   适合场合
		对数据可靠性、传输稳定性有要求, 不强调速度和实时性的场合. 
		
		例如: 文件传输 (FTP), 网页传输 (HTTP), 邮件传输 (SMTP) 等.



-	无连接通信
	-   优点
		1.  无需连接, 实时性, 速度快.
		2.  无需连接, 无确认、窗口、拥塞控制等机制, 不占用系统资源.
		3.  数据报首部开销小, 8 字节.
		4.  一对多、多对一、多对多通信.
	-   缺点
		1.  不可靠, 数据可能丢失、可能重复.
		2.  不保证顺序, 数据可能失序.
		3.  传输可能不稳定, 如拥塞现象.
	-   适合场合
		
		重视速度和实时性, 允许一定程度的丢包、出错或拥塞的场合.

		例如: 流媒体、实时游戏、网络会议.

1.  **实验过程中使用 socket 的时候是工作在阻塞方式还是非阻塞方式? 通过网络检索阐述这两种操作方式的不同.**

	本实验中, socket 工作在阻塞方式.

	不同:
	1.  阻塞是指当某个函数执行成功的条件当前不满足时, 该函数会阻塞当前执行线程, 程序执行流在超过时间到达或执行成功的条件满足后恢复继续执行.
	
		非阻塞模式相反, 即使某个函数执行成功的条件当前不满足, 该函数也不会阻塞当前执行线程, 而是立即返回, 继续执行程序流.
	2.  socket 默认工作在阻塞方式. 
		
		在调用 `socket()` 函数时为 `type` 参数增加 `SOCK_NONBLOCK` 标志, 可以创建非阻塞方式的 socket. 也可以使用 `fcntl()` 函数或 `ioctl()` 函数给创建的 socket 增加 `O_NONBLOCK` 标志来设置为非阻塞模式.
	3.  socket 工作在阻塞方式, 调用 `accept()`、`send()`、 `recv()` 函数, 程序会阻塞在调用处, 直到出错, 或成功接受连接或收发数据. 调用 `connect()` 函数, 程序会阻塞在调用处, 直到出错或 TCP 三次握手完成.
	
		socket 工作在非阻塞方式, 调用 `accept()`、`send()`、 `recv()` 函数, 如果没有新连接, 或没有数据可供收发, 不会阻塞程序执行流, 而是立即出错并返回, 得到错误码 `EWOULDBLOCK` 或 `EAGAIN`. 调用 `connect()` 函数, 程序不会等待握手完成, 而是直接出错并返回, 得到错误码 `EINPROGRESS`.
	4.	阻塞方式逻辑简单、易于控制. 适用于分段发送文件、问答模式的通信等.

		非阻塞方式流程复杂, 支持高并发. 适用于多连接的服务器.

## 附录: C 语言源文件

### `echo/client.c`

```C++
#include "net.h"

int sockfd = -1;

void signal_handler(int sig) {
    printf("\nSIGINT received, exiting...\n");

    if (sockfd != -1) {
        /* 关闭 socket */
        Close(sockfd);
        printf("Connection closed\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {

    /* 注册信号处理函数 */
    signal(SIGINT, signal_handler);

    /* 解析命令行参数 */
    char server_ip[16];
    in_port_t server_port;
    if (argc == 3) {
        strcpy(server_ip, argv[1]);
        server_port = atoi(argv[2]);
    } else {
        strcpy(server_ip, TCP_SERVER_ADDRESS);
        server_port = TCP_SERVER_PORT;
    }

    /* 创建客户端 socket */
    sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int enable = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    /* 建立 TCP 连接 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr.s_addr) != 1)
        perror_and_exit("inet_pton");

    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(struct sockaddr_in);

    if (getsockname(sockfd, (struct sockaddr *)&client_addr, &client_addr_len) != 0)
        perror_and_exit("getsockname");
    printf("Client socket created on %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    printf("File descriptor: %d\n", sockfd);

    /* 初始化缓冲区 */
    char buf[TCP_BUF_LENGTH];
    size_t pkt_len;

    while (1) {

        /* 读入文本 */
        printf("Input: ");
        fflush(stdout);
        pkt_len = Read(STDIN_FILENO, buf, TCP_BUF_LENGTH);
        if (buf[pkt_len - 1] == '\n') {
            buf[pkt_len - 1] = '\0';
            pkt_len--;
        }

        /* 发送报文 */
        printf("Send message: %s[%zu bytes]\n", buf, pkt_len);
        Write(sockfd, buf, pkt_len);

        /* 接收报文 */
        pkt_len = Read(sockfd, buf, TCP_BUF_LENGTH);
        buf[pkt_len] = '\0';
        if (pkt_len > 0)
            printf("Message received: %s[%zu bytes]\n", buf, pkt_len);
        else
            break;
    }

    /* 关闭 socket */
    Close(sockfd);
    printf("Connection closed\n");

    return 0;
}
```

### ``echo/server.c``

```C++
#include "net.h"

int server_sockfd = -1;
int client_sockfd = -1;

void sigint_handler(int sig) {
    printf("\nSIGINT received, exiting...\n");

    if (client_sockfd != -1) {
        /* 关闭客户端 socket */
        Close(client_sockfd);
        printf("Connection closed\n");
    }

    if (server_sockfd != -1) {
        /* 关闭服务器 socket */
        Close(server_sockfd);
        printf("Server closed\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {

    /* 注册信号处理函数 */
    signal(SIGINT, sigint_handler);

    /* 解析命令行参数 */
    char server_ip[16];
    in_port_t server_port;
    if (argc == 3) {
        strcpy(server_ip, argv[1]);
        server_port = atoi(argv[2]);
    } else {
        strcpy(server_ip, TCP_SERVER_ADDRESS);
        server_port = TCP_SERVER_PORT;
    }

    /* 创建服务器 socket */
    server_sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int enable = 1;
    Setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    /* 绑定端口 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr.s_addr) != 1) {
        perror_and_exit("inet_pton");
    }

    Bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 监听端口 */
    Listen(server_sockfd, CONNECTION_NUMBER);
    printf("Server listening on %s:%d\n", server_ip, server_port);
    printf("File descriptor: %d\n", server_sockfd);

    while (1) {

        /* 接受 TCP 连接 */
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(struct sockaddr_in);
        client_sockfd = Accept(server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
        printf("Accept client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("File descriptor: %d\n", client_sockfd);

        while (1) {

            /* 接收报文 */
            char buf[TCP_BUF_LENGTH];
            size_t pkt_len;

            pkt_len = Read(client_sockfd, buf, TCP_BUF_LENGTH);
            buf[pkt_len] = '\0';
            if (pkt_len > 0)
                printf("Message received: %s[%zu bytes]\n", buf, pkt_len);
            else
                break;

            /* 发送报文 */
            printf("Send message: %s[%zu bytes]\n", buf, pkt_len);
            Write(client_sockfd, buf, pkt_len);
        }

        /* 关闭客户端 socket */
        Close(client_sockfd);
        client_sockfd = -1;
        printf("Connection closed\n");
    }

    /* 关闭服务器 socket */
    Close(server_sockfd);
    printf("Server closed\n");

    return 0;
}
```

### ``udp/client.c``

```C++
#include "net.h"
#include <pthread.h>
#include <time.h>
#define MAX_MSG_SIZE 20
#define MSG_COUNT 10

void Pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine)(void *), void *arg) {
    if (pthread_create(thread, attr, start_routine, arg) != 0)
        perror_and_exit("pthread_create error");
}

void Pthread_join(pthread_t thread, void **retval) {
    if (pthread_join(thread, retval) != 0)
        perror_and_exit("pthread_join error");
}

void *thread_func(void *arg) {

    struct sockaddr_in server_addr = *(struct sockaddr_in *)arg;

    /* 创建 socket */
    int sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int enable = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    pthread_t tid = pthread_self();

    /* 生成报文 */
    srand((unsigned)time(NULL) + (size_t)tid);
    char buf[UDP_BUF_LENGTH];
    size_t pkt_len = rand() % MAX_MSG_SIZE;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < pkt_len; ++i)
        buf[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    buf[pkt_len] = '\0';

    /* 发送报文 */
    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    Send(sockfd, buf, pkt_len, 0);
    printf("Thread %p send message: %s [%zu bytes]\n", tid, buf, pkt_len);

    /* 关闭套接字 */
    close(sockfd);

    return NULL;
}

int main(int argc, char *argv[]) {

    /* 解析命令行参数 */
    char server_ip[16];
    in_port_t server_port;
    if (argc == 3) {
        strcpy(server_ip, argv[1]);
        server_port = atoi(argv[2]);
    } else {
        strcpy(server_ip, TCP_SERVER_ADDRESS);
        server_port = TCP_SERVER_PORT;
    }

    /* 设置服务器地址 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr.s_addr) != 1) {
        perror_and_exit("inet_pton");
    }

    pthread_t tids[MSG_COUNT];
    /* 创建线程 */
    for (size_t i = 0; i < MSG_COUNT; i++) {
        Pthread_create(&tids[i], NULL, thread_func, (void *)&server_addr);
    }
    /* 等待线程结束 */
    for (size_t i = 0; i < MSG_COUNT; i++) {
        Pthread_join(tids[i], NULL);
    }

    return 0;
}
```

### ``udp/server.c``

```C++
#include "net.h"

int sockfd = -1;

void sigint_handler(int sig) {
    printf("\nSIGINT received, exiting...\n");

    if (sockfd != -1) {
        /* 关闭服务器 socket */
        Close(sockfd);
        printf("Server closed\n");
        exit(0);
    }
}

int main(int argc, char *argv[]) {

    /* 注册信号处理函数 */
    signal(SIGINT, sigint_handler);

    /* 解析命令行参数 */
    char server_ip[16];
    in_port_t server_port;
    if (argc == 3) {
        strcpy(server_ip, argv[1]);
        server_port = atoi(argv[2]);
    } else {
        strcpy(server_ip, TCP_SERVER_ADDRESS);
        server_port = TCP_SERVER_PORT;
    }

    /* 创建服务器 socket */
    sockfd = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int enable = 1;
    Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    /* 绑定端口 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr.s_addr) != 1) {
        perror_and_exit("inet_pton");
    }

    Bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    printf("Server socket created on %s:%d\n", server_ip, server_port);

    while (1) {

        /* 接收报文 */
        char buf[UDP_BUF_LENGTH];
        size_t pkt_len;

        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        pkt_len = Recvfrom(sockfd, buf, UDP_BUF_LENGTH, 0, (struct sockaddr *)&client_addr, &client_addr_len);

        buf[pkt_len] = '\0';
        printf("Received \"%s\" [%zu bytes] from %s:%d\n", buf, pkt_len, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }

    /* 关闭服务器 socket */
    Close(sockfd);
    printf("Server closed\n");

    return 0;
}
```

### ``tcp/tcp.c``

```C++
#include "net.h"

/* 本地 socket 相关信息 */
int local_sockfd = -1;
struct sockaddr_in local_addr;
socklen_t local_addr_len;
char local_ip[16];
in_port_t local_port;

/* 远端 socket 相关信息 */
int remote_sockfd = -1;
struct sockaddr_in remote_addr;
socklen_t remote_addr_len;
char remote_ip[16];
in_port_t remote_port;

/* TCP 缓冲区 */
char buf[TCP_BUF_LENGTH];
size_t pkt_len;

/* 状态标识 */
#define STATE_BEGIN 0
#define STATE_WAIT 1
#define STATE_SERVER 2
#define STATE_CLIENT 3
#define STATE_END 4
int state = STATE_BEGIN;

/* 交互命令 */
void cmd_send(char *msg);
void cmd_listen(char *addr);
void cmd_connect(char *addr);
void cmd_close(void);
void cmd_exit(void);

#define CMD_LENGTH 256

/* 子进程相关 */
void sigchld_handler(int signo);
void fork_select_loop();
void fork_recv_loop();
pid_t pid;

int main() {

    /* 注册 SIGCHLD */
    signal(SIGCHLD, sigchld_handler);

    /* Read-Eval-Print Loop */
    while (state != STATE_END) {
        getchar();

        char line[CMD_LENGTH];
        printf("local> ");
        fgets(line, CMD_LENGTH, stdin);
        line[strlen(line) - 1] = '\0';

        char *cmd = strtok(line, " ");
        if (!cmd)
            continue;
        char *arg = strtok(NULL, " ");


        if (strcmp(cmd, "send") == 0) {
            cmd_send(arg);
        } else if (strcmp(cmd, "listen") == 0) {
            cmd_listen(arg);
        } else if (strcmp(cmd, "connect") == 0) {
            cmd_connect(arg);
        } else if (strcmp(cmd, "close") == 0) {
            cmd_close();
        } else if (strcmp(cmd, "exit") == 0) {
            cmd_exit();
        } else {
            printf("local: Unknown command: %s\n", cmd);
        }
    }

    return 0;
}

void sigchld_handler(int signo) {
    switch (state) {
    case STATE_WAIT:
        /* fork_select_loop 子进程结束 */
        remote_sockfd = Accept(local_sockfd, (struct sockaddr *)&remote_addr, &remote_addr_len);

        /* 此处未能正确获取地址, 原因未知 */
        remote_addr_len = sizeof(struct sockaddr_in);
        if (getsockname(remote_sockfd, (struct sockaddr *)&remote_addr, &remote_addr_len) != 0)
            perror_and_exit("getsockname");
        remote_port = ntohs(remote_addr.sin_port);
        inet_ntop(AF_INET, &remote_addr.sin_addr, remote_ip, sizeof(remote_ip));
        printf("local: Accept a connection from %s:%d.\n", remote_ip, remote_port);
        
        state = STATE_SERVER;
        fork_recv_loop();
        break;

    case STATE_SERVER:
    case STATE_CLIENT:
        /* fork_recv_loop 子进程结束 */
        cmd_close();
        break;
    }
}

void fork_select_loop() {
    /* 创建子进程 */
    pid = Fork();

    if (pid == 0) {
        /* 循环, 检查侦听队列 */
        fd_set set;
        struct timeval timeout;
        while (1) {
            timeout.tv_sec = 100;
            timeout.tv_usec = 0;
            FD_ZERO(&set);
            FD_SET(local_sockfd, &set);
            int ret = select(local_sockfd + 1, &set, NULL, NULL, &timeout);
            if (ret == -1) {
                perror_and_exit("select");
            } else if (ret == 0) {
                /* 超时 */
                printf("local: Timeout.\n");
            } else {
                exit(0);
            }
        }
    }
}

void fork_recv_loop() {
    /* 创建子进程 */
    pid = Fork();

    if (pid == 0) {
        /* 循环, 接收报文 */
        switch (state) {
        case STATE_SERVER:
            while ((pkt_len = Read(remote_sockfd, buf, TCP_BUF_LENGTH)) != 0) {
                buf[pkt_len] = '\0';
                printf("remote: %s\n", buf);
            }
            exit(0);
            break;
        case STATE_CLIENT:
            while ((pkt_len = Read(local_sockfd, buf, TCP_BUF_LENGTH)) != 0) {
                buf[pkt_len] = '\0';
                printf("remote: %s\n", buf);
            }
            exit(0);
            break;
        }
    }
}

/* 命令: 发送报文 */
void cmd_send(char *msg) {
    switch (state) {
    case STATE_CLIENT:
        pkt_len = strlen(msg);
        memcpy(buf, msg, pkt_len);

        Write(local_sockfd, buf, pkt_len);
        printf("local: Send %zu bytes to remote.\n", pkt_len);
        break;
    case STATE_SERVER:
        pkt_len = strlen(msg);
        memcpy(buf, msg, pkt_len);

        Write(remote_sockfd, buf, pkt_len);
        printf("local: Send %zu bytes to remote.\n", pkt_len);
        break;
    default:
        printf("local: Not connected yet.\n");
        break;
    }
}

/* 命令: 开始监听 */
void cmd_listen(char *addr) {
    /* 解析地址 */
    char *ip = strtok(addr, ":");
    char *port = strtok(NULL, ":");
    if (ip == NULL || port == NULL) {
        printf("local: Invalid address: %s\n", addr);
        return;
    }
    switch (state) {
    case STATE_BEGIN:
        strcpy(local_ip, ip);
        local_port = atoi(port);
        bzero(&local_addr, sizeof(local_addr));
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = htons(local_port);
        if (inet_pton(AF_INET, local_ip, &local_addr.sin_addr.s_addr) != 1) {
            perror_and_exit("inet_pton");
        }

        /* 创建服务器 socket */
        local_sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        int enable = 1;
        Setsockopt(local_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

        /* 绑定地址 */
        Bind(local_sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));

        /* 开始监听 */
        Listen(local_sockfd, CONNECTION_NUMBER);

        state = STATE_WAIT;
        printf("local: Listening on %s:%d\n", local_ip, local_port);
        fork_select_loop();
        break;
    case STATE_CLIENT:
        cmd_close();
        cmd_listen(addr);
        break;
    default:
        printf("local: Already listening on %s:%d\n", local_ip, local_port);
        break;
    }
}

/* 命令: 连接远端 */
void cmd_connect(char *addr) {
    /* 解析地址 */
    char *ip = strtok(addr, ":");
    char *port = strtok(NULL, ":");
    if (ip == NULL || port == NULL) {
        printf("local: Invalid address: %s\n", addr);
        return;
    }
    switch (state) {
    case STATE_BEGIN:
        strcpy(remote_ip, ip);
        remote_port = atoi(port);
        bzero(&remote_addr, sizeof(remote_addr));
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(remote_port);
        if (inet_pton(AF_INET, remote_ip, &remote_addr.sin_addr.s_addr) != 1) {
            perror_and_exit("inet_pton");
        }

        /* 创建客户端 socket */
        local_sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        int enable = 1;
        Setsockopt(local_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

        /* 连接远端 */
        Connect(local_sockfd, (struct sockaddr *)&remote_addr, sizeof(remote_addr));

        /* 获取本地地址 */
        local_addr_len = sizeof(struct sockaddr_in);
        if (getsockname(local_sockfd, (struct sockaddr *)&local_addr, &local_addr_len) != 0)
            perror_and_exit("getsockname");
        local_port = ntohs(local_addr.sin_port);
        inet_ntop(AF_INET, &local_addr.sin_addr, local_ip, sizeof(local_ip));

        printf("local: Connected to %s:%d\n", remote_ip, remote_port);
        state = STATE_CLIENT;
        fork_recv_loop();
        break;
    case STATE_WAIT:
        cmd_close();
        cmd_connect(addr);
        break;
    default:
        printf("local: Already connected to %s:%d\n", remote_ip, remote_port);
        break;
    }
}

/* 命令: 关闭连接 */
void cmd_close(void) {
    switch (state) {
    case STATE_WAIT:
        kill(pid, SIGKILL);
        Close(local_sockfd);
        printf("local: Stop listening.\n");
        state = STATE_BEGIN;
        break;
    case STATE_SERVER:
        kill(pid, SIGKILL);
        Close(remote_sockfd);
        printf("remote: Connection closed.\n");
        state = STATE_WAIT;
        break;
    case STATE_CLIENT:
        kill(pid, SIGKILL);
        Close(local_sockfd);
        printf("local: Connection closed.\n");
        state = STATE_BEGIN;
        break;
    default:
        printf("local: Not connected yet.\n");
        break;
    }
}

/* 命令: 退出程序 */
void cmd_exit(void) {
    switch (state) {
    case STATE_BEGIN:
        state = STATE_END;
        break;
    case STATE_SERVER:
        cmd_close();
        cmd_exit();
        break;
    default:
        cmd_close();
        cmd_exit();
        break;
    }
}
```

### `common/net.h`

```C++
#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>

#define TCP_SERVER_ADDRESS "127.0.0.1"
#define TCP_SERVER_PORT 8001
#define TCP_BUF_LENGTH 1000
#define CONNECTION_NUMBER 10

#define UDP_SERVER_ADDRESS "127.0.0.1"
#define UDP_SERVER_PORT 8002
#define UDP_BUF_LENGTH 1000

void perror_and_exit(const char *x) {
    perror(x);
    exit(1);
}

pid_t Fork() {
    pid_t pid;
    if ((pid = fork()) < 0)
        perror_and_exit("fork error");
    return pid;
}

int Socket(int family, int type, int protocol) {
    int ret;
    if ((ret = socket(family, type, protocol)) < 0)
        perror_and_exit("socket error");
    return ret;
}

void Bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen) {
    if (bind(sockfd, my_addr, addrlen) < 0)
        perror_and_exit("bind error");
}

void Listen(int sockfd, int backlog) {
    if (listen(sockfd, backlog) < 0)
        perror_and_exit("listen error");
}

int Accept(int sockfd, struct sockaddr *client_addr, socklen_t *addrlen) {
    int ret;
    if ((ret = accept(sockfd, client_addr, addrlen)) < 0)
        perror_and_exit("accept error");
    return ret;
}

void Connect(int sockfd, const struct sockaddr *server_addr, socklen_t addrlen) {
    if (connect(sockfd, server_addr, addrlen) < 0)
        perror_and_exit("connect error");
}

ssize_t Recv(int sockfd, void *buf, size_t nbytes, int flags) {
    ssize_t n;
    if ((n = recv(sockfd, buf, nbytes, flags)) < 0)
        perror_and_exit("recv error");
    return n;
}

ssize_t Recvfrom(int sockfd, void *buf, size_t nbytes, int flags,
                 struct sockaddr *addr, socklen_t *addrlen) {
    ssize_t n;
    if ((n = recvfrom(sockfd, buf, nbytes, flags, addr, addrlen)) < 0)
        perror_and_exit("recvfrom error");
    return n;
}

void Send(int sockfd, const void *buf, size_t nbytes, int flags) {
    if (send(sockfd, buf, nbytes, flags) != (ssize_t)nbytes)
        perror_and_exit("send error");
}

void Sendto(int sockfd, const void *buf, size_t nbytes, int flags,
            const struct sockaddr *addr, socklen_t addrlen) {
    if (sendto(sockfd, buf, nbytes, flags, addr, addrlen) != (ssize_t)nbytes)
        perror_and_exit("sendto error");
}

ssize_t Read(int fd, void *buf, size_t count) {
    ssize_t n;
    if ((n = read(fd, buf, count)) < 0)
        perror_and_exit("read error");
    return n;
}

ssize_t Write(int fd, const void *buf, size_t count) {
    ssize_t n;
    if ((n = write(fd, buf, count)) < 0)
        perror_and_exit("write error");
    return n;
}

void Close(int sockfd) {
    if (close(sockfd) < 0)
        perror_and_exit("close error");
}

void Shutdown(int sockfd, int how) {
    if (shutdown(sockfd, how) < 0)
        perror_and_exit("shutdown error");
}

void Setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    if (setsockopt(sockfd, level, optname, optval, optlen) < 0)
        perror_and_exit("setsockopt error");
}

int Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen) {
    int ret;
    if ((ret = getsockopt(sockfd, level, optname, optval, optlen)) < 0)
        perror_and_exit("getsockopt error");
    return ret;
}
```

### `Makefile`

```Makefile
# Build
CS_TARGET := echo udp
INC := -I common

.PHONY: all
all: $(CS_TARGET) tcp

%: %.c
	gcc $(INC) $< -o $@

.PHONY: $(CS_TARGET)
$(CS_TARGET): %: %/client %/server | git-sync

.PHONY: tcp
tcp: tcp/tcp | git-sync

.PHONY .SILENT: clean
clean:
	rm -f $(CS_TARGET:%=%/client)
	rm -f $(CS_TARGET:%=%/server)
	rm -f tcp/tcp

# Start server
IP := $(shell ifconfig 2>/dev/null| grep -oe 'inet [0-9\.]\+' |\
 grep -v '127.0.0.1\|172.19.0.1' | cut -d\  -f2)
PORT := 8080

.PHONY: $(CS_TARGET:%=%-server)
$(CS_TARGET:%=%-server): %-server: %/server | git-sync
	$< $(IP) $(PORT)

# Sync source between local and remote
HOST_NAME := $(shell hostname)
.PHONY .SILENT: git-sync
git-sync:
	git pull --quiet
	git diff --quiet ||\
	git commit -am 'Sync from $(HOST_NAME)' &&\
	git push --quiet
```
