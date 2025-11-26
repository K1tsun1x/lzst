#pragma once
#ifndef __SEGMENT_SELECTOR_H
#define __SEGMENT_SELECTOR_H

#include <typedefs.h>

/**
 * Bits 0..1 -	requested privilege level
 * Bit 2 -		table index (0 - GDT, 1 - LDT)
 * Bits 3..15 -	index
 */
typedef uint16_t			segment_selector_t;

#endif