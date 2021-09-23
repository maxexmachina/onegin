#ifndef SORT_H
#define SORT_H

#include "../include/split.h"

wchar_t *lineToWCharStr(const line *l);

int wIsAlpha(wchar_t c);

int wstrcmp(const wchar_t *s1, const wchar_t *s2);

int lineCmp(const void *l1, const void *l2);

int rwstrcmp(const wchar_t *s1, const wchar_t *s2, const size_t l1, const size_t l2);

int rLineCmp(const void *l1, const void *l2);


#endif
