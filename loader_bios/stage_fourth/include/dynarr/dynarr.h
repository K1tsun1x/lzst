#pragma once
#ifndef __DYNARR_H
#define __DYNARR_H

#include <pmm/pmm.h>
#include <align.h>

#define DYNARR_START_CAPACITY				64

#define DYNARR_HEADER_FROM_MEM(mem)			(((dynarr_header_t*)(mem)) - 1)
#define DYNARR_MEM_FROM_HEADER(header)		((void*)(((dynarr_header_t*)(header)) + 1))

#pragma pack(push, 1)
typedef struct _dynarr_header_t {
	size_t		elem_size;
	size_t		num_elems;
	size_t		capacity;
} dynarr_header_t;
#pragma pack(pop)

void* dynarr_create(size_t elem_size, size_t num_elems);

/**
 * @warning Pointer to original array must be replaced with returned value!
 */
void* dynarr_append(void* dynarr_mem, const void* elem);

/**
 * @warning Pointer to original array must be replaced with returned value!
 */
void* dynarr_insert(void* dynarr_mem, size_t index, const void* mem);

/**
 * @warning Pointer to original array must be replaced with returned value!
 */
void* dynarr_reserve(void* dynarr_mem, size_t capacity);

/**
 * @warning Pointer to original array must be replaced with returned value!
 */
void* dynarr_remove(void* dynarr_mem, size_t index);
void dynarr_free(void* dynarr);

size_t dynarr_get_length(void* dynarr_mem);

#endif