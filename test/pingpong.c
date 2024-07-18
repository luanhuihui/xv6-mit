#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdio.h>
#include <sys/wait.h>
#include<errno.h>
#define N 16
int main(int argc, char * argv[]){
    int fd[2];
    pipe(fd);//先创建管道
    char buf[5];
    int pid = fork();
    if(pid == 0){
        read(fd[0], buf, sizeof buf);
        close(fd[0]);
        printf("%d: received %s\n", pid, buf);
        write(fd[1], "pong", 5);

        close(fd[1]);
        exit(0);
    }
    else if(pid > 0){
        write(fd[1], "ping", 4);
        close(fd[1]);

        read(fd[0], buf, sizeof buf);
        close(fd[0]);
        printf("%d: received %s\n", pid, buf);
        exit(0);
    }
    else {
        exit(1);
    }
    return 0;

}