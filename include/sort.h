#ifndef SORT_H
#define SORT_H

#include <sys/types.h>

void swap(void *a, void *b, size_t size);

void heapify(void *array, size_t n, size_t i, size_t size, int (*cmp)(const void *, const void *));

void myHeapSort(void *base, size_t nmemb, size_t size, int (*cmp)(const void *, const void *));

#endif
