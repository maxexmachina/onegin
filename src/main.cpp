#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "../include/fileUtils.h"
#include "../include/split.h"
#include "../include/sort.h"

int main() {
    /*printf("This program reads all strings from a file, then prints them to standard output\n"
            "Please enter a relative file path:\n");
    char filePath[64] = {};
    if (scanf("%s", filePath) == EOF) {
        printf("There was an error reading file path\n");
        return 1;
    }*/
    setlocale(LC_ALL, "ru_RU.utf8");

    const char *filePath = "onegin.txt";
    const char *cleanPath = "clean.txt";
    const char *sortedPath = "sorted.txt";

    if (cleanFile(filePath, cleanPath) == 0) {
        printf("error\n");
        return EXIT_FAILURE;
    } 

    text_t text = {};
    if (getText(cleanPath, &text) == 0) {
        printf("Error getting lines from file %s\n", cleanPath);
    }

    qsort(text.lines, text.numLines, sizeof(line), &lineCmp);
    if (writeLinesToFile(&text, sortedPath) != (int)text.numLines + 1) {
        freeText(&text);
        return EXIT_FAILURE;
    }
    qsort(text.lines, text.numLines, sizeof(line), &rLineCmp);
    if (writeLinesToFile(&text, sortedPath) != (int)text.numLines + 1) {
        freeText(&text);
        return EXIT_FAILURE;
    }


    freeText(&text);
    return EXIT_SUCCESS; 
}
