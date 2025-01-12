#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>

#include "request_handler.h"
#include "file_serve.h"

#define PORT "8000"

int server_setup();
#endif //SERVER_H
