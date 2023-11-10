/*
       Using semaphores with threads
*/
#define _GNU_SOURCE
#define _REENTRANT
#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>                           // for POSIX semaphores
using namespace std;
const int BUF_SIZE= 15;
const int MAX     = 4;
int   world_state = 1;
sem_t check_state;
typedef struct {
        char word[BUF_SIZE];
        int  my_state;
} Info;
void *speaker( Info * );
//   Generate a random # within given range
int
my_rand(int start, int range){
  struct timeval t;
  gettimeofday(&t, (struct timezone *)NULL);
  return (int)(start+((float)range * rand_r((unsigned *)&t.tv_usec))
               / (RAND_MAX+1.0));
}
int
main( int argc, char *argv[] ){
  pthread_t t_ID[MAX];
  Info     words[MAX];
  if ( argc != MAX+1 ) {
     cerr << "Usage " << *argv << " word1 ... word" << MAX << endl;
     return 1;
  }
  sem_init( &check_state, 0, 1 );      // start semaphore at 1
  for (int i = 0; i < MAX; ++i){
    strcpy( words[i].word, argv[i+1] );
    words[i].my_state = i+1;
    if ( (pthread_create( &t_ID[i],NULL,
       ( void *(*)(void *) )speaker,(void *) &words[i])) != 0 ) {
     perror("Thread create speaker");
     return i;
     }
  }
  pthread_join( t_ID[MAX-1], (void **) NULL);
  cout << "!" << endl;
  return 0;
}
/*
   Display the passed in word
*/
void  *
speaker( Info * s ){
  while( true ) {
    sleep(my_rand(1,3));
    sem_wait( &check_state );          // obtain & decrement else block
    cout << s->word << " ";
    cout.flush( );
    if ( s->my_state == world_state ) {
      ++world_state;
      if ( world_state > MAX ) break;
    } else {
      cout << endl;
      world_state = 1;
    }
    sem_post( &check_state );          // release & increment
  }
  return( (void *) NULL );
}
