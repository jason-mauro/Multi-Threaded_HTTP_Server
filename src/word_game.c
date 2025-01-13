#include "word_game.h"

extern int wordCount;
extern char sorted_letters[30];

gameListNode* gameList = NULL;
wordListNode* wordList = NULL;

int initialization() {
    srand(time(NULL));

    int wordCount = 0;
    wordListNode* wordListEnd = wordList;

    FILE *fp = fopen("resources/dictionary.txt", "r");
    if (fp != NULL){
        char lineBuffer[30];
        while(fgets(lineBuffer, sizeof(lineBuffer), fp)){
            // format the word and add it to the list
            formatWord(lineBuffer);
            wordListNode* newNode = malloc(sizeof(wordListNode));
            if (newNode == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }
            strcpy(newNode->word, lineBuffer);
            newNode->next = NULL;
            if (wordList == NULL){
                wordList = newNode;
                wordListEnd = wordList;
            } else {
                wordListEnd->next = newNode;
                wordListEnd = wordListEnd->next;
            }
            wordCount++;
        }
    } else {
        printf("File could not be opened\n");
        exit(1);
    }
    fclose(fp);
    return wordCount;
}

void displayWinner(const int clientfd) {
     const char *game_won_html = "<!DOCTYPE html>\n"
                        "<html lang=\"en\">\n"
                        "<head>\n"
                        "    <meta charset=\"UTF-8\">\n"
                        "    <title>Words Without Friends</title>\n"
                        "    <style>\n"
                        "        @import url('https://fonts.googleapis.com/css2?family=Roboto+Mono:ital,wght@0,100..700;1,100..700&display=swap');\n"
                        "        * {\n"
                        "            margin: 0;\n"
                        "            padding: 0;\n"
                        "            box-sizing: border-box;\n"
                        "            font-family: 'Roboto Mono', monospace;\n"
                        "        }\n"
                        "\n"
                        "        body {\n"
                        "            background-color: #161821;\n"
                        "            color: #84a0c6;\n"
                        "            margin: 0;\n"
                        "            display: flex;\n"
                        "            justify-content: center;\n"
                        "            align-items: center;\n"
                        "            height: 100vh;\n"
                        "        }\n"
                        "\n"
                        "        .container {\n"
                        "            width: 500px;\n"
                        "            height: 300px;\n"
                        "            display: flex;\n"
                        "            flex-direction: column;\n"
                        "            background-color: #232531;\n"
                        "            border-radius: 15px;\n"
                        "            box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.5);\n"
                        "            border: 2px solid #595e76;\n"
                        "            align-items: center;\n"
                        "        }\n"
                        "\n"
                        "        .container h1 {\n"
                        "            padding: 10px;\n"
                        "        }\n"
                        "        .container a {\n"
                        "            margin-top: 10px;\n"
                        "            padding: 10px 15px;\n"
                        "            background-color: #84a0c6; \n"
                        "            color: #161821; \n"
                        "            border-radius: 5px;\n"
                        "            text-align: center;\n"
                        "            transition: background-color 0.3s ease, color 0.3s ease;\n"
                        "            text-decoration: none;\n"
                        "        }\n"
                        "    </style>\n"
                        "</head>\n"
                        "<body>\n"
                        "    <div class=\"container\">\n"
                        "        <h1>Congrats You Won!</h1>\n"
                        "        <a href=\"words\">Click Here to Play Again</a>\n"
                        "    </div>\n"
                        "</body>\n"
                        "</html>";
                        char http_response_header[256];
                        snprintf(http_response_header, sizeof(http_response_header),
                            "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html; charset=UTF-8\r\n"
                            "Content-Length: %ld\r\n"
                            "\r\n",
                        strlen(game_won_html));
    send(clientfd, http_response_header, strlen(http_response_header), 0);
    send(clientfd, game_won_html, strlen(game_won_html), 0);

}
// This sends the HTTP header and game board in HTML
void displayWorld(const int clientfd) {
    if (isDone()) {
        const char *game_won_html = "<!DOCTYPE html>\n"
                        "<html lang=\"en\">\n"
                        "<head>\n"
                        "    <meta charset=\"UTF-8\">\n"
                        "    <title>Words Without Friends</title>\n"
                        "    <style>\n"
                        "        @import url('https://fonts.googleapis.com/css2?family=Roboto+Mono:ital,wght@0,100..700;1,100..700&display=swap');\n"
                        "        * {\n"
                        "            margin: 0;\n"
                        "            padding: 0;\n"
                        "            box-sizing: border-box;\n"
                        "            font-family: 'Roboto Mono', monospace;\n"
                        "        }\n"
                        "\n"
                        "        body {\n"
                        "            background-color: #161821;\n"
                        "            color: #84a0c6;\n"
                        "            margin: 0;\n"
                        "            display: flex;\n"
                        "            justify-content: center;\n"
                        "            align-items: center;\n"
                        "            height: 100vh;\n"
                        "        }\n"
                        "\n"
                        "        .container {\n"
                        "            width: 500px;\n"
                        "            height: 300px;\n"
                        "            display: flex;\n"
                        "            flex-direction: column;\n"
                        "            background-color: #232531;\n"
                        "            border-radius: 15px;\n"
                        "            box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.5);\n"
                        "            border: 2px solid #595e76;\n"
                        "            align-items: center;\n"
                        "        }\n"
                        "\n"
                        "        .container h1 {\n"
                        "            padding: 10px;\n"
                        "        }\n"
                        "        .container a {\n"
                        "            margin-top: 10px;\n"
                        "            padding: 10px 15px;\n"
                        "            background-color: #84a0c6; \n"
                        "            color: #161821; \n"
                        "            border-radius: 5px;\n"
                        "            text-align: center;\n"
                        "            transition: background-color 0.3s ease, color 0.3s ease;\n"
                        "            text-decoration: none;\n"
                        "        }\n"
                        "    </style>\n"
                        "</head>\n"
                        "<body>\n"
                        "    <div class=\"container\">\n"
                        "        <h1>Congrats You Won!</h1>\n"
                        "        <a href=\"words\">Click Here to Play Again</a>\n"
                        "    </div>\n"
                        "</body>\n"
                        "</html>";
                        char http_response_header[256];
                        snprintf(http_response_header, sizeof(http_response_header),
                            "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html; charset=UTF-8\r\n"
                            "Content-Length: %ld\r\n"
                            "\r\n",
                        strlen(game_won_html));
        send(clientfd, http_response_header, strlen(http_response_header), 0);
        send(clientfd, game_won_html, strlen(game_won_html), 0);
    } else {
        // Send the content with a HTTP header which includes Transfer-Encoding to let the client know whan all the data has been sent
        const char* http_response = "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Transfer-Encoding: chunked\r\n"
            "\r\n";

        send(clientfd, http_response, strlen(http_response), 0); // Send the response
        char html_buffer[4096] = {0};
        int bytes_left = 4095; // Keep track of the number of bytes that the html buffer has left

        // HTML header and CSS for the webpage
        char* html_start = "<!DOCTYPE html>\n"
            "<html lang=\"en\">\n"
            "<head>\n"
            "    <meta charset=\"UTF-8\">\n"
            "    <title>Words Without Friends</title>\n"
            "    <style>\n"
            "        @import url('https://fonts.googleapis.com/css2?family=Roboto+Mono:ital,wght@0,100..700;1,100..700&display=swap');\n"
            "        * {\n"
            "            margin: 0;\n"
            "            padding: 0;\n"
            "            box-sizing: border-box;\n"
            "            font-family: 'Roboto Mono', monospace;\n"
            "        }\n"
            "\n"
            "        body {\n"
            "            background-color: #161821;\n"
            "            color: white;\n"
            "            display: flex;\n"
            "            align-items: center;\n"
            "            height: 100vh;\n"
            "            line-height: 1.6;\n"
            "            margin: 0;\n"
            "            flex-direction: column;\n"
            "        }\n"
            "\n"
            "        h1 {\n"
            "            color: #d2d4de;\n"
            "            text-align: center;\n"
            "        }\n"
            "\n"
            "        p {\n"
            "            color: #d2d4de;\n"
            "            text-align: center;\n"
            "            padding-bottom: 5px;\n"
            "        }\n"
            "\n"
            "        .sortedLetters {\n"
            "            display: flex;\n"
            "            justify-content: center;\n"
            "            gap: 10px;\n"
            "            margin-bottom: 20px;\n"
            "        }\n"
            "\n"
            "        .word {\n"
            "            display: flex;\n"
            "            justify-content: left;\n"
            "            align-items: center;\n"
            "            gap: 5px;\n"
            "            padding-left: 5px;\n"
            "            font-size: 2rem;\n"
            "            border-radius: 5px;\n"
            "            border: 2px solid #595e76;\n"
            "            background-color: #232531;\n"
            "            color: #d2d4de;\n"
            "            width: 300px;\n"
            "            height: 50px;\n"
            "            margin: 5px;\n"
            "        }\n"
            "\n"
            "        .word-container {\n"
            "            display: grid;\n"
            "            grid-template-columns: repeat(5, 1fr);\n"
            "            padding: 5px;\n"
            "            margin: 0 auto;\n"
            "            grid-auto-flow: row;\n"
            "            border-radius: 5px;"
            "        }\n"
            "\n"
            "        #letter {\n"
            "            font-size: 2rem; \n"
            "        }\n"
            "\n"
            "        #sortedletter {\n"
            "            width: 50px;\n"
            "            height: 50px;\n"
            "            display: flex;\n"
            "            justify-content: center;\n"
            "            align-items: center;\n"
            "            color: #d2d4de;\n"
            "            background-color: #232531;\n"
            "            border: 2px solid #595e76;\n"
            "            font-size: 2rem;\n"
            "            font-weight: bold;\n"
            "            border-radius: 5px;\n"
            "        }\n"
            "\n"
            "        .text-input {\n"
            "            color: #84a0c6;\n"
            "            display: flex;\n"
            "            justify-content: center;\n"
            "            width: 100%;\n"
            "        }\n"
            "\n"
            "        .text-input form {\n"
            "            display: flex;\n"
            "            justify-content: center;\n"
            "        }\n"
            "\n"
            "        .correct {\n"
            "            background-color: #84a0c6;\n"
            "            color: #161821;\n"
            "        }\n"
            "\n"
            "        input[type=text] {\n"
            "            padding: 15px; \n"
            "            font-size: 2rem; \n"
            "            border-radius: 5px;\n"
            "            border: 2px solid #595e76;\n"
            "            background-color: #232531;\n"
            "            color: #d2d4de;\n"
            "            width: 300px; \n"
            "            height: 50px; \n"
            "            margin-bottom: 20px;\n"
            "        }\n"
            "\n"
            "        input::placeholder {\n"
            "            color: #d2d4de;\n"
            "        }\n"
            "\n"
            "    </style>\n"
            "</head>\n"
            "<body>\n"
            "    <h1>Words Without Friends</h1>\n"
            "    <p>*Guess the words that can be created from the letters below*</p>\n"
            "    <div class=\"sortedLetters\">\n";

        // Send the start of the HTML with CSS since that is constant. (Use chunked transfer encoding)
        // Get the chunk size
        char header_size[30];
        snprintf(header_size, sizeof(header_size), "%zx\r\n", strlen(html_start));
        send(clientfd, header_size, strlen(header_size), 0); // Send the header for the chunk size of the content
        send(clientfd, html_start, strlen(html_start), 0); // Send the content
        send(clientfd, "\r\n", 2, 0); // Let the client know we are done with this chunk of data

        // Generate the sorted letters html and append them to the buffer
        for (int i = 0; sorted_letters[i] != '\0'; i++) {
            snprintf(html_buffer + strlen(html_buffer), sizeof(html_buffer) - strlen(html_buffer), "<div id=\"sortedletter\">%c</div>\n", sorted_letters[i]);
        }

        // Add the input field
        strcat(html_buffer, "</div>\n"
            "<div class=\"text-input\">\n"
            "<form method=\"GET\" action=\"/words\">\n"
            "<input type=\"text\" name=\"move\" autofocus placeholder=\"Enter a guess\">\n"
            "</form>\n"
            "</div>\n"
            "<div class=word-container>\n");
        bytes_left -= strlen(html_buffer); // Get the remaining amount of bytes left for the buffer

        gameListNode* current = gameList;

        // Add the words to the HTML and if the buffer is full send the content of the buffer then resume adding the words to the buffer
        while(current != NULL){
            char word_buffer[128];
            if (current->isFound){
                strcpy(word_buffer, "<div class=\"word correct\">");
            } else {
                strcpy(word_buffer, "<div class=\"word\">");
            }
            // Append the word if found
            if (current->isFound){
                strcat(word_buffer, current->word);
            } else {
                // Append x amount of underscores where x is the length of the word
                for (int i = 0; i < strlen(current->word); i++){
                    strcat(word_buffer, "_");
                }
            }
            strcat(word_buffer, "</div>\n");

            if (bytes_left > strlen(word_buffer)){
                strcat(html_buffer, word_buffer);
                bytes_left -= strlen(word_buffer);
            } else { // Buffer is full send it to the server using chunk transfer encoding
                char chunk_size[30];
                snprintf(chunk_size, sizeof(chunk_size), "%zx\r\n", strlen(html_buffer));
                send(clientfd, chunk_size, strlen(chunk_size), 0);
                send(clientfd, html_buffer, strlen(html_buffer), 0);
                send(clientfd, "\r\n", 2, 0);
                // Set the html buffer to the current word buffer
                memset(html_buffer, 0 , sizeof(html_buffer));
                strcpy(html_buffer, word_buffer);
                bytes_left = 4095 - strlen(html_buffer);
            }
            current = current->next;

        }
        // Add the final tags and send it to the client
        strcat(html_buffer, "</div>\n</body>\n</html>");
        char chunk_size[30];
        snprintf(chunk_size, sizeof(chunk_size), "%zx\r\n", strlen(html_buffer));
        send(clientfd, chunk_size, strlen(chunk_size), 0);
        send(clientfd, html_buffer, strlen(html_buffer), 0);
        send(clientfd, "\r\n", 2, 0);
        send(clientfd, "0\r\n\r\n", 5, 0); // Let the client know we are done sending data
    }
}

