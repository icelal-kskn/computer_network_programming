#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int
main(int argc, char *argv[] ) {
  int w, status;
  if ( argc < 4 ) {
    cerr << "Usage: " << *argv << " value_1 value_2 value_3 "
         << endl;
    return 1;
  }
  for(int i=1; i <= 3; ++i)
    if ( fork( ) == 0 ) {
       int t = atoi(argv[i]);
       cout << "Child " << getpid( ) << " waiting to die in "
            << t << " seconds." << endl;
       alarm( t );
       pause( );
       cout << getpid( ) << " is done." << endl;
    }
  while (( w=wait(&status)) && w != -1)
    cout << "Wait on PID: " << dec <<  w << " returns status of  "
         << setw(4) << setfill('0') << hex
        << setiosflags(ios::uppercase) << status << endl;
  return 0;
}
