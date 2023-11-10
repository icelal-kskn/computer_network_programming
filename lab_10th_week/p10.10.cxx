/*
     Program 10.10 - SERVER - Internet Domain - connectionless
*/
#include "local_sock.h"
int
main(  ) {
  int                sock, n;
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
    client_len = sizeof(client);                 // set the length
    memset(buf, 0, BUFSIZ);                      // clear the buffer
    if ((n=recvfrom(sock, buf, BUFSIZ, 0,        // get the client's msg
        (struct sockaddr *) &client, &client_len)) < 0){
     perror("SERVER recvfrom ");
     close(sock); return 4;
    }
    write(fileno(stdout), buf, n);               // display msg on server
    memset(buf, 0, BUFSIZ);                      // clear the buffer
    if ( read(fileno(stdin), buf, BUFSIZ) != 0 ){// get server's msg
      if ((sendto(sock, buf, strlen(buf) ,0,     // send to client
        (struct sockaddr *) &client, client_len)) <0){
        perror("SERVER sendto ");
        close(sock); return 5;
      }
    }
  }
  return 0;
}
