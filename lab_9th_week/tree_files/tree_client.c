/*
 
#####  #####   ######  ######   ####   #        #   ######  #    #   #####  
  #    #    #  #       #       #    #  #        #   #       ##   #     #
  #    #    #  #####   #####   #       #        #   #####   # #  #     #
  #    #####   #       #       #       #        #   #       #  # #     #
  #    #   #   #       #       #    #  #        #   #       #   ##     #
  #    #    #  ######  ######   ####   ######   #   ######  #    #     #
 */
#include "local.h"
#include "tree.h"
 
void
tree_1(char *host, char *the_dir ) {
  CLIENT         *client;
  dir_result     *result;
 
#ifndef DEBUG
  client = clnt_create(host, TREE, one, "tcp");
  if (client == (CLIENT *) NULL) {
    clnt_pcreateerror(host);
    exit(2);
  }
  result = do_dir_1(&the_dir, client);                  
#else                                                           
  result = do_dir_1_svc(&the_dir, (svc_req *) client);
#endif                        /* DEBUG */
  if (result == (dir_result *) NULL) {
#ifndef DEBUG
    clnt_perror(client, "call failed");
#else
    perror("Call failed");
#endif                        /* DEBUG */
    exit(3);
  } else                      /* display the whole array       */
    printf("%s:\n\n%s\n",the_dir,result->dir_result_u.line_ptr);
#ifndef DEBUG
  clnt_destroy(client);
#endif                        /* DEBUG */
}
int
main(int argc, char *argv[]) {
  char        *host;
  static char directory[DIR_1]; /* Name of the directory        */
  if (argc < 2) {
    fprintf(stderr, "Usage %s server [directory]\n", argv[0]);
    exit(1);
  }
  host = argv[1];             /* Assign the server            */
  if (argc > 2)
    strcpy(directory, argv[2]);
  else
    strcpy(directory , ".");
  tree_1(host, directory);    /* Give it a shot!              */
  return 0;
}
