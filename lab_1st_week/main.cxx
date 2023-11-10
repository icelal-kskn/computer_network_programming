#include <iostream>
#include "my_demo.h"
using namespace std;
int
main( ) {
  int start, stop;
  char b[20];                          // temp string buffer

  cout << "Enter start and stop value for string: ";
  cin  >> start >> stop;
  cout << "Created string  : " << ascii(start, stop) << endl;
  cin.ignore(80,'\n');
  cout << "Enter a string  : ";
  cin.getline(b,20);
  cout << "Converted string: " << change_case( b ) << endl;
  return 0;
}
