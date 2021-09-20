#ifndef SPLIT_H
#define SPLIT_H

#include <sys/types.h>

const size_t DEFAULT_ARR_SIZE = 1024;

typedef struct textLine {
    char *ptr;
    size_t len;
} line;

line *splitBuffer(char *buffer, size_t bufSize, size_t *totalLines);

#endif
