#include <sys/types.h>
#include <sys/socket.h>
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>

#define PATH "./my_sock"
#define BUFSZ 128
