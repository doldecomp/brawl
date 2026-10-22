/**
 * Platform specific macros, defines, and behavior
 */

#pragma once

#ifdef __MWERKS__
#define ASM asm
#else
#define ASM
#endif