#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(void){
    key_t skey;
    int sid;
    /* Αρχικοποίηση δομής για δέσμευση στόχου */
	struct sembuf sb = { 0, /* αριθμός σημαφόρου */
						-1, /* τιμή για δέσμευση */
						 0}; /* συνήθης τιμή sflag */
	skey = 1234;
    /* Αρπαγή του συνόλου σημαφόρων του semSetUp.c */
	if ((sid = semget(skey, 1, 0)) == -1){
		perror("semget"); /* Αποτυχημένη προσπάθεια */
		exit(1);
	}
	printf("\n\nGrap hold of semSetUp.c semaphore ");
	printf("with SID=%d on KEY=%d\n",sid,skey);
	printf("\n< < Press ENTER to block the target > >");
	getchar();
	printf("Trying to block the target...\n");
	if (semop(sid, &sb, 1) == -1){
		perror("semop"); /* Αποτυχημένη προσπάθεια */
		exit(1);
	}
	printf("Blocked!!!\n\n\n");
	printf("< < < Press ENTER to unblock > > > ");
	getchar();
	sb.sem_op = 1;
	/* τιμή για την αποδέσμευση */
	if (semop(sid, &sb, 1) == -1){
		perror("semop"); /* Αποτυχημένη προσπάθεια */
		exit(1);
	}
	printf("Unblocked!\n\n");
	return 0;
}