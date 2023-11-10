/*
  Using thread specific data
*/
#define _GNU_SOURCE
#define _REENTRANT
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
const int MAX=20;
void *TSD( int ),                                // manipulates TSD
      free_me( void *  );                        // destructor
static pthread_key_t  key;                       // global TSD key
int
main( int argc, char *argv[] ) {
  pthread_t thr_id[MAX];
  int inc;
  if ( argc  < 2 || atoi(argv[1]) > MAX){
    cerr << *argv << " num_threads" << endl;
    return 1;
  }
                                                 // generate key (once)
  pthread_key_create(&key, (void(*)(void*))free_me);
  for(int i=0; i < atoi(argv[1]); ++i){
   inc = i+1;                                    // can't cast an expr
   if (pthread_create(&thr_id[i],NULL,(void *(*)(void *))TSD,(void *)inc) > 0){
     cerr << "pthread_create failure" << endl;
     return 2;
   }
  }
                                                 // wait for all threads
  for(int i=0; i < argc-1; ++i)
    pthread_join(thr_id[i], NULL);
  sleep( 1 );
  return 0;
}
/*
   TSD routine - passed a value that it will keep private
*/
void *
TSD( int private_stuff ){
  static pthread_mutex_t  the_lock;
  void   *tsd = NULL;
  tsd = pthread_getspecific(key);                // initially NULL
  if (tsd == NULL) {
    tsd = new pthread_key_t;                     // create storage
    tsd = &private_stuff;                        // make the association
    pthread_setspecific(key, tsd);
    cout << pthread_self( ) << " TSD starts at \t "
         <<  *(int *)pthread_getspecific(key) << endl;
  }
  for( int i=0; i < 3; ++i ){
    sleep(1);
    pthread_mutex_lock(&the_lock);               // enter critical region
    cout << pthread_self( ) << " incrementing" << endl;
    *(int *)pthread_getspecific(key) *= 2;       // double private value
    cout << pthread_self( ) << " yielding" << endl;
    pthread_mutex_unlock(&the_lock);             // exit critical region
    sched_yield();                               // notify scheduler
  }
  cout << pthread_self( ) << " TSD finishes at \t "
       << *(int *)pthread_getspecific(key) << endl;
  cout.flush( );
  pthread_exit(NULL);
  return NULL;
}
/*
      Dummy destructor routine
*/
void
free_me( void *value ){
  cout << pthread_self( ) << " free reference to \t "
       << *(int *) value  << endl;
}
