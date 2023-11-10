/*
    First example of a fork system call (no error check)
 */
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int
main( ) {
  cout << "Hello\n";
  fork( );
  cout << "bye\n";
  return 0;
}
