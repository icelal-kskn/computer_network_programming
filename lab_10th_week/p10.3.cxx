/*
      Client - UNIX domain, connection-oriented
 */

#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>                    // UNIX protocol
using namespace std;

const char *NAME = "./my_sock";
const int  MAX = 1024;
int
main(  ) {
  int             orig_sock;           // Original socket descriptor
  static struct sockaddr_un
                  serv_adr;            // UNIX address of the server process
  static char     buf[MAX];            // Buffer for messages
                                       // Generate the SOCKET
  if ((orig_sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("generate error");
    return 1;
  }
  serv_adr.sun_family = AF_UNIX;
  strcpy(serv_adr.sun_path, NAME);
                                       // CONNECT
  if (connect( orig_sock, (struct sockaddr *) &serv_adr,
          sizeof(serv_adr.sun_family)+strlen(serv_adr.sun_path)) < 0) {
    perror("connect error");
    return 2;
  }
                                       // Prompt for expressions
  cout << "Enter an expression and press enter to process." << endl;
  for (int i = 0; i < 10; i++) {
    memset(buf, 0x0, MAX);
    cin.getline(buf, MAX-1, '\n');
    write(orig_sock, buf, sizeof(buf));
  }
  close(orig_sock);
  return 0;
}
