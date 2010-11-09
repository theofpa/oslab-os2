#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define NUM_LOOPS 20
union semun{
   int val;
   struct semid_ds *buf;
   ushort *array;
};
int main(){
   int sid;
   union semun sem_val;
   struct sembuf sem_op;
   int child_pid, i, rc;
   struct timespec delay;
   /* ���������� ���� ��������� (��������) ��������� */
sid = semget(IPC_PRIVATE, 1, 0600);
if (sid == -1) {
  perror("main: semget");
  exit(1);
}
printf("semaphore set created, id = %d\n", sid);
/* ������������ ��� ������ (��� ���������) ��������� */
sem_val.val = 0;
rc = semctl(sid, 0, SETVAL, sem_val);
/* ���������� ���������� ���������� */
child_pid = fork();
switch (child_pid){
  case -1:
    perror("fork");
    exit(1);
  case 0:         /* ��������� ����� */
    for (i=0; i<NUM_LOOPS; i++){
    /* �������� ��� ��������� */
      sem_op.sem_num = 0;
      sem_op.sem_op = -1;
      sem_op.sem_flg = 0;
      semop(sid, &sem_op, 1);
      printf("consumer: %d\n", i);
      fflush(stdout);
    }
    break;
  default:        /* ������ ��������� */
    for (i=0; i<NUM_LOOPS; i++){
      printf("producer: %d\n", i);
      fflush(stdout);
      /* ����������� ��� ��������� */
      sem_op.sem_num = 0;
      sem_op.sem_op = 1;
      sem_op.sem_flg = 0;
      semop(sid, &sem_op, 1);
      /* ����� ����������� ��� �� �������� ��
         ���������� � ��������� ��������� */
      if (rand() > 3*(RAND_MAX/4)) {
         delay.tv_sec = 0;
         delay.tv_nsec = 10;
         nanosleep(&delay, NULL);
      }
    }
    break;
  }
  return 0;
}

