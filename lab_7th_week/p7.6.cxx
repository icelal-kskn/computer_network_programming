/*
     The dining philosophers 
 */
#include <iostream>
#include "SSemaphore.h"                // Our basic semaphore class
const int MAX = 5;
SSemaphore Forks[MAX];
void Philosopher( int );
void Eat_It( const int,const int, const int );
int
main(int argc, char *argv[] ) {
  int i;
  if ( argc < 2 ) {
    cerr << "Usage: " << argv[0] << " secs_to_wait " << endl;
    return 1;
  }
  for( i=0; i < MAX; ++i )
    Forks[i].Put(true);
  for(i = 0; i < MAX; ++i )
    Philosopher( i );
  sleep(atoi(argv[1]));                // Parent process waits a bit
  return 0;
}
void
Philosopher(int number ){
  if (fork() == 0) {                   // Run in the child
    int left, right;
    srand(getpid( ));
    left = number;
    right= (number+1) % MAX;
    do {
      cout << "A. P" << number << " is thinking\n";
      sleep(rand( ) % 3 + 1);          // Take a while to THINK
      cout << "B. P" << number << " ASKS to eat with forks "
           << left << " & " << right << endl;
      Forks[left].P( );                // Acquire left fork
        Forks[right].P( );             // Acquire right fork
          Eat_It(number, left, right);
        Forks[right].V( );
      Forks[left].V( );
    } while( true );
  }
}
void
Eat_It(const int number, const int left, const int right) {
  cout << "C. P" << number << " is EATING   with forks "
       << left << " & " << right << endl;
  sleep(rand( ) % 3 + 1);              // Take a while to EAT
  cout << "D. P" << number << " is now DONE with forks "
       << left << " & " << right << endl;
}
