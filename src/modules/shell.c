// opOS Shell Module - Minimal Command Interpreter
#include "../../include/shell.h"
#include "../../include/module_system.h"

// Simple command shell implementation
void shell_init() {
    print("[opOS] wtf ur in the shell now\n");
}

void shell_run() {
    print("[opOS] type stuff if u dare\n");
    char cmd[64];
    int pos = 0;

    while (1) {
        print("opOS> ");
        pos = 0;
        
        // Read command char by char
        while (pos < 63) {
            char c = io_read_char();
            if (c == '\r') {
                io_write_char('\r');
                io_write_char('\n');
                cmd[pos] = 0;
                break;
            }
            else if (c == '\b' && pos > 0) {
                pos--;
                io_write_char('\b');
                io_write_char(' ');
                io_write_char('\b');
            }
            else if (c >= ' ' && c <= '~') {
                cmd[pos++] = c;
                io_write_char(c);
            }
        }

        // Process command
        if (strcmp(cmd, "scan") == 0) {
            shell_scan_modules();
        }
        else if (strcmp(cmd, "exit") == 0) {
            break;
        }
        else {
            print("wtf is this command: ");
            println(cmd);
        }
    }
}

void shell_scan_modules() {
    print("vital modules (if any of these are missing ur fucked):\n");
    print("- security: paranoid mode handler\n");
    print("- hwscan: tells u how compromised u are\n");
    print("- shell: ur using it rn dumbass\n");
}
