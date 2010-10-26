#include <stdio.h>
main() {
    int ret;
    printf("Creating new process!!!\n");
    ret=fork();
    if (ret == 0) {
        printf("CH: I am the child\n");
        printf("CH: I have PID=%d.\n", getpid());
        printf("CH: My PPID=%d!\n", getppid());
    }
    else {
        printf("PA: I am the parent\n");
        printf("PA: I have PID = %d\n", getpid());
        printf("PA: I have a PPID=%d, too!\n", getppid());
    }
    printf("Bye from %d ... \n", getpid());
}
