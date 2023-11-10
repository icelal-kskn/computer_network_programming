/*
       The producer/consumer problem 
 */
#include <iostream>                    // Section ONE
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define BUFFER "./buffer"
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
                              // definition in <sys/sem.h>
#else
union semun {                 // We define:
  int val;                    // value  for SETVAL
  struct semid_ds *buf;       // buffer for IPC_STAT, IPC_SET
  unsigned short int *array;  // array  for GETALL, SETALL
  struct seminfo *__buf;      // buffer for IPC_INFO
};
#endif
using namespace std;
int
main(int argc, char *argv[ ]) {
  FILE           *fptr;
  static struct sembuf acquire = {0, -1, SEM_UNDO},
                       release = {0,  1, SEM_UNDO};
  pid_t           c_pid;
  key_t           ipc_key;
  static unsigned short   start_val[2] = {1, 0};
  int             semid, producer = 0, i, n, p_sleep, c_sleep;
  union semun     arg;
  enum { READ, MADE };
  if (argc != 2) {
    cerr << argv[0] <<  " sleep_time" << endl;
    return 1;
  }
  ipc_key = ftok(".", 'S');
  if ((semid=semget(ipc_key, 2, IPC_CREAT|IPC_EXCL|0660)) != -1) {
    producer = 1;
    arg.array = start_val;
    if (semctl(semid, 0, SETALL, arg) == -1) {
      perror("semctl -- producer -- initialization");
      return 2;
    }
  } else if ((semid = semget(ipc_key, 2, 0)) == -1) {
    perror("semget -- consumer -- obtaining semaphore");
    return 3;
  }
  cout << (producer==1 ? "Producer" : "Consumer" ) << " starting" << endl;
                                       // Section TWO
  switch (producer) {
  case 1:                              // The PRODUCER 
    p_sleep = atoi(argv[1]);
    srand((unsigned) getpid());
    for (i = 0; i < 10; i++) {
      sleep(p_sleep);
      n = rand() % 99 + 1;
      cout << "A. The number [" << n << "] generated by producer" << endl;
      acquire.sem_num = READ;
      if (semop(semid, &acquire, 1) == -1) {
        perror("semop -- producer -- waiting for consumer to read number");
        return 4;
      }
      if ( (fptr = fopen(BUFFER, "w")) == NULL ){
        perror(BUFFER);
        return 5;
      }
      fprintf(fptr, "%d\n", n);
      fclose(fptr);
      release.sem_num = MADE;
      cout << "B. The number [" << n << "] deposited by producer" << endl;
      if (semop(semid, &release, 1) == -1) {
        perror("semop -- producer -- indicating new number has been made");
        return 6;
      }
    }
    sleep(5);
    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
      perror("semctl -- producer");
      return 7;
    }
    cout << "Semaphore removed" << endl;
    break;
  case 0:                              // Section THREE
    c_sleep = atoi(argv[1]);           // The CONSUMER
    c_pid = getpid();
    while (1) {
      sleep(c_sleep);
      acquire.sem_num = MADE;
      if (semop(semid, &acquire, 1) == -1) {
        perror("semop -- consumer -- waiting for new number to be made");
        return 8;
      }
      if ( (fptr = fopen(BUFFER, "r")) == NULL ){
        perror(BUFFER);
        return 9;
      }
      fptr = fopen(BUFFER, "r");
      fscanf(fptr, "%d", &n);
      fclose(fptr);
      release.sem_num = READ;
      if (semop(semid, &release, 1) == -1) {
        perror("semop -- consumer -- indicating number has been read");
        return 10;
      }
     cout << "C. The number [" << n << "] obtained  by consumer "
          <<  c_pid << endl;
    }
  }
  return 0;
}