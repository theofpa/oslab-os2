#include   <sys/types.h>
#include   <sys/ipc.h>
#include   <sys/sem.h>
#include   <errno.h>
#include   <stdio.h>
int sid;
key_t skey;
int ns;
int sflag;
int main(){
         skey = 1234;
         ns = 1;
         sflag = 0666 | IPC_CREAT;
         if ((sid = semget(skey, ns, sflag)) == -1){
                  perror("semget");
                  exit(1);
         }
         printf("Semget succeed! SID=%d\n", sid);
         exit(0);
}

