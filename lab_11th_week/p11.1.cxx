/*
         Creating and joining threads
*/
#define _GNU_SOURCE
#define _REENTRANT
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;
int MAX=5;
inline int my_rand( int, int );
void       *say_it( void * );
int
main(int argc, char *argv[]) {
  pthread_t       thread_id[MAX];
  int     status, *p_status = &status;
  setvbuf(stdout, (char *) NULL, _IONBF, 0);
  if ( argc > MAX+1 ){                 // check arg list
    cerr << *argv << " arg1, arg2, ... arg" << MAX << endl;
    return 1;
  }
  cout << "Displaying" << endl;
  for (int i = 0; i < argc-1; ++i) {   // generate threads
   if( pthread_create(&thread_id[i],NULL,say_it,(void *)argv[i+1]) > 0){
     cerr << "pthread_create failure" << endl;
     return 2;
   }
  }
  for (int i=0; i < argc-1; ++i){      // wait for each thread
    if ( pthread_join(thread_id[i], (void **) p_status) > 0){
      cerr << "pthread_join failure" << endl;
      return 3;
    }
    cout << endl << "Thread " << thread_id[i] << " returns "
         << status;
  }
  cout << endl << "Done" << endl;
  return 0;
}
//   Display the word passed a random # of times
void *
say_it(void *word) {
  int numb = my_rand(2,6);
  cout << (char *)word << "\t to be printed " << numb
       << " times." << endl;
  for (int i=0; i < numb; ++i){
    sleep(1);
    cout << (char *) word << " ";
  }
  return (void *) NULL;
}
//   Generate a random # within given range
int
my_rand(int start, int range){
  struct timeval t;
  gettimeofday(&t, (struct timezone *)NULL);
  return (int)(start+((float)range * rand_r((unsigned *)&t.tv_usec))
               / (RAND_MAX+1.0));
}
