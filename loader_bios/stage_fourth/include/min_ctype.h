#pragma once
#ifndef __MIN_CTYPE_H
#define __MIN_CTYPE_H

#include "typedefs.h"

static inline int tolower(int c) {
	if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
	return c;
}

static inline int toupper(int c) {
	if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
}

#endif