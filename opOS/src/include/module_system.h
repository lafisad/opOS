#ifndef MODULE_SYSTEM_H
#define MODULE_SYSTEM_H

#include <stdint.h>
#include <stddef.h>

typedef enum {
    MODULE_TYPE_KERNEL = 0,
    MODULE_TYPE_DRIVER = 1,
    MODULE_TYPE_FS = 2,
    MODULE_TYPE_OTHER = 3
} module_type_t;

typedef struct {
    const char* name;
    const char* description;
    module_type_t type;
    int (*init)(void);
    int (*fini)(void);
    uint32_t version;
} module_t;

// Module declaration macro
#define MODULE(name, desc, type, init_func, fini_func, ver) \
    __attribute__((section(".modinfo"))) \
    static const module_t _module_##name = { \
        #name, desc, type, init_func, fini_func, ver \
    }

// Module functions
void modules_init(void);
int register_module(const module_t* module);

#endif // MODULE_SYSTEM_H
