#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "../include/fileUtils.h"

size_t getFileSize(const char *filePath) {
    struct stat fileStats;
    stat(filePath, &fileStats);
    return fileStats.st_size;
}

char *readFile(const char *filePath, size_t *size) {
    const size_t fileSize = getFileSize(filePath);

    FILE *fileToRead = fopen(filePath, "r");
    if (fileToRead == nullptr) {
        printf("There was an error opening file %s : %s\n", filePath, strerror(errno));
        return nullptr;
    }
    char *readBuf = (char *)calloc(fileSize + 1, sizeof(*readBuf));
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
    *size = fileSize + 1;
    return readBuf;
}

bool isSpace(const char c) {
    return c == ' ' || c == '\t';
}

char *cleanBuffer(const char *readBuf, const size_t bufSize, size_t *numCleanBytes) {
    char *writeBuf = (char *)calloc(bufSize, sizeof(*writeBuf)); 
    if (writeBuf == nullptr) {
        printf("There was an error allocating memory : %s\n", strerror(errno));
        return nullptr;
    }

    for (size_t i = 0; i < bufSize - 1; ++i) {
        if (i == 0 || readBuf[i - 1] == '\n') {
            while (isSpace(readBuf[i])) {
                ++i;
            }
        }
        if (readBuf[i] == '\r') {
            ++i;
        }

        if (isSpace(readBuf[i])) {
            size_t j = i;
            while (isSpace(readBuf[j])) {
                ++j;
            }
            if (readBuf[j] == '\n') {
                i = j;
                writeBuf[*numCleanBytes] = readBuf[i];
                ++(*numCleanBytes);
            } else {
                writeBuf[*numCleanBytes] = readBuf[i];
                ++(*numCleanBytes);
            }
        } else {
            writeBuf[*numCleanBytes] = readBuf[i];
            ++(*numCleanBytes);
        }
    }
    return writeBuf;
}

int cleanFile(const char *filePath, const char *cleanPath) {
    const size_t fileSize = getFileSize(filePath);

    size_t bufSize = 0;
    char *readBuf = readFile(filePath, &bufSize); //fileSize + 1
    if (readBuf == nullptr) {
        printf("There was an error reading file %s : %s\n", filePath, strerror(errno));
        return 0;
    }

    size_t numCleanBytes = 0;
    char *writeBuf = cleanBuffer(readBuf, fileSize, &numCleanBytes);
    if (writeBuf == nullptr) {
        printf("There was an error allocating memory : %s\n", strerror(errno));
        free(readBuf);
        return 0;
    }

    FILE *fileToWrite = fopen(cleanPath, "w");
    if (fileToWrite == nullptr) {
        printf("There was an error opening file %s : %s\n", cleanPath, strerror(errno));
        free(readBuf);
        free(writeBuf);
        return 0;
    }
    if (fwrite(writeBuf, 1, numCleanBytes, fileToWrite) != numCleanBytes) {
        printf("There was an error writing to file %s : %s\n", cleanPath, strerror(errno));
        free(readBuf);
        free(writeBuf);
        fclose(fileToWrite);
        return 0;
    }
    if (fclose(fileToWrite) == EOF) {
        printf("There was an error closing file %s : %s\n", filePath, strerror(errno));
        free(readBuf);
        free(writeBuf);
        return 0;
    }
    free(readBuf);
    free(writeBuf);
    return 1;
}

int writeLinesToFile(const text_t *text, const char *filePath) {
    FILE *fileToWrite = fopen(filePath, "a");
    if (fileToWrite == nullptr) {
        printf("There was an error opening file %s : %s\n", filePath, strerror(errno));
        return 0;
    }

    size_t i = 0;
    for (; i < text->numLines; ++i) {
        const line cur = text->lines[i];
        if (fprintf(fileToWrite, "%s\n", cur.ptr) != int(cur.len) + 1) {
            printf("There was an error writing to file %s : %s\n", filePath, strerror(errno));
            fclose(fileToWrite);
            return 0;
        } 
    }

    fprintf(fileToWrite, "--------------------------------------------------\n");
    if (fclose(fileToWrite) == EOF) {
        printf("There was an error closing file %s : %s\n", filePath, strerror(errno));
        return 0;
    }
    return int(i + 1);
}
