ENTRY(_start)

/* Define the module information section */
SECTIONS {
    . = 0x100000;
    _kernel_start = .;

    /* Multiboot header must be at the start */
    .multiboot BLOCK(4K) : ALIGN(4K) {
        *(.multiboot_header)
    }

    /* Executable code */
    .text BLOCK(4K) : ALIGN(4K) {
        *(.text)
        *(.text.*)
    }

    /* Read-only data */
    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
        *(.rodata.*)
    }

    /* Module information */
    .modinfo BLOCK(4K) : ALIGN(4K) {
        __start_modinfo = .;
        *(.modinfo*)
        __stop_modinfo = .;
    }

    /* Module names */
    .modname BLOCK(4K) : ALIGN(4K) {
        *(.modname*)
    }

    /* Module versions */
    .modversion BLOCK(4K) : ALIGN(4K) {
        *(.modversion*)
    }

    /* Module descriptions */
    .moddesc BLOCK(4K) : ALIGN(4K) {
        *(.moddesc*)
    }

    /* Module authors */
    .modauthor BLOCK(4K) : ALIGN(4K) {
        *(.modauthor*)
    }

    /* Initialization functions */
    .init_array BLOCK(4K) : ALIGN(4K) {
        __init_array_start = .;
        KEEP(*(.init_array*))
        __init_array_end = .;
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
        *(.data.*)
    }

    /* Uninitialized data */
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }

    /* End of kernel */
    _kernel_end = .;
    _kernel_size = _kernel_end - _kernel_start;

    /* Discard sections we don't need */
    /DISCARD/ : {
        *(.comment)
        *(.note*)
        *(.eh_frame*)
    }
}
