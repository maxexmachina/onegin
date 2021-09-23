#ifndef COMPARE_H
#define COMPARE_H

#include "../include/split.h"

//------------------------------------------------------------ 
//! Converts a string of chars to its wide char representation based on current locale
//!
//! @param[in]  l   Line struct which holds the string to convert
//!
//! @return     Wide char representation of the line text
//------------------------------------------------------------ 
wchar_t *lineToWCharStr(const line *l);

//------------------------------------------------------------ 
//! Checks if the given wide character is alphabetic
//!
//! @param[in]  c   Wide character to check
//!
//! @return     1 if the character is alphabetic, 0 otherwise     
//------------------------------------------------------------ 
int wIsAlpha(wchar_t c);

//------------------------------------------------------------ 
//! Compares two given wide char strings alphabetically
//!
//! @param[in]  s1  First string to compare
//! @param[in]  s2  Second string to compare
//!
//! @return     Positive value if s1 > s2, 0 if s1 == s2, negative value if s1 < s2 
//------------------------------------------------------------ 
int wstrcmp(const wchar_t *s1, const wchar_t *s2);

//------------------------------------------------------------ 
//! Compares two line structs based on alphabetical order of stored text
//!
//! @param[in]  l1  First line to compare 
//! @param[in]  l2  Second line to compare 
//!
//! @return     Positive value if l1 > l2, 0 if l1 == l2, negative value if l1 < l2 
//------------------------------------------------------------ 
int lineCmp(const void *l1, const void *l2);

//------------------------------------------------------------ 
//! Compares two given wide char strings alphabetically in reverse order, starting from the end of the strings
//!
//! @param[in]  s1  First string to compare
//! @param[in]  s2  Second string to compare
//!
//! @return     Positive value if s1 > s2, 0 if s1 == s2, negative value if s1 < s2 
//------------------------------------------------------------ 
int rwstrcmp(const wchar_t *s1, const wchar_t *s2, const size_t l1, const size_t l2);

//------------------------------------------------------------ 
//! Compares two line structs based on alphabetical order of stored text, the comparison is performed in reverse, starting from the end of the string
//!
//! @param[in]  l1  First line to compare 
//! @param[in]  l2  Second line to compare 
//!
//! @return     Positive value if l1 > l2, 0 if l1 == l2, negative value if l1 < l2 
//------------------------------------------------------------ 
int rLineCmp(const void *l1, const void *l2);

//------------------------------------------------------------ 
//! Compares the values of two line pointers
//!
//! @param[in]  l1  First line pointer to compare
//! @param[in]  l2  Second line pointer to compare
//!
//! @return     Positive value if l1 > l2, 0 if l1 == l2, negative value if l1 < l2 
//------------------------------------------------------------ 
int linePtrNumCmp(const void *l1, const void *l2);

#endif
