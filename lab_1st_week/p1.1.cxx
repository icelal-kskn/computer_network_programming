/*
         Display Hello World 3 times
 */
#include <iostream>
#include <unistd.h>                      // needed for write
#include <cstring>                       // needed for strcpy
#include <cstdlib>                       // needed for exit
using namespace std;
char           *cptr = "Hello World\n";  // static by placement
char            buffer1[25];
int main( ){
  void            showit(char *);        // function prototype
  int             i = 0;                 // automatic variable
  strcpy(buffer1, "A demonstration\n");  // library function
  write(1, buffer1, strlen(buffer1)+1);  // system call
  for ( ; i < 3; ++i)
    showit(cptr);                        // function call
  return 0;
}
void showit( char *p ){
  char           *buffer2;
  buffer2= new char[ strlen(p)+1 ]; 
  strcpy(buffer2, p);                    // copy the string
  cout << buffer2;                       // display string
  delete [] buffer2;                     // release location
}
