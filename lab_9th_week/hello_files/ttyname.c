#include <stdio.h>
int
main( ){
  char *dev = (char *)ttyname(fileno(stdout));
  if (dev)
    printf("My standard output device is %s\n", dev);
  else
    fprintf(stderr, "I don't know my standard output device!\n");
  return 0;
}
