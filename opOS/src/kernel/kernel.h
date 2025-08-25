#ifndef KERNEL_H
#define KERNEL_H

#include "terminal.h"

// Kernel version information
#define KERNEL_NAME    "opOS"
#define KERNEL_VERSION "0.1.0"

// Function declarations
void kernel_main(unsigned long magic, unsigned long addr);

// Panic function for unrecoverable errors
void panic(const char* message);

#endif // KERNEL_H
