/*
   Displaying the contents of argv[ ] (the command line)
*/
#include <iostream>
using namespace std;
int
main(int argc, char *argv[ ]){
  for ( ; *argv; ++argv )
    cout <<  *argv << endl;
  return 0;
}
