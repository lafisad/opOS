#include "opos/kernel.h"
#include "opos/console.h"
#include "opos/module.h"

// External symbols for the module sections
extern const opos_module_t* __start_modinfo;
extern const opos_module_t* __stop_modinfo;

// Forward declarations
static void init_modules(void);

// Kernel entry point
void kernel_main(unsigned long magic, unsigned long addr) {
    // Initialize console first
    console_init();
    
    // Check if the bootloader provided a valid multiboot structure
    if (magic != 0x36d76289) {
        console_printf("Error: Invalid multiboot magic number: 0x%X\n", magic);
        panic("Invalid multiboot magic");
    }

    // Print welcome message
    console_printf("=== opOS v%d.%d.%d ===\n", 
                  OPOS_VERSION_MAJOR, 
                  OPOS_VERSION_MINOR, 
                  OPOS_VERSION_PATCH);
    
    console_printf("Kernel starting...\n");
    
    // Early kernel initialization
    early_init();
    
    // Initialize modules
    init_modules();
    
    // Main kernel initialization
    kernel_init();
    
    console_printf("Kernel initialization complete.\n");
    console_printf("System ready.\n");
    
    // Main kernel loop - just halt and wait for interrupts
    for (;;) {
        asm volatile ("hlt");
    }
}

/**
 * @brief Initialize all registered modules
 */
static void init_modules(void) {
    console_printf("Initializing modules...\n");
    
    // Calculate number of modules
    size_t module_count = (size_t)(&__stop_modinfo - &__start_modinfo);
    console_printf("Found %d modules\n", (int)module_count);
    
    // Initialize each module
    const opos_module_t** mod_ptr = &__start_modinfo;
    while (mod_ptr < &__stop_modinfo) {
        const opos_module_t* mod = *mod_ptr;
        
        if (mod && mod->name && mod->init) {
            console_printf("  Initializing: %s", mod->name);
            if (mod->version) {
                console_printf(" v%s", mod->version);
            }
            console_printf("\n");
            
            int ret = mod->init();
            if (ret != 0) {
                console_printf("  ERROR: Module %s failed to initialize (code: %d)\n", 
                              mod->name, ret);
                if (mod->flags & MODULE_VOLATILE) {
                    panic("Critical module failed to initialize");
                }
            }
        }
        mod_ptr++;
    }
    
    console_printf("Module initialization complete.\n");
}

// Kernel panic function
__attribute__((noreturn)) void panic(const char* message) {
    console_printf("\n*** KERNEL PANIC ***\n");
    console_printf("Reason: %s\n", message);
    console_printf("System halted.\n");
    
    // Disable interrupts and halt forever
    for (;;) {
        asm volatile ("cli; hlt");
    }
}

// Early initialization (called before module init)
void early_init(void) {
    // Early kernel initialization code goes here
    // This runs before modules are initialized
}

// Main kernel initialization (called after module init)
void kernel_init(void) {
    // Main kernel initialization code goes here  
    // This runs after modules are initialized
}