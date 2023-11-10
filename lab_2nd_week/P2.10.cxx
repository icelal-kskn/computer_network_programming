/*
    Determining Process ID by reading the contents of
    the symbolic link  /proc/self
*/
#define _GNU_SOURCE
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
const int size = 20;
int
main( ){
  pid_t proc_PID, get_PID;
  char buffer[size];
  get_PID = getpid( );
  readlink("/proc/self", buffer, size);
  proc_PID = atoi(buffer);
  cout << "getpid     : " << get_PID  << endl;
  cout << "/proc/self : " << proc_PID << endl;
  return 0;
}
