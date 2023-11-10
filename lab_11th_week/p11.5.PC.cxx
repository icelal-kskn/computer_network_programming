/*
      Common producer & consumer code
*/
#include "local_mutex.h"
struct timespec some_time;
fstream         fptr;                  // common buffer location
extern pthread_mutex_t *m_LOCK;        // shared mutex
extern int             *s_shm,         // setup flag
                       *c_shm;         // counter
/*
    Generate a random # within specified range
*/
int
my_rand(int start, int range){
  struct timeval t;
  gettimeofday(&t, (struct timezone *)NULL);
  return (int)(start+((float)range * rand_r((unsigned *)&t.tv_usec))
               / (RAND_MAX+1.0));
}
/*
      Produce a random # and write to a common repository
*/
void
produce( ) {
  int   err, *n;
  cout << pthread_self( ) << "\t P: attempting to produce \t"
       << getpid( ) << endl;
  cout.flush( );
  if (pthread_mutex_trylock(m_LOCK) != 0) {      // LOCK
    cout << pthread_self( ) << "\t P: lock busy             \t"
         << getpid( ) << endl;
    cout.flush( );
    return;
  }
  n  = new int;                                  // allocate
  *n = my_rand(1,MAX);
  fptr.open(BUFFER, ios::out | ios::app);        // Open for append
  fptr.write( (char *) n, sizeof(*n) );
  fptr.close( );
  delete n;                                      // release
  cout << pthread_self() << "\t P: The # [" << *n
       << "] deposited    \t" << getpid( )  << endl;
    cout.flush( );
  some_time.tv_sec = 0; some_time.tv_nsec = 10000;
  nanosleep(&some_time, NULL);                   // sleep a bit
  if ((err=pthread_mutex_unlock(m_LOCK)) != 0){  // UNLOCK
    cerr << "P: unlock failure " << err << endl;
    cout.flush( );
    exit(102);
  }
}
/*
      Consume the next random number from the common repository
*/
void
consume( ) {
  int             err, *n;
  cout << pthread_self( ) << "\t C: attempting to consume \t"
       << getpid( ) << endl;
  cout.flush( );
  if (pthread_mutex_trylock(m_LOCK) != 0) {      // LOCK
    cout << pthread_self( ) << "\t C: lock busy             \t"
         << getpid( ) << endl;
    cout.flush( );
    return;
  }
  fptr.open(BUFFER, ios::in);                    // Try to read
  if ( fptr ) {                                  // If present
    fptr.close( );
    fptr.open(BUFFER, ios::in|ios::out);         // Reopen for R/W
  }
  fptr.seekp( *c_shm * sizeof(int), ios::beg );
  n = new int;                                   // allocate
  *n = 0;
  fptr.read( (char *)n, sizeof(*n));
  if ((*n) > 0) {                                // For positive values
    cout << pthread_self() << "\t C: The # [" << *n
         << "] obtained    \t" << getpid( )   << endl;
    cout.flush( );
    fptr.seekp( *c_shm * sizeof(int), ios::beg );
    *n = -(*n);
    fptr.write( (char *) n, sizeof(*n) );
    fptr.close( );
    ++*c_shm;                                   // increment counter
  } else {
    cout << pthread_self( ) << "\t C: No new # to consume     \t"
         << getpid( ) << endl;
    cout.flush( );
  }
  delete n;                                       // release
  fptr.close( );
  some_time.tv_sec = 0; some_time.tv_nsec = 10000;
  nanosleep(&some_time, NULL);
  if ((err=pthread_mutex_unlock(m_LOCK)) != 0){  // UNLOCK
    cerr<< "C: unlock failure " << err << endl;
    exit(104);
  }
}
/*
   Simulate some work, 10 iterations about half produce, half consume
*/
void
do_work( ) {
  if (!(*s_shm)) {                               // Clear @ start
    pthread_mutex_lock(m_LOCK);                  // LOCK
    if (!(*s_shm)++) {
      cout << pthread_self( ) << "  \t  : clearing the buffer  \t"
           << getpid() << endl;
      fptr.open( BUFFER, ios::out | ios::trunc );
      fptr.close( );
    }
    pthread_mutex_unlock(m_LOCK);                // UNLOCK
  }
  for (int i = 0; i < 10; ++i) {
    some_time.tv_sec = 0; some_time.tv_nsec = 10000;
    nanosleep(&some_time, NULL);                 // sleep a bit
    switch ( my_rand(1,2) ) {
    case 1:
      produce();
      break;
    case 2:
      consume();
    }
  }
}
