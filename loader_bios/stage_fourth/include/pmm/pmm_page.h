#pragma once
#ifndef __PMM_PAGE_H
#define __PMM_PAGE_H

#include "pmm_page_flag.h"

#pragma pack(push, 1)
typedef struct _pmm_page_t {
	uint32_t			flags;				// PMM_PAGE_FLAG_* | ...

	/*
		Number of pages that were allocated
		in one allocation for use
		(so that they can be easily freed)
	*/
	uint32_t			chain_length;
} pmm_page_t;
#pragma pack(pop)

#endif