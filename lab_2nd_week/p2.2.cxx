/*
    Using the stat system call
*/
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;
const int N_BITS = 3;
int
main(int argc, char *argv[ ]){
  unsigned int    mask = 0700;
  struct stat     buff;
  static char    *perm[] = {"---", "--x", "-w-", "-wx",
                            "r--", "r-x", "rw-", "rwx"};
  if (argc > 1) {
    if ((stat(argv[1], &buff) != -1)) {
      cout << "Permissions for " << argv[1] << " ";
      for (int i=3; i; --i) {
        cout << perm[(buff.st_mode & mask) >> (i-1)*N_BITS];
        mask >>= N_BITS;
      }
      cout << endl;
    } else {
      perror(argv[1]);
      return 1;
    }
  } else {
    cerr <<  "Usage: " << argv[0] << " file_name\n";
    return 2;
  }
  return 0;
}
