#include "user.h"
char *combine(char *a, char *b, char *c)
{
    int i;
    for (i = 0; i < strlen(a); i++)
    {
        c[i] = a[i];//copying a to c
    }
    int j;
    for (j = 0; j < strlen(b); j++)
    {
        c[j + i] = b[j];//copying b to c
    }
    c[j+i]='\0';
    return c;
}

void main(int argc ,char *args[]){
    char **arr=(char **)malloc((argc-1)*sizeof(char *));//  array of strings
    for(int i=0;i<argc-1;i++){//  copying args to arr
        arr[i]=(char *)malloc(100*sizeof(char));//  allocating memory for each string
        arr[i]=args[i+2];//  copying args to arr
    }
    arr[argc-2]='\0';
    trace(atoi(args[1]));//  calling strace
    exec(arr[0],arr);//  executing the command
    exit(0);
}