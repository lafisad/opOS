// Hardware detection and paranoid warnings
#ifndef HARDWARE_H
#define HARDWARE_H

// CPU info structure
struct cpu_info {
    char vendor[13];
    unsigned int features;
    unsigned char has_management_engine;
};

// RAM info
struct ram_info {
    unsigned long total_kb;
    unsigned char potentially_compromised;
};

void scan_hardware(void);


void check_cpu_security(void);


void scan_memory_threats(void);

void print_security_warning(void);

#endif
