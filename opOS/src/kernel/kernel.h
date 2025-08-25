#ifndef KERNEL_H
#define KERNEL_H


#include <stdint.h>




// Kernel entry point
void kernel_main(void);



// Early initialization
void early_init(void);


// Main kernel initialization
void kernel_init(void);

// Panic handler
void panic(const char* message);

#endif // KERNEL_H
