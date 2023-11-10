/* Creating sets of semaphores */
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
using namespace std;
int
main( ){
  int      sem1, sem2, sem3;
  key_t    ipc_key;
  ipc_key = ftok(".", 'S');
  if ((sem1 = semget(ipc_key, 3, IPC_CREAT | 0660)) == -1) {
    perror("semget: IPC_CREAT | 0660");
  }
  cout << "sem1 identifier " <<  sem1 << endl;
  if ((sem2 = semget(ipc_key, 3, IPC_CREAT|IPC_EXCL|0660)) == -1) {
    perror("semget: IPC_CREAT | IPC_EXCL | 0660");
  }
  cout << "sem2 identifier " <<  sem2 << endl;
  if ((sem3 = semget(IPC_PRIVATE, 3, 0600)) == -1) {
    perror("semget: IPC_PRIVATE");
  }
  cout << "sem3 identifier " <<  sem3 << endl;
  return 0;
}
