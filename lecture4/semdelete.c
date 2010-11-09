#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(void){
    key_t skey;
    int sid;
    union semun{
         int val;
         struct semid_ds *buff;
         unsigned short *array;
    }arg;
    skey = 1234;
    /* Αρπαγή του συνόλου σημαφόρων του semSetUp.c */
  if ((sid = semget(skey, 1, 0)) == -1){
      perror("semget"); /* Αποτυχημένη προσπάθεια */
      exit(1);
  }
  printf("Semaphore ID=%d on KEY=%d\n", sid, skey);
  /* Διαγραφή του συνόλου των σημαφόρων */
  if (semctl(sid, 0, IPC_RMID, arg) == -1){
      perror("semctl"); /* Αποτυχημένη προσπάθεια */
      exit(1);
  }
  printf("Successful semaphore deletion!\n");
  return 0;
}
