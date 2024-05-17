#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<string.h>
int main(){
    int shmid,a ,i;
    char *ptr,*shmptr;
    shmid=shmget(3000,10,IPC_CREAT | 0666);
    shmptr=shmat(shmid,NULL,0);
    ptr=shmptr;
    for(i=0;i<3;i++){
        puts("ENter the mac: \n");
        scanf("%s",ptr);
        a=strlen(ptr);
        printf("string length: %d",a);
        ptr[a]=' ';
        puts("ENter the IP: ");
        ptr=ptr+a+1;
        scanf("%s",ptr);
        ptr[a]='\n';
        ptr=ptr+a+1;
    }
    ptr[strlen(ptr)]='\0';
    printf("\n ARP table at sever side is =\n%s",shmptr);
    shmdt(shmptr);
}
