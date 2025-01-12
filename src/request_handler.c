#include "request_handler.h"

extern const char* base_directory;
char sorted_letters[30] = {0};
extern gameListNode* gameList;
// Threaded function that takes a socket from a client and tries to serve the file that is requested
void* handle_connection(void* socketfd){
    const int clientfd = *((int*)socketfd); // Get the clients connection from the thread parameter
    free(socketfd);

    char client_request[2048] = {0};
    const int request = recv(clientfd, client_request, 1024, 0);
    if (request < 0){
        printf("Recieve Failed\n");
    } else if (request == 0){
        printf("Client Disconnected\n");
    } else { // Parse the HTTP request
        char *saveptr;
        char* tokenize = strtok_r(client_request, " ", &saveptr); // "GET"
        if (strcmp(tokenize, "GET") != 0){
            printf("Invalid HTTP request\n");
        }
        tokenize = strtok_r(NULL, " ", &saveptr); // Filepath
        // If "/words" initialize a new game
        if (strcmp(tokenize, "/words") == 0){
            cleanupGameListNodes();
            memset(sorted_letters, 0, sizeof(sorted_letters));
            wordListNode* master_word = getRandomWord();
            findWords(master_word);
            strcpy(sorted_letters, master_word->word);
            qsort(sorted_letters, strlen(sorted_letters), sizeof(char), compare);
            displayWorld(clientfd);
        } else if (strncmp(tokenize, "/words?move=", 12) == 0) {  // Process a guess in the current game
            // send a bad request if a game was never intialized!
            if (gameList == NULL){
                const char *file_not_found_response = "HTTP/1.0 404 Not Found\r\n"
                "\r\n"
                "<!doctype html>\n"
                "<html>\n"
                "<head><title>404 Not Found</title></head>\n"
                "<body>\n"
                "    <h1>404 Not Found</h1>\n"
                "    <p>No game was found and therefore, a guess is not allowed!</p>\n"
                "    <a href=\"words\">Click here if you want to play!</a>\n"
                "</body>\n"
                "</html>";
                printf("%d\n", clientfd);
                send(clientfd, file_not_found_response, strlen(file_not_found_response), 0);
            } else {
                tokenize += 12; // Skip the "/words?move="
                acceptInput(tokenize);
                // Parse the input from the query parameter
                if (!isDone()){
                    displayWorld(clientfd);
                } else { // Send a game won page with a button to start a new game
                    displayWinner(clientfd);
                }
                }
            } else {
                serve_file(tokenize, clientfd);
            }
        }
    close(clientfd);
    pthread_exit(NULL);
}