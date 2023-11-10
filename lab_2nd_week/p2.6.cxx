/*
    Command line using getopt
 */
#define _GNU_SOURCE
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
extern char    *optarg;
extern int      optind, opterr, optopt;
int
main(int argc, char *argv[ ]){
  int      c;
  char     optstring[] = "abs:";
  opterr = 0;                          // turn off auto err mesg
  while ((c = getopt(argc, argv, optstring)) != -1)
    switch (c) {
    case 'a':
      cout << "Found option a\n";
      break;
    case 'b':
      cout << "Found option b\n";
      break;
    case 's':
      cout << "Found option s with an argument of: ";
      cout << atoi(optarg) << endl;    // convert to integer
      break;
     case '?':
      cout << "Found an option that was not in optstring.\n";
      cout << "The offending character was " << char(optopt) << endl;
    }
  if (optind < argc){
    cout << (argc - optind) << " arguments not processed.\n";
    cout << "Left off at: " <<  argv[optind] << endl;
  }
  return 0;
}
