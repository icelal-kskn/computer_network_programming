/*
   Using the environ pointer to display the command line
*/
#include <iostream>
using namespace std;
extern char **environ;
int
main( ){
  for (  ; *environ ; )
    cout << *environ++ << endl;
  return 0;
}
