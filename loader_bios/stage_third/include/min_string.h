#pragma once
#ifndef __MIN_STRING_H
#define __MIN_STRING_H

#include "typedefs.h"

EXTERN_C void LOADERCALL memcpy16_32(uint32_t src, uint32_t dst, uint32_t count);

void* memcpy(void* d, const void* s, size_t n);
size_t strlen(const char* s);

#endif