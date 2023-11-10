/*
       Using the mmap system call
 */
#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
using namespace std;
int
main(int argc, char *argv[]){
  int          fd, changes, i, random_spot, kids[2];
  struct stat  buf;
  char         *the_file, *starting_string="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (argc != 3) {
    cerr << "Usage " << *argv << " file_name #_of_changes" << endl;
    return 1;
  }
  if ((changes = atoi(argv[2])) < 1) {
    cerr << "# of changes < 1" << endl;
    return 2;
  }
  if ((fd = open(argv[1], O_CREAT | O_RDWR, 0666)) < 0) {
    perror("file open");
    return 3;
  }
  write(fd, starting_string, strlen(starting_string));
                                       // Obtain size of file
  if (fstat(fd, &buf) < 0) {
    perror("fstat error");
    return 4;
  }
                                       // Establish the mapping
  if ((the_file = (char *) mmap(0, (size_t) buf.st_size,
                  PROT_READ | PROT_WRITE, MAP_SHARED,
                  fd, 0)) == (void *) - 1) {
    perror("mmap failure");
    exit(5);
  }
  for (i = 0; i < 2; ++i)
    if ((kids[i] = (int) fork()) == 0)
      while (1) {
        cout << "Child " << getpid() << " finds: " << the_file << endl;
        sleep(1);
      }
  srand((unsigned) getpid());
  for (i = 0; i < changes; ++i) {
    random_spot = (int) (rand() % buf.st_size);
    *(the_file + random_spot) = '*';
    sleep(1);
  }
  cout << "In parent, done with changes" << endl;
  for (i = 0; i < 2; ++i)
    kill(kids[i], 9);
  cout << "The file now contains: " << the_file << endl;
  return 0;
}
