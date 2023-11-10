/*
   Checking errno and using perror
 */
#include <iostream>
#include <cstdio>                       // needed for perror
#include <cstdlib>                      // needed for exit
#include <unistd.h>                     // needed for read and write
using namespace std;
extern int errno;
int
main(int argc, char *argv[ ]) {
  int  n_char = 0,                     // # of chars read
  buffer[10];                          // temporary buffer
  
  // Initially n_char is set to 0 and errno is 0 by default
  
  cout << "n_char = " << n_char << "\t errno = " << errno << endl;
  
  // Display a prompt to stdout
 
  n_char = write(1, "Enter a word: ", 15);
  
  // Use the read system call to obtain 10 characters from stdin
  
  n_char = read(0, buffer, 10);
  cout << "n_char = " << n_char << "\t errno = " << errno << endl;
  
  if (n_char == -1) {                  // If the read has failed
    perror(argv[0]);
    exit(1);
  }
  
  n_char = write(1, buffer, n_char);   // Display the characters read
  return 0;
}
