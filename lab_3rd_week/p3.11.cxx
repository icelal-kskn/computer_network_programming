#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int
main(int argc, char *argv[] ){
  pid_t  pid[3], w;
  int    status;
  if ( argc < 4 ) {
    cerr << "Usage " << *argv << " value_1 value_2 value_3\n";
    return 1;
  }
  for (int i=1; i < 4; ++i)          // generate 3 child processes
    if ((pid[i-1] = fork( )) == 0)
      execl("./child", "child", argv[i], (char *) 0);
    else                               // assuming no failures here
      cout << "Forked child " << pid[i-1] << endl;
/*
     Wait for the children
*/
  for (int i=0;(w=waitpid(pid[i], &status,0)) && w != -1; ++i){
    cout << "Wait on PID " << dec << w << " returns ";
    if (WIFEXITED(status))                        // test with macro
      cout << " a value of  " << setw(4) << setfill('0') << hex
           << setiosflags(ios::uppercase) << WEXITSTATUS(status) << endl;
    else if (WIFSIGNALED(status))                 // test with macro
      cout << " a signal of " << setw(4) << setfill('0') << hex
           << setiosflags(ios::uppercase) << WTERMSIG(status) << endl;
    else
      cout << " unexpectedly!" << endl;
  }
  return 0;
}
