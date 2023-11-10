/*
     Overlaying a child process via an exec
 */
#include <iostream>
#include <sstream>
#include <cstdio>
#include <unistd.h>
using namespace std;
int
main( ){
  char  *mesg[ ] = {"Fie", "Foh", "Fum"};
  int   display_msg(char *);
  for (int i=0; i < 3; ++i)
     display_msg(mesg[i]);
  return 0;
}
int
display_msg(char *m){
  ostringstream oss(ostringstream::out);
  switch (fork( )) {
  case 0:
    sleep(1);
    execlp("/bin/echo", "echo", m, (char *) NULL);
    oss << m << " exec failure";       // build error msg string
    perror(oss.str().c_str());
    return 1;
  case -1:
    perror("Fork failure");
    return 2;
  default:
    return 0;
  }
}
