/*
      Internet domain, connection-oriented SERVER - MSG_PEEK
*/
#include "local_sock.h"
void signal_catcher(int);
int
main(  ) {
  int             orig_sock,           // Original socket in server
                  new_sock;            // New socket from connect  
  socklen_t       clnt_len;            // Length of client address 
  struct sockaddr_in                   // Internet addr client & server
                  clnt_adr, serv_adr;
  int             len, i;              // Misc counters, etc.
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
  do {
    clnt_len = sizeof(clnt_adr);                 // ACCEPT a connect
    if ((new_sock = accept( orig_sock, (struct sockaddr *) &clnt_adr,
                            &clnt_len)) < 0) {  
      perror("accept error");
      close(orig_sock);
      return 5;
    }
    if ( fork( ) == 0 ) {                        // Generate a CHILD
       while ( (len=recv(new_sock, buf, BUFSIZ, MSG_PEEK)) > 0 ){
         write( fileno(stdout),"Peeked and found: ",19);
         write( fileno(stdout), buf, len);       // show peeked msg
         if ( !strncmp(buf, ".done", len-1) ) break;
         len=recv(new_sock, buf, BUFSIZ, 0 );    // retrieves same msg
         write( fileno(stdout), "Re-read buffer  : ",19);
         write( fileno(stdout), buf, len);
       }
       write( fileno(stdout),"Leaving child process\n",22);
       close(new_sock);                          // In CHILD process 
       return 0;
    } else close(new_sock);                      // In PARENT process
  } while( true );                               // FOREVER 
  return 0;
}
void
signal_catcher(int the_sig){
  signal(the_sig, signal_catcher);               // reset
  wait(0);                                       // keep the zombies at bay
}