// Finds all valid words that can be made from the master word and adds it to the game list
void findWords(const wordListNode* masterWord){
    gameListNode* gameListEnd = NULL;
    int masterDistribution[26] = {0};
    getLetterDistribution(masterWord->word, masterDistribution);
    wordListNode* current = wordList;
    // Walk through the dictionary comparing distributions and adding words that can be made to the list
    while(current != NULL){
        int wordDistribution[26] = {0};
        getLetterDistribution(current->word, wordDistribution);
        if (compareCounts(masterDistribution, wordDistribution)){
            gameListNode* newNode = malloc(sizeof(gameListNode));
            strcpy(newNode->word, current->word);
            newNode->next = NULL;
            newNode->isFound = false;
            if (gameList == NULL){
                gameList = newNode;
                gameListEnd = gameList;
            } else {
                gameListEnd->next = newNode;
                gameListEnd = gameListEnd->next;
            }
        }
        current = current->next;
    }
}

// Helper function for qsort to sort letters
int compare(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

// Free the memory of the game node list
void cleanupGameListNodes(){
    gameListNode* temp = NULL;
    while(gameList != NULL){
        temp = gameList;
        gameList = gameList->next;
        free(temp);
    }
}

// Capitalize and remove newline/carriage return characters in a word
void formatWord(char* word){
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '\n' || word[i] == '\r') {
            word[i] = '\0';
        }
        word[i] = toupper(word[i]);
    }
}

