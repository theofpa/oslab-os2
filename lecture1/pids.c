#include <stdio.h>
#include <stdlib.h>
main(){
      printf("I am the process with PID=%d\n", getpid());
      printf("and my parent PID=%d\n", getppid());
      exit(27);
}
