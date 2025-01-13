#include "file_serve.h"

extern const char* base_directory;

void serve_file(const char* path, const int clientfd) {
    char filepath[512] = {0};
    strcpy(filepath, base_directory); // Copy the base directory (files or specified) to the filepath
    strcat(filepath, path); // Concatanate the requested file to the filepath
    const int file = open(filepath, O_RDONLY);
    // Send HTTP 404 header as the requested file was not found
    if (file == -1){
        const char *file_not_found_response = "HTTP/1.0 404 Not Found\r\n"
            "\r\n"
            "<!doctype html>\n"
            "<html>\n"
            "<head><title>404 Not Found</title></head>\n"
            "<body>\n"
            "    <h1>404 Not Found</h1>\n"
            "    <p>Requested File was unable to be found from the provided file path.</p>\n"
            "</body>\n"
            "   </html>";
        send(clientfd, file_not_found_response, strlen(file_not_found_response), 0);
    } else {
        // Get the stats of the file and send a 200 OK HTTP response header
        struct stat file_stats;
        if (stat(filepath, &file_stats) == -1){
            close(file);
            close(clientfd);
            pthread_exit(NULL);
        }
        char http_response_header[256];
        snprintf(http_response_header, sizeof(http_response_header),
        "HTTP/1.0 200 OK\r\n"
            "Content-Length: %ld\r\n"
            "\r\n",
            file_stats.st_size);
        if (send(clientfd, http_response_header, strlen(http_response_header), 0) == -1) {
            perror("Error sending HTTP header\n");
            close(file);
            close(clientfd);
            pthread_exit(NULL);
        }
        // Read and send the file content using partial send and recieve (From the Networking Slides)
        char buffer[1024];
        int bytes_read;
        while ((bytes_read = read(file, buffer, sizeof(buffer))) > 0) {
            int total = 0;
            int bytes_left = bytes_read;
            while(total < bytes_read){
                const int sent = send(clientfd, buffer + total, bytes_left, 0);
                if (sent == -1) {
                    perror("Error when sending data");
                    close(file);
                    close(clientfd);
                    pthread_exit(NULL);
                }
                total += sent;
                bytes_left -= sent;
            }
        }
        close(file);
    }
}
