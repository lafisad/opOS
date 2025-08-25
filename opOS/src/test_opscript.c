/**
 * @file opscript_loader.c
 * @brief opScript module loader for kernel integration
 * @license MIT
 */

#include "opScript.h"
#include "opos/console.h"
#include <string.h>

// Test opScript configuration
static const char* test_config = 
    "begin FILE module_list -\n"
    "    begin ENTRY booter -\n"
    "        TYPE [volatileModule]\n"
    "        NAME 'booter'\n"
    "        DESC 'opOS boot and init, do NOT remove.'\n"
    "        LANG 'c'\n"
    "        LOCATION 'sysmodules/booter'\n"
    "        PERMISSIONS 'OP'\n"
    "        VERSION '0.0.1'\n"
    "    - end ENTRY booter\n"
    "- end FILE module_list\n";

/**
 * @brief Test the opScript parser functionality
 * @return 0 on success, -1 on failure
 */
int test_opscript_parser(void) {
    console_printf("Testing opScript parser...\n");
    
    module_list_t modules;
    module_list_init(&modules);
    
    if (!parse_opscript(test_config, &modules)) {
        console_printf("ERROR: Failed to parse opScript configuration\n");
        module_list_free(&modules);
        return -1;
    }
    
    console_printf("Successfully parsed %d modules:\n", (int)modules.count);
    
    for (size_t i = 0; i < modules.count; i++) {
        const module_entry_t *mod = &modules.entries[i];
        console_printf("  Module: %s\n", mod->name);
        console_printf("    Type: %s\n", 
                      mod->type == MODULE_TYPE_VOLATILE ? "volatile" : 
                      mod->type == MODULE_TYPE_NORMAL ? "normal" : "unknown");
        console_printf("    Description: %s\n", mod->description);
        console_printf("    Location: %s\n", mod->location);
        console_printf("    Permissions: %s\n", mod->permissions);
        console_printf("    Version: %s\n", mod->version);
    }
    
    module_list_free(&modules);
    console_printf("opScript parser test completed successfully\n");
    return 0;
}

/**
 * @brief Load modules from opScript configuration
 * This is a placeholder for future dynamic module loading
 */
void load_modules_from_opscript(void) {
    console_printf("opScript module loading not yet implemented\n");
    console_printf("Modules are currently loaded statically at compile time\n");
    
    // For now, just test the parser
    test_opscript_parser();
}