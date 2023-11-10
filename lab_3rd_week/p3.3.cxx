/*
     Running the cat utility via an exec system call
 */
#include <iostream>
#include <cstdio>
#include <unistd.h>
using namespace std;
int
main(int argc, char *argv[ ]){
  if (argc > 1) {
    execlp("/bin/cat", "cat", argv[1], (char *) NULL);
    perror("exec failure ");
    return 1;
  }
  cerr <<  "Usage: " << *argv << " text_file" << endl;
  return 2;
}
