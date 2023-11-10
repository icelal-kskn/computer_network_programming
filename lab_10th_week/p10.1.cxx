/*
    Creating a socket pair
 */
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
using namespace std;
const int BUF_SZ = 10;
int
main( ) {
  int          sock[2],                // The socket pair
               i;
  static char  buf[BUF_SZ];            // Temporary buffer for message
  if (socketpair(PF_LOCAL, SOCK_DGRAM, 0, sock) < 0) {
    perror("Generation error");
    return 1;
  }
  switch (fork( )) {
  case -1:
    perror("Bad fork");
    return 2;
  case 0:                              // The child process
    close(sock[1]);
    for (i = 0; i < 10; i += 2) {
      sleep(1);
      sprintf(buf, "c: %d", i);
      write(sock[0], buf, sizeof(buf));
      read( sock[0], buf, BUF_SZ);
      cout << "c-> " << buf << endl;   // Message from parent
    }
    close(sock[0]);
    break;
  default:                             // The parent process
    close(sock[0]);
    for (i = 1; i < 10; i += 2) {
      sleep(1);
      read( sock[1], buf, BUF_SZ);
      cout << "p-> " <<  buf << endl;  // Message from child
      sprintf(buf, "p: %d", i);
      write(sock[1], buf, sizeof(buf));
    }
    close(sock[1]);
  }
  return 0;
}
