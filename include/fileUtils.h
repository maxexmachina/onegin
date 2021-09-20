#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <sys/types.h>

#include "split.h"

bool isSpace(const char c);

char *cleanBuffer(const char *readBuf, const size_t bufSize, size_t *numCleanBytes);

size_t getFileSize(const char *filePath);
//------------------------------------------------------------ 
//! Reads text from a file and returns a null-terminated buffer 
//!
//! @param[in]  filePath    Path to file
//!
//! @return     null-terminated char buffer in case of success, nullptr otherwise
//------------------------------------------------------------ 
char *readFile(const char *filePath, size_t *size);

int cleanFile(const char *filePath);

int writeLinesToFile(const line *array, const size_t numLines, const char *filePath);

#endif
