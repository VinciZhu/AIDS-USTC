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
