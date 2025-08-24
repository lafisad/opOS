#include "../../include/module_system.h"

// Security module functions
int security_init(void);
int security_enable_ro(void);
int security_disable_ro(void);
int security_check_write(const char* path);

// Module definition
module_t security_module = {
    .name = "security",
    .init = security_init,
    .is_vital = 1
};

static int read_only = 1;

int security_init(void) {
    println("initializing paranoid security module");
    println("everything is readonly unless you say otherwise");
    return 0;
}

int security_enable_ro(void) {
    read_only = 1;
    println("ok cool now ur in full paranoid mode");
    return 0;
}

int security_disable_ro(void) {
    read_only = 0;
    println("holy shit ur actually gonna write?? dont blame me if the nsa finds u");
    return 0;
}

int security_check_write(const char* path) {
    if (read_only) {
        print("WRITE BLOCKED (paranoid mode): ");
        println(path);
        return -1;
    }
    return 0;
}
