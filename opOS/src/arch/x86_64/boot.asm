bits 64
section .multiboot_header
header_start:
    dd 0xe85250d6                ; Magic number (multiboot 2)
    dd 0                         ; Architecture 0 (protected mode i386)
    dd header_end - header_start ; Header length
    ; Checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; Insert optional multiboot tags here

    ; Required end tag
    dw 0    ; Type
    dw 0    ; Flags
    dd 8    ; Size
header_end:

section .text
global _start
extern kernel_main

_start:
    cli
    mov esp, stack_top
    push rbx    ; Multiboot info structure
    push rax    ; Multiboot magic number
    call kernel_main
    hlt

section .bss
align 16
stack_bottom:
    resb 16384  ; 16KB stack
stack_top:
