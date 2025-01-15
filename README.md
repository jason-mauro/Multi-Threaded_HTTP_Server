# Multi-Threaded HTTP Server Project

This project is a simple HTTP server written in C, using socket programming and multi-threading to handle requests. It binds, listens, and accepts connections on a specified port and serves files based on the request. The server also has a built-in game made in C which allows the user to play a word guessing game in the browser when they navigate to the "/words" url. The server serves files by default from the **`files`** directory. The server handles all the code for the game a serves HTML and CSS to display the game. The code is split into multiple files for simplicity and uses CMake to create and manage the build.


## Project Structure

```
project/
|- include/
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
|- CMakeLists.txt           # Build configuration
|- resources/
|  |-dictionary.txt         # Dictionary for word game
|- files/                   # Directory where files are served from
|  |-HelloWorld.html        # Sample file
```
### Files
- **`server.c`**: Contains the setup for the server which binds and listens for connections on the port.
- **`main.c`**: Contains the main function which sets the base directory, calls the setup for the server and game, and creates the server loop which accepts client connections, creating a new thread for each.
- **`request_handler.c`**: Contains the function to handle client connections and HTTP requests to the server.
- **`file_serve.c`**: Contains the function which serves files that the client requests.
- **`word_game.c`**: Contains the code for the built-in word game such as initializing the dictionary, finding a master word, finding words that can be made from that word, and accepting guesses. 
- **`dictionary.txt`**: Contains the required dictionary for the word game.


### Getting Started

#### Prerequisites
- **CMake** Version 3.22.1 or higher.
- **GCC** or other C compiler
- **UNIX based OS** (Linux or WSL (Windows Subsystem for Linux) is recommended)

## <ins>Setup Instructions</ins>

### Step 1:
Navigate to your specified directory where you want to clone the project

```bash
cd /path/to/directory
```
### Step 2:
Clone the repository and navigate to the directory:
```bash
git clone https://github.com/jason-mauro/Multi-Threaded_HTTP_Server.git <directory name>
cd Multi-Threaded_HTTP_Server
```
### Step 3:
Build the project
1. Create a `build` directory and navigate to it:
    ```bash
    mkdir build && cd build
   ```
2. Generate the makefiles with CMake:
    ```bash
   cmake ..
   ```

3. Compile the project:
   ```bash
   make
   ```
This creates an executable file named 'server' inside `bin` which is located in the `build` directory

### Step 4:
Run the server

After building, you can start the server with the following command:
```bash
./bin/server
```
The server will listen on port `8000` and serve files from the `files` folder located in the project

Navigate to `localhost:8000/` in your browser and you can access the game with the URL `/words` or serve files that are located in the `file` directory with typing the file name after the URL.



