/* Using the signal system call to ignore a hangup signal
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
const char  *file_out = "nohup.out";
int
main(int argc, char *argv[]){
  int       new_stdout;
  if (argc < 2) {
    cerr << "Usage: " << *argv << " command [arguments]" << endl;
    return 1;
  }
  if (isatty( 1 )) {
    cerr <<  "Sending output to " << file_out << endl;
    close( 1 );
    if ((new_stdout = open(file_out, O_WRONLY | O_CREAT |
                           O_APPEND, 0644)) == -1)        {
      perror(file_out);
      return 2;
    }
  }
  if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
    perror("SIGHUP");
    return 3;
  }
  ++argv;
  execvp(*argv, argv);
  perror(*argv);                       // Should not get here unless
  return 4;                            // the exec call fails.
}
