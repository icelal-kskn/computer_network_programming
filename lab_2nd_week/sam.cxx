/*
  Sam's environment program
*/
#define _GNU_SOURCE
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int
main( ){
  int numb;
  char *p;
  putenv("DEMO=abcdefghijklmnop");
  p = getenv("DEMO");
  cout << "1. Parent environment has " << p << endl;

  if ( fork( ) == 0 ){                // In the CHILD now
    *(p + 9) = 'X';                   // Change ref location
    p = getenv("DEMO");
    cout << "2. Child environment has  " << p << endl;
    cout << "3. Exiting child." << endl;
    return 0;
  }                                   // In the PARENT now
  sleep( 10 );                        // Make sure child is done
  cout << "4. Back in parent." << endl;
  p = getenv("DEMO");
  cout << "5. Parent environment has " << p << endl;
  return 0;
}
