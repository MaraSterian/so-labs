#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 5000 // constant for the port number the server will listen on
#define BUF_SIZE 1024 // buffer size for receiving data


int main(void) {
    int server_fd, client_fd; // fds for the listening socket and the connected clients

    struct sockaddr_in addr, cli_addr; // struct to hold server and client address information (IP address and port)
    socklen_t cli_len = sizeof(cli_addr); // store the size of the client address structure, needed for accept()
    char buffer[BUF_SIZE]; // to store received data

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Allow reuse of the address (avoid "Address already in use" on restart)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 2. Bind to 0.0.0.0:PORT
    memset(&addr, 0, sizeof(addr)); // initialize the server address structure to all zeros
    addr.sin_family = AF_INET; //set the address family to IPv4
    addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces (0.0.0.0)
    addr.sin_port = htons(PORT); // set the port number, converting from host byte order to network byte order (big-endian)
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) { // bind the socket to the specified address and port
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Listen
    if (listen(server_fd, 5) < 0) { // mark the socket as passive (ready to accept connections), 5=backlog (max queued connections)
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    
    // Main accept loop
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&cli_addr, &cli_len); // new socket for the new client connection
        if (client_fd < 0) {
            perror("accept");
            continue; // try accepting next client
        }

        char client_ip[INET_ADDRSTRLEN]; // to hold the client's IP address as a string
        inet_ntop(AF_INET, &cli_addr.sin_addr, client_ip, sizeof(client_ip)); // client's IP address: binary to human-readable
        printf("Client connected from %s:%d\n", client_ip, ntohs(cli_addr.sin_port));

        // Echo loop for this client
        while (1) {
            ssize_t n = recv(client_fd, buffer, BUF_SIZE - 1, 0); // receive bytes from client
            if (n < 0) {
                perror("recv");
                break;
            } else if (n == 0) {
                // client closed connection
                printf("Client disconnected.\n");
                break;
            }
            buffer[n] = '\0';
            printf("Received: %s", buffer);
            // Echo back
            if (send(client_fd, buffer, n, 0) < 0) {
                perror("send");
                break;
            }
        }
        close(client_fd);
    }
    close(server_fd);
    return 0;
}