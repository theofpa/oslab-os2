#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
  int fd, i, n;
  char buffer[100];
  if (argc < 2){
    fprintf(stderr, "Usage: %s message ...\n", argv[0]);
    exit(1);
  }
  if ((fd = open("FIFO", O_RDWR | O_NONBLOCK)) == -1){
    fprintf(stderr, "Sender: fifo open failed.\n");
    exit(3);
  }
  for (i = 1; i < argc; i++){
    strcpy(buffer, argv[i]);
    if ((n = write(fd, buffer, 100)) == -1){
      fprintf(stderr, "Sender: Write to fifo failed.\n");
      exit(4);
    }
  }
  return 0;
}

