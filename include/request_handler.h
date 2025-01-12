#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "file_serve.h"
#include "word_game.h"

void* handle_connection(void* socketfd);

#endif //REQUEST_HANDLER_H
