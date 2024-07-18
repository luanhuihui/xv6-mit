#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXSIZE 16

int main(int argc, char * argv[]){
    sleep(10);
    //read standard input by utilizing buffer
    char buf[MAXSIZE];
    read(0,buf,MAXSIZE);

    //reorganize the command line
    char *xargv[MAXSIZE];
    int xargc = 0;
    for (int i = 1; i < MAXSIZE; i++)
    {
        xargv[xargc] = argv[i];
        xargc++;
    }

    //exec the command line
    char *p = buf;
    for (int i = 0; i < xargc; i++)
    {
        if(buf[i] == '\n'){
            int fd = fork();
            if(fd == 0){
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0;
                xargc++;
                
                execv(xargv[0], xargv);
                exit(1);
                //exec正常执行后不会执行后续代码，因此通过exit(1)来表明子进程执行失败
            }
            else{
                p = &buf[i + 1];
                wait(0);
            }
        }
    }

    exit(0);
}