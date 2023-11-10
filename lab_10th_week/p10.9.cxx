/*
       CLIENT - UNIX domain - connectionless
*/
#include "local_sock.h"

void clean_up(int, const char *);     // Close socket and remove
int
main( ) {
  int             orig_sock;           // Original socket descriptor
  static struct sockaddr_un            // UNIX addresses to be used
                  clnt_adr,            // Client address
                  serv_adr;            // Server address
  static char     clnt_buf[BUFSIZ],    // Message from client
                  pipe_buf[BUFSIZ],    // Output from fortune command
                  clnt_file[]="XXXXXX";// Temporary file name
  FILE             *fin;               // File for pipe I/O
                                       // Assign SERVER address information
  serv_adr.sun_family = AF_UNIX;
  strcpy(serv_adr.sun_path, SERVER_FILE);
  if ((orig_sock = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
    perror("generate error");
    return 1;
  }
  mkstemp(clnt_file);
  clnt_adr.sun_family = AF_UNIX;       // Assign CLIENT address information
  strcpy( clnt_adr.sun_path, clnt_file );
  unlink( clnt_file );                 // Remove
                                       // BIND the address
  if (bind(orig_sock, (struct sockaddr *) &clnt_adr,
          sizeof(clnt_adr.sun_family)+strlen(clnt_adr.sun_path)) < 0) {
    perror("bind error");
    return 2;
  }                                    // Process
  for (int i=0; i < 10; i++) {
    sleep(1);                          // slow things down a bit
    fin = popen("/usr/games/fortune -s", "r");
    memset( pipe_buf, 0x0, BUFSIZ );   // clear buffer before reading cmd output
    read( fileno(fin), pipe_buf, BUFSIZ );
    sprintf( clnt_buf, "%d : %s", getpid(), pipe_buf );
    sendto( orig_sock, clnt_buf, sizeof(clnt_buf), 0,
            (struct sockaddr *) &serv_adr, sizeof(struct sockaddr) );
  }
  clean_up( orig_sock, clnt_file );
  return 0;
}
void
clean_up( int sd, const char *the_file ){
  close( sd );
  unlink( the_file );
}
