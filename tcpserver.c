#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

#define SERV_TCP_PORT 6880 // Corrected the definition of SERV_TCP_PORT
#define SERV_HOST_ADDR "127.0.0.1"

int main() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in cli_addr, serv_addr;
    char filename[25], buf[1000]; // Corrected the declaration of filename
    int n, m = 0;
    int fd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("server: can't open stream socket\n");
    else
        printf("server: stream socket opened successfully\n");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_TCP_PORT); // Corrected the usage of SERV_TCP_PORT

    if ((bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) < 0)
        printf("server: can't bind local address\n");
    else
        printf("server: bound to local address\n");

    listen(sockfd, 5); // Added backlog size for listen

    printf("\nSERVER: waiting for client...\n");

    for (;;) {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
        
        if (newsockfd < 0)
            printf("server: accept failed\n");
        else {
            printf("server: accepted\n");
            n = read(newsockfd, filename, 25);
            filename[n] = '\0';
            printf("\nSERVER: %s is found and ready to transfer\n", filename);

            fd = open(filename, O_RDONLY);
            if (fd < 0) {
                perror("open");
                close(newsockfd);
                continue; // Continue to the next iteration of the loop
            }

            while ((n = read(fd, buf, 1000)) > 0) {
                if (write(newsockfd, buf, n) < 0) {
                    perror("write");
                    break; // Break out of the loop on write error
                }
            }
            
            if (n < 0)
                perror("read");

            printf("\nTransfer complete\n");
            close(fd);
            close(newsockfd);
        }
    }

    return 0;
}