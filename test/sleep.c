#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc, char * argv[]){
    // if(argc <= 1){
    //     printf("Please input an argument\n");
    //     exit(1);
    // }
    int n;
    scanf("%d", &n);
    printf("%d", n);
    sleep(n);
    exit(0);

}