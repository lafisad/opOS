/**
 * @file module.h
 * @brief opOS Module System
 * @license MIT
 */

#ifndef _OPOS_MODULE_H_
#define _OPOS_MODULE_H_

#include <stdint.h>

// Module flags
#define MODULE_VOLATILE    (1 << 0)  // Module cannot be unloaded

// Module initialization structure
typedef struct opos_module {
    const char* name;           // Module name
    int (*init)(void);          // Initialization function
    void (*exit)(void);         // Cleanup function
    uint32_t flags;             // Module flags
    const char* version;        // Module version
} opos_module_t;

// Module registration macro
#define OPOS_MODULE_REGISTER(mod) \
    __attribute__((section(".modinfo"), used)) \
    static const opos_module_t* _module_##mod = &mod;

// Module name macro
#define MODULE_NAME(name) static const char* _module_name __attribute__((section(".modname"))) = name;

// Module version macro
#define MODULE_VERSION(ver) static const char* _module_version __attribute__((section(".modversion"))) = ver;

// Module description macro
#define MODULE_DESCRIPTION(desc) static const char* _module_desc __attribute__((section(".moddesc"))) = desc;

// Module author macro
#define MODULE_AUTHOR(author) static const char* _module_author __attribute__((section(".modauthor"))) = author;

// Module initialization function
int module_init(void);

// Module cleanup function
void module_exit(void);

#endif /* _OPOS_MODULE_H_ */
