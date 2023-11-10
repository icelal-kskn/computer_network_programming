/*
   Using getrlimt to display system resource limits
 */
#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include <sys/resource.h>
using namespace std;
int
main( ){
  struct rlimit plimit;
  char  *label[ ]={"CPU time", "File size",
                   "Data segment", "Stack segment",
                   "Core size","Resident set size",
                   "Number of processes", "Open files",
                   "Locked-in-memory", "Virtual memory",
                   0};
  int constant[]= { RLIMIT_CPU    , RLIMIT_FSIZE,
                    RLIMIT_DATA   , RLIMIT_STACK,
                    RLIMIT_CORE   , RLIMIT_RSS,
                    RLIMIT_NPROC  , RLIMIT_NOFILE,
                    RLIMIT_MEMLOCK, RLIMIT_AS };

  for (int i = 0; label[i]; ++i) {
    getrlimit(constant[i], &plimit);
    cout << setw(20) << label[i] << "\t Current: "
         << setw(10) << plimit.rlim_cur << "\t Max: "
         << setw(10) << plimit.rlim_max << endl;
  }
  return 0;
}

