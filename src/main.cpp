#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "../include/fileUtils.h"
#include "../include/split.h"

int main() {
    /*printf("This program reads all strings from a file, then prints them to standard output\n"
            "Please enter a relative file path:\n");
    char filePath[64] = {};
    if (scanf("%s", filePath) == EOF) {
        printf("There was an error reading file path\n");
        return 1;
    }*/

    if (cleanFile("onegin.txt") == 0) {
        printf("error\n");
        return EXIT_FAILURE;
    } 

    size_t bufSize = 0;
    char *textBuffer = readFile("onegin_clean.txt", &bufSize);
    if (textBuffer == nullptr) {
        return EXIT_FAILURE;
    }

    size_t numLines = 0;
    line *array = splitBuffer(textBuffer, bufSize, &numLines); 
    if (array == nullptr) {
        free(textBuffer);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < numLines; i++) {
        printf("%s\n", array[i].ptr);
    }
    free(textBuffer);
    free(array);
    return EXIT_SUCCESS;
}
