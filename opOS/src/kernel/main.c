#include "opos/kernel.h"
#include "opos/console.h"
#include "opos/module.h"

// External symbol for the start of the module section
extern const opos_module_t __start_modinfo;
extern const opos_module_t __stop_modinfo;

// Kernel entry point
void kernel_main(unsigned long magic, unsigned long addr) {
    // Initialize console
    console_init();
    
    // Check if the bootloader provided a valid multiboot structure
    if (magic != 0x36d76289) {
        console_printf("Error: Invalid multiboot magic number: 0x%x\n", magic);
        return;
    }

    // Print welcome message
    console_printf("opOS v%d.%d.%d\n", 
                  OPOS_VERSION_MAJOR, 
                  OPOS_VERSION_MINOR, 
                  OPOS_VERSION_PATCH);
    
    console_printf("Initializing kernel...\n");
    
    // Initialize modules
    const opos_module_t* mod = &__start_modinfo;
    while (mod < &__stop_modinfo) {
        if (mod->name && mod->init) {
            console_printf("Initializing module: %s\n", mod->name);
            int ret = mod->init();
            if (ret != 0) {
                console_printf("Failed to initialize module %s (error %d)\n", mod->name, ret);
            }
        }
        mod++;
    }
    
    console_printf("Kernel initialization complete.\n");
    
    // Main kernel loop
    for (;;) {
        asm volatile ("hlt");
    }
}

// Kernel panic function
__attribute__((noreturn)) void panic(const char* message) {
    console_printf("KERNEL PANIC: %s\n", message);
    for (;;) {
        asm volatile ("cli\nhlt");
    }
}

// Early initialization (called before global constructors)
__attribute__((section(".init"))) void early_init(void) {
    // Early initialization code goes here
}

// Main initialization (called after global constructors)
void kernel_init(void) {
    // Main kernel initialization code goes here
}
