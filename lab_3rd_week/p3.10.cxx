/*
   The child process
*/
#define _GNU_SOURCE
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using namespace std;
int
main(int argc, char *argv[ ]){
  pid_t     pid = getpid( );
  int       ret_value;
  srand((unsigned) pid);
  ret_value = int(rand( ) % 256);      // generate a return value
  sleep(rand( ) % 3);                  // sleep a bit
  if (atoi(*(argv + 1)) % 2) {         // assuming argv[1] exists!
    cout << "Child " << pid << " is terminating with signal 0009" << endl;
    kill(pid, 9);                      // commit hara-kiri
  } else {
    cout << "Child " << pid << " is terminating with   exit("
         << setw(4) << setfill('0') << setiosflags(ios::uppercase)
         << hex  << ret_value << ")" << endl;
    exit(ret_value);
  }
}
