#include  <signal.h>
#include  <stdio.h>
#include  <unistd.h>
#include  <sys/types.h>
static int alarm_fired = 0;
void dingdong(int sig){
     alarm_fired = 1;
}
int main(){
     pid_t pid;
     pid = fork();
     if (pid < 0){
           perror("fork");
           exit(1);
     }else{
           if (pid > 0){
                signal(SIGALRM, dingdong);
                pause();
                if (alarm_fired)
                     printf("Alarm\n");
                printf("current time is: \n");
                system("date");
                exit(0);
           }else{
                sleep(1);
                kill(getppid(), SIGALRM);
                exit(0);
           }
     }
}

