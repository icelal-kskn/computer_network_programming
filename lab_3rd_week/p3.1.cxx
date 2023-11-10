/*
    Generating a child process
 */
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int
main( ){
  if (fork(  ) == 0)
    cout << "In the CHILD process"  << endl;
  else
    cout << "In the PARENT process" << endl;
  return 0;
}
