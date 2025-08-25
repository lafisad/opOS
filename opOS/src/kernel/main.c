#include "kernel.h"

void kernel_main(unsigned long magic, unsigned long addr) {
    // Initialize terminal
    terminal_initialize();
    
    // Check if the bootloader provided a valid multiboot structure
    if (magic != 0x36d76289) {
        terminal_writestring("magicnumber invalid");
        return;
    }

    // Print welcome message
    terminal_writestring("opOS booted\n");
    terminal_writestring("you have the following modules loaded:\n");
    
    // Hang the system
    for (;;) {
        asm volatile ("hlt");
    }
}
