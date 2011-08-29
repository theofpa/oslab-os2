#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *line = "This is an IPC message, with pipe";
main(){
  int pid, fd[2], n;
  char message[100];
  /* Create a pipe */
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(1);
  }
  /* Fork a child */
  pid = fork();
  if ( pid == -1) {
    perror("fork");
    exit(2);
  }
  if (pid == 0){ /* Child process is the writer */
    /* Close the reading side */
    close(fd[0]);
    /* Write the line to pipe */
    write(fd[1], line, strlen(line)+1);
    /* At the end, close the writing side */
    close(fd[1]);
  }else{ /* Parent process is the reader */
    /* Close the writing side */
    close(fd[1]);
    /* Read from the pipe */
    n = read(fd[0], message, sizeof(message));
    /* write the message to stdout */
    write(1, message, n);
    /* At the end, close the reading side */
    close(fd[0]);
  }
}

