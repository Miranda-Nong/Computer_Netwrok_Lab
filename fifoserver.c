#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main(){
    char filename[100],buf[300],bufl[300];
    int num,num2,n,filesize,f1,fd,fd2;
    mknod("fifo1",S_IFIFO|0666,0);
    mknod("fifo2",S_IFIFO|0666,0);
    printf("\nServer online\n");
    fd=open("fifo1",O_RDONLY);
    printf("Client online!Waiting for request...\n\n");
    while(1){
        num=read(fd,filename,100);
        filename[num]='\0';
        f1=open(filename,O_RDONLY);
        printf("\n Server : %s is found!\n transferring the contents\n",filename);
        filesize=lseek(f1,0,2);
        printf("\nFile size is %d\n",filesize);
        lseek(f1,0,0);
        n=read(f1,bufl,filesize);
        bufl[n]='\0';
        fd2=open("fifo2",O_WRONLY);
        write(fd2,bufl,strlen(bufl));
        printf("\n SERVER:Transfer completed\n");
    exit(1);

    }
    unlink("fifo1");
    unlink("fifo2");
}