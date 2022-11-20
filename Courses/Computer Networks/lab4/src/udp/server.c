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
