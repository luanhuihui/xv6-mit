#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

#define MAXSIZE 36
#define ZERO 0
#define ONE 1

void prime(int pipe_read, int pipe_write){
    char buf[MAXSIZE];
    int val = 0;
    
    read(pipe_read, buf, MAXSIZE);

    for (int i = 0; i < MAXSIZE; i++)
    {
        if(buf[i] == ONE){
            val = i;
            break;
        }
    }

    if(val == 0){
        exit(0);
    }

    printf("prime %d\n", val);
    buf[val] = ZERO;

    for (int  i = 0; i < MAXSIZE; i++)
    {
        if(i % val == 0){
            buf[i] = ZERO;
        }
    }   

    int pid = fork();

    if(pid > 0){
        write(pipe_write, buf, MAXSIZE);
        
    }
    
    if(pid == 0){
        prime(pipe_read, pipe_write);
        
    }
    
}
int main(){
    int fd[2];
    pipe(fd);
     
    char buf[MAXSIZE];
    buf[0] = ZERO;
    buf[1] = ZERO;

    for (int i = 2; i < MAXSIZE; i++)
    {
        buf[i] = ONE;
    }

    int pid = fork();

    if(pid > 0){
        write(fd[1], buf, MAXSIZE);
        wait(0);
    }

    if(pid == 0){
        prime(fd[0], fd[1]);
        wait(0);
    }
    
    exit(0);
}