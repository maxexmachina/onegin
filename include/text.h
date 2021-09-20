#ifndef TEXT_H
#define TEXT_H

#include "split.h"

struct text_t {
    char *buffer;
    line *lines;
    size_t numBytes;
    size_t numLines;
};

void freeText(text_t *text);

int getText(const char *filePath, text_t *text);

#endif
