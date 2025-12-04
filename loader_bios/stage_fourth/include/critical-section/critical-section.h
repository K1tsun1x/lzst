#pragma once
#ifndef __CRITICAL_SECTION_H
#define __CRITICAL_SECTION_H

#include <asm.h>

#define ENTER_CRITICAL_SECTION()					__critical_section_enter()
#define EXIT_CRITICAL_SECTION()						__critical_section_exit()

void __critical_section_enter(void);
void __critical_section_exit(void);

#endif