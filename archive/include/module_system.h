#ifndef MODULE_SYSTEM_H
#define MODULE_SYSTEM_H

#define MAX_MODULES 16
#define MODULE_NAME_MAX 32

typedef struct {
    char name[MODULE_NAME_MAX];
    int (*init)(void);
    int (*run)(void);
    int (*cleanup)(void);
    int is_vital;
} module_t;

// Initialize module system
void module_system_init(void);

// Register a module
int register_module(module_t* module);

// Load vital modules
int load_vital_modules(void);

// Get module by name
module_t* get_module(const char* name);

#endif
