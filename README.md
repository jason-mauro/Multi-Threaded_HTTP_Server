# Multi-Threaded HTTP Server Project

This project is a simple HTTP server written in C, using socket programming and multi-threading to handle requests. It binds, listens, and accepts connections on a specified port and serves files based on the request. The server also has a built-in game made in C which allows the user to play a word guessing game in the browser when they navigate to the "/words" url. The server handles all the code for the game a serves HTML and CSS to display the game. The code is split into multiple files for simplicity and uses CMake to create the build.


## Project Structure

```
project/
|-- include/
|  |- file_serve.h          # Haeder for file serve
|  |- main.h                # Header for main
|  |- request_handler.h     # Header for request handler
|  |- server.h              # Header for server
|  |- word_game.h           # Header for word game
|- src/
|  |- file_serve.c          # Serves files and game
|  |- main.c                # Main server program
|  |- request_handler.c     # Handles client connections
|  |- server.c              # Server setup
|  |- word_game.c           # Word Game program
|- CMakeLists.txt          # Build configuration

```
### Files
