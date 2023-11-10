/*
     Program 1.1 modified to display identifier addresses
 */
#include <iostream>
#include <unistd.h>                    // needed for write
#include <cstring>                     // needed for strcpy
#include <cstdlib>                     // needed for exit
using namespace std;
char           *cptr = "Hello World\n";// static by placement
char            buffer1[25];
  
inline void SHW_ADR(char *ID,  int address){
  cout << "The id " << ID << "\t is at : "
       << hex << address << endl;
}
extern int etext, edata, end;
  
int main( ){
  void            showit(char *);      // function prototype
  int             i = 0;               // automatic variable
                                       // display addresses
  cout << "Adr etext: " << hex << int(&etext) << "\t ";
  cout << "Adr edata: " << hex << int(&edata) << "\t ";
  cout << "Adr end: "   << hex << int(&end  ) << "\n";
  SHW_ADR("main", int(main));          // function addresses
  SHW_ADR("showit", int(showit));
  SHW_ADR("cptr", int(&cptr));         // static
  SHW_ADR("buffer1", int(&buffer1));
  SHW_ADR("i", int(&i));               // automatic
 
  strcpy(buffer1, "A demonstration\n");// library function
  write(1, buffer1, strlen(buffer1)+1);// system call
  showit(cptr);                        // function call
  return 0;
}
void showit( char *p ){
  char           *buffer2;
  SHW_ADR("buffer2", int(&buffer2));   // display address
  
  if ((buffer2= new char[ strlen(p)+1 ]) != NULL){
    strcpy(buffer2, p);                // copy the string
    cout << buffer2;                   // display string
    delete [] buffer2;                 // release location
  } else {
    cerr << "Allocation error.\n";
    exit(1);
  }
}
