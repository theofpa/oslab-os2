#include <stdio.h>
#include <stdlib.h>
main(){
  int fd[2], pid;
  char message[100];
  if (pipe(fd) == -1){
    perror("pipe");
    exit(1);
  }
  /* Create a pipe */
  if ((pid = fork()) == -1){ /* Fork a child */
    perror("fork");
    exit(2);
  }
  if (pid == 0){
    /* Child process is the reader */
    /* Close the writing side */
    close(fd[1]);
    /* stdin becomes fd[0] */
    dup2(fd[0],0);
    /* now, close the fd[0] */
    close(fd[0]);
    printf("I am the child…\n");
    scanf("%s",message);
    printf("From parent: %s\n", message);
    scanf("%s", message);
    printf("From parent: %s\n", message);
    scanf("%s", message);
    printf("From parent: %s\n", message);
    exit(0);
  }else{
    /* Parent process is the writer */
    /* Close the reading side */
    close(fd[0]);
    /* stdout becomes fd[1] */
    dup2(fd[1],1);
    /* now, close the fd[1] */
    close(fd[1]);
    printf("Hello my child\n");
  }
}

