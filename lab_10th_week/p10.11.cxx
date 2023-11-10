/*
     Program 10.11 - CLIENT - Internet Domain - connectionless
 */
#include "local_sock.h"
int
main(int argc, char *argv[]){
  int             sock, n;
  socklen_t       server_len;
  struct sockaddr_in                   // Internet addresses
                  server, client;
  struct hostent *host;                // For host information
  if ( argc < 3 ) {                    // We need server name & port #
    cerr << "usage: " << argv[0] << "server_name   port_#" << endl;
    return 1;
  }                                    // Server information
  if (!(host=gethostbyname(argv[1]))){
    perror("CLIENT gethostname ");  return 2;
  }                                    // Set server address info
  memset(&server, 0, sizeof(server));  // Clear structure
  server.sin_family = AF_INET;         // Address type
  memcpy(&server.sin_addr, host->h_addr, host->h_length);
  server.sin_port   = htons(atoi(argv[2]));
                                       // SOCKET
  if ((sock=socket(PF_INET, SOCK_DGRAM, 0)) < 0 ) {
    perror("CLIENT socket "); return 3;
  }                                    // Set client address info
  memset(&client, 0, sizeof(client));  // Clear structure
  client.sin_family      = AF_INET;    // Address type
  client.sin_addr.s_addr = htonl(INADDR_ANY);
  client.sin_port        = htons( 0 );
                                       // BIND
  if (bind(sock, (struct sockaddr *) &client,
      sizeof(client)) < 0) {
    perror("CLIENT bind "); return 4;
  }
  cout << "Client must send first message." << endl;
  while( read(fileno(stdin), buf, BUFSIZ) != 0 ){// get client's msg
    server_len=sizeof(server);                   // length of address
    if (sendto( sock, buf, strlen(buf), 0,       // send msg to server
     (struct sockaddr *) &server, server_len) < 0 ){
       perror("CLIENT sendto ");
       close(sock); return 5;
    }
    memset(buf,0,BUFSIZ);                        // clear the buffer
    if ((n=recvfrom(sock, buf, BUFSIZ, 0,        // get server's msg
        (struct sockaddr *) &server, &server_len)) < 0){
      perror("CLIENT recvfrom ");
      close(sock); return 6;
    }
    write( fileno(stdout), buf, n );             // display msg on client
    memset(buf,0,BUFSIZ);                        // clear the buffer
  }
  close(sock);
  return 0;
}
