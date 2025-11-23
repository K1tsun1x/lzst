#pragma once
#ifndef __STRING_H
#define __STRING_H

#include "typedefs.h"

void* __cdecl memcpy(void* dest, const void* src, size_t count);
int __cdecl memcmp(const void* a, const void* b, size_t count);

size_t __cdecl strlen(const char* s);

#endif