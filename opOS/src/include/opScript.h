#ifndef OPSCRIPT_H
#define OPSCRIPT_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_MODULE_NAME 64
#define MAX_MODULE_DESC 256
#define MAX_MODULE_PATH 256
#define MAX_PERMISSIONS 16

typedef enum {
    MODULE_TYPE_VOLATILE,
    MODULE_TYPE_NORMAL,
    MODULE_TYPE_UNKNOWN
} module_type_t;

typedef struct {
    char name[MAX_MODULE_NAME];
    char description[MAX_MODULE_DESC];
    char location[MAX_MODULE_PATH];
    char permissions[MAX_PERMISSIONS];
    char version[32];
    module_type_t type;
    char language[16];
} module_entry_t;

typedef struct {
    module_entry_t *entries;
    size_t count;
    size_t capacity;
} module_list_t;

// Initialize a module list
void module_list_init(module_list_t *list);

// Free resources used by a module list
void module_list_free(module_list_t *list);

// Parse opScript content into a module list
bool parse_opscript(const char *script, module_list_t *list);

// Get module type from string
module_type_t get_module_type(const char *type_str);

#endif // OPSCRIPT_H