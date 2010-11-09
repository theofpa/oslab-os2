#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#define NUM_PROCS 5          /* ������ ���������� */
#define FILE_NAME "test.dat" /* ������ ����������� */
#define DELAY 300000         /* ����� ����������� */
#define SKEY 1234
union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
} arg;
void update_file(int sem_set_id, char* file, int num){
  struct sembuf sem_op;
  FILE *fp;
  sem_op.sem_num = 0;
  sem_op.sem_op = -1; /* �������� ��� ��������� */
  sem_op.sem_flg = 0;
  semop(sem_set_id, &sem_op, 1);
   /* ������������ ���������� ��� ������ ��� ������� ����
   ������� � ���� */
  fp = fopen(file, "w");
  if (fp != NULL){
     fprintf(fp, "%d\n", num);
     printf("%d\n", num);
     fclose(fp);
  }
  sem_op.sem_num = 0;
  sem_op.sem_op = 1;      /* ����������� ��� ��������� */
  sem_op.sem_flg = 0;
  semop(sem_set_id, &sem_op, 1);
}
void do_child_loop(int sem_set_id, char* file){
     pid_t pid = getpid();
     int i, j;
     for (i=0; i<3; i++) {
          update_file(sem_set_id, file, pid);
          for (j=0; j<DELAY; j++)    /* ����������� */
              ;
     }
}
int main(){
  int sid;
  union semun sem_val;
  int child_pid, i, rc;
  /* ���������� ��������� ��������� �� ������ 1234 ���
       ���������� ���� ��� ��� ������ */
  sid = semget(SKEY, 1, IPC_CREAT | 0600);
  if (sid == -1){
     perror("main: semget");
     exit(1);
  }
  /* ������������ ��� ��������� */
  sem_val.val = 1;
  rc = semctl(sid, 0, SETVAL, sem_val);
  if (rc == -1){
    perror("main: semctl");
    exit(1);
  }
  /* ���������� ���������� ���������� */
  for (i=0; i<NUM_PROCS; i++) {
    child_pid = fork();
    switch(child_pid) {
      case -1:
         perror("fork");
         exit(1);
      case 0:       /* ��������� ����� */
         do_child_loop(sid, FILE_NAME);
         exit(0);
      default:      /* ������ ��������� */
         break;
    }
  }
  /* ������� ��� ���������� ���� ��� ���������� */
  for (i=0; i<NUM_PROCS; i++) {
    int child_status;
    wait(&child_status);
  }
  printf("main: all done\n");
  fflush(stdout);
}

