 /*
     The SERVER program: hello_server.c
     This will be the server code executed by the "remote" process
 */
 #include <stdio.h>
 #include "hello.h"             /* is generated by rpcgen from hello.x  */
 int *
 print_hello_1_svc(void * filler, struct svc_req * req) {
   static int  ok;
   ok = printf("server : Hello, world.\n");
   return (&ok);
 }
