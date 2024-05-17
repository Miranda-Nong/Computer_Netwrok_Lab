#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<netdb.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(){
    char hostname[100];
    printf("enter the host name:");
    fgets(hostname,sizeof(hostname),stdin);
    hostname[strcspn(hostname,"\n")]=0;
    struct hostent *hen;
    hen=gethostbyname(hostname);
    if(hen==NULL){
        fprintf(stderr,"host not found\n");
        return 1;
    }
    printf("host name is %s\n",hen->h_name);
    printf("IP address of host is %s\n",inet_ntoa(*((struct in_addr*)hen->h_addr)));
    return 0;
    
}
