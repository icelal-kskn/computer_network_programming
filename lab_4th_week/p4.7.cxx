/* Demonstration of the sigprocmask call */
#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <signal.h>
#include <unistd.h>
using namespace std;
sigset_t new_signals;
int
main( ) {
  void    signal_catcher(int);
  struct  sigaction new_action;

  sigemptyset(&new_signals);
  sigaddset(&new_signals,SIGUSR1);

  sigprocmask(SIG_BLOCK, &new_signals, NULL);
  new_action.sa_handler = signal_catcher;
  new_action.sa_flags   = 0;
  if (sigaction(SIGUSR2, &new_action, NULL) == -1) {
    perror("SIGUSR2");
    return 1;
  }
  cout << "Waiting for signal" << endl;
  pause( );
  cout << "Done" << endl;
  return 0;
}
void
signal_catcher( int n ) {
  cout << "Received signal " << n << " will release SIGUSR1" << endl;
  sigprocmask(SIG_UNBLOCK, &new_signals, NULL);
  cout << "SIGUSR1 released!" << endl;
}
