/*
       Frick's CLIENT - UNIX domain - connectionless
*/
#include "local_sock.h"

int
main( ) {
  int             orig_sock;   
  static struct sockaddr_un   
                  serv_adr;  
  static char     clnt_buf[BUFSIZ], 
                  pipe_buf[BUFSIZ];
  FILE             *fin;       
                              
  if ((orig_sock = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
    perror("generate error");
    return 1;
  }
  serv_adr.sun_family = AF_UNIX;       
  strcpy( serv_adr.sun_path, SERVER_FILE );
  for (int i=0; i < 10; i++) {
    sleep(1);                
    fin = popen("/usr/games/fortune -s", "r");
    memset( pipe_buf, 0x0, BUFSIZ ); 
    read( fileno(fin), pipe_buf, BUFSIZ );
    sprintf( clnt_buf, "%d : %s", getpid(), pipe_buf );
    sendto( orig_sock, clnt_buf, sizeof(clnt_buf), 0,
            (struct sockaddr *) &serv_adr, sizeof(struct sockaddr) );
  }
  return 0;
}
