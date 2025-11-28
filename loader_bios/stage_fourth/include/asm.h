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
	__asm__ __volatile__("inb %1, %0":"=a"(res):"d"(port):"memory");
	return res;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t res;
	__asm__ __volatile__("inw %1, %0":"=a"(res):"d"(port):"memory");
	return res;
}

static inline uint32_t inl(uint16_t port) {
	uint32_t res;
	__asm__ __volatile__("inl %1, %0":"=a"(res):"d"(port):"memory");
	return res;
}

static inline void outb(uint16_t port, uint8_t value) {
	__asm__ __volatile__("outb %0, %1"::"a"(value), "d"(port):"memory");
}

static inline void outw(uint16_t port, uint16_t value) {
	__asm__ __volatile__("outw %0, %1"::"a"(value), "d"(port):"memory");
}

static inline void outl(uint16_t port, uint32_t value) {
	__asm__ __volatile__("outl %0, %1"::"a"(value), "d"(port):"memory");
}

static inline void io_wait(void) {
	outb(0x80, 0);
}

static inline void cpu_relax(void) {
	__asm__ __volatile__("pause":::"memory");
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
	__asm__ __volatile__("cli");
}

static inline void sti(void) {
	__asm__ __volatile__("sti");
}

static inline void xgetbv(uint32_t index, uint32_t* eax, uint32_t* edx) {
	uint32_t ceax;
	uint32_t cedx;
	__asm__ __volatile__("xgetbv":"=a"(ceax), "=d"(cedx):"c"(index));

	if (eax) *eax = ceax;
	if (edx) *edx = cedx;
}

static inline void xsetbv(uint32_t index, uint32_t eax, uint32_t edx) {
	__asm__ __volatile__("xsetbv"::"a"(eax), "c"(index), "d"(edx));
}

/**
 * Halt the CPU forever
 */
static inline void panic_halt(void) {
	for (;;) __asm__ __volatile__("jmp .;cli;hlt");
}

static inline void invlpg(uintptr_t virt) {
	__asm__ __volatile__("invlpg (%0)"::"r"(virt):"memory");
}

static inline uint64_t rdmsr(uint32_t index) {
	uint32_t low;
	uint32_t high;
    __asm__ __volatile__( "rdmsr":"=a"(low), "=d"(high):"c"(index));
	return ((uint64_t)high << 32) | low;
}

static inline void wrmsr(uint32_t index, uint64_t value) {
	uint32_t low = (uint32_t)(value & 0xffffffff);
    uint32_t high = (uint32_t)(value >> 32);
    __asm__ __volatile__("wrmsr"::"c"(index), "a"(low), "d"(high));
}

#endif