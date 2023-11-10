/*
     Server - UNIX domain, connection-oriented
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
void clean_up( int, const char *);     // Close socket and remove
int
main(  ) {
  socklen_t       clnt_len;            // Length of client address
  int             orig_sock,           // Original socket descriptor
                  new_sock;            // New socket descriptor from connect
  static struct sockaddr_un            // UNIX addresses to be used
                  clnt_adr,            // Client address
                  serv_adr;            // Server address
  static char     clnt_buf[MAX],       // Message from client
                  pipe_buf[MAX];       // output from bc command
  FILE *fin;                           // File for pipe I/O
                                       // Generate socket
  if ((orig_sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
    perror("generate error");
    return 1;
  }                                    // Assign address information
  serv_adr.sun_family = AF_UNIX;
  strcpy(serv_adr.sun_path, NAME);
  unlink(NAME);                        // Remove old copy if present
                                       // BIND the address
  if (bind( orig_sock, (struct sockaddr *) &serv_adr,
          sizeof(serv_adr.sun_family)+strlen(serv_adr.sun_path)) < 0) {
    perror("bind error");
    clean_up(orig_sock, NAME);
    return 2;
  }
  listen(orig_sock, 1);                // LISTEN for connections
  clnt_len = sizeof(clnt_adr);         // ACCEPT connection
  if ((new_sock = accept( orig_sock, (struct sockaddr *) &clnt_adr,
                          &clnt_len)) < 0) {
    perror("accept error");
    clean_up(orig_sock, NAME);
    return 3;
  }
                                       // Process 10 requests
  for (int i = 0; i < 10; i++) {
    memset(clnt_buf, 0x0, MAX);        // Clear client buffer
    read(new_sock, clnt_buf, sizeof(clnt_buf));
                                       // build command for bc
    memset(pipe_buf, 0x0, MAX);
    sprintf(pipe_buf, "echo \'%s\' | bc\n", clnt_buf);
    fin = popen( pipe_buf, "r" );
    memset(pipe_buf, 0x0, MAX);
    read(fileno(fin), pipe_buf, MAX);
    cout << clnt_buf << " = " << pipe_buf << endl;
  }
  close(new_sock);
  clean_up(orig_sock, NAME);
  return 0;
}
void
clean_up( int sd, const char *the_file ){
  close( sd );                         // Close socket
  unlink( the_file );                  // Remove it
}
