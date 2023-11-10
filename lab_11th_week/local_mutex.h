/*
     Common local header file: local_mutex.h
*/
#ifndef LOCAL_MUTEX_H
#define LOCAL_MUTEX_H
#define _GNU_SOURCE
#define _REENTRANT
#include <iostream>
#include <cstdio>
#include <pthread.h>
#include <fstream.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
                                                // When we share a mutex
#include <sys/ipc.h>                            // we will need these.
#include <sys/shm.h>
static const char *BUFFER="./buffer";
static const int MAX=99;
void do_work( void );
using namespace std;
#endif
