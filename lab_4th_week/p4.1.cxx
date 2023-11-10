/*
     Using a lock file as a process communication technique.
*/
#include <iostream>
#include <unistd.h>

#include "lock_file.h"
using namespace std;
int
main(int argc, char *argv[ ]){
  int  numb_tries, i = 5;
  int  sleep_time;
  char *fname;
  /*
        Assign values from the command line
  */
  set_defaults(argc, argv, &numb_tries, &sleep_time, &fname);
  /*
        Attempt to obtain lock file
  */
  if (acquire(numb_tries, sleep_time, fname)) {
    while (i--) {                      // simulate resource use
      cout << getpid( )<< " " << i << endl;
      sleep(sleep_time);
    }
    release(fname);                    // remove lock file
    return 0;
  } else
    cerr << getpid( ) << " unable to obtain lock file after "
         << numb_tries << " tries." << endl;
  return 1;
}
