#include <wchar.h>
#include <stdlib.h>

#include "compare.h"

wchar_t *lineToWCharStr(const line *l) {
    const size_t size = l->len + 1;
    wchar_t *wText = (wchar_t *)calloc(size, sizeof(*wText));
    mbstowcs(wText, l->ptr, size);
    return wText;
}

int wIsAlpha(wchar_t c) {
    return (c >= 0x0410 && c <= 0x042F) || // а to я 
           (c >= 0x0430 && c <= 0x044F) || // А to Я
           (c >= 0x41 && c <= 0x5a) || // A to Z
           (c >= 0x61 && c <= 0x7a); // a to z
}

int wstrcmp(const wchar_t *s1, const wchar_t *s2) {
    while (*s1 && !wIsAlpha(*s1)) {
        ++s1;
    }
    while (*s2 && !wIsAlpha(*s2)) {
        ++s2;
    }
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return (*s1 - *s2);
}

int lineCmp(const void *l1, const void *l2) {
    wchar_t *w1 = lineToWCharStr((const line *)l1);
    wchar_t *w2 = lineToWCharStr((const line *)l2);

    const int ret = wstrcmp(w1, w2);
    free(w1);
    free(w2);
    return ret;
}

int rwstrcmp(const wchar_t *s1, const wchar_t *s2, const size_t l1, const size_t l2) {
    ssize_t pos1 = l1;
    ssize_t pos2 = l2;
    while (pos1 >= 0 && !wIsAlpha(s1[pos1])) {
        --pos1;
    }
    while (pos2 >= 0 && !wIsAlpha(s2[pos2])) {
        --pos2;
    }
    while (pos1 >= 0 && pos2 >= 0 && (s1[pos1] == s2[pos2])) {
        --pos1;
        --pos2;
    }

    if (pos1 < 0 && pos2 < 0) {
        return 0;
    } else if (pos1 < 0) {
        return -1;
    } else if (pos2 < 0) {
        return 1;
    } else {
        return (s1[pos1] - s2[pos2]);
    }
}

int rLineCmp(const void *l1, const void *l2) {
    const line *line1 = (const line *)l1;
    const line *line2 = (const line *)l2;

    wchar_t *w1 = lineToWCharStr(line1);
    wchar_t *w2 = lineToWCharStr(line2);

    const int ret = rwstrcmp(w1, w2, line1->len, line2->len);
    free(w1);
    free(w2);
    return ret;
}

int linePtrNumCmp(const void *l1, const void *l2) {
    return ((const line *)l1)->ptr > ((const line *)l2)->ptr;
}
