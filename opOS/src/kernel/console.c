/**
 * @file console.c
 * @brief Simple console implementation
 * @license MIT
 */

#include "opos/console.h"
#include "opos/kernel.h"

// VGA text mode buffer
static volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static size_t terminal_row = 0;
static size_t terminal_column = 0;
static uint8_t terminal_color = 0x0F; // White on black

// Initialize console
void console_init(void) {
    // Clear the screen
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = (uint16_t)' ' | (uint16_t)terminal_color << 8;
        }
    }
}

// Scroll the terminal up by one line
static void terminal_scroll(void) {
    // Move all lines up by one
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index - VGA_WIDTH] = vga_buffer[index];
        }
    }
    
    // Clear the last line
    const size_t last_line = (VGA_HEIGHT - 1) * VGA_WIDTH;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[last_line + x] = (uint16_t)' ' | (uint16_t)terminal_color << 8;
    }
    
    terminal_row = VGA_HEIGHT - 1;
    terminal_column = 0;
}

// Put a character at the current position
void console_putc(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_scroll();
        }
        return;
    }
    
    const size_t index = terminal_row * VGA_WIDTH + terminal_column;
    vga_buffer[index] = (uint16_t)c | (uint16_t)terminal_color << 8;
    
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_scroll();
        }
    }
}

// Print a string to the console
void console_puts(const char* str) {
    while (*str) {
        console_putc(*str++);
    }
}

// Simple printf implementation
int console_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = console_vprintf(format, args);
    va_end(args);
    return ret;
}

// Formatted print with variable arguments
int console_vprintf(const char* format, va_list args) {
    int written = 0;
    
    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 's': {
                    const char* str = va_arg(args, const char*);
                    console_puts(str);
                    written++;
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    char buffer[32];
                    char* p = buffer + sizeof(buffer) - 1;
                    *p = '\0';
                    int is_neg = 0;
                    
                    if (num < 0) {
                        is_neg = 1;
                        num = -num;
                    }
                    
                    do {
                        *--p = '0' + (num % 10);
                        num /= 10;
                    } while (num > 0);
                    
                    if (is_neg) {
                        *--p = '-';
                    }
                    
                    console_puts(p);
                    written++;
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned int num = va_arg(args, unsigned int);
                    const char* hex_digits = "0123456789ABCDEF";
                    char buffer[9];
                    char* p = buffer + 8;
                    *p = '\0';
                    
                    for (int i = 0; i < 8; i++) {
                        *--p = hex_digits[num & 0xF];
                        num >>= 4;
                    }
                    
                    console_puts(p);
                    written++;
                    break;
                }
                case '%':
                    console_putc('%');
                    written++;
                    break;
                default:
                    console_putc('%');
                    console_putc(*format);
                    written += 2;
                    break;
            }
        } else {
            console_putc(*format);
            written++;
        }
        format++;
    }
    
    return written;
}
