#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
int main() {
  int fd;
  char buffer[100];
  unlink("FIFO");
  if (mkfifo("FIFO", 0755) == -1){
    fprintf(stderr,"Receiver: Coudn't create fifo.\n");
    exit(2);
  }
  if ((fd = open("FIFO", O_RDWR)) == -1){
    fprintf(stderr, "Receiver: fifo open failed.\n");
    exit(1);
  }
  while(1){
    if (read(fd, buffer, 100) == -1){
      fprintf(stderr,"Receiver: fifo reading failed.\n");
      exit(2);
    }
    printf("Received message: %s\n", buffer);
    if (!strcmp(buffer,"exit")) exit(0);
  }
return 0;
}

