#include "../include/module_system.h"
#include <string.h>

static module_t* modules[MAX_MODULES];
static int module_count = 0;

void module_system_init(void) {
    println("starting this clusterfuck of a module system...");
}

int register_module(module_t* module) {
    if (module_count >= MAX_MODULES) {
        println("wtf too many modules, ur getting greedy");
        return -1;
    }

    modules[module_count++] = module;
    print("found module: ");
    println(module->name);
    
    if (module->is_vital) {
        print("THIS SHIT IS VITAL BTW: ");
        println(module->name);
    }
    
    return 0;
}

int load_vital_modules(void) {
    println("loading vital shit (good luck lmao)");
    int loaded = 0;
    
    for (int i = 0; i < module_count; i++) {
        if (modules[i]->is_vital) {
            print("booting vital module: ");
            println(modules[i]->name);
            if (modules[i]->init() != 0) {
                print("FUCK MODULE FAILED: ");
                println(modules[i]->name);
                return -1;
            }
            loaded++;
        }
    }
    
    if (loaded == 0) {
        println("NO VITAL MODULES?? wtf are you doing");
        return -1;
    }
    
    return 0;
}
