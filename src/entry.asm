// Kernel entry and basic IO functions
[BITS 16]
[ORG 0x0000]

extern kernel_main
global _start

section .text
_start:
    ; Set up segments
    MOV AX, CS
    MOV DS, AX
    MOV ES, AX
    MOV SS, AX
    MOV SP, 0xFFFF

    ; Clear screen
    MOV AH, 0x00
    MOV AL, 0x03
    INT 0x10

    ; Call C kernel
    CALL kernel_main

    ; Should never return
    JMP $

; Basic IO functions used by kernel
global io_write_char
io_write_char:
    PUSH BP
    MOV BP, SP
    MOV AL, [BP+4]    ; character to print
    MOV AH, 0x0E      ; BIOS teletype
    INT 0x10
    POP BP
    RET

global io_read_char
io_read_char:
    MOV AH, 0x00
    INT 0x16
    RET
