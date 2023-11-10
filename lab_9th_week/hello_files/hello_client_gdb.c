/*
    The CLIENT program:  hello_client.c
    This will be the client code executed by the local client process.
 */
#include <stdio.h>
#include "hello.h"         /*** Generated by rpcgen from hello.x  */
int
main(int argc, char *argv[]) {
  CLIENT         *client;
  int            *return_value, filler;
  char           *server;
/*
    We must specify a host on which to run.  We will get the host name
    from the command line as argument 1.
 */
  if (argc != 2) {
    fprintf(stderr, "Usage: %s host_name\n", *argv);
    exit(1);
  }
   server = argv[1];
/*
    Generate the client handle to call the server
 */
#ifndef DEBUG
   if ((client=clnt_create(server,      DISPLAY_PRG, 
                           DISPLAY_VER, "tcp")) == (CLIENT *) NULL) {
    clnt_pcreateerror(server);
    exit(2);
  }
  printf("client : calling function.\n");
  return_value = print_hello_1((void *) &filler, client);
#else
  printf("client : calling function.\n");
  return_value = print_hello_1_svc((void *) &filler, (struct svc_req *)client);
#endif
  if (*return_value)
    printf("client : Mission accomplished\n");
  else
    printf("client : Unable to display message\n");
  return 0;
}
