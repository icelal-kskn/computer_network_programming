/*
       p11.10.cxx: Thread animation
       Compile   : g++ -o p11.10  p11.10.cxx  -lpthread
*/
#include "local_TSD.h"
int
main(int argc, char *argv[]) {
  char        the_screen[ROW][COL];
  pthread_t   thread_id[MAX];
  int         fd0, n_threads;
  struct stat buf;
  if (argc != 3) {                               // check cmd line
    cerr << "Usage " << *argv <<  " file_name #_threads" << endl;
    return 1;
  }
  if ((n_threads = atoi(argv[2])) > MAX ) {
    cerr << "# threads must be < " <<  MAX+1 << endl;
    return 2;
  }
  setbuf(stdout, NULL);
  guys[n_threads] = '\0';
  memset(the_screen, ' ', sizeof(the_screen));   // clear screen array
                                                 // open file for mapping
  if ((fd0 = open(argv[1], O_CREAT | O_RDWR, 0666)) < 0) {
    cerr << "Open error on file " << argv[1] << endl;
    return 3;
  }                                              // write screen to file
  write(fd0, the_screen, sizeof(the_screen));
  if (fstat(fd0, &buf) < 0) {                    // stats on mapped file
    cerr << "fstat error on file " << the_file << endl;
    return 4;
  }                                              // establish the mapping
  if ((the_file =(char *) mmap(0, (size_t) buf.st_size, PROT_READ | PROT_WRITE,
                       MAP_SHARED, fd0, 0)) ==  NULL) {
    cerr << "mmap failure" << endl;
    return 5;
  }
  CLS( );                                        // clear the display
  for (int i=0; i < n_threads; ++i) {            // generate the threads
    pthread_create( &thread_id[i], NULL, play, (void *)i);
  }
  do {                                           // in main thread
    sleep(1);                                    // pause a bit
    pthread_mutex_lock( &scrn_lock);
      display_screen(the_file);                  // display screen
    pthread_mutex_unlock( &scrn_lock);
  } while (n_dead < n_threads);                  // while threads left
  for(int i=0; i < n_threads; ++i)
    pthread_join( thread_id[i], (void **) NULL);
  LOCATE(25, 1);
  close(fd0);
  return 0;
}
/*
      Play the game by moving a character around the grid
*/
void *
play( void *numb ){
  static pthread_mutex_t  the_lock;              // single copy of these
  static pthread_key_t    the_key;
  static int              first_time = 1;
  int                     row, col;              // local to each invocation
  char                    pch;
  void                    *my_let = NULL;        // thread specific data
  if ( first_time ) {
    pthread_mutex_lock( &the_lock );
    if ( first_time ) {
      pthread_key_create( &the_key, NULL );
      first_time = 0;
    }
    pthread_mutex_unlock( &the_lock );
  }
  if ( (my_let = pthread_getspecific( the_key )) == NULL ) {
    my_let = (int *) &numb;
    pthread_setspecific( the_key, my_let );      // associate with key
  }
  row=my_rand(1,ROW)-1;                          // start at random location
  col=my_rand(1,COL)-1;
  pch = (char) (65+*(int *)pthread_getspecific(the_key));
  do {
    move(the_file, &row, &col, pch);             // move around
  } while( !boxed( the_file, row, col));         // while not boxed in
  n_dead++;                                      // update terminated threads
  guys[*(int *)pthread_getspecific(the_key)] = '*';
  pthread_mutex_lock( &scrn_lock );
    LOCATE(1, 1);
    cout << "Dead = " << n_dead << "[" << guys << "]";
  pthread_mutex_unlock( &scrn_lock );
  return NULL;
}
/*
       Find and move to new location.
*/
void
move(char *s, int *r, int *c, char pch) {
  int       old_offset = (*r * COL + *c),
            new_offset = -1;
  DIRECTION d;
  neighbors( *r, *c, &d );                       // get neighbor locations
  do {
    if ( my_rand(1,3) == 1 ) sleep(1);           // 1/3 time sleep first
    switch ( my_rand(1,4) ) {
    case 1:
      if ( *(s + d.left )  == ' ' ) new_offset = d.left;
      break;
    case 2:
      if ( *(s + d.right ) == ' ' ) new_offset = d.right;
      break;
    case 3:
      if ( *(s + d.top   ) == ' ' ) new_offset = d.top;
      break;
    case 4:
      if ( *(s + d.bot   ) == ' ' ) new_offset = d.bot;
      break;
    }
  } while( new_offset == -1 );
  *r = new_offset / COL;
  *c = new_offset % COL;
  *(s + new_offset) = pch;                       // assign new location
  if ( *(s + old_offset) != '@' )                // if its not a start loc
    *(s + old_offset) += 32;                     // change old loc to LC
}
/*
      Display the screen using VT100 escape codes for cursor placement.
*/
void
display_screen(char *s) {
  static int   pass = 1;
  static char  buffer[COL + 1];
  LOCATE(1, 33);
  cout << "Thread World";
  LOCATE(2, 18);
  cout << "+------------------------------------------+";
  for (int i=3; i < 23; ++i) {
    LOCATE(i, 18);                               // move to screen location
    strncpy(buffer, (s + (i - 3) * COL), COL);   // get output segment
    cout << "|" << buffer << "|";
  }
  LOCATE(23, 18);
  cout << "+------------------------------------------+";
  LOCATE(24, 20);
  cout << "Pass " << ++pass;
}
/*
       Check neighbors to see if any free locations are left
*/
bool
boxed(char *s, int r, int c) {
  DIRECTION d;
  neighbors( r, c, &d );                         // get my neighbors
  return ( *(s+d.left) != ' ' && *(s+d.right) != ' ' &&
           *(s+d.bot ) != ' ' && *(s+d.top  ) != ' ');
}
/*
       Calculate the surrounding locations
*/
void
neighbors( int row, int col, DIRECTION *d ){
  d->left  =  row * COL + (col > 0 ? col - 1 : COL - 1);
  d->right =  row * COL + (col > COL - 2 ? 0 : col + 1);
  d->top   =  (row > 0 ? row - 1 : ROW - 1) * COL + col;
  d->bot   =  (row > ROW - 2 ? 0 : row + 1) * COL + col;
}
