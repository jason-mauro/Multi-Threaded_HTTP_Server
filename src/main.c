#include "main.h"

int wordCount;
const char* base_directory;

// Takes in the base directory path to server files from
int main(int argc, char* argv[]){
    if (argc != 2){
        printf("This program requires a home directory which files will be served from!\n");
        return 1;
    }
    int clientfd; // clients fd, new_fd is used to pass in the clientfd to a thread
    struct sockaddr_storage client_address; // Address of client
    socklen_t client_length = sizeof(client_address);
    base_directory = argv[1];
    wordCount = initialization();
    const int socketfd = server_setup(); // Get the socket created in the network
    while(1) {
        if ((clientfd = accept(socketfd, (struct sockaddr *)&client_address, &client_length))) {
            pthread_t new_thread;
            int *new_fd = malloc(sizeof(int));
            if (new_fd == NULL) {
                printf("Memory allocationn failed!\n");
                return 1;
            }
            *new_fd = clientfd;
            if (pthread_create(&new_thread, NULL, handle_connection, (void *)new_fd) < 0){
                printf("Unable to create a thread for the incomming connection");
            }
        }
    }
}
