/*
   INTER process main (multiple processes - 1 thread each)
   Compile: g++  p11.5.PC.cxx  p11.5.INTER.cxx  -lpthread -o INTER
*/
#include "local_mutex.h"
pthread_mutex_t  *m_LOCK;                        // Shared memory pointer
int              m_shmid, i_shmid,               // Shared memory ID's
                 *s_shm, *c_shm;                 // Shared setup and counter
int
main(int argc, char *argv[]) {
  pthread_mutexattr_t  the_attr_obj;             // attribute object
  int  i, n;
  if ( argc != 2) {
    cerr <<  "Usage: " << *argv << " n_workers" << endl;
    return 1;
  }
  n = atoi(argv[1]) < MAX ? atoi(argv[1]) : MAX;
  if((m_shmid=shmget(IPC_PRIVATE,sizeof(pthread_mutex_t),IPC_CREAT|0666))< 0){
    perror("shmget fail mutex");
    return 2;
  }
  if ((m_LOCK=(pthread_mutex_t *)shmat(m_shmid,0,0)) == (pthread_mutex_t *) -1){
    perror("shmat fail mutex");
    return 3;
  }
  if ((i_shmid=shmget(IPC_PRIVATE,sizeof(int)*2,IPC_CREAT|0666))<0){
    perror("shmget fail ints");
    return 4;
  }
  if ((s_shm=(int *) shmat(i_shmid, 0, 0)) == (int *) -1){
    perror("shmat ints");
    return 5;
  }
  c_shm  = s_shm + sizeof(int);                  // reference  correct loc
  *s_shm = *c_shm = 0;                           // start counter (offset)
  pthread_mutexattr_init( &the_attr_obj);        // initialize attrib obj
  for( i=0; i < n; ++i)
    if ( fork() == 0 ){                          // generate child process
      do_work( );                                // child process does work
      exit( 2 );
    }
  while( (n = (int) wait( NULL)) && n != -1 )    // wait for child processes
                ;
  shmdt((char *) m_LOCK);                        // cleanup shared memory
  shmdt((char *) s_shm);
  shmctl(m_shmid, IPC_RMID, (struct shmid_ds *) 0);
  shmctl(i_shmid, IPC_RMID, (struct shmid_ds *) 0);
  cout << "Contents of " << BUFFER               // show contents of buffer
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
