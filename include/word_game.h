#ifndef WORD_GAME_H
#define WORD_GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "file_serve.h"



// Linked List Nodes
typedef struct wordListNode {
    char word[30];
    struct wordListNode* next;
} wordListNode;

typedef struct gameListNode {
    char word[30];
    struct gameListNode* next;
    bool isFound;
} gameListNode;

extern int wordCount;
extern wordListNode* wordList;
extern gameListNode* gameList;
extern char sorted_letters[30];

int initialization();
bool isDone();
bool compareCounts(const int* masterDistribution, const int* wordDistribution);
void getLetterDistribution(const char* word, int* letterDistribution);
void displayWorld(const int clientfd);
wordListNode* getRandomWord();
void findWords(const wordListNode* masterWord);
int compare(const void *a, const void *b);
void formatWord(char* word);
void acceptInput(char* word);
void cleanupGameListNodes();
void cleanupWordListNodes();
void displayWinner(const int clientfd);

#endif //WORD_GAME_H
