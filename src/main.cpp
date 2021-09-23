#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <errno.h>

#include "../include/fileUtils.h"
#include "../include/split.h"
#include "../include/compare.h"
#include "../include/sort.h"

int main() {
    printf("Please enter a relative file path to read the text from:\n");

    char filePath[64] = {};
    if (scanf("%s", filePath) != 1) {
        printf("There was an error reading file path\n");
        return EXIT_FAILURE;
    }

    setlocale(LC_ALL, "ru_RU.utf8");

    const char *cleanPath = "clean.txt";
    const char *sortedPath = "sorted.txt";

    if (cleanFile(filePath, cleanPath) == 0) {
        printf("There was an error reading clean file path : %s\n", strerror(errno));
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

    myHeapSort(text.lines, text.numLines, sizeof(line), &linePtrNumCmp);
    if (writeLinesToFile(&text, sortedPath) != (int)text.numLines + 1) {
        freeText(&text);
        return EXIT_FAILURE;
    }

    freeText(&text);
    return EXIT_SUCCESS; 
}
