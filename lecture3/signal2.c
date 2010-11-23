#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void question(){
     printf("continue or quit?\n");
     sleep(5);
}
int main(){
     struct sigaction act;
     act.sa_handler = question;
     sigemptyset(&act.sa_mask);
     act.sa_flags=0;
     sigaction(SIGINT, &act, 0);
     while(1){
          printf("current time is:\n");
          system("date");
          sleep(1);
     }
}

