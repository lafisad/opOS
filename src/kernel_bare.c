// opOS Kernel - Modular and Paranoid AF
#include "../include/module_system.h"

#define MAX_CMD_LEN 256
#define MAX_PATH_LEN 128

// Read-only mode flag
int read_only = 0;
int read_write = 0;


// External assembly functions
extern void io_write_char(char c);
extern char io_read_char(void);

// External modules
extern module_t security_module;
extern module_t hwscan_module;
extern module_t shell_module;

// Command buffer
static char cmd_buffer[MAX_CMD_LEN];
static int cmd_pos = 0;

void print(const char* str) {
    while(*str) io_write_char(*str++);
}

void println(const char* str) {
    print(str);
    io_write_char('\r');
    io_write_char('\n');
}

void shell_prompt(void) {
    print("\ropOS_paranoid> ");
}

void handle_command(void) {
    cmd_buffer[cmd_pos] = 0;
    
    if(cmd_pos == 0) {
        shell_prompt();
        return;
   }
    
    // Basic commands
    if(strcmp(cmd_buffer, "help") == 0) {
        println("[[HELP]]:");
        println("help    - this message");
        println("ro      - read-only");
        println("rw      - read-write");
        println("ls      - check files");
        println("cat     - print to stdout");
        println("scan    - re-scan hw (i dont know why you would do this btw, but i wanted to add it)");
        println("modules - check modules");
    }
    else if(strcmp(cmd_buffer, "ro") == 0) {
        read_only = 1;
        println("[[ro]]: READ-ONLY MODE ON");
    }
    else if(strcmp(cmd_buffer, "rw") == 0) {
        read_only = 0;
        println("[[rw]]: READ-WRITE MODE ON ");
    }
    else {
        print("[[CMDHELP]]: ");
        println(cmd_buffer);
    }
    
    cmd_pos = 0;
    shell_prompt();
}

void kernel_main(void) {
    println("opOS v00 - if you are clinically, terry davis style paranoid");
    
    // Initialize module system
    module_system_init();
    
    // Register vital modules
    register_module(&security_module);
    register_module(&hwscan_module);
    register_module(&shell_module);
    
    // Try to boot vital modules
    if (load_vital_modules() != 0) {
        println("NO VITAL MODULES FOUND");
        for(;;); // hang because we're useless
    }
    
    println("\nVITAL MODULES FOUND");
    println("type ''help'' for... help. are you dumb?");
    shell_prompt();
    
    while(1) {
        char c = io_read_char();
        
        if(c == '\r') {
            io_write_char('\r');
            io_write_char('\n');
            handle_command();
        }
        else if(c == '\b' && cmd_pos > 0) {
            cmd_pos--;
            io_write_char('\b');
            io_write_char(' ');
            io_write_char('\b');
        }
        else if(c >= ' ' && c <= '~' && cmd_pos < MAX_CMD_LEN - 1) {
            cmd_buffer[cmd_pos++] = c;
            io_write_char(c);
        }
    }
}
