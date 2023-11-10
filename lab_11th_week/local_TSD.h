/* local header file for example p11.10.cxx
 */
#define _REENTRANT
#define _GNU_SOURCE
#include <pthread.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/mman.h>
using namespace std;
const int  ROW=20, COL=42, MAX=10;
const char ESC='\033';
inline
void LOCATE(int row, int col){
  cout << ESC << "[" << row << ";" << col << "H";
}
inline
void CLS( ){
  LOCATE(1, 1);
  cout << ESC << "[2J";
}
int
my_rand(int start, int range){
  struct timeval t;
  gettimeofday(&t, (struct timezone *)NULL);
  return (int)(start+((float)range * rand_r((unsigned *)&t.tv_usec))
               / (RAND_MAX+1.0));
}
typedef struct {
   int left, right, top, bot;
}  DIRECTION;
static char     guys[] = "ABCDEFGHIJ";
int             n_dead = 0;
char            *the_file;
pthread_mutex_t scrn_lock;
                                                 // function prototypes
void            display_screen(char *);
bool            boxed(char *, int, int);
void            move(char *, int *, int *, char);
void            neighbors( int , int , DIRECTION * );
void            *play( void * );
