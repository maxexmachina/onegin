#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "../include/fileUtils.h"

char *readFile(const char *filePath) {
    struct stat fileStats;
    stat(filePath, &fileStats);
    const size_t fileSize = fileStats.st_size;

    FILE *fileToRead = fopen(filePath, "r");
    if (fileToRead == nullptr) {
        printf("There was an error opening file %s : %s\n", filePath, strerror(errno));
        return nullptr;
    }
    char *readBuf = (char *)calloc(fileStats.st_size + 1, 1);
    if (readBuf == nullptr) {
        printf("There was an error allocating memory : %s\n", strerror(errno));
        return nullptr;
    }
    if (fread(readBuf, 1, fileSize, fileToRead) != fileSize) {
        printf("There was an error reading file %s : %s\n", filePath, strerror(errno));
        free(readBuf);
        fclose(fileToRead);
        return nullptr;
    } 
    if (fclose(fileToRead) == EOF) {
        printf("There was an error closing file %s : %s\n", filePath, strerror(errno));
        free(readBuf);
        return nullptr; 
    }
    readBuf[fileSize] = '\0';
    return readBuf;
}

int cleanFile(const char *filePath) {
    FILE *fileToRead = fopen(filePath, "r");
}
