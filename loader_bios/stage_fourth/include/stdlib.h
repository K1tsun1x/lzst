#pragma once
#ifndef __STDLIB_H
#define __STDLIB_H

#include <typedefs.h>

char* __cdecl ultoa(unsigned long value, char* str, int radix);
char* __cdecl ltoa(long value, char* str, int radix);

#endif