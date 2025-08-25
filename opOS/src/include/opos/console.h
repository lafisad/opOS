/**
 * @file console.h
 * @brief Console I/O functions
 * @license MIT
 */

#ifndef _OPOS_CONSOLE_H_
#define _OPOS_CONSOLE_H_

#include <stddef.h>
#include <stdarg.h>

// Initialize the console
void console_init(void);

// Print a character to the console
void console_putc(char c);

// Print a string to the console
void console_puts(const char* str);

// Formatted print to console (simplified version)
int console_printf(const char* format, ...);

// Formatted print with variable arguments
int console_vprintf(const char* format, va_list args);

#endif /* _OPOS_CONSOLE_H_ */
