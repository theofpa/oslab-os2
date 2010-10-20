#include <stdio.h>
#include <stdlib.h>
main(){
  int zombie;
  printf("Creating zombie process!!!\n");
  zombie = fork();
  if (zombie != 0){ /* Parent process */
      printf("I am the Parent and I am busy...\n");
      while (1);     /* Always true */
  }else {
      printf("I am the child and ... the zombie...\n");
      exit(1);
  }
}
