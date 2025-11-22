#pragma once
#ifndef __MIN_STDLIB_H
#define __MIN_STDLIB_H

#include "typedefs.h"

#define NUM_DIGIT_CHARS							36

char* ltoa(long n, char* buffer, int radix);
char* ultoa(unsigned long n, char* buffer, int radix);

#endif