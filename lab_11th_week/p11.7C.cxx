#include "local_stack.h"
                                                 // global by placement
pthread_rwlock_t *rw_ACCESS=new pthread_rwlock_t;
Stack            *S=new Stack;
void *do_stack( void * );
int
main( int argc, char *argv[] ){
  int  i, n;
  pthread_t worker[MAX];
  pthread_rwlock_init(rw_ACCESS, NULL);
  if ( argc != 2) {
    cerr << "Usage: " << *argv << " n_workers" << endl;
    return 1;
  }
  n = atoi(argv[1]) < MAX ? atoi(argv[1]) : MAX;
  for( i=0; i < n; ++i )                         // create threads
    pthread_create(&worker[i],NULL,do_stack,(void *) NULL);
  for( i=0; i < n; ++i )                         // wait
    pthread_join(worker[i], (void **) NULL);
  return 0;
}
