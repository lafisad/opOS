#include "module_system.h"
#include "terminal.h"

// External references to module sections
extern const module_t __start_modinfo;
extern const module_t __stop_modinfo;

static int module_count = 0;

void modules_init(void) {
    // Count modules
    const module_t* mod;
    for (mod = &__start_modinfo; mod < &__stop_modinfo; mod++) {
        module_count++;
    }
    
    terminal_writestring("found module ");
    terminal_writestring(module_count);
    terminal_writestring(" modules\n");
    
    // Initialize all modules
    for (mod = &__start_modinfo; mod < &__stop_modinfo; mod++) {
        terminal_writestring("module init running for: ");
        terminal_writestring(mod->name);
        terminal_putchar('\n');
        
        if (mod->init) {
            int ret = mod->init();
            if (ret != 0) {
                terminal_writestring("  failed to run module init: ");
                terminal_writestring(mod->name);
                terminal_putchar('\n');
            }
        }
    }
}

int register_module(const module_t* module) {
    // In our implementation, modules are registered at link time
    // This function is kept for compatibility
    return 0;
}
