#include <stdio.h>
main()
{
  int pid, eid1, eid2;
  pid = fork();          /* create child process*/
  if (pid == -1){        /* create check */
      perror ("fork");   /* fork error check*/
      exit(10);
  }
  if (pid != 0){         /* Parent */
   printf("I am parent process with ID=%d\n", getpid());
   printf("My job is a ps list\n");
   eid1 = execl("/bin/ps", "ps", NULL);
  }else{                /* Clild */
   printf("Child:PID=%d - PPID=%d\n",getpid(),getppid());
   if ((eid2 = execl("/bin/ps", "ps", "-f",NULL)) == -1){
        exit(30);
   }
  }
}
