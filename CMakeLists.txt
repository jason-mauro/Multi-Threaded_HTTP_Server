cmake_minimum_required(VERSION 3.22.1)
project(Webserver C)

set(CMAKE_C_STANDARD 23)

include_directories(include)

add_executable(Webserver
        src/server.c
        src/request_handler.c
        src/file_serve.c
        src/word_game.c
        src/file_serve.c
        include/file_serve.h
        include/server.h
        include/server.h
        include/request_handler.h
        src/main.c
        include/main.h
)
