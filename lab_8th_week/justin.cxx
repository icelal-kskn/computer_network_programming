#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include "SSemaphore.h"
using namespace std;
char c = 0;                            // 'global' variable
int
main( ){
  SSemaphore S;                        // SSemaphore object
  S.Put(1);                            // Start it at 1
  switch(fork( )){
    case -1:
      perror("fork failure");
      return 1;
    case 0:                            // Child - lowercase
      srand(getpid( ));
      for (int i=0; i < 10; ++i){
        S.P( );                        // Obtain semaphore
          cout << char(c+'a'); cout.flush( );
          ++c;
        S.V( );                        // Release semaphore
        sleep(rand( ) % 3 + 1);
      }
      break;
    default:                           // Parent - uppercase
      srand(getpid( ));
      for (int i=0; i < 10; ++i){
        S.P( );                        // Obtain semaphore
          cout << char(c+'A'); cout.flush( );
          ++c;
        S.V( );                        // Release semaphore
        sleep(rand( ) % 3 + 1);
      }
      break;
  }
  wait(0);
  return 0;
}
