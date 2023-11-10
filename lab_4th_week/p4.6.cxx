/* Catching a signal using sigaction
 */
#define _GNU_SOURCE
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <unistd.h>
using namespace std;
int
main( ) {
  void   signal_catcher(int);
  struct sigaction new_action;
  new_action.sa_handler = signal_catcher;
  new_action.sa_flags   = 0;

  if (sigaction(SIGINT,  &new_action, NULL) == -1) {
    perror("SIGINT");
    return 1;
  } 
  if (sigaction(SIGQUIT, &new_action, NULL) == -1) {
    perror("SIGQUIT");
    return 2;
  }
  for (int i=0;  ; ++i) {              // Forever ...
    cout << i << endl;                 // display a number
    sleep(1);
  }
  return 0;
}
void
signal_catcher(int the_sig){
  cout << endl << "Signal " << the_sig << " received." << endl;
  if (the_sig == SIGQUIT)
    exit(3);
}
