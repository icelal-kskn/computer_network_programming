/*
    Using a condition variable
*/
#define _GNU_SOURCE
#define _REENTRANT
#include <iostream>
#include <cctype>
#include <pthread.h>
using namespace std;
const int MAX=5;
                                                 // global
pthread_mutex_t lock_it  = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  write_it = PTHREAD_COND_INITIALIZER;
typedef struct {                                 // a small data buffer
  char            buffer[MAX];                   // the buffer
  int             how_many;                      // # of chars in buffer
} BUFFER;
BUFFER         share = {"", 0};                  // start as empty
void           *read_some (void *),
               *write_some(void *);
bool           finished = false;using namespace std;
int
main( ) {
pthread_t       t_read,
                t_write;                         // TID's
                                                 // create the threads
  pthread_create(&t_read,  NULL, read_some, (void *) NULL);
  pthread_create(&t_write, NULL, write_some,(void *) NULL);
                                                 // wait for the writer                    
  pthread_join(t_write, (void **) NULL);
  pthread_mutex_destroy( &lock_it  );            // clean up
  pthread_cond_destroy(  &write_it );
  return 0;
}
//        Code to fill the buffer
void *
read_some(void * junk) {
  char  ch;
  cout << "R " << pthread_self( ) << "\t: Starting" << endl;
  while (!finished) {
    pthread_mutex_lock(&lock_it);
    if (share.how_many != MAX) {                 // buffer not full
      cin.get(ch);
      if ( cin.fail( ) ) {                       // end-of-file
        share.buffer[share.how_many] = (char)NULL;
        share.how_many = MAX;
        finished       = true;                   // we are all done
        cout << "R " << pthread_self( ) << "\t: Signaling done" << endl;
        pthread_cond_signal(&write_it);          // signal condition var
        pthread_mutex_unlock(&lock_it);
        break;
      } else {                                   // sanitize input chars
        share.buffer[share.how_many] =  isalnum(ch) ? ch : '#';
        cout << "R " << pthread_self( ) << "\t: Got char ["
                     << share.buffer[share.how_many++] << "]" << endl;
        if ( share.how_many == MAX ) {           // if full
          cout << "R " << pthread_self( ) << "\t: Signaling full" << endl;
          pthread_cond_signal(&write_it);
        }
      }
    }
    pthread_mutex_unlock(&lock_it);
  }
  cout << "R " << pthread_self( ) << "\t: Exiting" << endl;
  return NULL;
}
//    Code to write (display) buffer
void *
write_some(void *junk) {
  int i;
  cout << "W " << pthread_self( ) << "\t: Starting" << endl;
  while (!finished ) {
    pthread_mutex_lock(&lock_it);
    cout << "W " << pthread_self( ) << "\t: Waiting" << endl;
    while (share.how_many != MAX)                // while not full
      pthread_cond_wait(&write_it, &lock_it);    // wait for notify
    cout << "W " << pthread_self( ) << "\t: Writing buffer" << endl;
    for( i=0; share.buffer[i] && share.how_many; ++i, share.how_many--)
      cout.put(share.buffer[i]);
    cout.put('\n');
    pthread_mutex_unlock(&lock_it);
  }
  cout << "W " << pthread_self( ) << "\t: Exiting" << endl;
  return NULL;
}
