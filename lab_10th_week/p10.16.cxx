/*
      Internet domain, connection-oriented SERVER - MSG_PEEK
*/
#include "local_sock.h"
#include <time.h>                      // For nanosleep
void signal_catcher(int);
int
main(  ) {
  int             orig_sock,           // Original socket in server
                  new_sock;            // New socket from connect
  socklen_t       clnt_len;            // Length of client address
  struct sockaddr_in                   // Internet addr client & server
                  clnt_adr, serv_adr;
  int             len, i,              // Misc counters, etc.
                  urg, mark;           // Flag reception of OOB msg and to
                                       // note its location in the stream.
                                       // Catch when child terminates
  if (signal(SIGCHLD , signal_catcher) == SIG_ERR) {
    perror("SIGCHLD");
    return 1;
  }
  if ((orig_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("generate error");
    return 2;
  }
  memset( &serv_adr, 0, sizeof(serv_adr) );      // Clear structure
  serv_adr.sin_family      = AF_INET;            // Set address type
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // Any interface
  serv_adr.sin_port        = htons(PORT);        // Use our fake port
                                                 // BIND
  if (bind( orig_sock, (struct sockaddr *) &serv_adr,
            sizeof(serv_adr)) < 0){
    perror("bind error");
    close(orig_sock);
    return 3;
  }
  if (listen(orig_sock, 5) < 0 ) {               // LISTEN
    perror("listen error");
    close (orig_sock);
    return 4;
  }
  struct timespec req, rem;                      // For nanosleep
  do {
    clnt_len = sizeof(clnt_adr);                 // ACCEPT a connect
    if ((new_sock = accept( orig_sock, (struct sockaddr *) &clnt_adr,
                            &clnt_len)) < 0) {
      perror("accept error");
      close(orig_sock);
      return 5;
    }
    if ( fork( ) == 0 ) {                        // Generate a CHILD
      urg = mark = 0;
      do {
        req.tv_sec = 5; req.tv_nsec = 0;         // set time to sleep
        nanosleep( &req, &rem);                  // slow down the server
        if ( (len=recv(new_sock, buf, BUFSIZ, MSG_OOB)) > 0) {
          write( fileno(stdout), "URGENT msg pending\n", 19);
          urg = 1;
        }
        if ( urg ) ioctl(new_sock, SIOCATMARK, &mark);
        if ( mark ) {
          write( fileno(stdout), " <-- the URGENT msg\n",20);
          mark = urg = 0;
        }
        if ((len=recv(new_sock, buf, BUFSIZ, 0)) > 0) {
          if ( !strncmp(buf, ".done", len-1) ) break;
          write( fileno(stdout), buf, len);
        }
      } while( 1 );
      write( fileno(stdout),"Leaving child process\n",22);
      close(new_sock);                           // In CHILD process
      return 0;
    } else
      close(new_sock);                           // In PARENT process
  } while( true );                               // FOREVER
  return 0;
}
void
signal_catcher(int the_sig){
  signal(the_sig, signal_catcher);               // reset
  wait(0);                                       // keep the zombies at bay
}
