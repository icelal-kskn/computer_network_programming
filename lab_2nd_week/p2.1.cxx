/*
        Displaying process group ID information.
 */
#define _GNU_SOURCE
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int
main(  ){
  cout << "\n\nInitial process \t PID " << getpid()
       << "\t PPID "<< getppid()
       << "\t GID " << getpgid(0)
       << endl << getpgid(pid_t(getppid())) << endl;

  for (int i = 0; i < 3; ++i)
    if (fork( ) == 0)                  // Generate some processes
      cout << "New process      \t PID " << getpid()
           << "\t PPID "<< getppid()
           << "\t GID " << getpgid(0)
           << endl;
  return 0;
} 
