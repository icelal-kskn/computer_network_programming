/*
   Changing scheduling parameters.
*/
#define _GNU_SOURCE
#define _REENTRANT
#include <iostream>
#include <cstdio>
#include <cstring>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
using namespace std;
char *p[] = {"OTHER ","FIFO ","RR "};
struct parameter {                               // data to pass
  int   policy;                                  // new policy
  int   priority;                                // new priority
};
void *threadfunc( void *);
int
main( ) {
  pthread_t        t_id;
  struct parameter parm;
  int              status;
  setvbuf(stdout, (char *)NULL, _IONBF, 0);      // non-buffered output
  for( int i=0; i < 3; ++i ){                    // display limits
    cout << "Policy SCHED_" << p[i] << "\t MAX = "
         << sched_get_priority_max(i);
    cout << " MIN = " << sched_get_priority_min(i) << endl;
    parm.policy  = i;                            // assign data to pass
    parm.priority= (i+1) * 2;                    // make up a priority
    status=pthread_create( &t_id, NULL, threadfunc, (void *)&parm );
    sleep(1);
  }
  return 0;
}
void *
threadfunc( void *d ) {
  struct    sched_param  param;                  // local to this function
  int       policy;
  parameter *p_ptr=(parameter *)d;               // cast to access
  param.sched_priority = p_ptr->priority;        // passed data value
                                                 // set new scheduling
  pthread_setschedparam(pthread_self(), p_ptr->policy, &param );
  memset(&param, 0, sizeof(param));              // clear
                                                 // retrieve
  pthread_getschedparam(pthread_self(), &policy, &param );
  cout << "In thread with policy = SCHED_" << p[policy]
       << " \tpriority = " << (param.sched_priority)
       << " effective ID = " << geteuid() << endl;
  return NULL;
}
