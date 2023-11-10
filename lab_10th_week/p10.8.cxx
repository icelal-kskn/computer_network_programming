/*
       SERVER - UNIX domain - connectionless
*/
#include "local_sock.h"

void clean_up(int, const char *);      // Close socket and remove
int
main(  ) {
  socklen_t       clnt_len;            // Length of client address
  int             orig_sock;           // Original socket descriptor
  static struct sockaddr_un
                     clnt_adr,         // Client address
                     serv_adr;         // Server address
  static char        buf[BUFSIZ];      // Buffer for messages
                                       // Generate socket
  if ((orig_sock = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
    perror("generate error");
    return 1;
  }                                    // Assign address information
  serv_adr.sun_family = AF_UNIX;
  strcpy(serv_adr.sun_path,SERVER_FILE);
  unlink( SERVER_FILE);                // Remove old copy if present
                                       // BIND the address
  if (bind(orig_sock, (struct sockaddr *) &serv_adr,
          sizeof(serv_adr.sun_family)+strlen(serv_adr.sun_path)) < 0) {
   perror("bind error");
    clean_up(orig_sock, SERVER_FILE);
    return 2;
  }                                    // Process
  for (int i = 1; i <= 10; i++) {
    recvfrom(orig_sock, buf, sizeof(buf), 0,
           (struct sockaddr *) &clnt_adr, &clnt_len);
    cout << "S receives " << buf;
  }
  clean_up(orig_sock, SERVER_FILE);
  return 0;
}
void
clean_up( int sd, const char *the_file ){
  close( sd );                         // Close socket
  unlink( the_file );                  // Remove it
}
