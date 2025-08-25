/**
 * @file kernel.h
 * @brief opOS Kernel Main Header
 * @license MIT
 */

#ifndef _OPOS_KERNEL_H_
#define _OPOS_KERNEL_H_

#include <stdint.h>

// Kernel version information
#define OPOS_VERSION_MAJOR 0
#define OPOS_VERSION_MINOR 1
#define OPOS_VERSION_PATCH 0

// Kernel entry point
void kernel_main(void);

// Kernel panic function
__attribute__((noreturn)) void panic(const char* message);

// Early initialization
void early_init(void);

// Main initialization
void kernel_init(void);

#endif /* _OPOS_KERNEL_H_ */
