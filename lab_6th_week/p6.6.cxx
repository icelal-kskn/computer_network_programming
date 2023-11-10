/*
    A message queue manipulation utility
 */
#include "Message_que.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

typedef struct {
  long int m_type;
  char m_text[1024];
} MESSAGE;
extern char    *optarg;
extern int      optind, opterr, optopt;
int
main(int argc, char *argv[ ]){
  int      c;
  char     optstring[] = "sri:m:";
  opterr = 0;
  bool    snd_msg=false, get_msg=false, rmv_que=false;
  char    *the_message;
  //                                   Allocate msg - clear text
  MESSAGE my_msg;
  memset( my_msg.m_text, 0x0, 1024 );
  //                                   Allocate - acquire msg queue
  Message_que MQ('M');
  if ( !MQ.Exist('M') )
    MQ.Create( );
  else
    MQ.Acquire( );
  //                                   Process command line args
  while ((c = getopt(argc, argv, optstring)) != -1)
    switch (c) {
    case 's':
      snd_msg=true;
      break;
    case 'r':
      get_msg=true;
      break;
    case 'i':
      my_msg.m_type=atol(optarg);
      break;
     case 'm':
      strcpy(my_msg.m_text,optarg);
    }
  if ( snd_msg && my_msg.m_type > 0  ){
    MQ.Enque( &my_msg, strlen(my_msg.m_text)+1);
    cerr << "Added  : " << my_msg.m_text << endl;
  } else  if ( get_msg &&  my_msg.m_type > 0 ){
    MQ.Deque(&my_msg, 1024, my_msg.m_type);
    cerr << "Message: " << my_msg.m_text << endl;
  } else
    cerr << "Invalid command line option(s)" << endl;
  return 0;
}
