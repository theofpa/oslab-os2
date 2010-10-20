#include <stdio.h>
main() {
        int ret;
        printf("Creating new process!!!\n");

        ret=fork();
        if (ret == 0) {
                printf("CH: I am the child\n");
                printf("CH: and i have PID=%d.\n", getpid());
                printf("CH: My PPID=%d !!!\n", getppid());
        }
        else {
                printf("PA: I am the parent\n");
                printf("PA: and i have PID = %d\n", getpid());
                printf("PA: but i have a PPID=%d, too !!! \n", getppid());
        }
        printf("Bye from %d ... \n", getpid());
}
