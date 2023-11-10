/*
   INTRA process main (multiple threads - one process space)
   Compile: g++  p11.5.PC.cxx  p11.5.INTRA.cxx  -lpthread -o INTRA
*/
#include "local_mutex.h"
pthread_mutex_t LOCK,   *m_LOCK = &LOCK;
int             setup,  *s_shm  = &setup,
                current,*c_shm  = &current;
int
main(int argc, char *argv[]) {
  int  i, n;
  pthread_t worker[MAX];                         // worker TID's
  if ( argc != 2) {
    cerr <<  "Usage: " << *argv << " n_workers" << endl;
    return 1;
  }
  pthread_mutex_init(&LOCK,  NULL);
  *s_shm = 0;                                    // Start as NOT setup
  *c_shm = 0;                                    // current index (offset)
  n = atoi(argv[1]) < MAX ? atoi(argv[1]) : MAX; // # of threads to create
  for( i=0; i < n; ++i)                          // create each thread
    pthread_create( &worker[i], NULL,
                   (void *(*)(void *))do_work, (void *)NULL );
                                                 // wait for all to finish
  for(i=0; i < n; ++i )
    pthread_join(worker[i], (void **) NULL);
                                                 // show contents of buffer
  cout << "Contents of " << BUFFER
       << " negative values were 'consumed'." << endl;
  fstream  fptr;
  bool     done = false;
  fptr.open( BUFFER, ios::in );
  while ( !done ) {
    fptr.read( (char *)&n, sizeof(n) );
    if ( fptr.fail() )
      done = true;
    else
      cout << n << endl;
  }
  fptr.close( );
  return 0;
}
