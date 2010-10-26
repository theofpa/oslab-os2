#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
char username[40];
void catch_alarm(int sig_num){
    printf("Operation timed out. Exiting...\n\n");
    exit(0);
}
int main(){
    signal(SIGALRM, catch_alarm);
    printf("Username: ");
    fflush(stdout);
    alarm(15);            /* start a 15 seconds alarm */
    scanf("%s",username);
                          /* remove the timer */
    alarm(0);
    printf("User name: '%s'\n", username);
    return 0;
}

