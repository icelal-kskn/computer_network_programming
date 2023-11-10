#include <ctype.h>

char *
change_case( char *s ){
  char *t = &s[0];
  while ( *t ){
    if ( isalpha(*t) )
      *t += islower(*t) ? -32 : 32;
    ++t;
  }
  return s;
} 
