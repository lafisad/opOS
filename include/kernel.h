#ifndef KERNEL_H
#define KERNEL_H

#include <stdbool.h>

void kernel_init();

void kernel_set_read_only(bool enable);

int kernel_write(const char *resource);

void kernel_run();

#endif // KERNEL_H
