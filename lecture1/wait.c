#include <stdio.h>
main(){
     int status;
     if (!fork()) {          /* make a child process */
          printf("I am the child. That's all.\n");
          return(5);
     }
     wait(&status);             /* the parent process */
     printf("I am the parent and\n");
     printf("my child terminated with code %d\n",status>>8);
}

