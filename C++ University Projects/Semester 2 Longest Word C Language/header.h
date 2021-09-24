#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)
/** Structure describes list of words which are the longest in the text*/
typedef struct longest_words
{
    /** Pointer to character array which contains word*/
    char* word;
    /** Pointer to next element of the list*/
    struct longest_words* pNext;
}longest_words;

/** Function frees allocated memory space used to store list of our words
    @param root pointer to first element of list
*/
void removeStructs(longest_words** root);

/** Function checks if input file is correct, if yes it reads text from the file and saves the contect into character array
    @param input pointer to character array which stores name of the input file
*/
char* fileRead(char* input);

/** Functions creates node or adds node to our list
    @param head pointer to first node of our structure
    @param word current word which will be saved in our list
*/
void addWord(longest_words** head, char* word);

/** Function divide our text into token(word) and checks the lenght, then if the assumption(lenght longer that current max or equal to current max) are met then function calls addWord function
    @param root pointer to the first element of the structure
    @param input pointer to character array which stores our text from input file
*/
void findLongest(longest_words** root, char* input);

/** Function prints whole list of words
    @param head pointer to first element of the function
*/
void printList(longest_words* head);

/** Function prints whole list of words
    @param head pointer to first element of the function
*/
int countWords(longest_words* head);

/** Function bubble sorts our list into alphabetical order
    @param head pointer to first element of the function
*/
void sortAlpha(longest_words** head);

/** Function checks if current words is not already saved on the list
    @param head pointer to first element of the function
    @param word current word which is searched in the list
*/
int checkExist(longest_words** head, char* word);

/** Function save our list on the output file
    @param head pointer to first element of the function
    @param output pointer to character array which stores name of the output file
*/
void saveList(longest_words* head, char* output);