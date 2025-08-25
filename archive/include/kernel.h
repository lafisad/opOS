#ifndef KERNEL_H
#define KERNEL_H

#include <stdbool.h>

void kernel_init();

// Assembly IO functions
extern void io_write_char(char c);
extern char io_read_char(void);

// Kernel print functions
void print(const char* str);
void println(const char* str);
void shell_prompt(void);

// Assembly IDT loader
extern void idt_init(void);
extern void idt_load(void);
extern void serial_init(void);

void kernel_set_read_only(bool enable);

int kernel_write(const char *resource);

void kernel_run();

#endif // KERNEL_H
