/*
     Using rexec
*/
#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;
int
main(int argc, char *argv[]) {
  int    fd, count;
  char   buffer[BUFSIZ], *command, *host;
  if (argc != 3) {
    cerr <<  "Usage " << argv[0] << " host command" << endl;
    return 1;
  }
  host   = argv[1];
  command= argv[2];
  if ((fd=rexec(&host,htons(512),NULL,NULL,command,(int *)0)) == -1) {
    perror("rexec ");
    return 2;
  }
  while ((count = read(fd, buffer, BUFSIZ)) > 0)
    fwrite(buffer, count, 1, stdout);
  return 0;
}
