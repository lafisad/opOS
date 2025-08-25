// opOS Shell Module - Minimal Command Interpreter
#ifndef SHELL_H
#define SHELL_H

#include "module_system.h"

// Initialize shell
int shell_init();

// Run shell loop
int shell_run();

// The shell module instance
extern module_t shell_module;

// Scan for modules and output if found
void shell_scan_modules();

#endif // SHELL_H
