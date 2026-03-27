#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 512

int main(int argc, char **argv)
{
    const char *host = "127.0.0.1";
    unsigned short port = 9001;
    const char *message = "hello";
    int sockfd;
    struct sockaddr_in server;
    char buf[BUF_SIZE];

    if (argc > 1) {
        host = argv[1];
    }
    if (argc > 2) {
        port = (unsigned short)atoi(argv[2]);
    }
    if (argc > 3) {
        message = argv[3];
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &server.sin_addr) <= 0) {
        perror("inet_pton");
        close(sockfd);
        return 1;
    }

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    if (send(sockfd, message, strlen(message), 0) < 0) {
        perror("send");
        close(sockfd);
        return 1;
    }

    ssize_t n = recv(sockfd, buf, sizeof(buf) - 1, 0);
    if (n < 0) {
        perror("recv");
        close(sockfd);
        return 1;
    }

    buf[n] = '\0';
    printf("Response: %s\n", buf);

    close(sockfd);
    return 0;
}
