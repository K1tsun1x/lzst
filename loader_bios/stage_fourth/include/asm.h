#pragma once
#ifndef __ASM_H
#define __ASM_H

#include "typedefs.h"

#if defined(__x86_64__)
typedef uint64_t					irq_flags_t;
#elif defined(__i386__)
typedef uint32_t					irq_flags_t;
#endif

static inline uint8_t inb(uint16_t port) {
	uint8_t res;
	__asm__ volatile("inb %1, %0":"=a"(res):"d"(port):"memory");
	return res;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t res;
	__asm__ volatile("inw %1, %0":"=a"(res):"d"(port):"memory");
	return res;
}

static inline uint32_t inl(uint16_t port) {
	uint32_t res;
	__asm__ volatile("inl %1, %0":"=a"(res):"d"(port):"memory");
	return res;
}

static inline void outb(uint16_t port, uint8_t value) {
	__asm__ volatile("outb %0, %1"::"a"(value), "d"(port):"memory");
}

static inline void outw(uint16_t port, uint16_t value) {
	__asm__ volatile("outw %0, %1"::"a"(value), "d"(port):"memory");
}

static inline void outl(uint16_t port, uint32_t value) {
	__asm__ volatile("outl %0, %1"::"a"(value), "d"(port):"memory");
}

static inline uint32_t read_flags(void) {
	uint32_t res;
	__asm__ volatile("pushf; popl %0":"=r"(res));
	return res;
}

static inline void io_wait(void) {
	outb(0x80, 0);
}

static inline void cpu_relax(void) {
	__asm__ volatile("pause":::"memory");
}

static inline irq_flags_t irq_disable(void) {
	irq_flags_t flags;
#if defined(__x86_64__)
	__asm__ volatile(
		"pushfq\n\t"
		"cli\n\t"
		"popq %0"
		:"=r"(flags)
		::"memory"
	);
#elif defined(__i386__)
	__asm__ volatile(
		"pushfl\n\t"
		"cli\n\t"
		"popl %0"
		:"=r"(flags)
		::"memory"
	);
#endif
    return flags;
}

static inline void irq_restore(irq_flags_t flags) {
#if defined(__x86_64__)
	__asm__ volatile(
		"pushq %0\n\t"
		"popfq"
		::"r"(flags)
		:"memory"
	);
#elif defined(__i386__)
	__asm__ volatile(
		"pushl %0\n\t"
		"popfl"
		::"r"(flags)
		:"memory"
	);
#endif
}

static inline void cli(void) {
	__asm__ volatile("cli");
}

static inline void sti(void) {
	__asm__ volatile("sti");
}

static inline void hlt(void) {
	__asm__ volatile("hlt");
}

static inline uint32_t read_cr3(void) {
	uint32_t res;
	__asm__ volatile("mov %%cr3, %0":"=r"(res));
	return res;
}

static inline void write_cr3(uint32_t cr3) {
	__asm__ volatile("mov %0, %%cr3"::"r"(cr3));
}

static inline void memory_barrier(void) {
	__asm__ volatile("":::"memory");
}

static inline void lfence(void) {
	__asm__ volatile("lfence");
}

static inline void mfence(void) {
	__asm__ volatile("mfence");
}

static inline void xgetbv(uint32_t index, uint32_t* eax, uint32_t* edx) {
	uint32_t ceax;
	uint32_t cedx;
	__asm__ volatile("xgetbv":"=a"(ceax), "=d"(cedx):"c"(index));

	if (eax) *eax = ceax;
	if (edx) *edx = cedx;
}

static inline void xsetbv(uint32_t index, uint32_t eax, uint32_t edx) {
	__asm__ volatile("xsetbv"::"a"(eax), "c"(index), "d"(edx));
}

static inline void xsave(uint8_t* buffer) {
	if (!buffer) return;

	uint32_t eax, edx;
	__asm__ volatile("xgetbv":"=a"(eax), "=d"(edx):"c"(0));
	__asm__ volatile("xsave %[buf]"::[buf] "m"(*buffer), "a"(eax), "d"(edx):"memory");
}

static inline void xrstor(uint8_t* buffer) {
	if (!buffer) return;

	uint32_t eax, edx;
	__asm__ volatile("xgetbv":"=a"(eax), "=d"(edx):"c"(0));
	__asm__ volatile("xrstor %[buf]"::[buf] "m"(*buffer), "a"(eax), "d"(edx):"memory");
}

static inline void fxsave(uint8_t* buffer) {
	if (!buffer) return;

	__asm__ volatile("fxsave %0": "=m"(*buffer)::"memory");
}

static inline void fxrstor(uint8_t* buffer) {
	if (!buffer) return;

	__asm__ volatile("fxrstor %0"::"m"(*buffer):"memory");
}

static inline void invlpg(uintptr_t virt) {
	__asm__ volatile("invlpg (%0)"::"r"(virt):"memory");
}

static inline uint64_t rdmsr(uint32_t index) {
	uint32_t low;
	uint32_t high;
    __asm__ volatile( "rdmsr":"=a"(low), "=d"(high):"c"(index));
	return ((uint64_t)high << 32) | low;
}

static inline void wrmsr(uint32_t index, uint64_t value) {
	uint32_t low = (uint32_t)(value & 0xffffffff);
    uint32_t high = (uint32_t)(value >> 32);
    __asm__ volatile("wrmsr"::"c"(index), "a"(low), "d"(high));
}

/**
 * Halt the CPU forever
 */
static inline void panic_halt(void) {
	for (;;) __asm__ volatile("jmp .;cli;hlt");
}

#endif