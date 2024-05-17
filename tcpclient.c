#include <stdio.h>
#include <stdlib.h> // Added for exit()
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

#define SERV_TCP_PORT 6880
#define SERV_HOST_ADDR "127.0.0.1"

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char filename[100], buf[1000];
    int n;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Client: can't open stream socket\n");
        exit(1); // Exiting program if socket creation fails
    } else {
        printf("Client: Stream socket opened successfully\n");
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Client: can't connect to server\n");
        exit(1); // Exiting program if connection fails
    } else {
        printf("Client: connected to server successfully\n");
    }

    printf("\nEnter the filename to be displayed: ");
    scanf("%s", filename);
    write(sockfd, filename, strlen(filename));
    printf("\nFilename transferred to server\n");

    n = read(sockfd, buf, sizeof(buf)); // Changed buffer size to sizeof(buf)

    if (n < 0) {
        printf("\nError reading from socket\n");
        exit(1); // Exiting program if read error occurs
    }

    printf("\nClient: Displaying file content of %s\n", filename);
    printf("%.*s", n, buf); // Printing only the received bytes
    close(sockfd);
    exit(0);
}