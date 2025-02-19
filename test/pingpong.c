#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdio.h>
#include <sys/wait.h>
#include<errno.h>
#define N 16
int main(int argc, char * argv[]){
    int p[2];
    pipe(p);
    char buf[5];
    int pid = fork();
    if(pid == 0){
        read(p[0], buf, sizeof buf);
        close(p[0]);
        printf("%d :received  %s\n", pid, buf);
        write(p[1], "pong", 5);
        close(p[1]);
        exit(0);
    }
    else if(pid > 0){
        write(p[1], "ping", 5);
        close(p[1]);
        wait(0);
        read(p[0], buf, sizeof buf);
        close(p[0]);
        printf("%d :received %s\n", pid, buf);
        exit(0);
    }
    else{
        exit(1);
    }
    return 0;
}