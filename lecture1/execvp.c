#include <stdio.h>
main(){
     int pid;
     char *arg[3];
     if (!fork()) {          /* make a child process */
          printf("child process:\n");
       arg[0] = "ls"
       arg[1] = "-l"
       arg[2] = NULL;
       execvp("ls", arg);
       return(5);
  }
  wait(&pid);             /* the parent process */
  printf("I am the parent and\n");
  printf("my child terminated with code %d\n",pid>>8);
}
