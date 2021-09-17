#include <stdio.h>
#include <locale.h>

#include "../include/fileUtils.h"

int main() {
    /*printf("This program reads all strings from a file, then prints them to standard output\n"
            "Please enter a relative file path:\n");
    char filePath[64] = {};
    if (scanf("%s", filePath) == EOF) {
        printf("There was an error reading file path\n");
        return 1;
    }*/
    setlocale (LC_ALL, "ru");
    setlocale(LC_ALL, "cp1251");
    char *textBuffer = readFile("onegin.txt");

    if (textBuffer != nullptr) {
        printf("%s", textBuffer);
    }
}
