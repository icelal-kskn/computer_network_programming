/*
    Displaying the contents of the TERM variable
 */
#include <iostream>
#include <cstdlib>
using namespace std;
int
main( ){
  char  *c_ptr;
  c_ptr = getenv("TERM");
  cout << "The variable TERM is "
       << (c_ptr==NULL ?  "NOT found" : c_ptr)
       << endl;
  return 0;
}
