#include  <stdio.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/sem.h>
int main(void){
    key_t skey;
    int sid;
    union semun{
         int val;
         struct semid_ds *buff;
         unsigned short *array;
    }arg;
    skey = 1234;
    /* ���������� ������� ���������, �� 1 �������� */
  if ((sid = semget(skey, 1, 0666 | IPC_CREAT)) == -1){
      perror("semget");    /* ����������� ���������� */
      exit(1);
  }
  printf("Successful creation of semaphore set!\n");
  printf("Semaphore ID=%d on KEY=%d\n", sid, skey);
  /* ������������ ��� 1�� ��������� (#0) �� ���� 1 */
  arg.val = 1;
  if (semctl(sid, 0, SETVAL, arg) == -1){
      perror("semctl");   /* ����������� ���������� */
      exit(1);
  }
  printf("New Semaphore VALUE=%d\n", arg.val);
  return 0;
}
