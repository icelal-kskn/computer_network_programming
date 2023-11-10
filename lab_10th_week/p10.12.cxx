/*
   Program 10.12 - SERVER Internet Domain - connectionless - NON-BLOCKING
 */
#include "local_sock.h"
#include <sys/ioctl.h>
#include <errno.h>
int
main(  ) {
  int                sock, n,
                     errcount=0, flag=1;
  socklen_t          server_len, client_len;
  struct sockaddr_in server,           // Internet Addresses
                     client;
                                       // SOCKET
  if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("SERVER socket "); return 1;
  }
  if (ioctl(sock, FIONBIO, &flag) < 0 ) {
    perror("SERVER ioctl "); return 2;
  }
  memset(&server, 0, sizeof(server));  // Clear structure
  server.sin_family      = AF_INET;    // Set address type
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port        = htons(0);
                                       // BIND
  if (bind(sock, (struct sockaddr *) &server,
      sizeof(server) ) < 0) {
    perror("SERVER bind "); return 3;
  }
  server_len = sizeof(server);         // Obtain  address length
                                       // Find picked port #
  if (getsockname(sock, (struct sockaddr *) &server,
      &server_len) < 0) {
    perror("SERVER getsocketname "); return 4;
  }
  cout << "Server using port " << ntohs(server.sin_port) << endl;
  while ( 1 ) {                                  // Loop forever
    client_len = sizeof(client);                 // estimate length
    memset(buf, 0, BUFSIZ);                      // clear the buffer
    if ((n=recvfrom(sock, buf, BUFSIZ, 0,        // get the client's msg
        (struct sockaddr *) &client, &client_len)) < 0){
      if ( errcount++ > 60 || errno != EWOULDBLOCK ) {
        perror("SERVER recvfrom ");
        close(sock); return 5;
      }
      sleep(1);
      continue;
    }
    errcount = 0;
    write( fileno(stdout), buf, n );             // display msg on server
    memset(buf, 0, BUFSIZ);                      // clear the buffer
    if ( read(fileno(stdin), buf, BUFSIZ) != 0 ){// get server's msg   
      if ((sendto(sock, buf, strlen(buf) ,0,     // send to client
        (struct sockaddr *) &client, client_len)) <0){
        perror("SERVER sendto ");
        close(sock); return 6;
      }
    }
  }
  return 0;
}
