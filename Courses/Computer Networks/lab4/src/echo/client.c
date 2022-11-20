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
