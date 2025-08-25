#include "opScript.h"
#include <stdio.h>

int main() {
    const char *test_script = 
        "begin FILE module_list -\n"
        "    begin ENTRY booter -\n"
        "        TYPE [volatileModule]\n"
        "        NAME 'booter'\n"
        "        DESC 'opOS boot and init, do NOT remove.'\n"
        "        LANG 'c'\n"
        "        LOCATION 'sysmodules/booter'\n"
        "        PERMISSIONS '0' + '99'\n"
        "        VERSION '0.0.1'\n"
        "    - end ENTRY booter\n"
        "- end FILE module_list\n";

    module_list_t modules;
    module_list_init(&modules);

    printf("Parsing test script...\n");
    if (parse_opscript(test_script, &modules)) {
        printf("Successfully parsed %zu modules\n", modules.count);
        
        for (size_t i = 0; i < modules.count; i++) {
            const module_entry_t *mod = &modules.entries[i];
            printf("\nModule %zu:\n", i + 1);
            printf("  Name: %s\n", mod->name);
            printf("  Type: %s\n", 
                  mod->type == MODULE_TYPE_VOLATILE ? "volatile" : 
                  mod->type == MODULE_TYPE_NORMAL ? "normal" : "unknown");
            printf("  Description: %s\n", mod->description);
            printf("  Language: %s\n", mod->language);
            printf("  Location: %s\n", mod->location);
            printf("  Permissions: %s\n", mod->permissions);
            printf("  Version: %s\n", mod->version);
        }
    } else {
        printf("Failed to parse script\n");
    }

    module_list_free(&modules);
    return 0;
}
