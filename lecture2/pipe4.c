#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
main() {
  int fd[2], pid;
  char *argv[3];
  if (pipe(fd) == -1){
    perror("pipe");
    exit(1);
  }
  /* Create a pipe */
  if ((pid = fork()) == -1){
    /* on error */
    perror("fork");
    exit(2);
  }
  /* Fork a child */
  if (pid == 0){
    /* Child process is the reader */
    close(fd[1]); /* Close the writing side */
    dup2(fd[0],0); /* stdin becomes fd[0] */
    close(fd[0]); /* now, close the fd[0] */
    /* the exec command */
    execlp("wc", "wc" , NULL);
    perror("execlp");
  }else{
    /* Parent process is the writer */
    close(fd[0]); /* Close the reading side */
    dup2(fd[1],1); /* stdout becomes fd[1] */
    close(fd[1]); /* now, close the fd[1] */
    /* the exec command */
    argv[0] = "ls";
    argv[1] = "-l";
    argv[2] = NULL;
    execvp("ls", argv);
    perror("execvp");
  }
}
