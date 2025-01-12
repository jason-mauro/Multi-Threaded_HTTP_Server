#ifndef FILE_SERVE_H
#define FILE_SERVE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "word_game.h"
#include "server.h"

extern const char* base_directory;

void serve_file(const char* path, const int clientfd);

#endif //FILE_SERVE_H
