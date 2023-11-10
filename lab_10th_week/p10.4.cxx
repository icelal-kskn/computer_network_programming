/*
     Checking host entries
*/
#include <iostream>
#include <cstdio>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>                // for inet_ntoa
#include <arpa/inet.h>
#include <string.h>                    // for memcpy
extern int h_errno;
using namespace std;
int
main(  ) {
  struct hostent *host;
  static char who[60];
  cout << "Enter host name to look up: ";
  cin  >> who;
  host = gethostbyname( who );
  if ( host != (struct hostent *) NULL ) {
    cout << "Here is what I found about " << who << endl;
    cout << "Official name : " <<  host->h_name  << endl;
    cout << "Aliases       : ";
    while ( *host->h_aliases ) {
      cout << *host->h_aliases << " ";
      ++host->h_aliases;
    }
    cout << endl;
    cout << "Address type  : " << host->h_addrtype << endl;
    cout << "Address length: " << host->h_length   << endl;
    cout << "Address list  : ";
    struct in_addr in;
    while ( *host->h_addr_list ) {
      memcpy( &in.s_addr, *host->h_addr_list, sizeof (in.s_addr));
      cout << "[" << *host->h_addr_list << "] = "
           << inet_ntoa(in) << " ";
      ++host->h_addr_list;
    }
    cout << endl;
  } else
    herror(who);
  return 0;
}
