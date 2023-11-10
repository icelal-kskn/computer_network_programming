/*
      A C program with a local function
*/
#include <stdio.h>
int print_hello( );
int
main( ){
  printf("main : Calling function.\n");
  if (print_hello())
    printf("main : Mission accomplished.\n");
  else
    printf("main : Unable to display message.");
  return 0;
}
int
print_hello( ) {
  return printf("funct: Hello, world.\n");
}
