#include <stdio.h>
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>             // For resultproc_t cast

u_long   program_number, version;      // Note: These are global
static bool_t
who_responded(char *out, struct sockaddr_in *addr) {
  int my_port_T, my_port_U;
  my_port_T = pmap_getport(addr, program_number, version, IPPROTO_TCP);
  my_port_U = pmap_getport(addr, program_number, version, IPPROTO_UDP);
  if ( my_port_T )
    printf("host: %s \t TCP port: %d\n",inet_ntoa(addr->sin_addr),
            my_port_T);
  if ( my_port_U )
    printf("host: %s \t UDP port: %d\n",inet_ntoa(addr->sin_addr),
            my_port_U);
  return 0;
}
int
main(int argc, char *argv[]) {
  enum clnt_stat  rpc_stat;
  struct rpcent  *rpc_entry;
  if (argc < 2) {
    fprintf(stderr, "usage: %s RPC_service_[name | #] version\n", *argv);
    return 1;
  }
  ++argv;                              // Step past your own prog name
  if (isdigit(**argv))                 // Check to see if # was passed
    program_number = atoi(*argv);      // If # passed use it otherwise
  else {                               // obtain RPC entry information
    if ((rpc_entry = getrpcbyname(*argv)) == NULL) {
      fprintf(stderr, "Unknown service: %s\n", *argv);
      return 2;
    }                                  // Get the program number
    program_number = rpc_entry->r_number;
  }
  ++argv;                              // Move to version #
  version = atoi(*argv);
  rpc_stat = clnt_broadcast(program_number, version, NULLPROC,
                           (xdrproc_t)xdr_void, (char *) NULL,
                           (xdrproc_t)xdr_void, (char *) NULL,
                           (resultproc_t) who_responded);
  if (rpc_stat != RPC_SUCCESS)
   if (rpc_stat != RPC_TIMEDOUT) {     // If error is not a time out
    fprintf(stderr, "Broadcast failure : %s\n", clnt_sperrno(rpc_stat));
    return 3;
  }
  return 0;
}
