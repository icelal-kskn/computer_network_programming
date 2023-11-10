#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
const int size = 512;
int
main( ){

  ostringstream oss (ostringstream::out);
  oss  << "/proc/" << getpid( ) << "/cmdline";
  cout << "Reading from file: " << oss.str() << endl;

  static char buffer[size];
  ifstream i_file;
  i_file.open(oss.str().c_str());      // open to read
  i_file.getline(buffer, size, '\n');

  char *p = &buffer[0];                // ref 1st char of seq
  do {
    cout << "[" << p << "]" << endl;
    p += strlen(p)+1;                  // move to next location
  } while ( *p );                      // still ref a valid char
  return 0;
}
