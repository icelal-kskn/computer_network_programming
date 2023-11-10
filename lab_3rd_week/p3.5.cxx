/*
     Generating our own argv type list for execvp
 */
#include <iostream>
#include <cstdio>
#include <unistd.h>
using namespace std;
int
main( ){
  char    *new_argv[ ] = {"cat",
                          "test.txt",
                          (char *) 0
                         };
  execvp("/bin/cat", new_argv );
  perror("exec failure ");
  return 1;
}
