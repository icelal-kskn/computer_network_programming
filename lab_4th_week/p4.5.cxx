/* Catching a signal
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <unistd.h>
using namespace std;
int
main( ) {
  void            signal_catcher(int);
  if (signal(SIGINT , signal_catcher) == SIG_ERR) {
    perror("SIGINT");
    return 1;
  }
  if (signal(SIGQUIT , signal_catcher) == SIG_ERR) {
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
  signal(the_sig, signal_catcher);     // reset immediately
  cout << endl << "Signal " << the_sig << " received." << endl;
  if (the_sig == SIGQUIT)
    exit(3);
}
