/*
    Using ftok to generate key values
 */
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
using namespace std;
int
main( ){
  key_t key;
  for (char i = 'a'; i <= 'd'; ++i) {
    key = ftok(".", i);
    cout << "proj = " << i << " key = [" << hex << key
         << "] MSB = " << char(key >> 24) << endl;
  }
  return 0;
}
