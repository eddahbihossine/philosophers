#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    // int hi = getpid();
    int pid  = fork();
    printf(" process id %d\n",getpid());

    printf("Hello from process\n");
    if(pid == - 1)
        return -1 ;
    if(pid)
        wait();
    

    return 0;
}
