#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
int main(int argc, char * argv[]){
    if(argc <= 1){
        fprintf(2, "Please input an argument\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    sleep(n);
    exit(0);

}