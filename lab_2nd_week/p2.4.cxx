/*
   Using sysconf to display system limits
 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <unistd.h>
using namespace std;
int
main(  ){
  char *limits[ ]={"Max size of argv + envp",
                   "Max # of child processes",
                   "Ticks / second",
                   "Max # of streams",
                   "Max # of bytes in a TZ name",
                   "Max # of open files",
                   "Job control supported?",
                   "Saved IDs supported?",
                   "Version of POSIX supported",
                    0};
  int constant[ ]={ _SC_ARG_MAX,    _SC_CHILD_MAX,
                    _SC_CLK_TCK,    _SC_STREAM_MAX,
                    _SC_TZNAME_MAX, _SC_OPEN_MAX,
                    _SC_JOB_CONTROL,_SC_SAVED_IDS,
                    _SC_VERSION };
  for (int i=0; limits[i]; ++i) {
    cout << setw(30) << limits[i] << "\t"
         << sysconf(constant[i])  << endl;
  }
  return 0;
}
