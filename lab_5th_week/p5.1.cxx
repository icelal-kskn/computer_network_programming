/* Using a pipe to send data from a parent to a child process
 */
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <string.h>
using namespace std;
int
main(int argc, char *argv[ ]) {
  int            f_des[2];
  static char    message[BUFSIZ];
  if (argc != 2) {
    cerr << "Usage: " << *argv << " message\n";
    return 1;
  }
  if (pipe(f_des) == -1) {             // generate the pipe
    perror("Pipe");     return 2;
  }
  switch (fork( )) {
  case -1:
    perror("Fork");     return 3;
  case 0:                              // In the child
    close(f_des[1]);
    if (read(f_des[0], message, BUFSIZ) != -1) {
      cout << "Message received by child: [" << message
           << "]" << endl;
      cout.flush();
    } else {
      perror("Read");    return 4;
   }
    break;
  default:                             // In the Parent
    close(f_des[0]);
    if (write(f_des[1], argv[1], strlen(argv[1])) != -1) {
      cout << "Message sent by parent   : [" <<
           argv[1] << "]" << endl;
      cout.flush();
    } else {
      perror("Write");   return 5;
    }
  }
  return 0;
}

