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
