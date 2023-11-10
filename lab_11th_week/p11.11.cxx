/*
     Debugging multithreaded prgrms - WITH LOCKING ERRORS
     Compile: g++ p11.11.cxx -lpthread -o p11.11
*/
#define _REENTRANT
#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
const int  MAX=5,
           HOME=25;
int
my_rand(int start, int range){
  struct timeval t;
  gettimeofday(&t, (struct timezone *)NULL);
  return (int)(start+((float)range * rand_r((unsigned *)&t.tv_usec))
               / (RAND_MAX+1.0));
}
typedef struct {
  int increment;
  char *phrase;
} argument;
void  step( void * );
                                                 // common to all threads
pthread_t       thread_id[MAX];
bool            alive = true, home = false;
int             position,total=0;
char   walk[] = "     |     | ";
int
main(int argc, char *argv[]) {
  argument right={ +1, "ZOINK! Stepped off the RIGHT side.\n"},
           left ={ -1, "SPLAT! Stepped off the LEFT side.\n"};
  pthread_attr_t attr_obj;
  if (argc < 2) {                            /* check arg list       */
    cerr <<  *argv << " start_position" << endl;
    return 1;
  }
  position = atoi(argv[1]);
  if ( position < 1 )
     position = 1;
  else if ( position > MAX )
     position = MAX;
  walk[position+5] = '*';
  setvbuf(stdout, (char *) NULL, _IONBF, 0);
  cout << "The drunken sailor walk" << endl << endl;
  cout << "     +12345+" << endl;
  cout << walk << endl;
  pthread_attr_init( &attr_obj );
  pthread_attr_setdetachstate( &attr_obj, PTHREAD_CREATE_DETACHED );
  pthread_create(&thread_id[0], &attr_obj,
                 (void *(*) (void *)) step, (void *) &right);
  pthread_create(&thread_id[1], &attr_obj,
                 (void *(*) (void *)) step, (void *) &left );
  pthread_exit(NULL);
  return 0;
}
void
step( void *a ) {
  argument *my_arg=(argument *)a;
  do {
    sleep( my_rand(1,3) );                       // pause a bit
    walk[position+MAX] = ' ';                    // clear old position
    position += my_arg->increment;               // calculate new position
    alive = bool(position > 0  && position <= MAX);
    walk[position+MAX] = alive ? '*' : '$';
    cout << walk << endl;
    home = bool(++total >= HOME);
    if ( !alive || home ) {
      if ( !alive )
        cout << my_arg->phrase;
      else
        cout << "The sailor made it home safely this time!\n";
      pthread_kill(thread_id[ (position < 1 ? 1 : 0)], 9);
    }
    sched_yield( );
  } while ( alive && !home );
}
