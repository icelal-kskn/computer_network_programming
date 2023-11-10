/*
  Using putenv to modify the environment as seen by parent - child 
*/
#define _GNU_SOURCE
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
using namespace std;
extern char **environ;
int show_env( char ** );
int
main( ){
  int numb;
  cout << "Parent before any additions **********" << endl;
  show_env( environ );
  putenv("PARENT_ED=parent");
  cout << "Parent after one addition   **********" << endl;
  show_env( environ );
  if ( fork( ) == 0 ){                 // In the CHILD now
    cout << "Child before any additions *********" << endl;
    show_env( environ );
    putenv("CHILD_ED=child");
    cout << "Child after one addition   *********" << endl;
    show_env( environ );
    return 0;
  }                                    // In the PARENT now
  sleep( 10 );                         // Make sure child is done
  cout << "Parent after child is done  **********" << endl;
  numb = show_env( environ );
  cout << "... and at address [" << hex << environ+numb
       << "] is ... "
       << (*(environ+numb) == NULL ? "Nothing!" : *(environ+numb))
       << endl;
  return 0;
}
/*
   Display the contents of the passed list ... return number found
*/
int show_env( char **cp ){
  int i;
  for (i=0; *cp; ++cp, ++i)
    cout << "[" << hex << cp << "] " << *cp << endl;
  return i;
}