// Populate the frequency array of letters for a given word
void getLetterDistribution(const char* word, int* letterDistribution){
    // Increment the index in the array associated with each letter in word to populate the letterDistribution3
    for (int i = 0; word[i] != 0; i++){
        letterDistribution[toupper(word[i]) - 'A']++;
    }
}

// Compares the letter counts of a word to the master word and returns if it can be made from the master word
bool compareCounts(const int* masterDistribution, const int* wordDistribution){
    // Check if each letter's count in wordDistribution does not exceed the count of that letter in masterDistribution
    for (int i = 0; i < 26; i++){
        if (wordDistribution[i] > masterDistribution[i]){
            return false;
        }
    }
    return true;
}

// This function returns a random word from the dictionary that is 7 or more characters long
wordListNode* getRandomWord(){
    const int index = rand() % wordCount;

    wordListNode* current = wordList;
    // Walk to the random index in the list
    for (int i = 0; i < index; i++){
        current = current->next;
    }
    // Search until you find a word that is 7 or more characters
    while(current != NULL && strlen(current->word) < 7){
        current = current->next;
    }
    // If at the end of the list recursively call the function until it finds a valid word
    if (current == NULL){
        return getRandomWord();
    }

    return current;
}

// Takes in an input and checks it within the game list and if that word matches, it marks it found
void acceptInput(char* word) {
    gameListNode* current = gameList;
    for (int i = 0; word[i] != '\0'; i++){
        word[i] = toupper(word[i]);
    }
    // Walk through the gameList and if the input matches the word, set the word to found
    while(current != NULL){
        if (!current->isFound){
            if (strcmp(word, current->word) == 0){
                current->isFound = true;
            }
        }
        current = current->next;
    }

}

// Returns if all words have been found in the game list
bool isDone() {
    // Walk through the list and if any word is not found return false
    gameListNode* current = gameList;
    while(current != NULL){
        if (!current->isFound)
            return false;
        current = current->next;
    }
    return true;
}

// Free the memory of the word node list
void cleanupWordListNodes(){
    wordListNode* temp = NULL;
    while(wordList != NULL){
        temp = wordList;
        wordList = wordList->next;
        free(temp);
    }
}