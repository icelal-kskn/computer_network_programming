/*
     Using execvp to execute the contents of argv
 */
#include <iostream>
#include <cstdio>
#include <unistd.h>
using namespace std;
int
main(int argc, char *argv[ ]) {
  if ( argc > 1 ) {
    execvp(argv[1], &argv[1]);
    perror("exec failure");
    return 1;
  }
  cerr << "Usage: " << *argv << " exe [arg(s)]" << endl;
  return 2;
}
