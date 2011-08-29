#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
main(){
  int fd, n;
  char buff[100], msg[]="Text for FIFO";
  unlink("FIFO");
  /* remove, if exist */
  if (mkfifo("FIFO", 0764) == -1){
    perror("mkfifo");
    exit(1);
  }
  if ((fd=open("FIFO", O_RDWR)) == -1){
    perror("open");
    exit(2);
  }
  n=write(fd,msg,strlen(msg));
  if (read(fd, buff, n)==-1)
    fprintf(stderr,"Can't read from Fifo.\n");
  else
    printf("Read from FIFO: %s\n", buff);
}

