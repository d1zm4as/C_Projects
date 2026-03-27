#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 512

int main(int argc, char **argv)
{
    int server_fd;
    struct sockaddr_in addr;
    unsigned short port = 9001;

    if (argc > 1) {
        port = (unsigned short)atoi(argv[1]);
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 4) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("TCP echo server listening on port %u\n", port);

    for (;;) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int client_fd = accept(server_fd, (struct sockaddr *)&client, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        printf("Client connected: %s:%u\n",
               inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        for (;;) {
            char buf[BUF_SIZE];
            ssize_t n = recv(client_fd, buf, sizeof(buf), 0);
            if (n <= 0) {
                break;
            }

            if (send(client_fd, buf, (size_t)n, 0) < 0) {
                perror("send");
                break;
            }
        }

        close(client_fd);
        printf("Client disconnected\n");
    }

    close(server_fd);
    return 0;
}
