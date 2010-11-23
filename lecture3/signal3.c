#include <stdio.h>
#include <signal.h>
main()
{
     int pid1, pid2;
     if ((pid1 = fork()) == -1){
          perror("fork");
          exit(1);
     }
     if (pid1 == 0)           /* πρώτη διεργασία-παιδί */
       while (1){
             printf("First child-process\n");
             sleep(1);
       }
  if ((pid2 = fork()) == -1){
       perror("fork");
       exit(1);
  }
  if (pid2 == 0)          /* δεύτερη διεργασία-παιδί */
       while (1){
             printf("Second child-process\n");
             sleep(l);
       }
  sleep(2);
                         /* αναστολή 1ης διεργασίας */
  kill(pid1,  SIGSTOP);
  sleep(2);
                         /* επανέναρξη 1ης διεργασίας */
  kill(pid1,  SIGCONT);
  sleep(2);
                         /* τερματισμός 1ης διεργασίας */
  kill(pid1,  SIGTERM);
                         /* τερματισμός 2ης διεργασίας */
  kill(pid2,  SIGTERM);
}

