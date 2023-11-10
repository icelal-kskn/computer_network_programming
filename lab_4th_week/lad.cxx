/* Lad's signal catching program
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <unistd.h>
using namespace std;
int
main( ) {
  void  signal_catcher(int);
  char  a_num[5];
  for (int i=1; i < _NSIG; ++i)
    switch( i ){
    case SIGKILL: case SIGSTOP:
      break;
    default:
      if (signal(i , signal_catcher) == SIG_ERR) {
        sprintf( a_num, "%d", i );
        perror(a_num);
        return 1;
      }
  }
  for (int i=0;  ; ++i) {              // Forever ... 
    cout << i << endl;                 // display a number 
    sleep(1);
  }
  return 0;
}
void
signal_catcher(int the_sig){
  signal(the_sig, signal_catcher);     // reset
  cout << endl << "Signal " << the_sig << " received." << endl;
  if (the_sig == SIGQUIT)
    exit(3);
}
