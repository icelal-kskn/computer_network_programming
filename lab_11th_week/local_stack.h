/*
     Common local header file: local_stack.h 
*/
#ifndef  LOCAL_STACK_H
#define  LOCAL_STACK_H
#define  _GNU_SOURCE
#define  _REENTRANT
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
using namespace std;
const int MAX=6;
class Stack {
   public:
              Stack     ( ) : head( NULL ) {}
              ~Stack    ( );
      bool    StackEmpty( void ) const { return (head == NULL); }
      void    Display   ( void ) const ;
      void    Push      ( const char );
      char    Pop       ( void );
   private:
      struct node {
         char         item;
         struct node *next;
      };
      node *head;
};
#endif
