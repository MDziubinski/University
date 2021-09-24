#include "header.h"

char* inpFile = NULL;
char* outFile = NULL;
int flag = 0;


int main(int argc, char **argv)
{
    if(argc > 1)
    {
        int counter = 1;
        while(counter < argc)
        {
            char *arg = argv[counter++];
            if (strlen(arg) != 2 || arg[0] != '-')
            {
                printf("Possible arguments are -i for input or -o for output.");
                return 0;
            }
            switch (arg[1])
            {
            case 'i':
                if (counter == argc)
                    return 0;
                inpFile = argv[counter++];
                flag++;
                break;
            case 'o':
                if (counter == argc)
                    return 0;
                outFile = argv[counter++];
                flag++;
                break;
            default:
                printf("Possible arguments are -i for input or -o for output.");
                return 0;
            }
        }
        if (flag == 2)
        {
            char* input;
            int repeats = 0;
            longest_words* root = NULL;
            input = fileRead(inpFile);
            if (input == NULL)
                return 0;
            printf("Text: %s\n" , input);
            int text_size = strlen(input);
            findLongest(&root, input);
            repeats = countWords(root);
            for (int i = 0; i <= repeats; i++)
            {
                sortAlpha(&root);
            }
            printList(root);
            saveList(root, outFile);
            removeStructs(&root);
            free(input);
        }
    }
    else
    printf("Possible arguments are -i for input or -o for output.");
    return 0;
}
