/*
    Message queue implementation - Copyright (c) 2002  J. S. Gray
*/
#include "Message_que.h"
#include <cstdio>

// Message queue constructor.
Message_que::Message_que( const char the_key ){
  ipckey = ftok( ".", the_key );
  msqid  = -1;
}
// Remove the message Queue (if this process created it)
void
Message_que::Remove(  ) {
  if ( msgctl( msqid, IPC_RMID, (struct msqid_ds *) 0 ) == -1 )
    exit( 5 );
}
// Place a message in the message queue.
void
Message_que::Enque( void *msg, int msg_size ){
  if ( msgsnd( msqid, msg, msg_size, 0 ) == -1 )
    exit( 3 );
}
// Return a message from the message queue.
int
Message_que::Deque( void *msg, int msg_size, int msg_type ){
  int n;
  memset( msg, 0x0, msg_size );        // clear space
  if ( (n=msgrcv( msqid, msg, msg_size, msg_type, IPC_NOWAIT)) == -1 )
    exit( 4 );
  return n;
}
//   True if message queue exists else false.
bool
Message_que::Exist( const char the_key ){
  return (msgget(ipckey, 0) != -1);
}
//   Generate a new message queue.
void
Message_que::Create( ){
  if ( (msqid=msgget(ipckey, IPC_CREAT|0660)) == -1 )
    exit( 1 );
}
//   Acquire (gain access to) existing message queue.
void
Message_que::Acquire( ){
  if ( (msqid=msgget(ipckey, 0)) == -1 )
    exit( 2 );
}
