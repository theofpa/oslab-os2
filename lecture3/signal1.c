#include <signal.h>
#include <stdio.h>
void myfunc(int sig){
     printf("I got the signal %d\n", sig);
     signal(SIGINT, SIG_DFL);
}
int main(){
     signal(SIGINT, myfunc);
     while(1){
          printf("Hello World!\n");
          sleep(1);
     }
}

