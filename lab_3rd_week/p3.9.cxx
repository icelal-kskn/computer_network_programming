/*
    A parent process that waits for a child to finish
 */
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int
main(int argc, char *argv[] ){
  pid_t  pid, w;
  int    status;
  if ( argc < 4 ) {
    cerr << "Usage " << *argv << " value_1 value_2 value_3\n";
    return 1;
  }
  for (int i = 1; i < 4; ++i)          // generate 3 child processes
    if ((pid = fork( )) == 0)
      execl("./child", "child", argv[i], (char *) 0);
    else                               // assuming no failures here
      cout << "Forked child " << pid << endl;
/*
     Wait for the children
 */
  while ((w=wait(&status)) && w != -1)
      cout << "Wait on PID: " << dec <<  w << "  returns status of  "
           << setw(4) << setfill('0') << hex
           << setiosflags(ios::uppercase) << status << endl;
  return 0;
}

