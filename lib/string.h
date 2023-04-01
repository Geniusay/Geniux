#ifndef _LIB_STRING_H
#define _LIB_STRING_H
#include "stdint.h"
void memset(void *dst_, uint8_t value, uint32_t size);
void memcpy(void *dst_, const void *src_, uint32_t size);
int memcmp(const void* a_, const void* b_, uint32_t size);
char* strcpy(char* dst_, const char* src_);
uint32_t strlen(const char* str_);
int8_t strcmp(const char* a, const char* b);
char* strch(const char* str, const uint8_t ch);
char* strrch(const char* str, const uint8_t ch);
char* strcat(char* dst_, const char* src_);
char* newstrcat(char* dst_, const char* src_);
uint32_t strchrs(const char* str, uint8_t ch);
#endif