#include <wchar.h>
#include <stdlib.h>

#include "../include/sort.h"

wchar_t *lineToWCharStr(const line *l) {
    const size_t size = l->len + 1;
    wchar_t *wText = (wchar_t *)calloc(size, sizeof(*wText));
    mbstowcs(wText, l->ptr, size);
    return wText;
}

int	wstrcmp(const wchar_t *s1, const wchar_t *s2) {
	while (*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
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
