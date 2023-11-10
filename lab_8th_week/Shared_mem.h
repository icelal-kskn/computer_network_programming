/*
  A VERY simplified shared memory class for use in a std UNIX
  environment.  See the text for instructions on how to use
  this class.  Copyright (c) 2002 J. S. Gray
  
  Exit codes for class operations:
  
  1 - Unable to allocate memory      2 - Unable map memory
  3 - Could not remove shared memory
*/
#pragma interface
#ifndef Shared_mem_h
#define Shared_mem_h
#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;
template <class S_type>         // Allow for different data types
class Shared_mem {
  public:
    Shared_mem ( );             // Constructor
    ~Shared_mem( );             // Destructor - remove shared memory
    void   Put( const S_type ); // Assign value to shared memory
    S_type Get(  );             // Return value from shared memory

  private:
    int    shmid;               // ID of shared memory
    S_type *shm_ptr;            // Reference to shared memory
    pid_t  my_pid;              // Hang on to originator PID
};
#endif
