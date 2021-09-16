#include <stdio.h>
#include <string.h>

const int MAX_LINES = 100;
const int MAX_LINE_LEN = 100;

int readFromFileWrong(const char* index[], const char* path) {
    FILE* fileToRead = fopen(path, "r");
    for (size_t i = 0; i < MAX_LINES ; i++) {
        char str[MAX_LINE_LEN] = "";
        fgets(str, sizeof(str), fileToRead);
        index[i] = str;
    }
    fclose(fileToRead);
    return 1;
}

int readFromFile(const char* index[], const char* path) {
    FILE* fileToRead = fopen(path, "r");
    for (size_t i = 0; i < MAX_LINES ; i++) {
        char str[MAX_LINE_LEN] = "";
        fgets(str, sizeof(str), fileToRead);
        index[i] = strdup(str);
    }
    fclose(fileToRead);
    return 1;
}

int enumerateStringsInFile(const char* path) {
    const char* index[MAX_LINES] = {};
    if (readFromFile(index, path) == 0) {
        printf("There was an error reading lines from file\n");
        return 0;
    }
    for (size_t i = 0; i < MAX_LINES; i++) {
        puts(index[i]);
    }
    return 1;
}

int main() {
    printf("This program reads all strings from a file, then prints them to standard output\n"
            "Please enter a relative file path:\n");
    char filePath[64] = {};
    if (scanf("%s", filePath) == EOF) {
        printf("There was an error reading file path\n");
        return 1;
    }
    if (!enumerateStringsInFile(filePath)) {
        return 1;
    }
}
