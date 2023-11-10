#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
int
main(int argc, char *argv[]){
  cerr << "argc = " <<  argc  << endl;
  cerr << "Processes running" << endl;
  system("ps -f");                     // issue a shell ps cmd

  if ( argc > 1 ) {                    // value passed?
    int limit = atoi(argv[1]);         // convert to #
    for(int i=limit; i ; --i){         // count
       cerr << i << endl;
       sleep( 1 );
    }
  } else {
    cerr << "Nothing to count" << endl;
    return 2;
  }
  return 0;
}
