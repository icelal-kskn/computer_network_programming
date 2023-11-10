/*
   Local include file for socket programs
*/
#ifndef LOCAL_SOCK_H
#define LOCAL_SOCK_H
#define _GNU_SOURCE
#include <iostream>
#include <sys/ioctl.h>
#include <cstdio>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
const  int  PORT=2002;                 // Arbitrary port programmer chooses
static char buf[BUFSIZ];               // Buffer for messages
const  char *SERVER_FILE="server_socket";
#endif
using namespace std;
