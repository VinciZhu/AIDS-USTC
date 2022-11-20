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
