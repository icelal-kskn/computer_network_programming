/*
     A very funny program ...
 */
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
int
main(  ) {
  fork( );   cout << "hee " << endl;
  fork( );   cout << "ha "  << endl;
  fork( );   cout << "ho "  << endl;
  return 0;
}
