#include "server.h"

// setup_server will try to create a socket, and bind and listen to that socket. If the socket creation is successful, it will return that socket's file descriptor. Otherwise it will exit the program.
int server_setup(){
    struct addrinfo hints, *server_info, *current_info;
    int serverfd = -1; // server file descriptor
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // IPv4 or Ipv6
    hints.ai_socktype = SOCK_STREAM; // TCP connection
    hints.ai_flags = AI_PASSIVE; // Fill in my IP address

    if (getaddrinfo(NULL, PORT, &hints, &server_info) != 0){
        printf("Error getting address information\n");
        exit(1);
    }
    // Try to create a socket and bind to it
    for (current_info = server_info; current_info != NULL; current_info = current_info->ai_next){
        serverfd = socket(current_info->ai_family, current_info->ai_socktype, current_info->ai_protocol);
        if (serverfd == -1){
            continue; // Socket creation failed try next one
        }
        // Try to bind to the socket
        if (bind(serverfd, current_info->ai_addr, current_info->ai_addrlen) == 0){
            printf("Binded to socket!\n");
            break;
        }
        close(serverfd); // CLose the serverfd and try the next one
    }
    freeaddrinfo(server_info);

    // Bind was not successful
    if (current_info == NULL){
        printf("failed to bind to socket\n");
        exit(1);
    }

    // Try to listen for connections
    if (listen(serverfd, 1) == -1){
        printf("listen failed");
        exit(1);
    }
    printf("Listening\n");
    return serverfd;
}