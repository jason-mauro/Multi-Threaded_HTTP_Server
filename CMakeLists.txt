cmake_minimum_required(VERSION 3.22.1)
project(server C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
# Copy resources directory to the build folder
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})


add_executable(server
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
