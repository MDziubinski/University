#include "header.h"

void removeStructs(longest_words** root)
{
    longest_words* temp = *root;
    longest_words* next;
    while (temp != NULL)
    {
        next = temp->pNext;
        free(temp);
        temp = next;
    }
    *root = NULL;
}

char* fileRead(char* input)
{
    FILE* inFile;
    inFile = fopen("text.txt", "r");
    char* text;
    if (!inFile)
    {
        printf("Failed to open the file! Please remember to input text file.");
        return NULL;
    }
    fseek(inFile, 0, SEEK_END);
    int size = ftell(inFile);
    rewind(inFile);
    text = (char*)malloc(size + 1);
    if (text)
    {
        fread(text, 1, size, inFile);
        text[size] = '\0';
    }
    fclose(inFile);
    return text;
}

int checkExist(longest_words** head, char* word)
{
    longest_words* temp = *head;

    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (strcmp(word, temp->word) == 0)
            {
                return 1;
            }
            else
            {
                temp = temp->pNext;
            }
        }
    }
    return 0;
}

void addWord(longest_words** head, char* word)
{
    int bool = checkExist(head, word);
    if (bool == 0)
    {
        longest_words* new_word = (struct longest_words*) malloc(sizeof(longest_words));
        new_word->word = word;
        new_word->pNext = NULL;
        longest_words* temp = *head;
        if (*head == NULL)
        {
            *head = new_word;
        }
        else
        {
            while (temp->pNext != NULL)
            {
                temp = temp->pNext;
            }
            temp->pNext = new_word;
        }
    }
}

void findLongest(longest_words** root, char* input)
{
    int max_lenght = 0;
    int temp_lenght = 0;
    char* token;
    token = strtok(input, " ,.?!-+()[]{}:;=<>/!@#$%^&*-_|/\n");
    temp_lenght = strlen(token);
    max_lenght = temp_lenght;
    addWord(root, token);
    while (token != NULL)
    {
        token = strtok(NULL, " ,.?!-+()[]{}:;=<>/!@#$%^&*-_|/\n");
        if (token != NULL)
        {
            temp_lenght = strlen(token);
            if (temp_lenght == max_lenght)
            {
                addWord(root, token);
            }
            else if (temp_lenght > max_lenght)
            {
                removeStructs(root);
                addWord(root, token);
                max_lenght = temp_lenght;
            }
        }
    }
}

void printList(longest_words* head)
{
    if(head != NULL)
    {
        int i = 1;
        int lenght = strlen(head->word);
        printf("Max lenght of the word in this text is: %d\n", lenght);
        while (head != NULL)
        {
            printf("%d Word: %s \n", i, head->word);
            head = head->pNext;
            i++;
        }
    }
}

int countWords(longest_words* head)
{
    int i = 0;
    if(head != NULL)
    { 
        
        while (head != NULL)
        {
            i++;
            head = head->pNext;
        }
    }
    return i;
}
void sortAlpha(longest_words** head)
{
    {
        longest_words* root;
        char* temp;

        root = *head;

        if (root)
        {
            while (root && root->pNext)
            {
                if (strcmp(root->word, root->pNext->word) > 0)
                {
                    temp = root->word;
                    root->word = root->pNext->word;
                    root->pNext->word = temp;
                }
                root = root->pNext;
            }
        }
    }
}

void saveList(longest_words *head, char* output)
{
    FILE* outFile;
    outFile = fopen(output, "w");
    if (!outFile)
    {
        printf("Failed to open the file!.");
        return;
    }
    if (head != NULL)
    {
        longest_words* temp = head;
        while (temp != NULL)
        {
            fprintf(outFile, "%s\n", temp->word);
            temp = temp->pNext;
        }
    }
    fclose(outFile);
}