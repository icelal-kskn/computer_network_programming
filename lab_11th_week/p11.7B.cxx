#include "local_stack.h"
                                                 // previously declared
extern pthread_rwlock_t  *rw_ACCESS;             // RW lock
extern Stack   *S;                               // Stack
                                                 // remaining Stack methods
Stack::~Stack( ){                                // List destructor
  node *curr = head, *next;
  while( curr ){
    next = curr->next;
    delete curr;
    curr = next;
  }
  head = NULL;
}
void                                             // Display the list
Stack::Display( void ) const {
  node *temp = head;
  cout << "\t" << pthread_self() << " [head]" << endl;
  while( temp != NULL ){
     cout << "\t" << pthread_self() << " [" << temp->item
          << "]" << endl;
     cout.flush( );
     temp = temp->next;
     sleep(1);                                   // slow things down
  }
  cout << "\t" << pthread_self( ) << " [tail]" << endl;
}
void                                             // Add an item
Stack::Push( const char item ){
  node *temp = new node;
  temp->item = item;
  temp->next = head;
  head       = temp;
}
char                                             // Remove an item
Stack::Pop( void ){
  char item;
  node *temp = head;
  item = temp->item;
  head = temp->next;
  delete temp;
  return item;
}
int                                              // Random # in range
my_rand(int start, int range){
  struct timeval t;
  gettimeofday(&t, (struct timezone *)NULL);
  return (int)(start+((float)range * rand_r((unsigned *)&t.tv_usec))
               / (RAND_MAX+1.0));
}
void *
do_stack( void *junk ) {                         // Activity for thread
  char  item;
  sleep( my_rand(1,3) );                         // random start up time
  do {
    switch ( my_rand(1,10) ) {                   // choose value 1-10
    case 1: case 2:                              // Display 2/10
      pthread_rwlock_rdlock(rw_ACCESS);          // read lock - block on W
      cout << pthread_self( ) << " Display:" << endl;
      if ( S->StackEmpty( ) )
        cout << pthread_self( ) << " Empty list" << endl;
      else
        S->Display();
      pthread_rwlock_unlock(rw_ACCESS);          // unlock
      break;
    case 3: case 4: case 5:                      // Add item 3/10
      item = my_rand(1,25) + 64;
      pthread_rwlock_wrlock(rw_ACCESS);          // write lock - block on W|R
      cout << pthread_self( ) << " Push   : " << item << endl;
      S->Push( item );
      pthread_rwlock_unlock(rw_ACCESS);          // unlock
      break;
    case 6: case 7: case 8:                      // Remove item 3/10
      pthread_rwlock_wrlock(rw_ACCESS);          // write lock - block on W|R
      if (S->StackEmpty( ))
        cout << pthread_self( ) << " Underflow" << endl;
      else {
        cout << pthread_self( ) << " Pop    : ";
        item = S->Pop( );
        cout << pthread_self( ) << " " << item << endl;
      }
      pthread_rwlock_unlock(rw_ACCESS);          // unlock
      break;
    case 9:                                      // Sleep 1/10
      cout << pthread_self( ) << " Sleep  :" << endl;
      sleep( my_rand(1,3));
      break;
    case 10:                                     // Quit 1/10
      cout << pthread_self( ) << " Quit   :" << endl;
      return NULL;
    }
  } while ( 1 );
}
