10.13.cxx
/*
     Program 10.13 - SERVER - Internet Domain - connectionless
*/
#include "local_sock.h"
#include <sys/time.h>
int
main(  ) {
  int                sock, n,
                     n_ready, need_rsp;
  fd_set             read_fd;
  struct timeval     w_time;
  |
  socklen_t          server_len, client_len;
  struct sockaddr_in server,           // Internet Addresses
                     client;
                                       // SOCKET
  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("SERVER socket "); return 1;
  }
  memset(&server, 0, sizeof(server));  // Clear structure
  server.sin_family      = AF_INET;    // Set address type
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port        = htons(0);
                                       // BIND
  if (bind(sock, (struct sockaddr *) &server,
      sizeof(server) ) < 0) {
    perror("SERVER bind "); return 2;
  }
  server_len = sizeof(server);         // Obtain  address length
                                       // Find picked port #
  if (getsockname(sock, (struct sockaddr *) &server,
      &server_len) < 0) {
    perror("SERVER getsocketname "); return 3;
  }
  cout << "Server using port " << ntohs(server.sin_port) << endl;
  while ( 1 ) {                                  // Loop forever
    w_time.tv_sec = 5; w_time.tv_usec = 0;       // set the wait time
    FD_ZERO( &read_fd );                         // zero all bits
    FD_SET( sock, &read_fd );                    // indicate one to read
    if ( (n_ready=select( sock + 1, &read_fd, (fd_set *) NULL,
                        (fd_set *) NULL, &w_time)) < 0 ) {
      perror("SERVER read socket select "); continue;
    }
    if ( FD_ISSET( sock, &read_fd ) ) {          // activity on socket
      client_len = sizeof(client);               // estimate length
      memset(buf, 0, BUFSIZ);                    // clear the buffer
      if ((n=recvfrom(sock, buf, BUFSIZ, 0,      // get the client's msg
          (struct sockaddr *) &client, &client_len)) < 0){
        perror("SERVER recvfrom ");
        close(sock); return 4;
      }
      write( fileno(stdout), buf, n );           // display msg on server
      memset(buf, 0, BUFSIZ);                    // clear the buffer
      need_rsp = 1;
    }
    if ( need_rsp ) {
      w_time.tv_sec = 5; w_time.tv_usec = 0;     // set the wait time
      FD_ZERO( &read_fd );                       // zero all bits
      FD_SET( fileno(stdin), &read_fd );         // the one to read
      if ( (n_ready=select( fileno(stdin) + 1, &read_fd,
           (fd_set *) NULL,(fd_set *) NULL, &w_time)) < 0 ) {
        perror("SERVER read stdin select "); continue;
      }                                          // get server's msg
                                                 // if activity stdin
      if ( FD_ISSET( fileno(stdin), &read_fd ) ) {
        if ( read( fileno(stdin),buf,BUFSIZ) != 0 ) {   
          if ((sendto(sock, buf, strlen(buf) ,0, // send to client
              (struct sockaddr *) &client, client_len)) <0){
            perror("SERVER sendto ");
            close(sock); return 5;
          }
          need_rsp = 0;
        }
      }
    }
  }
  return 0;
}
