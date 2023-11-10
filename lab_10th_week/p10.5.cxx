/*
     Checking service -- port entries for a host
*/
#include <iostream>
#include <cstdio>
#include <netdb.h>
using namespace std;
int
main( ) {
  struct servent *serv;
  static char protocol[10], service[10];
  cout << "Enter service to look up : ";
  cin  >> service;
  cout << "Enter protocol to look up: ";
  cin  >> protocol;
  serv = getservbyname( service, protocol );
  if ( serv != (struct servent *)NULL ) {
    cout << "Here is what I found " << endl;
    cout << "Official name  : " << serv->s_name << endl;
    cout << "Aliases        : ";
    while ( *serv->s_aliases ) {
      cout << *serv->s_aliases << " ";
      ++serv->s_aliases;
      }
    cout << endl;
    cout << "Port number    : " << ntohs(serv->s_port) << endl;
    cout << "Protocol Family: " << serv->s_proto << endl;
  } else
    cout << "Service " << service << " for protocol "
         <<  protocol  << " not found." << endl;
  return 0;
}
