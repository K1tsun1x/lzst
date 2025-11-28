#pragma once
#ifndef __DYNARR_H
#define __DYNARR_H

#include <pmm/pmm.h>
#include <align.h>

#define DYNARR_START_CAPACITY				64

typedef struct _dynarr_t {
	size_t		elem_size;
	size_t		num_elems;
	size_t		capacity;
} dynarr_t;

void* dynarr_alloc(size_t size);
void* dynarr_calloc(size_t size, size_t count);
void* dynarr_realloc(void* dynarr_old, size_t size);
void dynarr_free(void* dynarr);

void* dynarr_create(size_t elem_size, size_t num_elems);
void* dynarr_append(void* dynarr_mem, const void* elem);

#endif