#ifndef STRING_H
#define STRING_H 

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "terminal.h"

size_t strlen(const char* str);

void* memcpy(void* dest, const void *src, size_t size);
void* memset(void* dest, const int value, size_t size);
void * memchr ( const void * ptr, int value, size_t num );
char* strcpy(char* dest, const char *source);

int strcmp(const char* first, const char* second);
int strcmpwc(const unsigned char* first, const char* second);

char* hexdump(char *dest, const void* data, size_t size);
char* itoa(char *dest, long long int number);
int atoi(const char *src);

int printf(char *format, ...);

#endif