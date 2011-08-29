#include <stdio.h>
main(){
  int fd[2], n;
  char message[100];
  /* create a pipe */
  pipe(fd);
  /* write "This is a pipe message" to pipe */
  write(fd[1], "This is a pipe message", 22);
  /* read from pipe */
  n = read(fd[0], message, 100);
  /* write the message to stdout */
  write(1, message, n);
}
