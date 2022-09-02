#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc ,char *argv[]){
    if(argc<3){
        printf("invalid no of argments");
        printf("\n");
        exit(0);
    }
    if(set_priority(atoi(argv[1]),atoi(argv[2]))<0){
        printf("Invalid arguments");
        printf("\n");
    }
    exit(0);
}