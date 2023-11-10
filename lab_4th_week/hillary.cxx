/*
  Source code for using lock file. Compile using -c and 
  -D_GNU_SOURCE options. Link object code as needed. 
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
const int  NTRIES = 5;                 // default values
const int  SLEEP  = 5;
const char *LFILE = "/tmp/TEST.LCK";
using namespace std;
void
set_defaults(int ac, char *av[ ], 
             int *n_tries, int *s_time, char **f_name){
  static char full_name[PATH_MAX];
  *n_tries = NTRIES;                   // Start with defaults 
  *s_time  = SLEEP;
  strcpy(full_name, LFILE);
  switch (ac) {
  case 4:                              // File  name was specified 
    full_name[0] = '\0';               // "clear" the string
    strcpy(full_name, av[3]);          // Add the passed in file
  case 3:
    if ((*s_time = atoi(av[2])) <= 0)  // Seconds of sleep time 
      *s_time = SLEEP;
  case 2:
    if ((*n_tries = atoi(av[1])) <= 0) // Number of times to try
      *n_tries = NTRIES;
  case 1:                              // Use the defaults 
    break;
  default:
    cerr << "Usage: " << av[0] <<
            " [[tries][sleep][lockfile]]" << endl;
    exit(1);
  }
  *f_name = full_name;                     
}
#include <cstdio>
bool
acquire(int numb_tries, int sleep_time, char *file_name){
  char   my_link[512];
  sprintf( my_link, "%s.%d", file_name, getpid());
  int count = 0;
  struct stat buf;
  while ( ++count < numb_tries) {
     creat( my_link,0);
     link( my_link, file_name );
     if (!stat(my_link, &buf) && buf.st_nlink == 2){
       unlink(my_link);
       return true;
     }
    sleep(sleep_time);
  }
  return false;
}

bool
release(char *file_name){
  return (bool(unlink(file_name) == 0));
}
