#pragma once
#ifndef __PAGING_PTE_FLAG_H
#define __PAGING_PTE_FLAG_H

#include <typedefs.h>

/*
	If this bit is set, the page is in physical memory,
	otherwise an access attempt will cause a page fault
*/
#define PAGING_PTE_FLAG_PRESENT						1 << 0

/*
	If the bit is set, the page is read/write.
	Otherwise when it is not set, the page is read-only.
	The WP bit in CR0 determines if this is only applied to userland,
	always giving the kernel write access (the default)
	or both userland and the kernel (see Intel Manuals 3A 2-20).
	The R/W bit of the parent tables is also checked:
	if any are 0, the page is treated as read-only.
*/
#define PAGING_PTE_FLAG_READ_WRITE					1 << 1

/*
	If the bit is set, then the page may be accessed by all;
	if the bit is not set, however, only the supervisor can access it.
	For a page directory entry, the user bit controls access to all
	the pages referenced by the page directory entry.
	Therefore if you wish to make a page a user page,
	you must set the user bit in the relevant page directory entry
	as well as the page table entry.
*/
#define PAGING_PTE_FLAG_USER_SUPERVISOR				1 << 2

/*
	If the bit is set, write-through caching is enabled.
	If not, then write-back is enabled instead.
*/
#define PAGING_PTE_FLAG_PAGE_WRITE_THROUGH			1 << 3

/*
	If the bit is set, the page will not be cached.
	Otherwise, it will be.
*/
#define PAGING_PTE_FLAG_PAGE_CACHE_DISABLE			1 << 4
#define PAGING_PTE_FLAG_ACCESSED					1 << 5

/*
	'Dirty' is used to determine whether a page has been written to.
*/
#define PAGING_PTE_FLAG_DIRTY						1 << 6

/*
	If PAT is supported, then PAT along with PCD and PWT
	shall indicate the memory caching type.
	Otherwise, it is reserved and must be set to 0.
*/
#define PAGING_PTE_FLAG_PAGE_ATTRIBUTE_TABLE		1 << 7

/*
	tells the processor not to invalidate the TLB entry
	corresponding to the page upon a MOV to CR3 instruction.
	Bit 7 (PGE) in CR4 must be set to enable global pages.
*/
#define PAGING_PTE_FLAG_GLOBAL						1 << 8

// #define PAGING_PTE_FLAG_AVL0
// #define PAGING_PTE_FLAG_AVL1
// #define PAGING_PTE_FLAG_AVL2

#endif