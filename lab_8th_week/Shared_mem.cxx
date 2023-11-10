#pragma implementation
/*
    Shared memory implementation -  Copyright (c) 2002 J. S. Gray
    Compile with: -fexternal-templates
 */
#include "Shared_mem.h"
                                       // Generate private mem segment
template <class S_type>                // Generalize data type
Shared_mem<S_type>::Shared_mem(  ){
  my_pid = getpid( );           // Save PID of creating process
  if ((shmid = shmget(IPC_PRIVATE, sizeof(S_type), IPC_CREAT | 0660)) < 0)
    exit(1);
  if ((shm_ptr = (S_type *) shmat(shmid, NULL, 0)) == NULL)
    exit(2);
}
                                       // Remove memory if creator
template <class S_type>
Shared_mem<S_type>::~Shared_mem(  ) {
  if ( getpid( ) == my_pid ) {
    shmdt( (char *) shm_ptr );
    if ( shmctl(shmid, IPC_RMID, (struct shmid_ds *) 0) == -1 )
      exit( 3 );
  }
}
                                       // Assign value to this location
template <class S_type>
void
Shared_mem<S_type>::Put( const S_type stuff  ){
  *shm_ptr = stuff;
}
                                       // Retrieve value from location
template <class S_type>
S_type
Shared_mem<S_type>::Get(  ){
  static S_type stuff;
  stuff = *shm_ptr;
  return stuff;
}
                                       // Force instantiation
typedef Shared_mem<int>    Shared_int;
typedef Shared_mem<char>   Shared_char;
typedef Shared_mem<float>  Shared_float;
typedef Shared_mem<double> Shared_double;

