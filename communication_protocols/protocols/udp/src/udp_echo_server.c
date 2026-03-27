#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 512

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in addr;
    unsigned short port = 9000;

    if (argc > 1) {
        port = (unsigned short)atoi(argv[1]);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    printf("UDP echo server listening on port %u\n", port);

    for (;;) {
        char buf[BUF_SIZE];
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        ssize_t n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0,
                             (struct sockaddr *)&client, &client_len);
        if (n < 0) {
            perror("recvfrom");
            continue;
        }

        buf[n] = '\0';
        printf("Received %zd bytes from %s:%u: %s\n", n,
               inet_ntoa(client.sin_addr), ntohs(client.sin_port), buf);

        if (sendto(sockfd, buf, (size_t)n, 0,
                   (struct sockaddr *)&client, client_len) < 0) {
            perror("sendto");
        }
    }

    close(sockfd);
    return 0;
}
