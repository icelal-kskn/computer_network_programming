/*
    pthread_sigmask example.
*/
#define _GNU_SOURCE
#define _REENTRANT
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
using namespace std;
const int MAX=3;
void  trapper( int );
int   global_i = 0;
int
main(int argc, char *argv[]) {
  struct sigaction  new_action;
  new_action.sa_handler = &trapper;
  new_action.sa_flags = 0;
  sigset_t        my_sigs;             // Signal mask
  int             sig_in;
  setvbuf(stdout, (char *)NULL, _IONBF, 0);
  if ( argc > 1 && argc < MAX+2 ) {
    sigemptyset(&my_sigs);             // Clear it out, set to all 0's
    while( argc-- > 1 )                // Add signal #'s passed in
      sigaddset(&my_sigs, atoi(argv[argc]));
  } else {
    cerr << *argv << " SIG1 ... SIG" <<  MAX << endl;
    return 1;
  }
  for (int i=1; i < NSIG; ++i)         // Attempt to trap all signals
   sigaction(i, &new_action, NULL);
                                       // BLOCK signals in mask
  pthread_sigmask(SIG_BLOCK, &my_sigs, NULL);
  cout << "Signal bits turned on" << endl;
  for (int i=1; i < NSIG; ++i)
    putchar( sigismember(&my_sigs, i) == 0 ? '0' : '1');
  cout << "\nWaiting for signals\n";   // Wait for a few signals
  while (global_i < MAX){
    if ( (sigwait(&my_sigs, &sig_in)) != -1 )
      cout << "Signal " << sig_in
           << " in mask - no signal catcher" << endl;
    ++global_i;
  }
  return 0;
}
void
trapper( int s ){
  cout << "Signal " << s << " not in mask - in signal catcher" << endl;
  ++global_i;
}
