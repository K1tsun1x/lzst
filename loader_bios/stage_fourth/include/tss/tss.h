#pragma once
#ifndef __TSS_H
#define __TSS_H

#include <typedefs.h>

#pragma pack(push, 1)
typedef struct _tss_t {
	uint32_t			link;	// offset: 0x00
	uint32_t			esp0;	// offset: 0x04
	uint32_t			ss0;	// offset: 0x08
	uint32_t			esp1;	// offset: 0x0c
	uint32_t			ss1;	// offset: 0x10
	uint32_t			esp2;	// offset: 0x14
	uint32_t			ss2;	// offset: 0x18
	uint32_t			cr3;	// offset: 0x1c
	uint32_t			eip;	// offset: 0x20
	uint32_t			eflags;	// offset: 0x24
	uint32_t			eax;	// offset: 0x28
	uint32_t			ecx;	// offset: 0x2c
	uint32_t			edx;	// offset: 0x30
	uint32_t			ebx;	// offset: 0x34
	uint32_t			esp;	// offset: 0x38
	uint32_t			ebp;	// offset: 0x3c
	uint32_t			esi;	// offset: 0x40
	uint32_t			edi;	// offset: 0x44
	uint32_t			es;		// offset: 0x48
	uint32_t			cs;		// offset: 0x4c
	uint32_t			ss;		// offset: 0x50
	uint32_t			ds;		// offset: 0x54
	uint32_t			fs;		// offset: 0x58
	uint32_t			gs;		// offset: 0x5c
	uint32_t			ldtr;	// offset: 0x60
	uint32_t			iopb;	// offset: 0x64
	// uint32_t			ssp;	// offset: 0x68 - NOT USED
} tss_t;
#pragma pack(pop)

int a = sizeof(tss_t);

#endif