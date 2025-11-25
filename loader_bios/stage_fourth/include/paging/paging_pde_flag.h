#pragma once
#ifndef __PAGING_PDE_FLAG_H
#define __PAGING_PDE_FLAG_H

#include <typedefs.h>

/*
	If this bit is set, the directory is in physical memory,
	otherwise an access attempt will cause a page fault
*/
#define PAGING_PDE_FLAG_PRESENT				1 << 0

/*
	If the bit is set, the directory is read/write.
	Otherwise when it is not set, the directory is read-only.
	The WP bit in CR0 determines if this is only applied to userland,
	always giving the kernel write access (the default)
	or both userland and the kernel (see Intel Manuals 3A 2-20).
	The R/W bit of the parent tables is also checked:
	if any are 0, the directory is treated as read-only.
*/
#define PAGING_PDE_FLAG_READ_WRITE			1 << 1

/*
	Controls access to all
	the pages referenced by the page directory entry.
	Therefore if you wish to make a page a user page,
	you must set the user bit in the relevant page directory entry
	as well as the page table entry.
*/
#define PAGING_PDE_FLAG_USER_SUPERVISOR		1 << 2

/*
	If the bit is set, write-through caching is enabled.
	If not, then write-back is enabled instead.
*/
#define PAGING_PDE_FLAG_PAGE_WRITE_THROUGH	1 << 3

/*
	If the bit is set, the derctory will not be cached.
	Otherwise, it will be.
*/
#define PAGING_PDE_FLAG_PAGE_CACHE_DISABLE	1 << 4


#define PAGING_PDE_FLAG_ACCESSED			1 << 5

// #define PAGING_PDE_FLAG_AVL0				1 << 6

/*
	If the bit is set, then the PDE maps to a page that is 4 MiB in size.
	Otherwise, it maps to a 4 KiB page table.
	Please note that 4-MiB pages require PSE to be enabled.
*/
#define PAGING_PDE_FLAG_PAGE_SIZE			1 << 7

// #define PAGING_PDE_FLAG_AVL1				1 << 8
// #define PAGING_PDE_FLAG_AVL2				1 << 9
// #define PAGING_PDE_FLAG_AVL3				1 << 10
// #define PAGING_PDE_FLAG_AVL4				1 << 11

#endif